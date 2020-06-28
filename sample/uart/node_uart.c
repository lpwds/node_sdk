/*



*/
#include "node_uart.h"
#include "node_profile.h"

#include "nrf.h"
#include "simple_uart.h"
#include "uart_frame.h"
#include "simple_uart_lp.h"

void node_uart_irq_handler(void);

void node_uart_on_cmd_handler(uint32_t profile, uint8_t *data, uint32_t length)
{
    if(profile == NODE_PROFILE_USER_UART){
        if(length) {
            simple_uart_lp_tx_start();
            static uint8_t out_frame[64];
            uint32_t out_length = uart_slip_frame_build(out_frame, data, length);
            uint32_t i=0;
            for(i=0; i<out_length; i++) {
                simple_uart_put(out_frame[i]);
            }
            simple_uart_lp_tx_stop();
        }
    }
}


void node_uart_tick_process(void)
{
    simple_uart_lp_process();
}

void node_uart_process(void)
{
    uart_slip_process();
}


void node_uart_init(void)
{
    uart_slip_init();
    
    simple_uart_config(0xff, 9, 0xff, 10, false);
    simple_uart_irq_register(node_uart_irq_handler);
    
    NRF_UART0->INTENSET = UART_INTENSET_RXDRDY_Enabled << UART_INTENSET_RXDRDY_Pos;
	
	NVIC_ClearPendingIRQ(UARTE0_UART0_IRQn);
	NVIC_SetPriority(UARTE0_UART0_IRQn, 2);
	NVIC_EnableIRQ(UARTE0_UART0_IRQn);
    
    debug_out("node uart\n");
    
    simple_uart_lp_init();
}

void node_uart_irq_handler(void)
{
	if(NRF_UART0->EVENTS_RXDRDY != 0) {
		NRF_UART0->EVENTS_RXDRDY = 0;
		
		uint8_t rxd[4];
		rxd[0] = (uint8_t)NRF_UART0->RXD;
		//hal_uart_rx_fifo_in(rxd, 1);
		//uint8_t rxd = (uint8_t)NRF_UART0->RXD;
		//simple_uart_put(rxd);
        uart_slip_put(rxd[0]);
	}
	
	NRF_UART0->EVENTS_CTS = 0;
	NRF_UART0->EVENTS_ERROR = 0;
	NRF_UART0->EVENTS_NCTS = 0;
	NRF_UART0->EVENTS_RXTO = 0;
	NRF_UART0->EVENTS_TXDRDY = 0;
}
