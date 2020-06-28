/*



*/
#ifndef NODE_DEVICE_INFO_H__
#define NODE_DEVICE_INFO_H__

#include <stdint.h>

void node_device_info_cmd_process(uint32_t profile, uint8_t *data, uint8_t len);
void node_device_info_process(void);
void node_device_info_init(void);

#endif

