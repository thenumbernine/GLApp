DISTDIR_BASE=dist
DISTDIR=$(DISTDIR_BASE)/$(PLATFORM)/$(BUILD)
DIST=$(DISTDIR)/$(DIST_FILENAME)

SRCDIR_BASE=src
SOURCES=$(shell find $(SRCDIR_BASE) -type f -name *.cpp)
HEADERS=$(shell find include -type f)
OBJECTS=$(patsubst $(SRCDIR_BASE)/%.cpp, %.o, $(SOURCES))

OBJDIR_BASE=obj
OBJDIR=$(OBJDIR_BASE)/$(PLATFORM)/$(BUILD)
OBJPATHS=$(addprefix $(OBJDIR)/, $(OBJECTS))

INCLUDE=include

MACROS=PLATFORM_$(PLATFORM) BUILD_$(BUILD)
MACROS_debug=DEBUG
MACROS_release=NDEBUG

CC=clang++
CFLAGS=-c -Wall -std=c++11
CFLAGS_debug=-O0 -mfix-and-continue -gdwarf-2
CFLAGS_release=-O3

PATH_TO_GLAPP=$(dir $(lastword $(MAKEFILE_LIST)))

LIBS_app=GLApp SDL2 SDL2main
LIBPATHS_app=$(PATH_TO_GLAPP)/dist/$(PLATFORM)/$(BUILD)

LD=clang++
LDFLAGS_dylib=-dynamiclib -undefined suppress -flat_namespace
LDFLAGS_app= -framework Cocoa -framework OpenGL

.PHONY: default
default: all

.PHONY: all
all: osx

.PHONY: help
help:
	echo "make <platform>"
	echo "platform: osx"

.PHONY: osx
osx:
	$(MAKE) PLATFORM="osx" build_platform

.PHONY: build_platform
build_platform: $(PLATFORM)_debug $(PLATFORM)_release

.PHONY: $(PLATFORM)_debug
$(PLATFORM)_debug:
	$(MAKE) BUILD="debug" dist

.PHONY: $(PLATFORM)_release
$(PLATFORM)_release:
	$(MAKE) BUILD="release" dist

buildVar = \
	$($(1)_$(PLATFORM))\
	$($(1)_$(BUILD))\
	$($(1)_$(DIST_TYPE))\
	$($(1)_$(DIST_TYPE)_$(PLATFORM))\
	$($(1)_$(DIST_TYPE)_$(BUILD))\
	$($(1)_$(PLATFORM)_$(BUILD))\
	$($(1)_$(DIST_TYPE)_$(PLATFORM)_$(BUILD))

.PHONY: dist
dist: CFLAGS+= $(call buildVar,CFLAGS)
dist: CFLAGS+= $(addprefix -I,$(INCLUDE) $(call buildVar,INCLUDE))
dist: CFLAGS+= $(addprefix -D,$(MACROS) $(call buildVar,MACROS))
dist: LDFLAGS+= $(call buildVar,LDFLAGS)
dist: LDFLAGS+= $(addprefix -l,$(LIBS) $(call buildVar,LIBS))
dist: LDFLAGS+= $(addprefix -L,$(LIBPATHS) $(call buildVar,LIBPATHS))
dist: $(DIST)

$(OBJDIR)/%.o : $(SRCDIR_BASE)/%.cpp $(HEADERS)
	-mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

$(DIST):: $(OBJPATHS)
	-mkdir -p $(@D)
	$(LD) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	-rm -fr $(OBJDIR_BASE)

.PHONY: distclean
distclean:
	-rm -fr $(DISTDIR_BASE)

