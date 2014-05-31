#any dependent projects need these:
GLAPP_PATH:=$(dir $(lastword $(MAKEFILE_LIST)))

INCLUDE+=$(GLAPP_PATH)/include
LIBPATHS+=$(GLAPP_PATH)/dist/$(PLATFORM)/$(BUILD)
LIBS+=GLApp

LIBS+=SDL2 SDL2main
LDFLAGS_osx+= -framework Cocoa -framework OpenGL

