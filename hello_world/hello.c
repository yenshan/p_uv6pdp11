#define KL11_TTY_REG_ADDRESS 0177564;
#define TXRDY (1<<7)

static volatile struct kl11_tty {
	  int out_csr;
	    int out_dbr;
} *pkl11 = (struct kl11_tty*)KL11_TTY_REG_ADDRESS;

int putchar(int c)
{
	  while(!(pkl11->out_csr & TXRDY))
		      ;
	    pkl11->out_dbr = c;
}
int puts(unsigned char *s)
{
	  while(*s)
		      putchar(*s++);
	    return 0;
}
int cstart()
{
	  puts("Hello, World!\n\r");
	    while(1);
}
