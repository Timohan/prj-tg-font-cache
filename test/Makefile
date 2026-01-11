#/*!
#* \file Makefile
#* \brief Makefile for compiling
#*
#* Copyright of Timo hannukkala, Inc. All rights reserved.
#*
#* \author Timo Hannukkala <timohannukkala@hotmail.com>
#*/
TARGET:=prj_tg_font_cache_test
CXX:=$(if $(CXX),$(CXX),g++)
PKGFLAGS=`pkg-config --cflags --libs prj-ttf-reader`
PKGFLAGS+=`pkg-config --cflags --libs prj-tg-font-cache-lib`
CXXFLAGS+=-g -Wall -pedantic -c -pipe -std=gnu++17 -W -D_REENTRANT -fPIC
CXXFLAGS+=-I./src
CXXFLAGS+=$(PKGFLAGS)
CXXFLAGS+=-Wno-unused-parameter -Wuninitialized -Wconversion -Wshadow -Wpointer-arith \
	 -Wswitch-default -Wswitch-enum -Wcast-align \
	 -Winline -Wundef -Wcast-qual -Wunreachable-code -Wlogical-op -Wfloat-equal \
	 -Wredundant-decls -Werror \
	 -Wno-unused-const-variable
CXXFLAGS+=-DTEST_CASE
LDFLAGS:=$(PKGFLAGS)
# set current make dir
CURRENT_DIR=$(dir $(abspath $(lastword $(MAKEFILE_LIST))))

src_SRCDIR:=$(CURRENT_DIR)src
src_SRCS:=$(wildcard $(src_SRCDIR)/*.cpp)
src_OBJS:=$(src_SRCS:.cpp=.o)

src_libfiles_list_character_SRCDIR:=$(CURRENT_DIR)src/libfiles/list_character
src_libfiles_list_character_SRCS:=$(wildcard $(src_libfiles_list_character_SRCDIR)/*.cpp)
src_libfiles_list_character_OBJS:=$(src_libfiles_list_character_SRCS:.cpp=.o)

all: default

default: $(src_OBJS) $(src_libfiles_list_character_OBJS)
	$(CXX) $(src_OBJS) $(src_libfiles_list_character_OBJS) $(LDFLAGS) -o $(TARGET)

$(src_OBJS):%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(src_libfiles_list_character_OBJS):%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -f $(src_SRCDIR)/*.o
	rm -f $(src_libfiles_list_character_SRCDIR)/*.o
