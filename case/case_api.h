/*


*/
#ifndef CASE_API_H__
#define CASE_API_H__


#include <stdint.h>
#include "pipe_api.h"

struct case_config_t
{
	uint8_t addr[6];
	uint16_t panid;
	uint16_t extid;
    
    uint32_t poll_interval;
    uint32_t max_lose_cnt;
    uint32_t scan_interval;
	
	uint8_t key[16];
	
	uint8_t key2[16];
	uint8_t iv2[16];
	uint32_t token;
    uint32_t adv_mode;
    
    uint32_t multi_mode;
    uint32_t phy_mode;
};

uint32_t __svc(0) case_low_init(void);
uint32_t __svc(1) case_init(void);
uint32_t __svc(2) case_evt_read(uint8_t *data);
uint32_t __svc(3) case_write(uint32_t profile, uint8_t *data, uint8_t len, uint8_t ack);

// 5A Len 00 00 xx xx xx xx
uint32_t __svc(4) case_evt_hs_read(uint8_t *data, uint32_t id);
uint32_t __svc(5) case_evt_hs_ack(uint8_t *data, uint8_t length, uint8_t ack);
uint32_t __svc(6) case_evt_hs_ack_fifo_register(void *fifo);

uint32_t __svc(7) case_clock_request(uint32_t on);

uint32_t __svc(8) case_config_read(void *config);
uint32_t __svc(9) case_config_update(void *config);
uint32_t __svc(10) case_rssi_read(void);

void case_process(void);

#endif


