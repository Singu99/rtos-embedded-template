#pragma once

#include <optional>

#include "io/resource.hpp"

// TODO: Add concepts for better error handling

/** 
 * Static:    Interface for retreiving devices.
 * Nonstatic: Base class for all devices.
 */
class device {
public:

    template<typename dev, typename id>
    static std::optional<dev*> claim_device(id dev_id, io::resource_id claimer) 
    {
        dev* device = device::get<dev>(dev_id);
        if (device->m_claimer == io::resource_id::FREE || device->m_claimer == claimer) {
            device->m_claimer = claimer;
            return device;
        } 
        return {};
    }
    
    template<typename dev>
    static bool release_device(dev* device, io::resource_id claimer) 
    {
        if (device->m_claimer == claimer) {
            device->m_claimer = io::resource_id::FREE;
            return true;
        }
        return false;
    }

protected:
    /* Ownership will belong to the device specific module. There should be provided the template speciallization of this getter */
    template<typename dev, typename id>
    static dev* get(id dev_id);

protected:
    device() : m_claimer(io::resource_id::FREE) {};
    ~device() = default;

private:
    io::resource_id m_claimer;                                                  // Keep track of who is using this device

};