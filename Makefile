#################################
############ MACROS #############
#################################

#=========================================
#	Converts every .c or .cpp in .o and change the folder from src/ to obj/
#
#	$(1) = xx.cpp / xx.c
define C2O
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

#=========================================
#	Converts every .c or .cpp in .o and change the folder from src/ to obj/
#
#	$(1) = xx.cpp / xx.c
define C2OLIB
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(LIB)%,$(OBJLIB)%,$(1))))
endef

#   $(1) = compiler
#   $(2) = xx.o
#   $(3) = xx.cpp
#   $(4) = xx.hpp
#   $(5) = includes
#	$(6) = flags
define COMPILE_CPP
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5) $(6)
endef

#=========================================
#	Converts every .c or .cpp in .h or .hpp
#
#	$(1) = xx.cpp / xx.c
define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef

#=========================================
# COMPILER
CCACHE		:= #ccache
CC          := $(CCACHE) g++
C           := $(CCACHE) gcc

# FLAGS
FLAGS       := -pthread -Wall -fno-exceptions -O3
CCFLAGS     := $(FLAGS) -std=c++17 
CFLAGS      := $(FLAGS)
SANI        := 
ifeq ($(sani), true)
	SANI += -fsanitize=address
endif

# STRUCTURE FOLDERS
APPDIR      := 		                              #EXECUTABLE DIRECTORY (Folder root)
MKDIR 		:= mkdir -p
#IMGUI_DIR   := imgui
#LIBS_DIR    := libs
#IMPL_DIR    := backends
#	source code
SRC 		:= src
OBJ 		:= obj
SUBDIRS 	:= $(shell find $(SRC) -type d)
OBJSUBDIRS 	:= $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))
#	libs
LIB         := lib
OBJLIB      := lib_obj
SUBLIBDIRS  := $(shell find $(LIB) -type d)
OBJSUBLIB 	:= $(patsubst $(LIB)%,$(OBJLIB)%,$(SUBLIBDIRS))


# FILES
APP 		:= ai_prototype
#	source code
ALLC        := $(shell find $(SRC)/ -type f -iname *.c)
ALLCPP    	:= $(shell find $(SRC)/ -type f -iname *.cpp)
ALLOBJ      := $(foreach F,$(ALLCPP) $(ALLC),$(call C2O,$(F)))
#	libs
ALLCLIB     := $(shell find $(LIB)/ -type f -iname *.c)
ALLCPPLIB   := $(shell find $(LIB)/ -type f -iname *.cpp)
ALLOBJLIB   := $(foreach L,$(ALLCLIB) $(ALLCPPLIB),$(call C2OLIB,$(L)))

# HEADERS AND LIBRARIES
INCLUDE 	:= -I.$(APPDIR)/$(SRC) -I.$(APPDIR)/$(LIB) -I.$(APPDIR)/$(LIB)/gl3w -DIMGUI_IMPL_OPENGL_LOADER_GL3W
LIBS 		:= -L.$(APPDIR)/$(LIB) -lX11 -lGL -lglfw -ldl
GOLD_OPTION	:= #-fuse-ld=gold

# CLEAN
RM          := rm -f

#========================================================================
#	LINKER

# CREATES AN EXECUTABLE NAMED CYBORGEDDON LINKING ALLOBJ AND LIBS
#   CONSOLE COMMANDS:
#                       make

$(APPDIR)$(APP) : $(OBJSUBDIRS) $(ALLOBJ) $(OBJSUBLIB) $(ALLOBJLIB)
	$(CC) -o $(APPDIR)$(APP) $(ALLOBJ) $(ALLOBJLIB) $(LIBS) $(GOLD_OPTION) $(SANI)

#========================================================================
#	COMPILER C++

# COMPILES EVERY .CPP / .C IF IT HAS NOT CHANGED SINCE THE LAST MAKE
#	source code
$(foreach F,$(ALLCPP),$(eval $(call COMPILE_CPP,$(CC),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(INCLUDE),$(CCFLAGS) $(SANI))))
$(foreach F,$(ALLC),$(eval $(call COMPILE_CPP,$(C),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(INCLUDE),$(CFLAGS))))
#	libs
$(foreach F,$(ALLCPPLIB),$(eval $(call COMPILE_CPP,$(CC),$(call C2OLIB,$(F)),$(F),$(call C2H,$(F)),$(INCLUDE),$(CCFLAGS))))
$(foreach F,$(ALLCLIB),$(eval $(call COMPILE_CPP,$(C),$(call C2OLIB,$(F)),$(F),$(call C2H,$(F)),$(INCLUDE),$(CFLAGS))))

#========================================================================
#	FOLDER STRUCTURE

$(OBJSUBDIRS) : 
	$(MKDIR) $(OBJSUBDIRS)
	$(MKDIR) $(OBJSUBLIB)


#========================================================================
#	OTHER COMMANDS

.PHONY: info clean clean_all

#===========================================================
# SHOW WHICH ELEMENTS ARE BEING INCLUDED IN THIS VARIABLES
#	CONSOLE COMMAND:
#                       make info

info :
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(SUBLIBDIRS))
	$(info $(OBJSUBLIB))
	$(info $(ALLCPP))
	$(info $(ALLC))
	$(info $(ALLOBJ))
	$(info $(ALLCPPLIB))
	$(info $(ALLCLIB))
	$(info $(ALLOBJLIB))


#===========================================================
# DELETE EXECUTABLE AND MAIN FOLDERS CONTENT
#	CONSOLE COMMAND:
#                       make clean
clean :
	$(RM) $(APP) -r $(OBJ)

# DELETE LIBS TOO
cleanall :
	$(RM) $(APP) -r $(OBJ) $(OBJLIB)

