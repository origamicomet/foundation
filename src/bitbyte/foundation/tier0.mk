#=== bitbyte/foundation/tier0.mk ==============================================#
#                                                                              #
#  Foundation                                                                  #
#                                                                              #
#  This file is distributed under the terms described in LICENSE.              #
#                                                                              #
#  Author(s):                                                                  #
#   Michael Williams <mwilliams@bitbyte.ca>                                    #
#                                                                              #
#===------------------------------------------------------------------------===#

## @file bitbyte/foundation/tier0.mk
## @brief ...
##

BITBYTE_FOUNDATION_TIER0_CONFIGURATION := $(CONFIGURATION)
BITBYTE_FOUNDATION_TIER0_LINKAGE := $(LINKAGE)

#==============================================================================#
# Debugging and optimization
#

ifeq ($(BITBYTE_FOUNDATION_TIER0_CONFIGURATION),debug)
  CFLAGS_  += $(call cc-define,BITBYTE_FOUNDATION_TIER0_CONFIGURATION=1) $(call cc-debug)
  LDFLAGS_ += $(call ld-debug)
  ARFLAGS_ += $(call ar-debug)
endif
ifeq ($(BITBYTE_FOUNDATION_TIER0_CONFIGURATION),development)
  CFLAGS_  += $(call cc-define,BITBYTE_FOUNDATION_TIER0_CONFIGURATION=2) $(call cc-development)
  LDFLAGS_ += $(call ld-development)
  ARFLAGS_ += $(call ar-development)
endif
ifeq ($(BITBYTE_FOUNDATION_TIER0_CONFIGURATION),release)
  CFLAGS_  += $(call cc-define,BITBYTE_FOUNDATION_TIER0_CONFIGURATION=3) $(call cc-release)
  LDFLAGS_ += $(call ld-release)
  ARFLAGS_ += $(call ar-release)
endif

#==============================================================================#
# Rules
#

ifeq ($(BITBYTE_FOUNDATION_TIER0_LINKAGE),statically)
  TIER0 := $(LIB_DIR)/$(STATIC_LIB_PREFIX)tier0$(STATIC_LIB_SUFFIX)$(STATIC_LIB_EXTENSION)
endif
ifeq ($(BITBYTE_FOUNDATION_TIER0_LINKAGE),dynamically)
  TIER0 := $(BIN_DIR)/$(SHARED_LIB_PREFIX)tier0$(SHARED_LIB_SUFFIX)$(SHARED_LIB_EXTENSION)
endif

INCLUDES := $(call cc-includes,include)
DEPENDENCIES :=

SOURCES := $(shell find $(SRC_DIR)/bitbyte/foundation/tier0 -name '*.cc')
OBJECTS := $(addprefix $(OBJ_DIR)/, $(subst $(SRC_DIR)/,,$(SOURCES:%.cc=%.o)))
OBJECTS += $(OBJ_DIR)/bitbyte/foundation/tier0.o

DEFINES := $(call cc-define,BITBYTE_FOUNDATION_TIER0_COMPILING)
ifeq ($(BITBYTE_FOUNDATION_TIER0_LINKAGE),statically)
  DEFINES += $(call cc-define,BITBYTE_FOUNDATION_TIER0_LINKAGE=1)
endif
ifeq ($(BITBYTE_FOUNDATION_TIER0_LINKAGE),dynamically)
  DEFINES += $(call cc-define,BITBYTE_FOUNDATION_TIER0_LINKAGE=2)
endif
ifeq ($(HOST_ARCHITECTURE),x86)
  DEFINES += $(call cc-define,BITBYTE_FOUNDATION_HOST_ARCHITECTURE=0)
endif
ifeq ($(HOST_ARCHITECTURE),x86-64)
  DEFINES += $(call cc-define,BITBYTE_FOUNDATION_HOST_ARCHITECTURE=1)
endif
ifeq ($(HOST_PLATFORM),windows-mingw)
  DEFINES += $(call cc-define,BITBYTE_FOUNDATION_HOST_PLATFORM=0)
endif
ifeq ($(HOST_PLATFORM),macosx)
  DEFINES += $(call cc-define,BITBYTE_FOUNDATION_HOST_PLATFORM=1)
endif
ifeq ($(HOST_PLATFORM),linux)
  DEFINES += $(call cc-define,BITBYTE_FOUNDATION_HOST_PLATFORM=2)
endif

-include $(OBJECTS:%.o=%.d)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@echo "[CC] $<"
	@mkdir -p ${@D}
	$(call c++) $(INCLUDES) $(DEFINES) $(CFLAGS_) $(call cc-input,$<) $(call cc-output,$@)
	$(call c++) $(INCLUDES) $(DEFINES) $(CFLAGS_) $(call cc-input,$<) -MM -MT $@ >$(patsubst %.o,%.d,$@)

$(TIER0): $(OBJECTS)
	@echo "[LD] $@"
	@mkdir -p ${@D}
ifeq ($(BITBYTE_FOUNDATION_TIER0_LINKAGE),statically)
	@$(call ar++) $(ARFLAGS_) $(call ar-output,$@) $(foreach input,$^,$(call ar-input,$(input))) $(DEPENDENCIES)
endif
ifeq ($(BITBYTE_FOUNDATION_TIER0_LINKAGE),dynamically)
	@$(call ld++) $(call ld-shared) $(LDFLAGS_) $(call ld-output,$@) $(foreach input,$^,$(call ld-input,$(input))) $(DEPENDENCIES)
endif
