//-------------------------------------------------------------------------
// Memory pool allocator
//-------------------------------------------------------------------------
#pragma once
#include <iostream>

template <typename T>
class PoolAllocator
{
private:
	const char* name;
	unsigned short depth = 0;
	T* buffer;

	size_t elementSize;
	size_t size;
	size_t used = 0;
	T** handles;

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

	PoolAllocator(const char* name, size_t count)
	{
		this->name = name;
		used = 0;
		size = count;
		elementSize = sizeof(T);

		buffer = new T[size];
		handles = new T * [size];

		for (size_t i = 0; i < size; i++)
		{
			T* element = buffer + i;
			handles[i] = element;
		}
	}

	/**
	 * @return Pointer to recently allocated element.
	 */
	T* allocate()
	{
		if (size == 0)
			assert("Pool was never defined!");

		if (used >= size)
		{
			if (depth == 0)
				used++;

			// Allocate in next pool (recursively if overlowed)
			return allocateInNextPool();
		}

		// Allocate new place in standard way
		T* pos = handles[used];
		used++;

		return pos;
	}

	void deallocate()
	{
		used = 0;
	}

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

		if (pos == -1)
			return;

		// Decrease used and switch element position
		used--;

		if (pos < used)
		{
			T* temp = handles[pos];
			handles[pos] = handles[used];
			handles[used] = temp;
		}
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

	/**
	 * @return How many elements in pool are actually allocated.
	 */
	int getUsedAmount()
	{
		return used;
	}

	int getSize()
	{
		return size;
	}
};