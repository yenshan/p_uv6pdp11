#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint16_t  magic; 
    uint16_t  text; 
    uint16_t  data;
    uint16_t  bss;
    uint16_t  syms;
    uint16_t  entry;
    uint16_t  trsize;
    uint16_t  drsize;
} AoutHeader_t;

void
read_aout_data(char *buf, int size, FILE *f)
{
    if (size <= 0)
        return;
    fread(buf, size, 1, f);
}

int
chksum(void *dat, int size)
{
    int sum = 0;
    unsigned char *p = dat;
    while (p < (unsigned char*)(dat+size))
        sum += *p++;
    return sum;
}	

int
write_and_sum(void *dat, int size, FILE *f)
{
    if (dat == 0 || size == 0)
        return 0;
    fwrite(dat, size, 1, f); 
    return chksum(dat, size); 
}

int
write_blk_dat(const char *dat, int dat_size, uint16_t load_adr, FILE *f)
{
    struct {
        char d1;
        char d2;
        uint16_t block_size;
        uint16_t load_adr;
    } block_header = {
        1, 0,
        .block_size = dat_size+sizeof(block_header),
        .load_adr   = load_adr
    };
    int sum = 0;
    sum += write_and_sum((void*)&block_header, sizeof(block_header), f);
    sum += write_and_sum((void*)dat, dat_size, f);
    char csum = 0-(char)(sum & 0xff);
    fwrite(&csum, 1, 1, f);
    return (sizeof(block_header) + dat_size + 1);
}

int
main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s <a.out file> <target file>\n", argv[0]);
        return 1;
    }
    const char  *fn_aout = argv[1],
                *fn_save = argv[2];

    AoutHeader_t h_aout;
    FILE *f = fopen(fn_aout, "r");
    fread(&h_aout, sizeof(h_aout), 1, f); /* only little endian is OK */

    char text_buf[h_aout.text], 
         data_buf[h_aout.data];
    read_aout_data(text_buf, sizeof(text_buf), f);
    read_aout_data(data_buf, sizeof(data_buf), f); 

    fclose(f);

    FILE *tf = fopen(fn_save, "w+");
    write_blk_dat(text_buf, 
                  sizeof(text_buf), 
                  h_aout.entry, 
                  tf);
    write_blk_dat(data_buf, 
                  sizeof(data_buf), 
                  h_aout.entry + sizeof(text_buf),
                  tf);

    /* last block only has entry point address */
    write_blk_dat(0, 0, h_aout.entry, tf);
    fclose(tf);
}
