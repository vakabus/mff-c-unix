CFLAGS=-std=c99 -Wall -Wextra -pedantic 
CFLAGS_SANITIZER=-fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer


all: libmin.so main-shared

libmin.o: libmin.c libmin.h
	$(CC) $(CFLAGS) -c libmin.c

main.o: main.c libmin.h
	$(CC) $(CFLAGS) -c main.c

main: main.o libmin.o
	$(CC) $(CFLAGS) -o main libmin.o main.o

libmin.so: libmin.o
	# fpic a shared tam musi byt, aby je dynamicky linker mohl presouvat
	$(CC) $(CFLAGS) -shared -fpic -o libmin.so libmin.o

main-shared: libmin.so main.o
	ld main.o libmin.so -lc -rpath=$(PWD) -o main-shared /usr/lib/Scrt1.o
	$(CC) $(CFLAGS) main.o -lmin -L. -lc -Xlinker -rpath=$(PWD) -o main-shared

.PHONY: clean
clean:
	-rm *.o
	-rm *.so
	-rm main
	-rm main-shared


# verifiing that the binary is ok
#  file, readelf -d, nm (vypisuje exportovane symboly)
