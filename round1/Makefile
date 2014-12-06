
IDIR=../include
CC=g++
CFLAGS=-I$(IDIR) -Wall -O2 -Wextra

ODIR=obj
DEPS=

%.o: %.c $(DEPS)
  $(CC) -c -o $@ $< $(CFLAGS)

1:  






.PHONY: clean

clean:
  rm -f $(ODIR)/*.o
