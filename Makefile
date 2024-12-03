CC=clang
CFLAGS=-Os -target i386-unknown-none-code16 -c
LINKER=ld
LDFLAGS=-m elf_i386

MOUNT=/mnt

-include config.mk

rect.com: com.ld rectangle.o dos.o graphics.o
	$(LINKER) $(LDFLAGS) -o $@ --script=$< $(filter-out $<, $^)

gdc.com: com.ld rectangle-gdc.o dos.o gdc.o
	$(LINKER) $(LDFLAGS) -o $@ --script=$< $(filter-out $<, $^)

com.ld: crt0.o
	touch com.ld

crt0.o: crt0.s
	$(CC) $(CFLAGS) -o $@ $<

rectangle.o: rectangle.c dos.h graphics.h
	$(CC) $(CFLAGS) -o $@ $<

rectangle-gdc.o: rectangle-gdc.c dos.h gdc.h
	$(CC) $(CFLAGS) -o $@ $<

dos.o: dos.c dos.h
	$(CC) $(CFLAGS) -o $@ $<

graphics.o: graphics.c graphics.h
	$(CC) $(CFLAGS) -o $@ $<

gdc.o: gdc.c gdc.h
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm *.com *.o

.PHONY: install
install: rect.com gdc.com
	cp rect.com $(MOUNT)
	cp gdc.com $(MOUNT)
	sync

.PHONY: format
format:
	clang-format -i --style=Chromium *.c *.h
