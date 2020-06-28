/*


*/
#include "node_resource_discovery.h"
#include "util_ascii.h"
#include "node_profile.h"

#define NODE_RESOURCE_MAX_COUNT     32

static uint32_t node_resources[NODE_RESOURCE_MAX_COUNT];
static uint32_t node_resource_cnt = 0;

#define NODE_RES_CMD_REQUEST            0x01
#define NODE_RES_CMD_RESPONSE           0x02

#define NODE_RES_STATE_IDLE         0
#define NODE_RES_STATE_UPLOAD       1

static uint32_t node_resource_state = NODE_RES_STATE_IDLE;
static uint32_t node_resource_upload_cnt = 0;
static uint32_t node_resource_upload_index = 0;

static uint32_t node_resource_package_cnt = 0;


void node_resource_register(uint32_t profile)
{
    node_resources[node_resource_cnt++] = util_32host2net(profile);
}

static void node_resource_upload(void)
{
    uint32_t temp[4];
    
    temp[0] = (node_resource_cnt & 0xFF);
    temp[0] = (temp[0]<< 8) | (node_resource_upload_cnt & 0xFF);
    temp[0] = (temp[0]<< 8) | 0x00;
    temp[0] = (temp[0]<< 8) | NODE_RES_CMD_RESPONSE;
    
    temp[1] = node_resources[node_resource_upload_index++];
    temp[2] = node_resources[node_resource_upload_index++];
    temp[3] = node_resources[node_resource_upload_index++];
    
    node_profile_write(NODE_PROFILE_RESOURCE_DISCOVERY, (uint8_t *)(&temp[0]), 16, 0);
}


void node_resource_cmd_process(uint32_t profile, uint8_t *data, uint8_t len)
{
    if(profile == NODE_PROFILE_RESOURCE_DISCOVERY) {
        if(data[0] == NODE_RES_CMD_REQUEST) {
            node_resource_state = NODE_RES_STATE_UPLOAD;
            node_resource_upload_cnt = 0;
            node_resource_upload_index = 0;
            node_resource_package_cnt = (node_resource_cnt+2)/3;
        }
    } else {}
}


void node_resource_tick_process(void)
{
    switch(node_resource_state) {
        case NODE_RES_STATE_IDLE:
            break;
        
        case NODE_RES_STATE_UPLOAD:
            if(node_resource_package_cnt == node_resource_upload_cnt){
                node_resource_state = NODE_RES_STATE_IDLE;
            } else {
                node_resource_upload();
            }
            
            node_resource_upload_cnt++;
            break;
    }
}


void node_resource_init(void)
{
    uint32_t i = 0;
    for(i=0; i<NODE_RESOURCE_MAX_COUNT; i++) {
        node_resources[i] = 0;
    }
    
    node_resource_cnt = 0;
    //node_resources[node_resource_cnt++] = util_32host2net(NODE_PROFILE_RESOURCE_DISCOVERY);
    node_resource_register(NODE_PROFILE_RESOURCE_DISCOVERY);
    
    node_resource_state = NODE_RES_STATE_IDLE;
    node_resource_upload_cnt = 0;
    node_resource_upload_index = 0;
    node_resource_package_cnt = 0;
}

