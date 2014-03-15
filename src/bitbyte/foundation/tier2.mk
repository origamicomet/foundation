#=== bitbyte/foundation/tier2.mk ==============================================#
#                                                                              #
#  Foundation                                                                  #
#                                                                              #
#  This file is distributed under the terms described in LICENSE.              #
#                                                                              #
#  Author(s):                                                                  #
#   Michael Williams <mwilliams@bitbyte.ca>                                    #
#                                                                              #
#===------------------------------------------------------------------------===#

## @file bitbyte/foundation/tier2.mk
## @brief ...
##

BITBYTE_FOUNDATION_TIER2_CONFIGURATION := $(BITBYTE_FOUNDATION_CONFIGURATION)
BITBYTE_FOUNDATION_TIER2_LINKAGE := $(BITBYTE_FOUNDATION_LINKAGE)
BITBYTE_FOUNDATION_TIER2_CFLAGS  := $(BITBYTE_FOUNDATION_CFLAGS)
BITBYTE_FOUNDATION_TIER2_LDFLAGS := $(BITBYTE_FOUNDATION_LDFLAGS)
BITBYTE_FOUNDATION_TIER2_ARFLAGS := $(BITBYTE_FOUNDATION_ARFLAGS)

#==============================================================================#
# Rules
#

ifeq ($(BITBYTE_FOUNDATION_TIER2_LINKAGE),statically)
  TIER2 := $(LIB_DIR)/$(STATIC_LIB_PREFIX)tier2$(STATIC_LIB_SUFFIX)$(STATIC_LIB_EXTENSION)
endif
ifeq ($(BITBYTE_FOUNDATION_TIER2_LINKAGE),dynamically)
  TIER2 := $(BIN_DIR)/$(SHARED_LIB_PREFIX)tier2$(SHARED_LIB_SUFFIX)$(SHARED_LIB_EXTENSION)
endif

INCLUDES := $(call cc-includes,include)
DEPENDENCIES :=

SOURCES := $(shell find $(SRC_DIR)/bitbyte/foundation/tier2 -name '*.cc')
OBJECTS := $(addprefix $(OBJ_DIR)/, $(subst $(SRC_DIR)/,,$(SOURCES:%.cc=%.o)))
OBJECTS += $(OBJ_DIR)/bitbyte/foundation/tier2.o

DEFINES := $(call cc-define,BITBYTE_FOUNDATION_TIER2_COMPILING)

-include $(OBJECTS:%.o=%.d)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@echo "[CC] $<"
	@mkdir -p ${@D}
	$(call c++) $(INCLUDES) $(DEFINES) $(BITBYTE_FOUNDATION_TIER2_CFLAGS) $(call cc-input,$<) $(call cc-output,$@)
	$(call c++) $(INCLUDES) $(DEFINES) $(BITBYTE_FOUNDATION_TIER2_CFLAGS) $(call cc-input,$<) -MM -MT $@ >$(patsubst %.o,%.d,$@)

$(TIER2): $(OBJECTS)
	@echo "[LD] $@"
	@mkdir -p ${@D}
ifeq ($(BITBYTE_FOUNDATION_TIER2_LINKAGE),statically)
	$(call ar++) $(BITBYTE_FOUNDATION_TIER2_ARFLAGS) $(call ar-output,$@) $(foreach input,$^,$(call ar-input,$(input))) $(DEPENDENCIES)
endif
ifeq ($(BITBYTE_FOUNDATION_TIER2_LINKAGE),dynamically)
	$(call ld++) $(call ld-shared) $(BITBYTE_FOUNDATION_TIER2_LDFLAGS) $(call ld-output,$@) $(foreach input,$^,$(call ld-input,$(input))) $(DEPENDENCIES)
endif
