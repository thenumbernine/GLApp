#any dependent projects need these:
GLAPP_PATH:=$(dir $(lastword $(MAKEFILE_LIST)))

INCLUDE+=$(GLAPP_PATH)/include

DYNAMIC_LIBS+=$(GLAPP_PATH)dist/$(PLATFORM)/$(BUILD)/libGLApp$(LIB_SUFFIX)

# this is in common with Makefile:

LIBS_linux+=GL
LDFLAGS_osx+= -framework Cocoa -framework OpenGL
#LIBS_linux+=GLU
#DYNAMIC_LIBS_linux+=/usr/lib/x86_64-linux-gnu/libGL$(LIB_SUFFIX)
#DYNAMIC_LIBS_linux+=/usr/lib/x86_64-linux-gnu/libGLU$(LIB_SUFFIX)
