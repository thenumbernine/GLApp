DIST_FILENAME=test
DIST_TYPE=app

include ../../Common/Makefile.mk

#GLApp:
INCLUDE+=../include
LIBS=GLApp SDL2 SDL2main
LIBPATHS=../dist/$(PLATFORM)/$(BUILD)
LDFLAGS= -framework Cocoa -framework OpenGL


$(DIST):: $(OBJPATHS)
	install_name_tool -change dist/$(PLATFORM)/$(BUILD)/libGLApp.dylib ../dist/$(PLATFORM)/$(BUILD)/libGLApp.dylib dist/$(PLATFORM)/$(BUILD)/test

