#/*!
#* \file Makefile
#* \brief Makefile for compiling prj-tg-font-cache library
#* and generating pkgconfig file
#* and making install & uninstall
#*
#* Copyright of Timo Hannukkala. All rights reserved.
#*
#* \author Timo Hannukkala <timohannukkala@hotmail.com>
#*/
TARGET:=libprj-tg-font-cache.so
VERSION:=0.1
PREFIX:=/usr
LIBDIR:= $(PREFIX)/lib
PKGCONFIGDIR:=$(LIBDIR)/pkgconfig
PKGCONFIGFILE:=prj-tg-font-cache-lib
CCX:=$(if $(CCX),$(CCX),g++)
PKG_CFLAGS:=$(shell pkg-config --cflags prj-ttf-reader)
PKG_LIBS:=$(shell pkg-config --libs prj-ttf-reader)
CXXFLAGS+=$(PKG_CFLAGS)
CXXFLAGS+=-Wuninitialized -Wconversion -Wshadow -Wpointer-arith \
	-Wswitch-default -Wswitch-enum -Wcast-align \
	-Wundef -Wcast-qual -Wunreachable-code -Wfloat-equal \
	-Wredundant-decls -Wextra -Wall
CXXFLAGS+=-Werror
CXXFLAGS+=-O2
CXXFLAGS+=-g -fPIC -std=c++17
LDFLAGS+=-shared $(PKG_LIBS)
GLFW:=$(if $(USE_GLFW),$(USE_GLFW),off)

CURRENT_DIR=$(dir $(abspath $(lastword $(MAKEFILE_LIST))))

src_SRCDIR:=$(CURRENT_DIR)src
src_SRCS:=$(wildcard $(src_SRCDIR)/*.cpp)
src_OBJS:=$(src_SRCS:.cpp=.o)

src_private_SRCDIR:=$(CURRENT_DIR)src/private
src_private_SRCS:=$(wildcard $(src_private_SRCDIR)/*.cpp)
src_private_OBJS:=$(src_private_SRCS:.cpp=.o)

src_private_list_character_SRCDIR:=$(CURRENT_DIR)src/private/list_character
src_private_list_character_SRCS:=$(wildcard $(src_private_list_character_SRCDIR)/*.cpp)
src_private_list_character_OBJS:=$(src_private_list_character_SRCS:.cpp=.o)

.PHONY: all default clean install uninstall
all: default

default: $(src_OBJS) $(src_private_OBJS) $(src_private_list_character_OBJS)
	$(CCX) $(src_OBJS) $(src_private_OBJS) $(src_private_list_character_OBJS) $(LDFLAGS) -o $(TARGET)

$(src_OBJS):%.o: %.cpp
	$(CCX) $(CXXFLAGS) -c $< -o $@

$(src_private_OBJS):%.o: %.cpp
	$(CCX) $(CXXFLAGS) -c $< -o $@

$(src_private_list_character_OBJS):%.o: %.cpp
	$(CCX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.so
	rm -f $(src_private_list_character_SRCDIR)/*.o
	rm -f $(src_private_SRCDIR)/*.o
	rm -f $(src_SRCDIR)/*.o

install: $(PKGCONFIGDIR)/$(PKGCONFIGFILE).pc
	mkdir -p $(DESTDIR)$(LIBDIR)/prj-tg-font-cache
	install -m 0755 lib*.so $(DESTDIR)$(LIBDIR)/prj-tg-font-cache
	mkdir -p $(DESTDIR)$(PREFIX)/include/prj-tg-font-cache
	install -m 0644 src/prj_tg_font_cache.h $(DESTDIR)$(PREFIX)/include/prj-tg-font-cache/

$(PKGCONFIGDIR)/$(PKGCONFIGFILE).pc:
	@echo "installing $(PKGCONFIGDIR)/$(PKGCONFIGFILE).pc"
	@echo "prefix=$(PREFIX)" > $@
	@echo "exec_prefix=\$${prefix}" >> $@
	@echo "libdir=\$${prefix}/lib/prj-tg-font-cache" >> $@
	@echo "includedir=\$${prefix}/include/prj-tg-font-cache" >> $@
	@echo "" >> $@
	@echo "Name: prj-tg-font-cache" >> $@
	@echo "Description: prj-tg-font-cache cache for fonts lib" >> $@
	@echo "Version: $(VERSION)" >> $@
	@echo "Cflags: -I\$${includedir}" >> $@
	@echo "Libs: -L\$${libdir} -lprj-tg-font-cache -Wl,--rpath=\$${libdir}" >> $@

uninstall:
	rm -rf $(LIBDIR)/prj-tg-font-cache
	rm -rf $(PREFIX)/include/prj-tg-font-cache
	rm -f $(PKGCONFIGDIR)/$(PKGCONFIGFILE).pc
