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

CC=clang++
CFLAGS_BASE=-c -Wall -Iinclude -std=c++11
CFLAGS_debug=-O0 -mfix-and-continue -gdwarf-2 -DDEBUG
CFLAGS_release=-O3 -DNDEBUG
# there has to be a better way to do this ... -DPLATFORM_$(PLATFORM) isn't working ...
CFLAGS_osx=-DPLATFORM_OSX
CFLAGS_windows=-DPLATFORM_WINDOWS

#PATH_TO_GLAPP=../GLApp
PATH_TO_GLAPP=$(dir $(lastword $(MAKEFILE_LIST)))

LD=clang++
LDFLAGS_dylib=-dynamiclib -undefined suppress -flat_namespace
LDFLAGS_app=-L$(PATH_TO_GLAPP)/dist/$(PLATFORM)/$(BUILD) -lGLApp -lSDL2 -lSDL2main -framework Cocoa -framework OpenGL
LDFLAGS_BASE=$(LDFLAGS_$(DIST_TYPE))

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

.PHONY: dist
dist: CFLAGS= $(CFLAGS_BASE)
dist: CFLAGS+= $(CFLAGS_$(PLATFORM))
dist: CFLAGS+= $(CFLAGS_$(BUILD))
dist: CFLAGS+= $(CFLAGS_$(PLATFORM)_$(BUILD))
dist: LDFLAGS= $(LDFLAGS_BASE)
dist: LDFLAGS+= $(LDFLAGS_$(BUILD))
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

