/*


*/
#include "node_profile.h"
#include "case_api.h"
#include "nrf.h"

#include "node_resource_discovery.h"
#include "node_app.h"
//#include "simple_uart.h"

static __IO uint32_t __case_state = 0;
static __IO uint32_t beacon_tick_flag = 0;
void node_profile_data_recv_handler(uint32_t profile, uint8_t *data, uint8_t len);

__weak void case_evt_on_send_ok(void)
{
    
}

__weak void case_evt_on_connect(uint16_t panid, uint8_t *mac)
{
    
}

__weak void case_evt_on_disconnect(void)
{
    
}

__weak void case_evt_on_hs_data(uint8_t *data)
{
    
}

uint32_t case_state(void)
{
    return __case_state;
}

void case_evt_handler(uint8_t *data)
{
    struct pipe_header_t *evt = (struct pipe_header_t *)data;
    switch(evt->evt_id) {
        
        case PIPE_EVT_ON_CONNECT:
        {
            //debug_out("connect\n");
            __case_state = 1;
            
            uint16_t panid = evt->data[0] & 0xff;
            panid = panid << 8 | evt->data[1];
            case_evt_on_connect(panid, evt->data+2);
        }
            break;
        
        case PIPE_EVT_ON_DISCONNECT:
            //debug_out("disconnect\n");
            __case_state = 0;
            case_evt_on_disconnect();
            break;
        
        case PIPE_EVT_ON_DATA:
        {
            struct pipe_evt_data_t *d = (struct pipe_evt_data_t *)data;
            //debug_out("d: %08X: %02x\n", d->profile, d->payload[0]);
            node_profile_data_recv_handler(d->profile, d->payload, d->length);
        }
            break;
        
        case PIPE_EVT_ON_BEACON:
            beacon_tick_flag++;
            break;
        
        case PIPE_EVT_ON_SEND_OK:
            case_evt_on_send_ok();
            break;
        
        case PIPE_EVT_ON_HS_DATA:
        {
            struct pipe_evt_hs_data_t *hs_evt = (struct pipe_evt_hs_data_t *)data;
            static uint8_t temp[256];
            case_evt_hs_read(temp, hs_evt->fifo_id);
            case_evt_on_hs_data(temp);
            //data in temp
        } break;
        
        default:
        {
            //debug_out("evt: %02X\n", evt->evt_id);
        }
        break;
    }
}


void node_profile_data_recv_handler(uint32_t profile, uint8_t *data, uint8_t len)
{
    node_resource_cmd_process(profile, data, len);
    node_app_on_cmd_handler(profile, data, len);
}


uint32_t node_profile_write(uint32_t profile, uint8_t *data, uint8_t len, uint8_t ack)
{
    return case_write(profile, data, len, ack);
}

void node_profile_tick_process(void)
{
    node_resource_tick_process();
    node_app_tick_process();
}

void node_profile_process(void)
{
    if(beacon_tick_flag) {
        beacon_tick_flag = 0;
        node_profile_tick_process();
    }
    node_app_process();
}

void node_profile_init(void)
{
    node_resource_init();
    node_app_init();
    __case_state = 0;
}

