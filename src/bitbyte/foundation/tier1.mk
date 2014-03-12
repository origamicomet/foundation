#=== bitbyte/foundation/tier1.mk ==============================================#
#                                                                              #
#  Foundation                                                                  #
#                                                                              #
#  This file is distributed under the terms described in LICENSE.              #
#                                                                              #
#  Author(s):                                                                  #
#   Michael Williams <mwilliams@bitbyte.ca>                                    #
#                                                                              #
#===------------------------------------------------------------------------===#

## @file bitbyte/foundation/tier1.mk
## @brief ...
##

BITBYTE_FOUNDATION_TIER1_CONFIGURATION := $(BITBYTE_FOUNDATION_CONFIGURATION)
BITBYTE_FOUNDATION_TIER1_LINKAGE := $(BITBYTE_FOUNDATION_LINKAGE)
BITBYTE_FOUNDATION_TIER1_CFLAGS  := $(BITBYTE_FOUNDATION_CFLAGS)
BITBYTE_FOUNDATION_TIER1_LDFLAGS := $(BITBYTE_FOUNDATION_LDFLAGS)
BITBYTE_FOUNDATION_TIER1_ARFLAGS := $(BITBYTE_FOUNDATION_ARFLAGS)

#==============================================================================#
# Rules
#

ifeq ($(BITBYTE_FOUNDATION_TIER1_LINKAGE),statically)
  TIER1 := $(LIB_DIR)/$(STATIC_LIB_PREFIX)tier1$(STATIC_LIB_SUFFIX)$(STATIC_LIB_EXTENSION)
endif
ifeq ($(BITBYTE_FOUNDATION_TIER1_LINKAGE),dynamically)
  TIER1 := $(BIN_DIR)/$(SHARED_LIB_PREFIX)tier1$(SHARED_LIB_SUFFIX)$(SHARED_LIB_EXTENSION)
endif

INCLUDES := $(call cc-includes,include)
DEPENDENCIES :=

SOURCES := $(shell find $(SRC_DIR)/bitbyte/foundation/tier1 -name '*.cc')
OBJECTS := $(addprefix $(OBJ_DIR)/, $(subst $(SRC_DIR)/,,$(SOURCES:%.cc=%.o)))
OBJECTS += $(OBJ_DIR)/bitbyte/foundation/tier1.o

DEFINES := $(call cc-define,BITBYTE_FOUNDATION_TIER1_COMPILING)

-include $(OBJECTS:%.o=%.d)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@echo "[CC] $<"
	@mkdir -p ${@D}
	$(call c++) $(INCLUDES) $(DEFINES) $(BITBYTE_FOUNDATION_TIER1_CFLAGS) $(call cc-input,$<) $(call cc-output,$@)
	$(call c++) $(INCLUDES) $(DEFINES) $(BITBYTE_FOUNDATION_TIER1_CFLAGS) $(call cc-input,$<) -MM -MT $@ >$(patsubst %.o,%.d,$@)

$(TIER1): $(OBJECTS)
	@echo "[LD] $@"
	@mkdir -p ${@D}
ifeq ($(BITBYTE_FOUNDATION_TIER1_LINKAGE),statically)
	$(call ar++) $(BITBYTE_FOUNDATION_TIER1_ARFLAGS) $(call ar-output,$@) $(foreach input,$^,$(call ar-input,$(input))) $(DEPENDENCIES)
endif
ifeq ($(BITBYTE_FOUNDATION_TIER1_LINKAGE),dynamically)
	$(call ld++) $(call ld-shared) $(BITBYTE_FOUNDATION_TIER1_LDFLAGS) $(call ld-output,$@) $(foreach input,$^,$(call ld-input,$(input))) $(DEPENDENCIES)
endif
