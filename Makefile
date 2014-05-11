# PLATFORM: osx
# BUILD: debug, release

OBJECTS=GLApp.o

DISTDIR_BASE=dist
DIST_FILENAME=libGLApp.dylib
DISTDIR=$(DISTDIR_BASE)/$(PLATFORM)/$(BUILD)
DIST=$(DISTDIR)/$(DIST_FILENAME)

OBJDIR_BASE=obj
OBJDIR=$(OBJDIR_BASE)/$(PLATFORM)/$(BUILD)
OBJPATHS=$(addprefix $(OBJDIR)/, $(OBJECTS))

CC=clang++
CFLAGS_BASE=-c -Wall -Iinclude -std=c++11
CFLAGS_DEBUG=$(CFLAGS_BASE) -O0 -mfix-and-continue -gdwarf-2 -DDEBUG
CFLAGS_RELEASE=$(CFLAGS_BASE) -O3 -DNDEBUG

LD=clang++
LDFLAGS_BASE=-dynamiclib -undefined suppress -flat_namespace
LDFLAGS_DEBUG=$(LDFLAGS_BASE)
LDFLAGS_RELEASE=$(LDFLAGS_BASE)

.PHONY: default
default: osx

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
	$(MAKE) BUILD="debug" CFLAGS="$(CFLAGS_DEBUG)" LDFLAGS="$(LDFLAGS_DEBUG)" dist 

.PHONY: $(PLATFORM)_release
$(PLATFORM)_release: 
	$(MAKE) BUILD="release" CFLAGS="$(CFLAGS_RELEASE)" LDFLAGS="$(LDFLAGS_RELEASE)" dist 

.PHONY: dist
dist: $(DIST)

$(OBJDIR)/%.o : src/%.cpp
	-mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

$(DIST): $(OBJPATHS)
	-mkdir -p $(@D)
	$(LD) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	-rm -fr $(OBJDIR_BASE)

.PHONY: distclean
distclean:
	-rm -fr $(DISTDIR_BASE)

.PHONY: test
test: $(DIST)
	$(MAKE) -C test run

