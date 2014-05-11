DISTDIR_BASE=dist
DISTDIR_DEBUG=$(DISTDIR_BASE)/osx/debug
DISTDIR_RELEASE=$(DISTDIR_BASE)/osx/release
DIST=$(DISTDIR)/libGLApp.dylib

OBJECTS=GLApp.o

OBJDIR_BASE=obj
OBJDIR_DEBUG=$(OBJDIR_BASE)/osx/debug
OBJDIR_RELEASE=$(OBJDIR_BASE)/osx/release
OBJPATHS=$(addprefix $(OBJDIR)/, $(OBJECTS))

CC=clang++
CFLAGS_BASE=-c -Wall -Iinclude -std=c++11
CFLAGS_DEBUG=$(CFLAGS_BASE) -O0 -mfix-and-continue -gdwarf-2 -DDEBUG
CFLAGS_RELEASE=$(CFLAGS_BASE) -O3 -DNDEBUG

LD=clang++
LDFLAGS_BASE=-dynamiclib -undefined suppress -flat_namespace
LDFLAGS_DEBUG=$(LDFLAGS_BASE)
LDFLAGS_RELEASE=$(LDFLAGS_BASE)

.PHONY: debug
debug: OBJDIR=$(OBJDIR_DEBUG)
debug: DISTDIR=$(DISTDIR_DEBUG)
debug: CFLAGS=$(CFLAGS_DEBUG)
debug: LDFLAGS=$(LDFLAGS_DEBUG)

.PHONY: release
release: OBJDIR=$(OBJDIR_RELEASE)
release: DISTDIR=$(DISTDIR_RELEASE)
release: CFLAGS=$(CFLAGS_RELEASE)
release: LDFLAGS=$(LDFLAGS_RELEASE)

.PHONY: all debug release clean distclean test

all: debug release

debug:
	$(MAKE) OBJDIR="$(OBJDIR_DEBUG)" DISTDIR="$(DISTDIR_DEBUG)" CFLAGS="$(CFLAGS_DEBUG)" LDFLAGS="$(LDFLAGS_DEBUG)" $(DIST)

release: 
	$(MAKE) OBJDIR="$(OBJDIR_RELEASE)" DISTDIR="$(DISTDIR_RELEASE)" CFLAGS="$(CFLAGS_RELEASE)" LDFLAGS="$(LDFLAGS_RELEASE)" $(DIST)

$(OBJDIR)/%.o : src/%.cpp
	-mkdir -p $(OBJDIR)/$(^D)
	$(CC) $(CFLAGS) -o $@ $<

$(DIST): $(OBJPATHS)
	-mkdir -p $(DISTDIR)
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	-rm -fr $(OBJDIR_BASE)

distclean:
	-rm -f $(DISTDIR_BASE)

test: $(DIST)
	$(MAKE) -C test run

