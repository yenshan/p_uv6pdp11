TARGET = aout2simhbin
OBJS = main.o 

CC = gcc
CFLAGS = -std=c99

all: 		$(TARGET)

$(TARGET):	$(OBJS)
			$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)

.c.o:		$<
			$(CC) -c $(CFLAGS) $<

clean:
			rm -f $(OBJS) $(TARGET)

