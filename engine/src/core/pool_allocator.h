//-------------------------------------------------------------------------
// Memory pool allocator
//-------------------------------------------------------------------------
#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "dev/fika_dev.h"

namespace FikaEngine
{
	static const size_t POOL_DEFAULT_SIZE = 256;

	template <typename T>
	class PoolAllocator
	{
	private:
		const char* name;
		unsigned short depth = 0;
		T* buffer = nullptr;

		size_t elementSize = 0;
		size_t size = 0;
		size_t used = 0;
		T** handles = nullptr;
		std::unordered_map<T*, unsigned int> handlesMap;

		PoolAllocator<T>* nextPool = nullptr;

		/**
		 * @brief Recursively tries to allocate element in next free pool.
		 * @return Pointer to recently allocated element in any of free pools.
		 */
		T* allocateInNextPool()
		{
			if (!nextPool)
			{
				nextPool = new PoolAllocator<T>(name, size);
				nextPool->depth = depth + 1;
				unsigned int recommendation = (depth + 2) * size;
				std::cout << "Pool allocator overflow! Expanding pool '" << name << "'" << " by depth: " << nextPool->depth << ".";
				std::cout << "Consider expanding pool size from " << size << " to " << recommendation << " to improve performance.\n";
			}

			return nextPool->allocate();
		}

	public:
		PoolAllocator()
		{
			this->name = "Default";
			used = 0;
			size = 0;
		}

		PoolAllocator(const char* name, size_t count = POOL_DEFAULT_SIZE)
		{
			init(name, count);
		}

		~PoolAllocator()
		{
			delete[] buffer;
			delete[] handles;

			if (nextPool)
				delete nextPool;
		}

		/**
		 * @brief Print order of element ids inside the pool
		 */
		void reportOrder(std::string actionName)
		{
			// NOTE: Temporary ignore
			std::string strName(name);
			if (strName != "Mesh Components")
			{
				return;
			}

			std::cout << "(" << actionName << ") Pool order [" << name << "]: ";
			for (size_t i = 0; i < used; i++)
			{
				std::cout << handlesMap[handles[i]];
				if (i < used - 1)
					std::cout << ", ";
			}

			std::cout << "\n";
		}

		void init(const char* name, size_t count = POOL_DEFAULT_SIZE)
		{
			this->name = name;
			used = 0;
			size = count;
			elementSize = sizeof(T);

			buffer = new T[size];
			handles = new T * [size];
			handlesMap.reserve(size);

			for (size_t i = 0; i < size; i++)
			{
				T* element = buffer + i;
				handles[i] = element;
				handlesMap[element] = i;
			}
		}

		/**
		 * @return Pointer to recently allocated element.
		 */
		T* allocate()
		{
			// Pool undefined or defined empty!
			assert(size > 0);

			if (used >= size)
			{
				// Increase used amount on top level so allocator gives total element count
				if (depth == 0)
					used++;

				// Allocate in next pool (recursively if overlowed)
				return allocateInNextPool();
			}

			// Allocate new place in standard way
			T* pos = handles[used];
			used++;

			assert(pos != nullptr);

#if POOLALLOCATORS_DEBUG == 1
			reportOrder("Allocate");
#endif

			return pos;
		}

		void deallocate()
		{
			used = 0;
		}

		/**
		 * @brief Remove a specific element inside the pool.
		 * Removed element swaps place with last active element in the pool.
		 * @param element 
		 */
		void remove(T* element)
		{
			// Find element
			int pos = -1;
			for (size_t i = 0; i < size; i++)
			{
				if (handles[i] == element)
				{
					pos = i;
					break;
				}
			}

			assert(pos != -1);

			if (pos == -1)
				return;

			// Decrease used and switch element position
			assert (used > 0);
			used--;

			if (pos < used)
			{
				T* temp = handles[pos];			// Temp is selected 
				handles[pos] = handles[used];	// Selected move to end 
				handles[used] = temp;			// Selected replaced by last element

				// Switch order
				handlesMap[handles[pos]] = used;
				handlesMap[handles[used]] = pos;
			}

#if POOLALLOCATORS_DEBUG == 1
			reportOrder("Remove");
#endif
		}

		T& operator[](std::size_t idx)
		{
			if (idx >= size * (depth + 1))
			{
				return (*nextPool)[idx];
			}

			idx -= size * depth;

			// Standart search
			return *handles[idx];
		}

		unsigned int orderOfElement(T& element)
		{
			return handlesMap.at(&element);
		}

		/**
		 * @return How many elements in pool are actually allocated.
		 */
		int getUsedAmount()
		{
			return used;
		}

		size_t getSize()
		{
			return size;
		}
	};
} // namespace FikaEngine