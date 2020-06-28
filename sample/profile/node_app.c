/*



*/
#include "node_app.h"
#include "node_auth.h"
#include "node_uart.h"
//#include "user_led.h"

void node_app_on_cmd_handler(uint32_t profile, uint8_t *data, uint32_t length)
{
    node_auth_cmd_process(profile, data, length);
    node_uart_on_cmd_handler(profile, data, length);
    //user_led_cmd_process(profile, data, length);
}


void node_app_tick_process(void)
{
    node_uart_tick_process();
}

void node_app_process(void)
{
    node_uart_process();
}


void node_app_init(void)
{
    node_auth_init();
    node_uart_init();
    //user_led_init();
}

