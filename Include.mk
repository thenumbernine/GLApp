#any dependent projects need these:
GLAPP_PATH:=$(dir $(lastword $(MAKEFILE_LIST)))

INCLUDE+=$(GLAPP_PATH)/include
DYNAMIC_LIBS+=$(GLAPP_PATH)/dist/$(PLATFORM)/$(BUILD)/libGLApp.dylib
LDFLAGS_osx+= -framework Cocoa -framework OpenGL
# these better be static libs =P otherwise ... provide a full path to DYNAMIC_LIBS
LIBS+=SDL2
LIBS+=SDL2main

