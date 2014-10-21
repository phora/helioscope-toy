
# The directory containing the GLFW includes and libraries
GLFW_DIR ?= /usr
SWISS_DIR ?= /usr
GLTW_DIR ?= $(HOME)/School/csce412/gltw
GLM_DIR ?= $(HOME)/School/csce412/glm
ifneq ($(strip $(HAS_FTGL)),)
FTGL_DIR ?= /usr
FT_DIR ?= /usr
endif

INCLUDES = -I$(GLFW_DIR)/include -I$(GLM_DIR) -I$(SWISS_DIR)/include -I$(FTGL_DIR)/include -I$(FT_DIR)/include/freetype2 -I$(FT_DIR)/include
CFLAGS = -g -O2 -Wno-pointer-sign -Wno-deprecated-declarations
CXXFLAGS =	$(INCLUDES) -O2 -g -Wall -fmessage-length=0
ifneq ($(strip $(HAS_FTGL)),)
CXXFLAGS+=-DHAS_FTGL=1
endif

# A list of object files that this Makefile should generate and link
OBJS =		main.o gl_compat_3_2.o OpenGLController.o shape.o shaderprogram.o sphere.o ring.o planet.o camera.o bmpreader.o

# Update LIBS below to point to the appropriate libraries for your system
LIBS_COMMON = -lswe -L$(SWISS_DIR)/lib
ifneq ($(strip $(HAS_FTGL)),)
LIBS_COMMON += -lfreetype -L$(FT_DIR)/lib -lftgl -L$(FTGL_DIR)/lib
endif
LIBS_APPLE = -L$(GLFW_DIR)/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit
LIBS_WIN =   -L$(GLFW_DIR)/lib -lglfw -lopengl32
LIBS_LINUX = -L$(GLFW_DIR)/lib -pthread -lGL -lglfw2 -lrt
LIBS =       $(LIBS_LINUX) $(LIBS_COMMON) 

# The name of the output executable
TARGET =	helioscope-toy

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
