/*


*/
#ifndef SIMPLE_UART_LP_H__
#define SIMPLE_UART_LP_H__

void simple_uart_lp_process(void);

void simple_uart_lp_tx_start(void);
void simple_uart_lp_tx_stop(void);
void simple_uart_lp_rx_start(void);
void simple_uart_lp_rx_stop(void);

void simple_uart_lp_init(void);

#endif

