#any dependent projects need these:
GLAPP_PATH:=$(dir $(lastword $(MAKEFILE_LIST)))

INCLUDE+=$(GLAPP_PATH)/include
DYNAMIC_LIBS+=$(GLAPP_PATH)dist/$(PLATFORM)/$(BUILD)/libGLApp$(LIB_SUFFIX)
DYNAMIC_LIBS+=$(HOME)/lib/libSDL2-2.0.0$(LIB_SUFFIX)
LDFLAGS_osx+= -framework Cocoa -framework OpenGL
# these better be static libs =P otherwise ... provide a full path to DYNAMIC_LIBS
LIBS+=SDL2main
