/*


*/
#ifndef NODE_APP_H__
#define NODE_APP_H__

#include <stdint.h>

void node_app_on_cmd_handler(uint32_t profile, uint8_t *data, uint32_t length);
void node_app_tick_process(void);
void node_app_process(void);
void node_app_init(void);

#endif

