CFLAGS=-std=c99 -g -Wall -Wextra -pedantic -O0
SANITIZER=-fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer

CFILES=$(wildcard *.c)

build: $(CFILES)
	@for s in $(CFILES); do \
		echo "Building $$s" ; \
		scan-build gcc $(CFLAGS) $(SANITIZER) -o $$(echo $$s | sed 's/\.c//').bin $$s ; \
	done

.PHONY: debug
debug: $(CFILES)
	@for s in $(CFILES); do \
		echo "Building $$s" ; \
		gcc $(CFLAGS) -o $$(echo $$s | sed 's/\.c//').bin $$s ; \
	done

clean:
	rm -rf *.bin
