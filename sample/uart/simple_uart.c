/*


*/
#include "simple_uart.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#include "nrf.h"
#include "simple_uart.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"

static uart_irq_handler uart_irq = NULL;

uint8_t simple_uart_get(void)
{
  while (NRF_UART0->EVENTS_RXDRDY != 1)
  {
    // Wait for RXD data to be received
  }
  
  NRF_UART0->EVENTS_RXDRDY = 0;
  return (uint8_t)NRF_UART0->RXD;
}

bool simple_uart_get_with_timeout(int32_t timeout_ms, uint8_t *rx_data)
{
  bool ret = true;
  
  while (NRF_UART0->EVENTS_RXDRDY != 1)
  {
    if (timeout_ms-- >= 0)
    {
      // wait in 1ms chunk before checking for status
      nrf_delay_us(1000);
    }
    else
    {
      ret = false;
      break;
    }
  }  // Wait for RXD data to be received

  if (timeout_ms >= 0)
  {
    // clear the event and set rx_data with received byte
      NRF_UART0->EVENTS_RXDRDY = 0;
      *rx_data = (uint8_t)NRF_UART0->RXD;
  }

  return ret;
}

void simple_uart_put(uint8_t cr)
{
  NRF_UART0->TXD = (uint8_t)cr;

  while (NRF_UART0->EVENTS_TXDRDY!=1)
  {
    // Wait for TXD data to be sent
  }

  NRF_UART0->EVENTS_TXDRDY=0;
}

static uint8_t hexstring[] = "0123456789ABCDEF";;
void simple_uart_puthexstring(const uint8_t *str, uint32_t len)
{
    uint32_t i=0;
    uint8_t chh;
    uint8_t chl;
    for(i=0; i<len; i++) {
        chh = (str[i] >> 4) & 0x0f;
        chl = str[i] & 0x0f;
        simple_uart_put(hexstring[chh]);
        simple_uart_put(hexstring[chl]);
    }
}

void simple_uart_putstring(const uint8_t *str)
{
  uint_fast8_t i = 0;
  uint8_t ch = str[i++];
  while (ch != '\0')
  {
    simple_uart_put(ch);
    ch = str[i++];
  }
}

void simple_uart_config(  uint8_t rts_pin_number,
                          uint8_t txd_pin_number,
                          uint8_t cts_pin_number,
                          uint8_t rxd_pin_number,
                          bool hwfc)
{
  nrf_gpio_cfg_output(txd_pin_number);
  nrf_gpio_pin_set(txd_pin_number);
  nrf_gpio_cfg_input(rxd_pin_number, NRF_GPIO_PIN_PULLUP);  

  NRF_UART0->PSEL.TXD = txd_pin_number;
  NRF_UART0->PSEL.RXD = rxd_pin_number;

  if (hwfc)
  {
    nrf_gpio_cfg_output(rts_pin_number);
    nrf_gpio_cfg_input(cts_pin_number, NRF_GPIO_PIN_NOPULL);
    NRF_UART0->PSEL.CTS = cts_pin_number;
    NRF_UART0->PSEL.RTS = rts_pin_number;
    NRF_UART0->CONFIG  = (UART_CONFIG_HWFC_Enabled << UART_CONFIG_HWFC_Pos);
  }

  NRF_UART0->BAUDRATE         = (UART_BAUDRATE_BAUDRATE_Baud115200 << UART_BAUDRATE_BAUDRATE_Pos);
  NRF_UART0->ENABLE           = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);
  NRF_UART0->TASKS_STARTTX    = 1;
  NRF_UART0->TASKS_STARTRX    = 1;
  NRF_UART0->EVENTS_RXDRDY    = 0;
}


void simple_uart_irq_register(uart_irq_handler irq)
{
	uart_irq = irq;
}


void UARTE0_UART0_IRQHandler(void)
{
	if(uart_irq != NULL) {
		uart_irq();
	}
}

void __log(uint8_t level, const char * func, uint32_t line, const char * restrict format, ...)
{
    if( level >= __LEVEL__ ) {
		char	str[64];
        va_list ap;
        
        snprintf(str, sizeof(str), "[%d]%s(%d):",level,func,line);
        simple_uart_putstring((const uint8_t *)str);
        
        va_start(ap, format);
        (void)vsnprintf(str, sizeof(str), format, ap);
        va_end(ap);
        
        simple_uart_putstring((const uint8_t *)str);
        simple_uart_putstring((const uint8_t *)"\r\n");
    }
}


void debug_out(const char * restrict format, ...)
{
	char str[128];
	va_list ap;

	va_start(ap, format);
	int len = vsnprintf(str, sizeof(str)-1, format, ap);
	va_end(ap);
	if(len>0){
		str[len] = '\0';
	}
	simple_uart_putstring((const uint8_t *)str);
}

