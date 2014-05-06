DISTDIR=dist/osx
DIST=$(DISTDIR)/libGLApp.dylib

OBJECTS=GLApp.o

OBJDIR=obj/osx/release
OBJPATHS=$(addprefix $(OBJDIR)/, $(OBJECTS))

CC=clang++
CFLAGS_BASE=-c -Wall -Iinclude -std=c++11
CFLAGS_DEBUG=$(CFLAGS_BASE) -O0 -mfix-and-continue -gdwarf-2
CFLAGS_RELEASE=$(CFLAGS_BASE) -Os
CFLAGS=$(CFLAGS_RELEASE)

LD=clang++
LDFLAGS_BASE=-dynamiclib -undefined suppress -flat_namespace
LDFLAGS_DEBUG=$(LDFLAGS_BASE)
LDFLAGS_RELEASE=$(LDFLAGS_BASE)
LDFLAGS=$(LDFLAGS_RELEASE)

.PHONY: all prep clean distclean test

all: prep $(DIST)

prep:
	-mkdir -p $(OBJDIR)
	-mkdir -p $(DISTDIR)

$(OBJDIR)/%.o : src/%.cpp
	-mkdir -p $(OBJDIR)/$(^D)
	$(CC) $(CFLAGS) -o $@ $<

$(DIST): $(OBJPATHS)
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	-rm -f $(OBJPATHS)

distclean:
	-rm -f $(DIST)

test: $(DIST)
	$(MAKE) -C test run
