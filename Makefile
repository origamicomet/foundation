################################################################################
##                                                                            ##
## This file is part of Foundation.                                           ##
##                                                                            ##
## Author(s):                                                                 ##
##                                                                            ##
##   Michael Williams <devbug@bitbyte.ca>                                     ##
##                                                                            ##
## This is free and unencumbered software released into the public domain.    ##
##                                                                            ##
## Anyone is free to copy, modify, publish, use, compile, sell, or distribute ##
## this software, either in source code form or as a compiled binary, for any ##
## purpose, commercial or non-commercial, and by any means.                   ##
##                                                                            ##
## In jurisdictions that recognize copyright laws, the author or authors of   ##
## this software dedicate any and all copyright interest in the software to   ##
## the public domain. We make this dedication for the benefit of the public   ##
## large and to the detriment of our heirs and successors. We intend this     ##
## dedication to be an overt act of relinquishment in perpetuity of all       ##
## present and future rights to this software under copyright law.            ##
##                                                                            ##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR ##
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   ##
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    ##
## THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER   ##
## OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      ##
## ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR      ##
## OTHER DEALINGS IN THE SOFTWARE.                                            ##
##                                                                            ##
## For more information, please refer to <http://unlicense.org/>              ##
##                                                                            ##
################################################################################
## Makefile                                                                   ##
##  Specifies all build rules for Foundation.                                 ##
################################################################################

-include build/config
ifndef _FOUNDATION_BUILD_CONFIG_
  $(error Please ./configure first.)
endif

include build/toolchain.mk
include build/platform.mk
include build/architecture.mk
include build/detect/platform.mk
include build/detect/architecture.mk

################################################################################
# Binary, library, object, and source directories:                             #
################################################################################

BIN_DIR := bin
LIB_DIR := lib
OBJ_DIR := obj
SRC_DIR := src

################################################################################
# Debugging and optimization:                                                  #
################################################################################

ifeq ($(PARANOID),yes)
  CFLAGS += $(call cc-define,FND_PARANOID)
endif

ifeq ($(CONFIGURATION),debug)
  CFLAGS  += $(call cc-define,FND_CONFIGURATION=1) $(call cc-debug)
  LDFLAGS += $(call ld-debug)
  ARFLAGS += $(call ar-debug)
endif
ifeq ($(CONFIGURATION),development)
  CFLAGS  += $(call cc-define,FND_CONFIGURATION=2) $(call cc-development)
  LDFLAGS += $(call ld-development)
  ARFLAGS += $(call ar-development)
endif
ifeq ($(CONFIGURATION),release)
  CFLAGS  += $(call cc-define,FND_CONFIGURATION=3) $(call cc-release)
  LDFLAGS += $(call ld-release)
  ARFLAGS += $(call ar-release)
endif

################################################################################
# Rules:                                                                       #
################################################################################

FOUNDATION := $(LIB_DIR)/$(STATIC_LIB_PREFIX)foundation$(STATIC_LIB_SUFFIX)$(STATIC_LIB_EXTENSION)

.PHONY: all docs clean

all: $(FOUNDATION)

docs:
	@echo "[DOXYGEN] docs/doxygen.conf"
	@doxygen docs/doxygen.conf

clean:
	@echo "Cleaning..."
	@rm -R -f $(BIN_DIR)
	@rm -R -f $(LIB_DIR)
	@rm -R -f $(OBJ_DIR)
	@rm -R -f docs/html

SOURCES      := $(shell find $(SRC_DIR) -name '*.c')
OBJECTS      := $(addprefix $(OBJ_DIR)/, $(subst $(SRC_DIR)/,,$(SOURCES:%.c=%.o)))

INCLUDES     := $(call cc-includes,include)
DEPENDENCIES :=

DEFINES      := $(call cc-define,FND_COMPILING)
DEFINES      += $(call cc-define,FND_LINKAGE=1)

-include $(OBJECTS:%.o=%.d)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "[CXX] $<"
	@mkdir -p ${@D}
	@$(call c++) $(INCLUDES) $(DEFINES) $(call cc-input,$<) $(call cc-output,$@)
	@$(call c++) $(INCLUDES) $(DEFINES) $(call cc-input,$<) -MM -MT $@ >$(patsubst %.o,%.d,$@)

$(FOUNDATION): $(OBJECTS)
	@echo "[LD] $@"
	@mkdir -p ${@D}
	@$(call ar++) $(call ar-output,$@) $(foreach input,$^,$(call ar-input,$(input))) $(DEPENDENCIES)
