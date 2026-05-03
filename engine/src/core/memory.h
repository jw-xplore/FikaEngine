//-------------------------------------------------------------------------
// Memory pool allocator
//-------------------------------------------------------------------------

template <typename T>
class PoolAllocator
{
public:
	T* buffer;
	//size_t size;
	size_t elementSize;
	size_t elementsCount;

	size_t usedCount = 0;
	T** handles;

	PoolAllocator(size_t count)
	{
		usedCount = 0;
		elementsCount = count;
		elementSize = sizeof(T);

		//size = elementsCount * elementSize;
		buffer = new T[elementsCount];
		handles = new T * [elementsCount];

		for (size_t i = 0; i < elementsCount; i++)
		{
			T* element = buffer + i;
			handles[i] = element;
		}
	}

	T* Allocate()
	{
		if (usedCount >= elementsCount)
			return nullptr;

		T* pos = handles[usedCount];
		usedCount++;

		return pos;
	}

	void Remove(T* element)
	{
		// Find element
		int pos = -1;
		for (size_t i = 0; i < elementsCount; i++)
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
		usedCount--;

		if (pos < usedCount)
		{
			T* temp = handles[pos];
			handles[pos] = handles[usedCount];
			handles[usedCount] = temp;
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