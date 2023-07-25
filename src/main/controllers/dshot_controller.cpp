#include "dshot_controller.hpp"

#include "drivers/platform.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuseless-cast"

static void Error_Func()
{
    while (true)
    {
    }
}

/**
 * First just a quick implementation of the dshot protocol in order to test how it works.
 * Later refactor properly
*/

/**
 * Our board uses the following pinout: 
 *  PE9    ->  TIM1_CH1 
 *  PE11   ->  TIM1_CH2
 *  PE13   ->  TIM1_CH3
 *  PE14   ->  TIM1_CH4
*/

// Handlers stuff

// Define the PWM frequency in Hz
#define PWM_FREQ 1000

// Define the DMA channel and stream to use for PWM
#define PWM_DMA_STREAM DMA2_Stream1

#define MOTOR_1_BIT 687/2
#define MOTOR_0_BIT 343/2

// Define the memory buffer size and values for duty cycle
#define BUFFER_SIZE 18
uint32_t duty_cycle_buffer[BUFFER_SIZE] = {
    MOTOR_1_BIT,
    MOTOR_0_BIT,
    MOTOR_1_BIT,
    MOTOR_0_BIT,
    MOTOR_1_BIT,
    MOTOR_0_BIT,
    MOTOR_1_BIT,
    MOTOR_0_BIT,
    MOTOR_1_BIT,
    MOTOR_0_BIT,
    MOTOR_1_BIT,
    MOTOR_0_BIT,
    MOTOR_1_BIT,
    MOTOR_0_BIT,
    MOTOR_1_BIT,
    MOTOR_0_BIT,
    0,
    0
};

// Declare the timer handle structure
TIM_HandleTypeDef htim1;        

// Declare the timer output compare configuration structure
TIM_OC_InitTypeDef sConfigOC;

// Declare the DMA handle structure
DMA_HandleTypeDef hdma_tim1_ch1;

void MX_GPIO_Init()
{
    // Enable GPIO clock
    __HAL_RCC_GPIOE_CLK_ENABLE();

    // Configuring PE9 as TIM1_CH1 output
    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

// Initialize the timer for PWM mode
void MX_TIM1_Init(void)
{
    // Timer clock
    __HAL_RCC_TIM1_CLK_ENABLE();

    // Set the timer instance
    htim1.Instance = TIM1;

    // Set the timer prescaler to get the maximum frequency
    htim1.Init.Prescaler = 0;   // 550 Mhz -> 1 Mhz

    // Set the timer period to get the desired PWM frequency
    // TIM_Period = timer_tick_frequency / PWM_frequency - 1
    htim1.Init.Period = 916/2 - 1;

    // Set the timer clock division, counter mode and repetition counter
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.RepetitionCounter = 0;

    // Initialize the timer PWM
    if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
    {
        Error_Func();
    }

        // Set the DMA instance
    hdma_tim1_ch1.Instance = DMA2_Stream1;
    hdma_tim1_ch1.Init.Request = DMA_REQUEST_TIM1_CH1;
    hdma_tim1_ch1.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_tim1_ch1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim1_ch1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim1_ch1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_tim1_ch1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_tim1_ch1.Init.Mode = DMA_CIRCULAR;
    hdma_tim1_ch1.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_tim1_ch1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    hdma_tim1_ch1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_tim1_ch1.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_tim1_ch1.Init.PeriphBurst = DMA_PBURST_SINGLE;

    // Initialize the DMA
    if (HAL_DMA_Init(&hdma_tim1_ch1) != HAL_OK)
    {
        Error_Func();
    }

    // Associate the initialized DMA handle to the timer handle
    __HAL_LINKDMA(&htim1, hdma[TIM_DMA_ID_CC1], hdma_tim1_ch1);


    // Set the output compare mode, polarity, pulse and idle state
    // Pulse = (TIM_Period + 1) * duty_cycle / 100 - 1
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

    // Configure the timer output compare channel
    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Func(); 
    }

    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {};
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.BreakFilter = 0;
    sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
    sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
    sBreakDeadTimeConfig.Break2Filter = 0;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
    {
        Error_Func();
    }

}

// Initialize the DMA for PWM mode
void MX_DMA_Init(void)
{
  __HAL_RCC_DMA2_CLK_ENABLE();

  // NVIC configuration for DMA interrupt
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

}

dshot_controller::dshot_controller()
    : Runnable(__func__, Runnable::initThreadAttr(__func__, 4096, osPriorityNormal))
{


}

void dshot_controller::Run()
{
    // TIM1->CCR1 = 343/2;
    __HAL_DMA_ENABLE_IT(&hdma_tim1_ch1, DMA_IT_TC);
    __HAL_DMA_ENABLE(&hdma_tim1_ch1);
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)duty_cycle_buffer, BUFFER_SIZE);
    
    while (true)
    {
        // Wait some time
        // Write to motors a value
        osDelay(1000);
        // HAL_DMA_Start_IT(&hdma_tim1_ch1, (uint32_t)duty_cycle_buffer, (uint32_t)&htim1.Instance->CCR1, BUFFER_SIZE);
    }
    
}

void dshot_controller::Init()
{
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_TIM1_Init();

}

extern "C" void DMA2_Stream1_IRQHandler()
{
    HAL_DMA_IRQHandler(&hdma_tim1_ch1);
}



#pragma GCC diagnostic pop


/*

void pwmWriteDshotInt(uint8_t index, uint16_t value)
{
    motorDmaOutput_t *const motor = &dmaMotors[index];

    if (!motor->timerHardware || !motor->timerHardware->dmaRef) {
        return;
    }

    uint16_t packet = prepareDshotPacket(motor, value);

    uint8_t bufferSize = loadDmaBuffer(motor, packet);

    if (motor->timerHardware->output & TIMER_OUTPUT_N_CHANNEL) {
        if (HAL_TIMEx_PWMN_Start_DMA(&motor->TimHandle, motor->timerHardware->channel, motor->dmaBuffer, bufferSize) != HAL_OK) {
            // Starting PWM generation Error 
            return;
        }
    } else {
        if (HAL_TIM_PWM_Start_DMA(&motor->TimHandle, motor->timerHardware->channel, motor->dmaBuffer, bufferSize) != HAL_OK) {
            // Starting PWM generation Error 
            return;
        }
    }
}


*/