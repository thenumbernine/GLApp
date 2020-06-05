DIST_FILENAME=GLApp
DIST_TYPE=lib
include ../Common/Base.mk
include ../Tensor/Include.mk

# this is in common with Include.mk:
# the only part that is different is that here we don't want to include libGLApp.so

DYNAMIC_LIBS_osx+=$(HOME)/lib/libSDL2-2.0.0$(LIB_SUFFIX)
LIBS_linux+=GL SDL2
INCLUDE_osx+=$(HOME)/include/SDL2
INCLUDE_linux+=/usr/include/SDL2
#DYNAMIC_LIBS_linux+=/usr/lib/x86_64-linux-gnu/libSDL2-2.0$(LIB_SUFFIX)
LDFLAGS_osx+= -framework Cocoa -framework OpenGL
#LIBS_linux+=GL GLU
#DYNAMIC_LIBS_linux+=/usr/lib/x86_64-linux-gnu/libGL$(LIB_SUFFIX)
#DYNAMIC_LIBS_linux+=/usr/lib/x86_64-linux-gnu/libGLU$(LIB_SUFFIX)
#LIBS+=SDL2main
