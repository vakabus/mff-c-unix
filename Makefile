SUBDIRS=l01


COMPILER_OPTIONS=-std=c99 -g -Wall -Wextra -pedantic -O0 -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer

latest:
	@for subdir in $(SUBDIRS); do \
	    $(MAKE) -C $$subdir ; \
	    break ; \
	done


all:
	$(foreach subdir,$(SUBDIRS),$(MAKE) -C $(subdir);)

clean:
	$(foreach subdir,$(SUBDIRS),$(MAKE) -C $(subdir) clean;)

.PHONY: all latest
