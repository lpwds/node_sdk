/*


*/
#include "util_ascii.h"

#include <ctype.h>

union union32
{
	uint32_t data;
	uint8_t b[4];
};

uint32_t util_32host2net(uint32_t data)
{
	union union32 d0, d1;

	d0.data = data;
	d1.b[0] = d0.b[3];
	d1.b[1] = d0.b[2];
	d1.b[2] = d0.b[1];
	d1.b[3] = d0.b[0];
	return d1.data;
}

uint32_t util_32net2host(uint32_t data)
{
	union union32 d0, d1;

	d0.data = data;
	d1.b[0] = d0.b[3];
	d1.b[1] = d0.b[2];
	d1.b[2] = d0.b[1];
	d1.b[3] = d0.b[0];
	return d1.data;
}

union union16
{
	uint16_t data;
	uint8_t b[2];
};

uint16_t util_16host2net(uint16_t data)
{
	union union16 d0, d1;

	d0.data = data;
	d1.b[0] = d0.b[1];
	d1.b[1] = d0.b[0];

	return d1.data;
}

uint16_t util_16net2host(uint16_t data)
{
	union union16 d0, d1;

	d0.data = data;
	d1.b[0] = d0.b[1];
	d1.b[1] = d0.b[0];
    
	return d1.data;
}

static uint32_t check_hexchar(uint8_t ch)
{
    if( ('0'<=ch) && (ch <='9') ) {
        return 0;
    }
    if( ('a'<=ch) && (ch <='f') ) {
        return 0;
    }
    if( ('A'<=ch) && (ch <='F') ) {
        return 0;
    }
    return 1;
}

static uint8_t one_hexchar_to_bin(uint8_t h)
{
	uint8_t x = 0;
	if (isdigit(h)) {
		x = h - '0';
	} else if (isupper(h)) {
		x = h - 'A' + 10;
	} else {
		x = h - 'a' + 10;
	}
	return x;
}

static uint8_t hexString[] = "0123456789ABCDEF";

uint32_t bin_to_hexString(uint8_t *out, uint8_t *data, uint32_t len)
{
	uint32_t out_len = 0;
	uint32_t i = 0;

	for(i=0; i<len; i++) {
		uint8_t temp = data[i];
		out[out_len++] = hexString[(temp>>4) & 0x0F];
		out[out_len++] = hexString[temp & 0x0F];
	}
	return out_len;
}

uint32_t hexString_to_bin(uint8_t *out, uint8_t *data, uint32_t len)
{
	uint32_t out_len = len>>1;
	uint32_t i = 0;
	uint32_t j = 0;
	uint8_t ch = 0;
    uint32_t is_hex = 0;
	for(i=0; i<out_len; i++){
        ch = data[j++];
        is_hex = check_hexchar(ch);
        if(is_hex != 0) {
            return 0;
        }
		uint8_t temph = one_hexchar_to_bin(ch) & 0x0f;
        
        ch = data[j++];
        is_hex = check_hexchar(ch);
        if(is_hex != 0) {
            return 0;
        }
		uint8_t templ = one_hexchar_to_bin(ch) & 0x0f;
        
		out[i] = temph << 4 | templ;
	}
	return out_len;
}
