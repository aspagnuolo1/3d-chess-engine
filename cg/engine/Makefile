CXX = g++
AR = ar
LD = g++
WINDRES = windres

# Detect OS
UNAME_S := $(shell uname -s)

# Default settings
LIB = -lGL -lglut -lfreeimage -lGLU
OUT_EXTENSION = so
LINK_FLAGS = -shared
INC = -I../dependencies/glm/include/ -I../dependencies/freeimage/include/ -I../dependencies/glew/include/
LIBDIR =

ifeq ($(UNAME_S), Darwin) # macOS
    OUT_EXTENSION = dylib
    LINK_FLAGS = -dynamiclib
    INC = -I/opt/homebrew/include
    LIBDIR = -L/opt/homebrew/lib
    LIB = -lGL -lglut -lfreeimage
endif

# Compiler flags
CFLAGS = -Wall -std=c++20 -fPIC -m64 -fexceptions
RCFLAGS = 
RESINC = 
LDFLAGS = -m64

# Debug settings
INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g -D_DEBUG
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/libengine.$(OUT_EXTENSION)

# Release settings
INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/libengine.$(OUT_EXTENSION)

# Object files
OBJ_DEBUG = $(OBJDIR_DEBUG)/engine.o \
            $(OBJDIR_DEBUG)/attenuationLight.o \
            $(OBJDIR_DEBUG)/camera.o \
            $(OBJDIR_DEBUG)/directionalLight.o \
            $(OBJDIR_DEBUG)/light.o \
            $(OBJDIR_DEBUG)/list.o \
            $(OBJDIR_DEBUG)/material.o \
            $(OBJDIR_DEBUG)/mesh.o \
            $(OBJDIR_DEBUG)/node.o \
            $(OBJDIR_DEBUG)/object.o \
            $(OBJDIR_DEBUG)/omnidirectionalLight.o \
            $(OBJDIR_DEBUG)/ortoCamera.o \
            $(OBJDIR_DEBUG)/perspCamera.o \
            $(OBJDIR_DEBUG)/spotLight.o \
            $(OBJDIR_DEBUG)/texture.o \
            $(OBJDIR_DEBUG)/texture2D.o \
            $(OBJDIR_DEBUG)/ovoreader.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/engine.o \
              $(OBJDIR_RELEASE)/attenuationLight.o \
              $(OBJDIR_RELEASE)/camera.o \
              $(OBJDIR_RELEASE)/directionalLight.o \
              $(OBJDIR_RELEASE)/light.o \
              $(OBJDIR_RELEASE)/list.o \
              $(OBJDIR_RELEASE)/material.o \
              $(OBJDIR_RELEASE)/mesh.o \
              $(OBJDIR_RELEASE)/node.o \
              $(OBJDIR_RELEASE)/object.o \
              $(OBJDIR_RELEASE)/omnidirectionalLight.o \
              $(OBJDIR_RELEASE)/ortoCamera.o \
              $(OBJDIR_RELEASE)/perspCamera.o \
              $(OBJDIR_RELEASE)/spotLight.o \
              $(OBJDIR_RELEASE)/texture.o \
              $(OBJDIR_RELEASE)/texture2D.o \
            $(OBJDIR_DEBUG)/ovoreader.o

ENGINE_OBJECTS = ovoreader.cpp attenuationLight.cpp camera.cpp directionalLight.cpp light.cpp list.cpp material.cpp mesh.cpp node.cpp object.cpp omnidirectionalLight.cpp ortoCamera.cpp perspCamera.cpp spotLight.cpp texture.cpp texture2D.cpp engine.cpp

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LINK_FLAGS) $(LIBDIR_DEBUG) $(OBJ_DEBUG)  -o $(OUT_DEBUG) $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/%.o: %.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $^ -o $@

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LINK_FLAGS) $(LIBDIR_RELEASE) $(OBJ_RELEASE)  -o $(OUT_RELEASE) $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/%.o: %.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $< -o $@

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release