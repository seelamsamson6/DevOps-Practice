TOPDIR = $(shell pwd)

VERSION := 0.0

CROSS_COMPILE ?=
O ?= $(TOPDIR)

o := $(O)/

CC ?= $(CROSS_COMPILE)gcc
AR ?= $(CROSS_COMPILE)ar
INSTALL ?= install

# install directories
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
INCLUDEDIR ?= $(PREFIX)/include
LIBDIR ?= $(PREFIX)/lib

ALL_TARGETS :=
CLEAN_TARGETS :=

IS_GIT := $(shell if [ -d .git ] ; then echo yes ; else echo no; fi)
ifeq ($(IS_GIT),yes)
VERSION := $(shell git describe --abbrev=8 --dirty --always --tags --long)
endif

cflags_for_lib = $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_LIBDIR) pkg-config --cflags $(1))
ldflags_for_lib = $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_LIBDIR) pkg-config --libs $(1))

# let the user override the default CFLAGS/LDFLAGS
CFLAGS ?= -O2
LDFLAGS ?=

LIBS += $(call ldflags_for_lib,glib-2.0)
CFLAGS += $(call cflags_for_lib,glib-2.0)

MY_CFLAGS := $(CFLAGS)
MY_CFLAGS += -DVERSION=\"$(VERSION)\"
MY_CFLAGS += -I/usr/include
MY_CFLAGS += -I$(TOPDIR)/include
MY_CFLAGS += -I$(TOPDIR)/src

MY_LDFLAGS := $(LDFLAGS)

tar_CFLAGS += $(call cflags_for_lib,zlib)
tar_LDFLAGS += -L/usr/lib/x86_64-linux-gnu -larchive
tar_LIBS += $(call ldflags_for_lib,zlib)

tests_CFLAGS := -Isrc/ -Wno-missing-field-initializers

define compile_tgt
	@mkdir -p $(dir $@)
	$(CC) -MD -MT $@ -MF $(@:.o=.d) $(CPPFLAGS) $($(1)_CPPFLAGS) $(MY_CFLAGS) $($(1)_CFLAGS) -c -o $@ $<
endef

define link_tgt
	$(CC) $(MY_LDFLAGS) $($(1)_LDFLAGS) -o $@ $(filter-out %.a,$^) -L/ $(addprefix -l:,$(filter %.a,$^)) $(LIBS) $($(1)_LIBS)
endef

MY_CFLAGS += -Wall -Werror -W -O2

ifeq ($(DEBUG),1)
	MY_CFLAGS += -g -O0
endif

ifeq ($(COVERAGE),1)
	MY_CFLAGS += --coverage
	MY_LDFLAGS += --coverage
endif

DEPS := $(shell find $(o) -name '*.d')

all: real-all

include src/src.mk
include tools/tools.mk
include tests/tests.mk

real-all: $(ALL_TARGETS)

.PHONY: $(CLEAN_TARGETS) clean
clean: $(CLEAN_TARGETS)
	rm -f $(DEPS)

.PHONY: $(INSTALL_TARGETS) install
install: $(INSTALL_TARGETS)

-include $(DEPS)
