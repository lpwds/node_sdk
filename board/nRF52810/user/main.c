/*



*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nrf.h"
#include "nrf_nvmc.h"

#include "case_api.h"
#include "node_profile.h"
#include "simple_uart.h"

extern void check_flash_and_set_key(struct case_config_t *case_info);
struct case_config_t case_info;

static void __flash_protect_check(void)
{
    uint32_t temp = *(uint32_t *)0x10001208;
    
//    if( (temp & 0x000000FF) != 0x00) {
//        nrf_nvmc_write_word(0x10001208, 0xFFFFFF00);
//        uint32_t i=0;
//        for(i=0; i<0xffff; i++) {
//        }
//        NVIC_SystemReset();
//    }
    
    temp = *(uint32_t *)0x1000120C;
    
    if( (temp & 0x000000FF) != 0x00) {
        nrf_nvmc_write_word(0x1000120C, 0xFFFFFF00);
        uint32_t i=0;
        for(i=0; i<0xffff; i++) {
        }
        NVIC_SystemReset();
    }
}

int main(void)
{   
    case_low_init();
    __flash_protect_check();
    
    case_config_read(&case_info);
    case_info.adv_mode = 1;
    //case_info.phy_mode = 0x00010001;
    case_info.phy_mode = 0x00000001;
    //case_info.panid = 0xffff;
    
    case_config_update(&case_info);
    case_init();
    node_profile_init();
    
    while(1) {
        case_process();
        node_profile_process();
    }
    
}

