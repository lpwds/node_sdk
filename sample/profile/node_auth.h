/*


*/
#ifndef NODE_AUTH_H__
#define NODE_AUTH_H__

#include <stdint.h>

void node_auth_cmd_process(uint32_t profile, uint8_t *data, uint8_t len);
void node_auth_init(void);

#endif
