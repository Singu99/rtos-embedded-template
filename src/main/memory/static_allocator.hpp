#pragma once

#include <cstdint>

class Factory;

template <typename T, size_t MaxElements>
class StaticAllocator {
    friend class Factory;
private:
    static T* allocate() {
        if (count >= MaxElements) {
            return nullptr;  // Return nullptr if maximum capacity reached
        }

        // Find the first unused slot
        for (size_t i = 0; i < MaxElements; i++) {
            T* slot = GetSlot(i);
            if (!slot->used) {
                slot->used = true;
                count++;
                return slot;
            }
        }

        return nullptr;         // Should never happen
    }

    static void deallocate(T* object) {
        if (object != nullptr) {
            
            // Mark the slot as unused
            object->used = false;  

            // Decrement the count of allocated objects
            count--;
        }
    }

    static inline T* GetSlot(uint32_t index) {
        static std::aligned_storage<sizeof(T) * MaxElements, alignof(T)> buffer;
        return reinterpret_cast<T*>(&buffer) + index;
    }

protected:
    StaticAllocator() : used(false) {}
    ~StaticAllocator() = default;

private:
    bool used;                          // Member variable to keep track if the slot is used

private:
    static inline size_t count = 0;     // Keep track of the number of allocated objects
};