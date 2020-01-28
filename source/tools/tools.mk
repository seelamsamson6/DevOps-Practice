ALL_TARGETS += $(o)tools/example $(o)tools/spawn $(o)tools/tar
CLEAN_TARGETS += clean-tools
INSTALL_TARGETS += install-tools


example_SOURCES := tools/example.c
example_OBJECTS := $(addprefix $(o),$(example_SOURCES:.c=.o))

$(o)tools/%.o: $(example_SOURCES)
	$(call compile_tgt,dll)

$(o)tools/example: $(example_OBJECTS) $(o)src/libdll.a
	$(call link_tgt,dll)


spawn_SOURCES := tools/spawn.c
spawn_OBJECTS := $(addprefix $(o),$(spawn_SOURCES:.c=.o))

$(o)tools/%.o: $(example_spawn)
	$(call compile_tgt,spawn)

$(o)tools/spawn: $(spawn_OBJECTS)
	$(call link_tgt,spawn)


tar_SOURCES := tools/tar.c
tar_OBJECTS := $(addprefix $(o),$(tar_SOURCES:.c=.o))

$(o)tools/%.o: $(example_tar)
	$(call compile_tgt,tar)

$(o)tools/tar: $(tar_OBJECTS)
	$(call link_tgt,tar)


clean-tools:
	rm -f $(example_OBJECTS) \
		$(example_OBJECTS) \
		$(ALL_TARGETS)

install-tools: $(o)tools/example
	$(INSTALL) -d -m 0755 $(DESTDIR)$(BINDIR)
	$(INSTALL) -m 0755 $(o)tools/example $(DESTDIR)$(BINDIR)/
