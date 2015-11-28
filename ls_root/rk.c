#include "types.h"

typedef struct {
    uint16_t rkds; // Drive Status Register 
    uint16_t rker; // Error Register
    uint16_t rkcs; // Control Status Register
    uint16_t rkwc; // Word Count Register
    uint16_t rkba; // Bus Address Register
    uint16_t rkda; // Disk Address Register
} RK11register_t;

#define RK11_CTL_REG_ADDR (0177400)
static volatile RK11register_t *rk11_p = (RK11register_t*)RK11_CTL_REG_ADDR;

enum rk11_cs {
    CS_GO         = (1),
    CS_WRITE      = (1<<1),
    CS_READ       = (1<<2),
    CS_READ_RDY   = (1<<7)
};

void
read_blk(int drv_no, int blk_no, volatile void *dst_buf)
{
    static const int NUM_READ_WORDS=256;
    uint16_t cylnder = (blk_no / 12) >> 1;
    uint16_t surface = (blk_no / 12) & 1;
    uint16_t sector  = (blk_no % 12);

    rk11_p->rkda = (drv_no << 13) | (cylnder << 5) | (surface << 4) | sector;
    rk11_p->rkba = (uint16_t)dst_buf;
    rk11_p->rkwc = -(NUM_READ_WORDS);
    rk11_p->rkcs = CS_READ | CS_GO;

    while(!(rk11_p->rkcs & CS_READ_RDY))
        ;
}

