/*


*/
#include "uart_frame.h"
#include "node_profile.h"

#include "fifo.h"
#include "slip.h"

#define HAL_UART_RX_FIFO_SIZE		1024
static uint8_t uart_rx_fifo_buf[HAL_UART_RX_FIFO_SIZE];
static struct fifo uart_rx_fifo_info;

#define SLIP_TEMP_SIZE	64
static struct slip_info_t uart_slip_info;

static void on_slip_frame_recv_handler(void *args, int len)
{
	struct slip_info_t *slip = (struct slip_info_t *)args;
	uint32_t temp_len = len;
	
	if(temp_len) {
		if(temp_len > NODE_PROFILE_PAYLOAD_SIZE){
			temp_len = NODE_PROFILE_PAYLOAD_SIZE;
		}
        node_profile_write(NODE_PROFILE_USER_UART, slip->p, temp_len, 0);
	}else{
	}
}

uint32_t uart_slip_frame_build(uint8_t *out, uint8_t *in, uint32_t length)
{
    return build_packet(out, in, length);
}

void uart_slip_put(uint8_t ch)
{
    uint8_t temp[4];
    temp[0] = ch;
    fifo_in(&uart_rx_fifo_info, temp, 1);
}

void uart_slip_process(void)
{
    static uint8_t temp[SLIP_TEMP_SIZE];
	uint32_t ret = fifo_out(&uart_rx_fifo_info, temp, SLIP_TEMP_SIZE);
	if(ret){
        uint32_t i = 0;
        for(i=0; i<ret; i++) {
            recv_package(&uart_slip_info, temp[i]);
        }
	}
}


void uart_slip_init(void)
{
    fifo_init(&uart_rx_fifo_info, uart_rx_fifo_buf, HAL_UART_RX_FIFO_SIZE);
    slip_init(&uart_slip_info);
    slip_register(&uart_slip_info, on_slip_frame_recv_handler);
}

