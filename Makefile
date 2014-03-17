#=== Makefile =================================================================#
#                                                                              #
#  Foundation                                                                  #
#                                                                              #
#  This file is distributed under the terms described in LICENSE.              #
#                                                                              #
#  Author(s):                                                                  #
#   Michael Williams <mwilliams@bitbyte.ca>                                    #
#                                                                              #
#===------------------------------------------------------------------------===#

-include conf.mk
ifndef _BITBYTE_FOUNDATION_BUILD_CONFIG_
  $(error Please ./configure first.)
endif

include build/detect/platform.mk
include build/detect/architecture.mk
include build/toolchain.mk
include build/platform.mk
include build/architecture.mk

#==============================================================================#
# Binary, library, object, and source directories
#

BIN_DIR := bin
LIB_DIR := lib
OBJ_DIR := obj
SRC_DIR := src

#==============================================================================#
# Rules
#

.PHONY: all docs clean foundation

all: foundation

include src/Makefile

foundation: $(TIER0) $(TIER1) $(TIER2) $(TIER3)

docs:
	@echo "[DOXYGEN] Doxyfile"
	@doxygen Doxyfile

clean:
	@echo "Cleaning..."
	@rm -R -f $(BIN_DIR)
	@rm -R -f $(LIB_DIR)
	@rm -R -f $(OBJ_DIR)
	@rm -R -f docs/html
