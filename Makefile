#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

include Makefile.mk

all: libs plugins gen

# --------------------------------------------------------------

PREFIX  ?= /usr/local
DESTDIR ?=

# --------------------------------------------------------------

libs:
ifeq ($(HAVE_DGL),true)
	$(MAKE) -C dpf/dgl
endif

plugins: libs
	$(MAKE) all -C plugins/WaveShaper

gen: plugins dpf/utils/lv2_ttl_generator
	@$(CURDIR)/dpf/utils/generate-ttl.sh
ifeq ($(MACOS),true)
	@$(CURDIR)/dpf/utils/generate-vst-bundles.sh
endif

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator

# --------------------------------------------------------------

clean:
ifeq ($(HAVE_DGL),true)
	$(MAKE) clean -C dpf/dgl
endif
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator

	$(MAKE) clean -C plugins/WaveShaper

# --------------------------------------------------------------

install:
	install -d $(DESTDIR)$(PREFIX)/lib/ladspa/
	install -d $(DESTDIR)$(PREFIX)/lib/dssi/
	install -d $(DESTDIR)$(PREFIX)/lib/lv2/
	install -d $(DESTDIR)$(PREFIX)/lib/vst/

	cp bin/*-ladspa.* $(DESTDIR)$(PREFIX)/lib/ladspa/
	cp bin/*-dssi.*   $(DESTDIR)$(PREFIX)/lib/dssi/
	cp bin/*-vst.*    $(DESTDIR)$(PREFIX)/lib/vst/

ifeq ($(HAVE_DGL),true)
	cp -r bin/*-dssi  $(DESTDIR)$(PREFIX)/lib/dssi/
endif
	cp -r bin/*.lv2   $(DESTDIR)$(PREFIX)/lib/lv2/

# --------------------------------------------------------------

.PHONY: plugins