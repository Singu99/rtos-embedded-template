#pragma once

#include <cstdint>
#include <new>
#include <type_traits>
#include <utility>


/**
 * @brief      A factory class that creates and destroys objects of type T. It is intended to be used with Allocators that will be passed as T on the tamplate parameter.
 * An allocator class should have allocate and deallocate static methods. Have protected constructors and destructors. 
*/
class Factory {
public:
    template <typename T, typename... Args>
    static T* create(Args&&... args) {
        T* object = T::allocate();
        if (object == nullptr) {
            return nullptr;
        }
        new (object) T(std::forward<Args>(args)...);  // Placement new with variadic arguments
        return object;
    }

    template <typename T>
    static void destroy(T* object) {
        if (object != nullptr) {
            object->~T();  // Explicitly call the destructor
            T::deallocate(object);
        }
    }
private:
    Factory() = delete;
    ~Factory() = delete;
};
