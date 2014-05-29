DIST_FILENAME=test
DIST_TYPE=app

include ../Makefile.mk

INCLUDE_BASE+=../include

$(DIST):: $(OBJPATHS)
	install_name_tool -change dist/$(PLATFORM)/$(BUILD)/libGLApp.dylib ../dist/$(PLATFORM)/$(BUILD)/libGLApp.dylib dist/$(PLATFORM)/$(BUILD)/test

