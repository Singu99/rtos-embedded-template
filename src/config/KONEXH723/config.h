/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 *
 * Betaflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once


#define FC_TARGET_MCU     STM32H723

#define BOARD_NAME        KONEXH723
#define MANUFACTURER_ID   KONX

#define USE_GYRO
#define USE_ACC
#define USE_ACCGYRO_BMI270

#define MOTOR1_PIN           PE9
#define MOTOR2_PIN           PE11
#define MOTOR3_PIN           PE13
#define MOTOR4_PIN           PE14

#define UART1_TX_PIN         PB14
#define UART2_TX_PIN         PA2
#define UART4_TX_PIN         PA0
#define UART6_TX_PIN         PC6
#define UART7_TX_PIN         PE8
#define UART8_TX_PIN         PE1
#define UART9_TX_PIN         PD15

#define UART1_RX_PIN         PB15
#define UART2_RX_PIN         PA3
#define UART4_RX_PIN         PA1
#define UART6_RX_PIN         PC7
#define UART7_RX_PIN         PE7
#define UART8_RX_PIN         PE0
#define UART9_RX_PIN         PD14

#define LED0_PIN             PD2
#define LED1_PIN             PD4
#define SPI1_SCK_PIN         PA5
#define SPI1_SDI_PIN         PA6
#define SPI1_SDO_PIN         PA7

#define GYRO_1_EXTI_PIN      PC4
#define GYRO_1_CS_PIN        PA4

/*
#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, PE9 , 1,  0) \
    TIMER_PIN_MAP( 1, PE11 , 1,  0) \
    TIMER_PIN_MAP( 2, PE13 , 1,  0) \
    TIMER_PIN_MAP( 3, PE14 , 1,  0)
*/

/*
#define ADC1_DMA_OPT                    8
#define ADC2_DMA_OPT                    9
#define ADC3_DMA_OPT                    10

#define TIMUP1_DMA_OPT                  0
#define TIMUP3_DMA_OPT                  0
#define TIMUP4_DMA_OPT                  0
#define TIMUP5_DMA_OPT                  0
#define TIMUP8_DMA_OPT                  0
*/

//TODO #define SDCARD_MODE OFF
#define USE_SPI_GYRO
#define GYRO_1_SPI_INSTANCE SPI1

#define DEFAULT_GYRO_TO_USE GYRO_CONFIG_USE_GYRO_1


