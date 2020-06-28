/*


*/
#include "node_auth.h"
#include "node_profile.h"
#include "nrf.h"
#include "nrf_delay.h"


#define NODE_AUTH_ACCEPT  	0x5a
#define NODE_AUTH_REJECT 	0x5b

void node_auth_cmd_process(uint32_t profile, uint8_t *data, uint8_t len)
{
    if(profile == NODE_PROFILE_DEVICE_AUTH){
		if(data[0] == NODE_AUTH_REJECT) {
			nrf_delay_ms(5);
			NVIC_SystemReset();
		} else {
			
		}
	}
}


void node_auth_init(void)
{
	
}


