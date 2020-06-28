/*


*/
#ifndef USER_LED_H__
#define USER_LED_H__

#include <stdint.h>

void user_led_cmd_process(uint32_t profile, uint8_t *data, uint8_t len);
void user_led_init(void);

#endif

