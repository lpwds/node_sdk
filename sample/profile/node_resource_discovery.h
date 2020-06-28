/*


*/
#ifndef NODE_RESOURCE_DISCOVERY_H__
#define NODE_RESOURCE_DISCOVERY_H__

#include <stdint.h>

void node_resource_register(uint32_t profile);

void node_resource_cmd_process(uint32_t profile, uint8_t *data, uint8_t len);
void node_resource_tick_process(void);
void node_resource_init(void);

#endif

