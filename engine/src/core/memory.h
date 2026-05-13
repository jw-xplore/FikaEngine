//-------------------------------------------------------------------------
// Memory pool allocator
//-------------------------------------------------------------------------

template <typename T>
class PoolAllocator
{
public:
	T* buffer;
	
	size_t elementSize;
	size_t reserved;
	size_t used = 0;
	T** handles;

	PoolAllocator(size_t count)
	{
		used = 0;
		reserved = count;
		elementSize = sizeof(T);

		//size = reserved * elementSize;
		buffer = new T[reserved];
		handles = new T * [reserved];

		for (size_t i = 0; i < reserved; i++)
		{
			T* element = buffer + i;
			handles[i] = element;
		}
	}

	T* allocate()
	{
		if (used >= reserved)
			return nullptr;

		T* pos = handles[used];
		used++;

		return pos;
	}

	void remove(T* element)
	{
		// Find element
		int pos = -1;
		for (size_t i = 0; i < reserved; i++)
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

	const T& operator[](std::size_t idx) const
	{
		return handles[idx];
	}

	T& at(size_t idx)
	{
		return *handles[idx];
	}
};