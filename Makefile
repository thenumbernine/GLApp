# PLATFORM: osx
# BUILD: debug, release

DIST_FILENAME=libGLApp.dylib
DIST_TYPE=dylib

CFLAGS_BASE+= -arch i386 -arch x86_64
LDFLAGS_BASE+= -arch i386 -arch x86_64

include Makefile.mk
