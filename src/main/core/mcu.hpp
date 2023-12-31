#pragma once

#include "controllers/core_controller.hpp"
#include "controllers/rx_controller.hpp"
#include "controllers/dshot_controller.hpp"

namespace mcu {

    // Controller
    extern core_controller* core;
    extern rx_controller* rx;
    extern dshot_controller* dshot;

}

