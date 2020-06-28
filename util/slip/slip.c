/*


*/
#include "slip.h"

#include <stdio.h>
#include <string.h>

/* SLIP special character codes
*/
#define END             0xc0 //0300    /* indicates end of packet */
#define ESC             0xdb //0333    /* indicates byte stuffing */
#define ESC_END         0xdc //0334    /* ESC ESC_END means END data byte */
#define ESC_ESC         0xdd //0335    /* ESC ESC_ESC means ESC data byte */

static void check_index(struct slip_info_t *slip, int d)
{
    if(d<SLIP_FRAME_MAX_SIZE) {

    } else {
        slip->received = 0;
        slip->rxing = 0;
        slip->esc_flag = 0;
    }
}

void recv_package(struct slip_info_t *slip, unsigned char c)
{
    if(slip->esc_flag == 0) {

        switch(c) {
            case END:

                if(slip->received){
					if(slip->handler != NULL) {
						slip->handler(slip, slip->received);
					}
                    slip->rxing = 0;
                } else {
                    slip->rxing = 1;
                }
                slip->received = 0;
                break;

            case ESC:
                slip->esc_flag = 1;
                break;

            default:
                if(slip->rxing == 1) {
                    slip->p[slip->received++] = c;
                    check_index(slip, slip->received);
                }
                break;
        }
    }else{

        switch(c) {
            case ESC_END:
                slip->p[slip->received++] = END;
                check_index(slip, slip->received);
                break;

            case ESC_ESC:
                slip->p[slip->received++] = ESC;
                check_index(slip, slip->received);
                break;
        }
        slip->esc_flag = 0;
    }
}

/* SEND_PACKET: sends a packet of length "len", starting at
* location "p".
*/
int build_packet(unsigned char *out, unsigned char *p, int len)
{
    if( (out == NULL) || (p == NULL) ){
        return -1;
    }
    int out_cnt = 0;
    int p_cnt = 0;
    /* send an initial END character to flush out any data that may
    * have accumulated in the receiver due to line noise
    */
    out[out_cnt++] = END;

    /* for each byte in the packet, send the appropriate character
    * sequence
    */
    for(p_cnt=0; p_cnt<len; p_cnt++) {
        switch(p[p_cnt]) {
            /* if it's the same code as an END character, we send a
            * special two character code so as not to make the
            * receiver think we sent an END
            */
            case END:
                out[out_cnt++] = ESC;
                out[out_cnt++] = ESC_END;
                break;

            /* if it's the same code as an ESC character,
            * we send a special two character code so as not
            * to make the receiver think we sent an ESC
            */
            case ESC:
                out[out_cnt++] = ESC;
                out[out_cnt++] = ESC_ESC;
                break;

            /* otherwise, we just send the character
            */
            default:
                out[out_cnt++] = p[p_cnt];
        }
    }

    /* tell the receiver that we're done sending the packet
    */
    out[out_cnt++] = END;
    return out_cnt;
}

void slip_init(struct slip_info_t *slip)
{
	memset(slip, 0x00, sizeof(struct slip_info_t));
	slip->handler = NULL;
}

void slip_register(struct slip_info_t *slip, on_frame_recv_handler_t handler)
{
	slip->handler = handler;
}

#if 0
int main(void)
{
    unsigned char out[SLIP_FRAME_MAX_SIZE];
    unsigned char demo[SLIP_FRAME_MAX_SIZE];

    demo[0] = 0x02;
    demo[1] = 0xc0;
    demo[2] = 0xdb;
    demo[3] = 0xdc;
    demo[4] = 0xdd;

    int len = build_packet(out+4, demo, 5) +4;

    printf("\r\nTX: ");
    hex_print(out, len);
    printf("\r\n");

    //read from fifo;

    struct slip_info_t slip_info;
    memset(&slip_info, 0x00, sizeof(slip_info));

    int i = 0;
    for(i=0; i<64; i++) {
        recv_package(&slip_info, out[i]);
    }

    return 0;

}
#endif

