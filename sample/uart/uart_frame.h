/*



*/
#ifndef UART_FRAME_H__
#define UART_FRAME_H__

#include <stdint.h>

void uart_slip_put(uint8_t ch);

uint32_t uart_slip_frame_build(uint8_t *out, uint8_t *in, uint32_t length);
void uart_slip_process(void);
void uart_slip_init(void);

#endif


