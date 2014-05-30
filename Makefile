# PLATFORM: osx
# BUILD: debug, release

DIST_FILENAME=GLApp
DIST_TYPE=lib

include Makefile.mk

CFLAGS+= -arch i386 -arch x86_64
LDFLAGS+= -arch i386 -arch x86_64
