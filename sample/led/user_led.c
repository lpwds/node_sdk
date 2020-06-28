/*


*/
#include "user_led.h"
#include "node_profile.h"
#include "nrf_gpio.h"

#if 1

#define USER_LED_PIN			07 //18

static void user_led_write(uint32_t val)
{
	if(val == 0) {
		nrf_gpio_pin_set(USER_LED_PIN);
	} else {
		nrf_gpio_pin_clear(USER_LED_PIN);
	}
}

#else
//PIPE
#define USER_LED_PIN			27

static void user_led_write(uint32_t val)
{
	if(val) {
		nrf_gpio_pin_clear(USER_LED_PIN);
	} else {
		nrf_gpio_pin_set(USER_LED_PIN);
	}
}

#endif


void user_led_cmd_process(uint32_t profile, uint8_t *data, uint8_t len)
{
    if(profile == NODE_PROFILE_USER_LED){
		if(data[0]) {
			user_led_write(1);
		} else {
			user_led_write(0);
		}
	}
}


void user_led_init(void)
{
    nrf_gpio_cfg_output(USER_LED_PIN);
	user_led_write(0);
}
