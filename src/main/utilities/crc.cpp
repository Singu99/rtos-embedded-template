#include "crc.hpp"


uint16_t crc16_ccitt(uint16_t crc, unsigned char a)
{
    crc ^= (uint16_t)a << 8;
    for (int ii = 0; ii < 8; ++ii) {
        if (crc & 0x8000) {
            crc = (crc << 1) ^ 0x1021;
        } else {
            crc = crc << 1;
        }
    }
    return crc;
}

uint16_t crc16_ccitt_update(uint16_t crc, const void *data, uint32_t length)
{
    const uint8_t *p = (const uint8_t *)data;
    const uint8_t *pend = p + length;

    for (; p != pend; p++) {
        crc = crc16_ccitt(crc, *p);
    }
    return crc;
}

uint8_t crc8_calc(uint8_t crc, unsigned char a, uint8_t poly)
{
    crc ^= a;
    for (int ii = 0; ii < 8; ++ii) {
        if (crc & 0x80) {
            crc = (crc << 1) ^ poly;
        } else {
            crc = crc << 1;
        }
    }
    return crc;
}

uint8_t crc8_update(uint8_t crc, const void *data, uint32_t length, uint8_t poly)
{
    const uint8_t *p = (const uint8_t *)data;
    const uint8_t *pend = p + length;

    for (; p != pend; p++) {
        crc = crc8_calc(crc, *p, poly);
    }
    return crc;
}


uint8_t crc8_xor_update(uint8_t crc, const void *data, uint32_t length)
{
    const uint8_t *p = (const uint8_t *)data;
    const uint8_t *pend = p + length;

    for (; p != pend; p++) {
        crc ^= *p;
    }
    return crc;
}



// Fowler–Noll–Vo hash function; see https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
uint32_t fnv_update(uint32_t hash, const void *data, uint32_t length)
{
    const uint8_t *p = (const uint8_t *)data;
    const uint8_t *pend = p + length;

    for (; p != pend; p++) {
        hash *= FNV_PRIME;
        hash ^= *p;
    }

    return hash;
}

