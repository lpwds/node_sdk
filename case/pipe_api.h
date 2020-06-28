/*



*/
#ifndef PIPE_API_H__
#define PIPE_API_H__

#include <stdint.h>

#if defined ( __CC_ARM )

#define PACKED(TYPE) __packed TYPE
#define PACKED_STRUCT PACKED(struct)

#elif defined   ( __GNUC__ )

#define PACKED __attribute__((packed))
#define PACKED_STRUCT struct PACKED

#elif defined (__ICCARM__)

#define PACKED_STRUCT __packed struct

#endif


#define PIPE_EVT_NULL               0x00
#define PIPE_EVT_ON_CONNECT         0x01
#define PIPE_EVT_ON_DISCONNECT      0x02
#define PIPE_EVT_ON_DATA            0x03
#define PIPE_EVT_ON_BEACON          0x04   
#define PIPE_EVT_ON_SEND_OK         0x05
#define PIPE_EVT_ON_ACK             0x06
#define PIPE_EVT_ON_POLL            0x07
#define PIPE_EVT_ON_ADV_RESP        0x08
#define PIPE_EVT_ON_ADV             0x09
#define PIPE_EVT_ON_INIT            0x0A
#define PIPE_EVT_ON_HS_DATA         0x0B
#define PIPE_EVT_ON_HS_ACK          0x0C

#define PIPE_EVT_SIZE               32

PACKED_STRUCT pipe_header_t
{
    uint8_t evt_id;
    uint8_t data[PIPE_EVT_SIZE-1];
};

PACKED_STRUCT pipe_evt_beacon_t
{
    uint8_t evt_id;
    uint32_t beacon_cnt;
    uint8_t payload[4];
    uint8_t length;
    uint8_t res[PIPE_EVT_SIZE - 10];
};

PACKED_STRUCT pipe_evt_data_t
{
    uint8_t evt_id;
    uint32_t profile;
    uint8_t length;
    uint8_t payload[16];
    uint8_t res[PIPE_EVT_SIZE - 22];
};

PACKED_STRUCT pipe_evt_adv_resp_t
{
    uint8_t evt_id;
    uint8_t op;
    uint16_t panid;
    uint32_t token;
    uint8_t res[PIPE_EVT_SIZE - 8];
};

PACKED_STRUCT pipe_evt_hs_data_t
{
    uint8_t evt_id;
    uint8_t fifo_id;
    uint8_t data[PIPE_EVT_SIZE-2];
};

PACKED_STRUCT pipe_evt_hs_ack_t
{
    uint8_t evt_id;
    uint16_t ack_id;
    uint8_t data[PIPE_EVT_SIZE-3];
};

#endif



