/*


*/
#include "case_api.h"
#include "nrf.h"

struct pipe_header_t pipe_evt;

static void node_enter_lowpower(void)
{
#if (__FPU_USED == 1)
	__set_FPSCR(__get_FPSCR() & ~(0x0000009F)); 
	(void) __get_FPSCR();
	NVIC_ClearPendingIRQ(FPU_IRQn);
#endif
    
    NRF_POWER->TASKS_LOWPWR = 1;
    __WFI();
}

void case_process(void)
{
    node_enter_lowpower();
}


__weak void case_evt_handler(uint8_t *data)
{
    struct pipe_header_t *evt = (struct pipe_header_t *)data;
    switch(evt->evt_id) {
        
        case PIPE_EVT_ON_CONNECT:
            break;
        
        case PIPE_EVT_ON_DISCONNECT:
            break;
        
        case PIPE_EVT_ON_DATA:
            break;
        
        case PIPE_EVT_ON_BEACON:
            break;
    }
}

void SWI0_EGU0_IRQHandler(void)
{
    while(1) {
        uint32_t len = case_evt_read((uint8_t *)&pipe_evt);
        if(len == 32) {
            case_evt_handler((uint8_t *)&pipe_evt);
        } else {
            break;
        }
    }
    
    NVIC_ClearPendingIRQ(SWI0_EGU0_IRQn);
}
