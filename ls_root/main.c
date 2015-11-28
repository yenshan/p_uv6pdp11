#include "ino.h"

#define BLOCK_SIZE 512

extern void read_blk(int drv_no, int blk_no, volatile void *dst_buf);
extern void putchar(const int);
extern void puts(const char*);
extern int getchar(void);
extern int getline(char *);

typedef enum {
    IGET_OK,
    IGET_ERROR
} IgetResultT;

IgetResultT
iget(int ino, inode_t *dst_ibuf)
{
    void memcpy(void *dst, void *src, int n);
    static const int inode_start_block = 2;
    static const int inodes_per_block = BLOCK_SIZE / sizeof(inode_t);

    if (ino <= 0)
       return IGET_ERROR;

    static char _buf[BLOCK_SIZE];
    int blk_no = inode_start_block + (ino-1) / inodes_per_block;
    read_blk(0, blk_no, _buf);
    
    int i_offset = ((ino-1) % inodes_per_block) * sizeof(inode_t);
    memcpy(dst_ibuf, _buf+i_offset, sizeof(inode_t));

    return IGET_OK; 
}

typedef struct {
  uint16_t ino;
  char name[14];
} dir_t;

int 
cstart()
{
  // get root's inode info
  inode_t inode;
  iget(1, &inode);

  // print file name in root directory
  dir_t dir_info[BLOCK_SIZE/sizeof(dir_t)],
        *dirp = dir_info;
  read_blk(0, inode.i_addr[0], (void*)dir_info);
  do {
      if (dirp->name[0] == '\0') break;
      puts (dirp->name); puts("\n\r");
      dirp++;
  } while (dirp < (dir_info+BLOCK_SIZE));

  while(1);
}

void
memcpy(void *dst, void *src, int n)
{
    while(n--)
        *(char*)dst++ = *(char*)src++;
}

