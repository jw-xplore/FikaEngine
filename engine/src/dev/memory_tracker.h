#pragma once
#include <iostream>
#include "fika_dev.h"

namespace FikaMemoryTracker
{
#if MEMORY_DEBUG == 1
    int dynamicAlloc = 0;
    size_t dynamicAllocSize = 0;
    int totalAdds = 0;
    int totalDels = 0;
    size_t highestAdd = 0;
    size_t highestDel = 0;
#endif

    void report()
    {
#if MEMORY_DEBUG == 1
        std::cout << "Leaks: " << dynamicAlloc << ", Amout: " << dynamicAllocSize << "\n";
        std::cout << "Adds: " << totalAdds << ", Dels: " << totalDels << "\n";
        std::cout << "HA: " << highestAdd << ", HD: " << highestDel << "\n";
#else
        std::cout << "FikaMemoryTracker debug DEACTIVATED! \n";
#endif
    }
}

//-------------------------------------------------------
// New & delete override
//-------------------------------------------------------

#if MEMORY_DEBUG == 1
void* operator new(size_t size)
{
    if (void* p = std::malloc(size))
    {
        FikaMemoryTracker::dynamicAlloc++;
        FikaMemoryTracker::dynamicAllocSize += size;

        if (size > FikaMemoryTracker::highestAdd)
            FikaMemoryTracker::highestAdd = size;

        FikaMemoryTracker::totalAdds++;
        return p;
    }

    throw std::bad_alloc{};
}

void operator delete(void* p) noexcept
{
    FikaMemoryTracker::dynamicAlloc--;
    size_t size = sizeof(p);
    FikaMemoryTracker::dynamicAllocSize -= size;
    FikaMemoryTracker::totalDels++;

    free(p);
}

void operator delete(void* p, std::size_t size) noexcept
{
    FikaMemoryTracker::dynamicAlloc--;
    //size_t size = sizeof(p);
    FikaMemoryTracker::dynamicAllocSize -= size;
    FikaMemoryTracker::totalDels++;

    if (size > FikaMemoryTracker::highestDel)
        FikaMemoryTracker::highestDel = size;

    free(p);
}

void* operator new[](size_t size)
{
    if (void* p = std::malloc(size))
    {
        FikaMemoryTracker::dynamicAlloc++;
        FikaMemoryTracker::dynamicAllocSize += size;

        if (size > FikaMemoryTracker::highestAdd)
            FikaMemoryTracker::highestAdd = size;

        FikaMemoryTracker::totalAdds++;
        return p;
    }

    throw std::bad_alloc{};
}

void operator delete[](void* p) noexcept
{
    FikaMemoryTracker::dynamicAlloc--;
    size_t size = sizeof(p);
    FikaMemoryTracker::dynamicAllocSize -= size;
    FikaMemoryTracker::totalDels++;

    free(p);
}

void operator delete[](void* p, std::size_t size) noexcept
{
    FikaMemoryTracker::dynamicAlloc--;
    FikaMemoryTracker::dynamicAllocSize -= size;
    FikaMemoryTracker::totalDels++;

    if (size > FikaMemoryTracker::highestDel)
        FikaMemoryTracker::highestDel = size;

    free(p);
}
#endif