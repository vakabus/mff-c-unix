SUBDIRS=l01


latest:
	@for subdir in $(SUBDIRS); do \
	    $(MAKE) -C $$subdir ; \
	    break ; \
	done

%:
	$(foreach subdir,$(SUBDIRS),$(MAKE) -C $(subdir) $@;)

.PHONY: latest %
