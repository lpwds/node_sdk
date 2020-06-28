/*


*/
#include "node_device_info.h"
#include <string.h>
#include "cell_mac_node.h"
#include "node_profile.h"
#include "node_resource_discovery.h"

#define NODE_DEVICE_SW_VERSION      "v1.0.1"
#define NODE_DEVICE_HW_VERSION      "DPK001"

#define NODE_DEVICE_CMD_REQUEST     0x01

void node_device_info_cmd_process(uint32_t profile, uint8_t *data, uint8_t len)
{
    if(profile == NODE_PROFILE_DEVICE_INFO_SW_VERSION){
        
        node_profile_write(NODE_PROFILE_DEVICE_INFO_SW_VERSION, (uint8_t *)NODE_DEVICE_SW_VERSION, strlen(NODE_DEVICE_SW_VERSION), 0);
        
    } else if(profile == NODE_PROFILE_DEVICE_INFO_HW_VERSION) {
        
        node_profile_write(NODE_PROFILE_DEVICE_INFO_HW_VERSION, (uint8_t *)NODE_DEVICE_HW_VERSION, strlen(NODE_DEVICE_HW_VERSION), 0);
        
    } else if(profile == NODE_PROFILE_DEVICE_INFO_UUID) {
        //node_send();
    } else if(profile == NODE_PROFILE_USER_RSSI) {
        
        uint8_t temp[4];
        temp[0] = cell_mac_node_rssi_get();
        node_profile_write(NODE_PROFILE_USER_RSSI, temp, 1, 0);
        
    } else {}
    
}

void node_device_info_process(void)
{
    
}

void node_device_info_init(void)
{
    node_resource_register(NODE_PROFILE_DEVICE_INFO_SW_VERSION);
    node_resource_register(NODE_PROFILE_DEVICE_INFO_HW_VERSION);
    node_resource_register(NODE_PROFILE_USER_RSSI);
}

