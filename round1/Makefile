
IDIR=include
CC=g++
CFLAGS=-I$(IDIR) -I./ -Wall -O2 -Wextra

ex1: main1.cpp 
	$(CC) -o $@.exe $(CFLAGS) $<

ex1v1: main1v1.cpp
	$(CC) -o $@.exe $(CFLAGS) $<

ex2: ex2.cpp
	$(CC) -o $@.exe $(CFLAGS) $@.cpp

ex3: ex3.cpp
	$(CC) -o $@.exe $(CFLAGS) $@.cpp

ex4: ex4.cpp
	$(CC) -o $@.exe $(CFLAGS) $@.cpp

ex5: ex5.cpp
	$(CC) -o $@.exe $(CFLAGS) $@.cpp

ex6: ex6.cpp
	$(CC) -o $@.exe $(CFLAGS) $@.cpp

ex7: ex7.cpp
	$(CC) -o $@.exe $(CFLAGS) $@.cpp

tester: tester.cpp
	$(CC) -o $@.exe $(CFLAGS) $@.cpp

.PHONY: clean

clean:
	rm -f *.exe
