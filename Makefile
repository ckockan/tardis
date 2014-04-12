CC=gcc
CFLAGS = -c -O2 -g -I htslib
LDFLAGS = htslib/libhts.a  -lz -lm -lpthread
SOURCES = tardis.c cmdline.c common.c processbam.c 
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = tardis

all: $(SOURCES) $(EXECUTABLE)
	rm -rf *.o

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -f $(EXECUTABLE) *.o *~

libs:
	make clean -C htslib
	make -C htslib
	
