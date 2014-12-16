
IDIR=include
CC=g++
CFLAGS=-I$(IDIR) -I./ -Wall -O2 -Wextra

ex9: ex9.cpp 
	$(CC) -o $@.exe $(CFLAGS) $<

ex10: ex10.cpp
	$(CC) -o $@.exe $(CFLAGS) -lssl -lm -lcrypto $@.cpp

ex11: ex11.cpp
	$(CC) -o $@.exe $(CFLAGS) $@.cpp

ex12: ex12.cpp
	$(CC) -o $@.exe $(CFLAGS) $@.cpp

ex13: ex13.cpp
	$(CC) -o $@.exe $(CFLAGS) $@.cpp

ex14: ex14.cpp
	$(CC) -o $@.exe $(CFLAGS) $@.cpp

ex15: ex15.cpp
	$(CC) -o $@.exe $(CFLAGS) -lssl -lm -lcrypto $@.cpp

ex16: ex16.cpp
	$(CC) -o $@.exe $(CFLAGS) -lssl -lm -lcrypto $@.cpp

tester: tester.cpp
	$(CC) -o $@.exe $(CFLAGS) $@.cpp

.PHONY: clean

clean:
	rm -f *.exe
