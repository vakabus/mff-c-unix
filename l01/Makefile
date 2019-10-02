CFILES=$(wildcard *.c)

build: $(CFILES)
	@for s in $(CFILES); do \
		echo "Building $$s" ; \
		gcc $(COMPILER_OPTIONS) -o $$(echo $$s | sed 's/\.c//').bin $$s ; \
	done

clean:
	rm -rf *.bin
