/*


*/
#include "simple_uart_lp.h"
#include "nrf.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
//#include "board.h"

#define UART_WAKEUP_DEVICE_PIN          26
#define UART_DEVICE_WAKEUP_PIN          28

#define LOW_POWER_HW_STATE_DISABLE      0
#define LOW_POWER_HW_STATE_ENABLE       1

static volatile uint32_t lpu_hw_state = LOW_POWER_HW_STATE_DISABLE;

static volatile uint32_t lpu_txing = 0;
static volatile uint32_t lpu_rxing = 0;

static volatile uint32_t lpuart_close_delay = 0;
static volatile uint32_t lpuart_close_enable = 0;

static void __low_power_uart_disable(void)
{
    if(lpu_hw_state != LOW_POWER_HW_STATE_DISABLE){
		
//        NRF_UARTE0->TASKS_STOPTX = 1;
//        NRF_UARTE0->TASKS_STOPRX = 1;
        NRF_UARTE0->ENABLE       = (UARTE_ENABLE_ENABLE_Disabled << UARTE_ENABLE_ENABLE_Pos);
        lpu_hw_state = LOW_POWER_HW_STATE_DISABLE;
    }
}

static void __low_power_uart_enable(void)
{
    if(lpu_hw_state != LOW_POWER_HW_STATE_ENABLE){

//        NRF_UARTE0->TASKS_STARTTX = 1;
//        NRF_UARTE0->TASKS_STARTRX = 1;
        NRF_UARTE0->ENABLE       = (UARTE_ENABLE_ENABLE_Enabled << UARTE_ENABLE_ENABLE_Pos);
        lpu_hw_state = LOW_POWER_HW_STATE_ENABLE;
    }
}

static void low_power_uart_active(void)
{
    __low_power_uart_enable();
}

static void low_power_uart_deactive(void)
{
    if( (lpu_txing == 0) && (lpu_rxing == 0) ){
        __low_power_uart_disable();
    }
}


static uint32_t low_power_uart_status(void)
{
    return !nrf_gpio_pin_read(UART_DEVICE_WAKEUP_PIN);
	//return nrf_gpio_pin_read(UART_DEVICE_WAKEUP_PIN);
	//return 0;
    //return 1;
}


void simple_uart_lp_process(void)
{	
	if(low_power_uart_status() == 1){
		lpuart_close_enable = 0;
		lpuart_close_delay = 0;
        simple_uart_lp_rx_start();
    }else{
		if(lpuart_close_enable == 0) {
			lpuart_close_enable = 1;
			lpuart_close_delay = 0;
		} else {
			lpuart_close_delay++;
			if(lpuart_close_delay > 5) {
				simple_uart_lp_rx_stop();
			}
		}
    }
}

void simple_uart_lp_tx_start(void)
{
	if(lpu_txing == 0) {
		lpu_txing = 1;
		nrf_gpio_pin_clear(UART_WAKEUP_DEVICE_PIN);
		low_power_uart_active();
		nrf_delay_ms(10);
	}
}

void simple_uart_lp_tx_stop(void)
{
	if(lpu_txing == 1) {
		
		nrf_delay_ms(10);
		lpu_txing = 0;
		low_power_uart_deactive();
		nrf_gpio_pin_set(UART_WAKEUP_DEVICE_PIN);
	}
}

void simple_uart_lp_rx_start(void)
{
	if(lpu_rxing == 0) {
		lpu_rxing = 1;
		low_power_uart_active();
	}
}

void simple_uart_lp_rx_stop(void)
{
	if(lpu_rxing == 1) {
		//nrf_delay_ms(10);
		lpu_rxing = 0;
		low_power_uart_deactive();
	}
}


void simple_uart_lp_init(void)
{
	
	nrf_gpio_pin_set(UART_WAKEUP_DEVICE_PIN);
    nrf_gpio_cfg_output(UART_WAKEUP_DEVICE_PIN);
    
    NRF_GPIOTE->INTENCLR = 0xFFFFFFFF;
	
    nrf_gpio_cfg_sense_input(UART_DEVICE_WAKEUP_PIN, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
	
    NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_PORT_Enabled << GPIOTE_INTENSET_PORT_Pos;

	NVIC_ClearPendingIRQ(GPIOTE_IRQn);
	NVIC_SetPriority(GPIOTE_IRQn, 2);
	NVIC_EnableIRQ(GPIOTE_IRQn);
	
	NRF_UARTE0->ENABLE       = (UARTE_ENABLE_ENABLE_Disabled << UARTE_ENABLE_ENABLE_Pos);
	lpu_hw_state = LOW_POWER_HW_STATE_DISABLE;
	
	lpu_rxing = 0;
	lpu_txing = 0;
}	



void GPIOTE_IRQHandler(void)
{
	if(NRF_GPIOTE->EVENTS_PORT){

		simple_uart_lp_rx_start();
		
		lpuart_close_enable = 0;
		lpuart_close_delay = 0;
		
	}
    NRF_GPIOTE->EVENTS_PORT = 0;
	
	NRF_GPIOTE->EVENTS_IN[0] = 0;
	NRF_GPIOTE->EVENTS_IN[1] = 0;
	NRF_GPIOTE->EVENTS_IN[2] = 0;
	NRF_GPIOTE->EVENTS_IN[3] = 0;
	NRF_GPIOTE->EVENTS_IN[4] = 0;
	NRF_GPIOTE->EVENTS_IN[5] = 0;
	NRF_GPIOTE->EVENTS_IN[6] = 0;
	NRF_GPIOTE->EVENTS_IN[7] = 0;
}

