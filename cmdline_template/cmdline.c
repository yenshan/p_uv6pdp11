#define KL11_TTY_REG_ADDRESS 0177560;
#define TXRDY (1<<7)
#define NRETRY 5000

static volatile struct kl11_tty {
  int in_csr;
  int in_dbr;
  int out_csr;
  int out_dbr;
} *pkl11 = (struct kl11_tty*)KL11_TTY_REG_ADDRESS;

void bzero(char *, int);
void putchar(const int);
void puts(const char*);
int getchar(void);
int getline(char *);


int cstart()
{
  char buf[256];

  bzero(buf, sizeof(buf));
  do {
	  puts("> ");
	  if(getline(buf)>0) {
		  puts("\r\n");
		  puts(buf);
		  bzero(buf, sizeof(buf));
	  }
	  puts("\r\n");
  } while(1);
}

void putchar(const int c)
{
	while(!(pkl11->out_csr & TXRDY))
		;
	pkl11->out_dbr = c;
}

void puts(const char *s)
{
  while(*s)
    putchar(*s++);
}

int getchar()
{
  while(!(pkl11->in_csr & TXRDY))
	  ;
  return pkl11->in_dbr;
}

int getline(char *buf)
{
	char c;
	int nc = 0;

	while((c=getchar()) != '\r') {
		putchar(c);
		*buf++ = c;
		nc++;
	}
	return nc;
}

void bzero(char *buf, int len)
{
	while(len--)
		*buf++ = 0;
}

