# PLATFORM: osx
# BUILD: debug, release

DIST_FILENAME=libGLApp.dylib
DIST_TYPE=dylib

include Makefile.mk

CFLAGS+= -arch i386 -arch x86_64
LDFLAGS+= -arch i386 -arch x86_64
