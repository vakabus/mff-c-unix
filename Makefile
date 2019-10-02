SUBDIRS=l01


export CFLAGS=-std=c99 -g -Wall -Wextra -pedantic -O0
export SANITIZER=-fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer

latest:
	@for subdir in $(SUBDIRS); do \
	    $(MAKE) -C $$subdir ; \
	    break ; \
	done

%:
	$(foreach subdir,$(SUBDIRS),$(MAKE) -C $(subdir) $@;)

.PHONY: latest %
