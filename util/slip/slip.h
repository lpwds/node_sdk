/*


*/
#ifndef SLIP_H__
#define SLIP_H__

#define SLIP_FRAME_MAX_SIZE     128

typedef void (*on_frame_recv_handler_t)(void *args, int len);

struct slip_info_t 
{
    int received;
    int esc_flag;
    int rxing;
	on_frame_recv_handler_t handler;
    unsigned char p[SLIP_FRAME_MAX_SIZE];
};

//typedef void (*on_frame_recv_handler_t)(struct slip_info_t *slip, int len);

void recv_package(struct slip_info_t *slip, unsigned char c);

int build_packet(unsigned char *out, unsigned char *p, int len);
void slip_register(struct slip_info_t *slip, on_frame_recv_handler_t handler);
void slip_init(struct slip_info_t *slip);

#endif

