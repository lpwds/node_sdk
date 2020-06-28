/*


*/
#ifndef SIMPLE_UART_H__
#define SIMPLE_UART_H__

/*lint ++flb "Enter library region" */

#include <stdbool.h>
#include <stdint.h>

typedef void (*uart_irq_handler)(void);

/** @file
* @brief Simple UART driver
*
*
* @defgroup nrf_drivers_simple_uart Simple UART driver
* @{
* @ingroup nrf_drivers
* @brief Simple UART driver
*/

/** @brief Function for reading a character from UART.
Execution is blocked until UART peripheral detects character has been received.
\return cr Received character.
*/
uint8_t simple_uart_get(void);

/** @brief Function for reading a character from UART with timeout on how long to wait for the byte to be received.
Execution is blocked until UART peripheral detects character has been received or until the timeout expires, which even occurs first
\return bool True, if byte is received before timeout, else returns False.
@param timeout_ms maximum time to wait for the data.
@param rx_data pointer to the memory where the received data is stored.
*/
bool simple_uart_get_with_timeout(int32_t timeout_ms, uint8_t *rx_data);

/** @brief Function for sending a character to UART.
Execution is blocked until UART peripheral reports character to have been send.
@param cr Character to send.
*/
void simple_uart_put(uint8_t cr);

/** @brief Function for sending a string to UART.
Execution is blocked until UART peripheral reports all characters to have been send.
Maximum string length is 254 characters including null character in the end.
@param str Null terminated string to send.
*/
void simple_uart_putstring(const uint8_t *str);

void simple_uart_puthexstring(const uint8_t *str, uint32_t len);

/** @brief Function for configuring UART to use 38400 baud rate.
@param rts_pin_number Chip pin number to be used for UART RTS
@param txd_pin_number Chip pin number to be used for UART TXD
@param cts_pin_number Chip pin number to be used for UART CTS
@param rxd_pin_number Chip pin number to be used for UART RXD
@param hwfc Enable hardware flow control
*/
void simple_uart_config(uint8_t rts_pin_number, uint8_t txd_pin_number, uint8_t cts_pin_number, uint8_t rxd_pin_number, bool hwfc);


void simple_uart_irq_register(uart_irq_handler irq);

/**
 *@}
 **/


#define LEVEL_VERBOSE       1
#define LEVEL_INFO          2
#define LEVEL_DEBUG         3
#define LEVEL_WARNING       4
#define LEVEL_ERROR         5
#define LEVEL_NONE          6

#define __LEVEL__   LEVEL_VERBOSE
#if 0
void __log(uint8_t level, const char * func, uint32_t line, const char * restrict format, ...);
#if defined(DEBUG_LOG) || defined(DEBUG_ACC) || defined(DEBUG_PHILL)
#define LOG(level, format, ...) __log(level, __func__, __LINE__, format, ##__VA_ARGS__);
#else
#define LOG(level, format, ...)
#endif
#else
#define LOG(level, format, ...)                   \
        if( level >= __LEVEL__ ) {                                          \
        char    str[64];                                \
        snprintf(str, sizeof(str), "[%d|%s|%d]"format,      \
        level,__func__,__LINE__,##__VA_ARGS__);\
        simple_uart_putstring((const uint8_t *)str);                    \
        }
#endif

		
void debug_out(const char * restrict format, ...);
		
/*lint --flb "Leave library region" */

#endif
