CLEAN_TARGETS += clean-libdll
INSTALL_TARGETS += install-libdll

dll_SOURCES := $(wildcard src/*.c)
dll_OBJECTS := $(addprefix $(o),$(dll_SOURCES:.c=.o))

$(o)src/%.o: $(dll_SOURCES)
	$(call compile_tgt,dll)

$(o)src/libdll.a: $(dll_OBJECTS)
	$(AR) rcs $@ $^

clean-libdll:
	rm -f $(dll_OBJECTS) $(o)src/libdll.a

install-libdll: $(o)src/libdll.a
	$(INSTALL) -d -m 0755 $(DESTDIR)$(LIBDIR)
	$(INSTALL) -d -m 0755 $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL) -m 0644 $(o)src/libdll.a $(DESTDIR)$(LIBDIR)/
	$(INSTALL) -m 0644 include/dll.h $(DESTDIR)$(INCLUDEDIR)/
