CC = arm-linux-gnueabihf-gcc
CPP = arm-linux-gnueabihf-g++

OBJSH = cf_stub.o pynq_dma.o portinfo.o 
LIBS = -l pthread /usr/lib/libsds_lib.so
INC = -I include/

all:	
	# $(CC) -fPIC $(INC) -c -g3 -gstabs devreg.c
	$(CC) -fPIC $(INC) -c -g3 -gstabs cf_stub.c
	$(CC) -fPIC $(INC) -c -g3 -gstabs pynq_dma.cpp
	$(CC) -fPIC $(INC) -c -g3 -gstabs portinfo.c
	$(CPP) -g3 -gstabs -shared -fPIC -rdynamic $(OBJSH)  -Wl,--start-group $(LIBS) -Wl,--end-group -o libpynq_dma.so
	rm *.o

clean:
	rm -f *.so *.o

