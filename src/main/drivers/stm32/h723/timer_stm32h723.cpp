#include "drivers/stm32/common/stm32_timer_impl.hpp"

#include <etl/unordered_map.h>

#include "common/utils.h"

#include "drivers/platform.hpp"
#include "drivers/common/hardware.hpp"
#include "drivers/rcc.h"

static constexpr size_t TIM_COUNT = static_cast<uint32_t>(pal::timer::id::COUNT);
static const etl::unordered_map<pal::timer::id, pal::stm32::timer_hardware_t, TIM_COUNT> timer_hardware = {
    { pal::timer::id::t1,  { .reg = TIM1,  .rcc = RCC_APB2(TIM1),   .isr = TIM1_CC_IRQn} },
    { pal::timer::id::t2,  { .reg = TIM2,  .rcc = RCC_APB1L(TIM2),  .isr = TIM2_IRQn} },
    { pal::timer::id::t3,  { .reg = TIM3,  .rcc = RCC_APB1L(TIM3),  .isr = TIM3_IRQn} },
    { pal::timer::id::t4,  { .reg = TIM4,  .rcc = RCC_APB1L(TIM4),  .isr = TIM4_IRQn} },
    { pal::timer::id::t5,  { .reg = TIM5,  .rcc = RCC_APB1L(TIM5),  .isr = TIM5_IRQn} },
    { pal::timer::id::t6,  { .reg = TIM6,  .rcc = RCC_APB1L(TIM6),  .isr = TIM6_DAC_IRQn} },
    { pal::timer::id::t7,  { .reg = TIM7,  .rcc = RCC_APB1L(TIM7),  .isr = TIM7_IRQn} },
    { pal::timer::id::t8,  { .reg = TIM8,  .rcc = RCC_APB2(TIM8),   .isr = TIM8_CC_IRQn} },
    { pal::timer::id::t12, { .reg = TIM12, .rcc = RCC_APB1L(TIM12), .isr = TIM8_BRK_TIM12_IRQn} },
    { pal::timer::id::t13, { .reg = TIM13, .rcc = RCC_APB1L(TIM13), .isr = TIM8_UP_TIM13_IRQn} },
    { pal::timer::id::t14, { .reg = TIM14, .rcc = RCC_APB1L(TIM14), .isr = TIM8_TRG_COM_TIM14_IRQn} },
    { pal::timer::id::t15, { .reg = TIM15, .rcc = RCC_APB2(TIM15),  .isr = TIM15_IRQn} },
    { pal::timer::id::t16, { .reg = TIM16, .rcc = RCC_APB2(TIM16),  .isr = TIM16_IRQn} },
    { pal::timer::id::t17, { .reg = TIM17, .rcc = RCC_APB2(TIM17),  .isr = TIM17_IRQn} },
};


// ***********************************************************************************
// Template specialization for retrieving stm32h723 uart hardware details. Used by hardware.hpp
// ***********************************************************************************
template <>
template <>
const pal::stm32::timer_hardware_t* hardware<pal::stm32::timer_hardware_t>::get(pal::timer::id id) {
    // return &uartHardware.at(id);
    return &timer_hardware.at(id);
}

