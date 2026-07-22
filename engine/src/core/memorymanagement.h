//-------------------------------------------------------------------------
// Memory pool allocator
//-------------------------------------------------------------------------

template <typename T>
class PoolAllocator
{
private:
	T* buffer;

	size_t elementSize;
	size_t size;
	size_t used = 0;
	T** handles;

public:
	PoolAllocator(size_t count)
	{
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

	T* allocate()
	{
		if (used >= size)
			return nullptr;

		T* pos = handles[used];
		used++;

		return pos;
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
		return *handles[idx];
	}

	int getUsedAmount()
	{
		return used;
	}
};