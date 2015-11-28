#include "types.h"

typedef struct inode {
  uint16_t i_mode;
  char i_nlink;
  char i_uid;
  char i_gid;
  char i_size0;
  uint16_t i_size1;
  uint16_t i_addr[8];
  int16_t i_atime[2];
  int16_t i_mtime[2];
} inode_t;

/* modes */
#define	IALLOC	0100000 // 0x1000
#define	IFMT	060000  // 0x6000
#define	IFDIR	040000  // 0x800
#define	IFCHR	020000  // 0x2000
#define	IFBLK	060000  // 0x6000
#define	ILARG	010000  // 0x1000
#define	ISUID	04000   // 0x800
#define	ISGID	02000   // 0x400
#define ISVTX	01000   // 0x200
#define	IREAD	0400    // 0x100
#define	IWRITE	0200    // 0x80
#define	IEXEC	0100    // 0x40
