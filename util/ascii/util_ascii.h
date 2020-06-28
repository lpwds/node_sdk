/*


*/
#ifndef UTIL_ASCII__
#define UTIL_ASCII__

#include <stdint.h>

uint16_t util_16host2net(uint16_t data);
uint16_t util_16net2host(uint16_t data);

uint32_t util_32host2net(uint32_t data);
uint32_t util_32net2host(uint32_t data);

uint32_t hexString_to_bin(uint8_t *out, uint8_t *data, uint32_t len);
uint32_t bin_to_hexString(uint8_t *out, uint8_t *data, uint32_t len);

#endif

