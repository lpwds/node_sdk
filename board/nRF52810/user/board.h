/*
 * board.h
 *
 *  Created on: 2018年4月10日
 *      Author: larry
 */

#ifndef BOARD_H__
#define BOARD_H__

//#define BOARD_E01010037RC
#define BOARD_PIPE
//#define SMART_LOCK

#ifdef SMART_LOCK

#define UART_WAKEUP_DEVICE_PIN      12
#define UART_DEVICE_WAKEUP_PIN      10

#define RX_PIN_NUMBER  25
#define TX_PIN_NUMBER  27
#define CTS_PIN_NUMBER 0xFF
#define RTS_PIN_NUMBER 0xFF
#define HWFC           false

#define USE_XTAL				1

#define HAL_RADIO_PA_ENABLE		1
#define HAL_RADIO_PA_TX_EN		20
#define HAL_RADIO_PA_RX_EN		19

#endif

#ifdef BOARD_PIPE

#define UART_WAKEUP_DEVICE_PIN      5
#define UART_DEVICE_WAKEUP_PIN      6

#define RX_PIN_NUMBER  7
#define TX_PIN_NUMBER  8
#define CTS_PIN_NUMBER 0xFF
#define RTS_PIN_NUMBER 0xFF
#define HWFC           false

#define USE_XTAL				1

#define HAL_RADIO_PA_ENABLE		0
#define HAL_RADIO_PA_TX_EN		20
#define HAL_RADIO_PA_RX_EN		19

#endif

#ifdef BOARD_E01010037RC

#define RX_PIN_NUMBER  12
#define TX_PIN_NUMBER  11
#define CTS_PIN_NUMBER 0xFF
#define RTS_PIN_NUMBER 0xFF
#define HWFC           false

#define USE_XTAL				1

#define HAL_RADIO_PA_ENABLE		1
#define HAL_RADIO_PA_TX_EN		20
#define HAL_RADIO_PA_RX_EN		19

#endif

#ifdef BOARD_PCA10000

#define RX_PIN_NUMBER  11
#define TX_PIN_NUMBER  9
#define CTS_PIN_NUMBER 10
#define RTS_PIN_NUMBER 8
#define HWFC           false

#endif  /* BOARD_PCA10000 */

#ifdef BOARD_PTR9618PA

#define RX_PIN_NUMBER  12
#define TX_PIN_NUMBER  11
#define CTS_PIN_NUMBER 0xFF
#define RTS_PIN_NUMBER 0xFF
#define HWFC           false

#define USE_SYNTH	1

#define HAL_RADIO_PA_ENABLE	1

//#define HAL_RADIO_PA_EN_PIN	20
#define HAL_RADIO_PA_TX_EN		24
#define HAL_RADIO_PA_RX_EN		20

#endif

#ifdef BAORD_PTR5518PA

#define RX_PIN_NUMBER  12
#define TX_PIN_NUMBER  9
#define CTS_PIN_NUMBER 28
#define RTS_PIN_NUMBER 29
#define HWFC           false

#define USE_SYNTH	1

#define HAL_RADIO_PA_ENABLE	1

#define HAL_RADIO_PA_EN_PIN	20

#endif


#ifdef BAORD_HOLYIOT

#define RX_PIN_NUMBER  11
#define TX_PIN_NUMBER  9
#define CTS_PIN_NUMBER 10
#define RTS_PIN_NUMBER 8
#define HWFC           false


#define USE_XTAL		1

#endif

#ifdef BAORD_HOLYIOT17081

#define RX_PIN_NUMBER  12
#define TX_PIN_NUMBER  8
#define CTS_PIN_NUMBER 10
#define RTS_PIN_NUMBER 9
#define HWFC           false

#define UART_WAKEUP_DEVICE_PIN  15
#define UART_DEVICE_WAKEUP_PIN  16

#define HAL_RADIO_PA_ENABLE		1
#define HAL_RADIO_PA_EN_PIN		17

#define USE_XTAL		1

#endif


#ifdef BAORD_HOLYIOT15004

#define RX_PIN_NUMBER  11
#define TX_PIN_NUMBER  9
#define CTS_PIN_NUMBER 10
#define RTS_PIN_NUMBER 8
#define HWFC           false

#define UART_WAKEUP_DEVICE_PIN  0
#define UART_DEVICE_WAKEUP_PIN  1

#define HAL_RADIO_PA_ENABLE		1
#define HAL_RADIO_PA_EN_PIN		17

#define USE_XTAL		1

#endif

#ifdef BAORD_YJ14004PA

#define UART_WAKEUP_DEVICE_PIN  28
#define UART_DEVICE_WAKEUP_PIN  29

#define RX_PIN_NUMBER  11
#define TX_PIN_NUMBER  9

#define CTS_PIN_NUMBER 10
#define RTS_PIN_NUMBER 8
#define HWFC           false

#define HAL_RADIO_PA_ENABLE		1
#define HAL_RADIO_PA_EN_PIN		17

#define USE_XTAL		1

#endif

#endif /* BOARD_H__ */
