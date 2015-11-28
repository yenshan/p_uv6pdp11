TARGET = cmdline
OBJS = start.o $(TARGET).o
CC = pdp11-aout-gcc
AS = pdp11-aout-as

CFLAGS = -ffreestanding

all: $(TARGET).lda rc-pdp11

run: rc-pdp11
	pdp11 $<

rc-pdp11: $(TARGET).lda
	@echo "l " $< > rc-pdp11

$(TARGET).lda: $(TARGET).out
	aout2simhbin.rb $< $@

$(TARGET).out: $(OBJS) ld.script
	pdp11-aout-ld -T ld.script $(OBJS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.c.s:
	$(CC) -S $< -o $@

.S.o:
	$(AS) $< -o $@

clean:
	rm -f *.lda
	rm -f *.out
	rm -f *.o
	rm -f rc-pdp11
