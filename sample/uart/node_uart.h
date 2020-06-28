/*


*/
#ifndef NODE_UART_H__
#define NODE_UART_H__

#include <stdint.h>

void node_uart_on_cmd_handler(uint32_t profile, uint8_t *data, uint32_t length);
void node_uart_tick_process(void);
void node_uart_process(void);
void node_uart_init(void);

#endif

