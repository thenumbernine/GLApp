DIST_FILENAME=GLApp
DIST_TYPE=lib
include ../Common/Base.mk
include ../Tensor/Include.mk
include ../SDLApp/Include.mk
include ../GLCxx/Include.mk		# only for GLCxx/gl.h for finding the headers for now

# this is in common with Include.mk:
# the only part that is different is that here we don't want to include libGLApp.so

LIBS_linux+=GL
LDFLAGS_osx+= -framework Cocoa -framework OpenGL
#LIBS_linux+=GLU
#DYNAMIC_LIBS_linux+=/usr/lib/x86_64-linux-gnu/libGL$(LIB_SUFFIX)
#DYNAMIC_LIBS_linux+=/usr/lib/x86_64-linux-gnu/libGLU$(LIB_SUFFIX)
