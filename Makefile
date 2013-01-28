# Tool settings
CC=g++
DB=gdb
OPENMP=yes
DEBUG=yes
AA=no

# Test files
FPOINT=./dat/test_polar_727902.txt
FCONTOUR=./dat/Polar_Cone.txt

# Main program
TARGET=pq

ifeq ($(OPENMP),yes)
MODE=parallel
CORE=pq_core_openmp
else
MODE=sequential
CORE=pq_core
endif

ifeq ($(DEBUG),yes)
DBFLAG=-g
else
DBFLAB=
endif

ifeq ($(AA),yes)
LIBYALAA=/usr/local/lib/libyalaa.so /usr/local/cxsc/lib/libcxsc.so
OBJ=$(TARGET)_aa
else
LIBYALAA=
OBJ=$(TARGET)
endif

CCFLAGS=-O3 -Wall -I/usr/local/cxsc/include -I./headers -D=$(MODE) $(DBFLAG)
CLFLAGS=-lm

all: $(OBJ)

pq_io.o: ./src/pq_io.cpp
	$(CC) $(CCFLAGS) -c $^ -o $@

pq_wrapper.o: ./src/pq_wrapper.cpp
	$(CC) $(CCFLAGS) -c $^ -o $@

$(CORE).o: ./src/$(CORE).cpp
	$(CC) $(CCFLAGS) -c $^ -o $@

$(OBJ).o: ./src/$(TARGET).cpp
	$(CC) $(CCFLAGS) -c $^ -o $@

$(OBJ): $(OBJ).o $(CORE).o pq_wrapper.o pq_io.o $(LIBYALAA)
	$(CC) $^ -o $@ $(CLFLAGS)

debug: $(OBJ)
	$(DB) --args ./$(OBJ) 0 $(FPOINT) $(FCONTOUR) 0 11

run: $(OBJ)
	./$(OBJ) 0 $(FPOINT) $(FCONTOUR) 0 11

clean:
	rm -f $(OBJ) *.o *~ ./headers/*~ ./src/*~ ./dat/*~
