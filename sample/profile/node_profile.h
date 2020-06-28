/*


*/

#ifndef NODE_PROFILE_H__
#define NODE_PROFILE_H__

#include <stdint.h>

#define NODE_PROFILE_PAYLOAD_SIZE                       18

#define NODE_PROFILE_RESOURCE_DISCOVERY                 0xFFFFFE01
#define NODE_PROFILE_DEVICE_INFO_UUID                   0xFFFFFE02
#define NODE_PROFILE_DEVICE_INFO_SW_VERSION             0xFFFFFE03
#define NODE_PROFILE_DEVICE_INFO_HW_VERSION             0xFFFFFE04
#define NODE_PROFILE_DEVICE_AUTH                        0xFFFFFE05

#define NODE_PROFILE_USER_OTA                           0xFFFFFE06
#define NODE_PROFILE_USER_RSSI                          0xFFFFFE07
#define NODE_PROFILE_USER_IP                            0xFFFFFE08


#define NODE_PROFILE_USER_LED                           0x00000064
#define NODE_PROFILE_USER_UART                          0x00000068
#define NODE_PROFILE_USER_LOCK                          0x0000006A
#define NODE_PROFILE_USER_AT						    0x0000006B

uint32_t node_profile_write(uint32_t profile, uint8_t *data, uint8_t len, uint8_t ack);

void node_profile_tick_process(void);
void node_profile_process(void);

void node_profile_init(void);

#endif

