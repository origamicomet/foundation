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

ifeq ($(TOOLCHAIN),msvc)
  TIER2_IMPORT_LIB := $(STATIC_LIB_PREFIX)tier2$(STATIC_LIB_SUFFIX)$(STATIC_LIB_EXTENSION)
else
  TIER2_IMPORT_LIB := $(SHARED_LIB_PREFIX)tier2$(SHARED_LIB_SUFFIX)
endif

BITBYTE_FOUNDATION_TIER2_INCLUDES := $(call cc-includes,include)
BITBYTE_FOUNDATION_TIER2_DEPENDENCIES := $(call ld-link,$(TIER1_IMPORT_LIB))

BITBYTE_FOUNDATION_TIER2_SOURCES := $(shell find $(SRC_DIR)/bitbyte/foundation/tier2 -name '*.cc')
BITBYTE_FOUNDATION_TIER2_OBJECTS := $(addprefix $(OBJ_DIR)/, $(subst $(SRC_DIR)/,,$(BITBYTE_FOUNDATION_TIER2_SOURCES:%.cc=%.o)))
BITBYTE_FOUNDATION_TIER2_OBJECTS += $(OBJ_DIR)/bitbyte/foundation/tier2.o

BITBYTE_FOUNDATION_TIER2_DEFINES := $(call cc-define,BITBYTE_FOUNDATION_TIER2_COMPILING)

-include $(BITBYTE_FOUNDATION_TIER2_OBJECTS:%.o=%.d)
$(OBJ_DIR)/bitbyte/foundation/tier2/%.o: $(SRC_DIR)/bitbyte/foundation/tier2/%.cc
	@echo "[CC] $<"
	@mkdir -p ${@D}
	$(call c++) $(BITBYTE_FOUNDATION_TIER2_INCLUDES) $(BITBYTE_FOUNDATION_TIER2_DEFINES) $(BITBYTE_FOUNDATION_TIER2_CFLAGS) $(call cc-input,$<) $(call cc-output,$@)
	$(call c++) $(BITBYTE_FOUNDATION_TIER2_INCLUDES) $(BITBYTE_FOUNDATION_TIER2_DEFINES) $(BITBYTE_FOUNDATION_TIER2_CFLAGS) $(call cc-input,$<) -MM -MT $@ >$(patsubst %.o,%.d,$@)

$(OBJ_DIR)/bitbyte/foundation/tier2.o: $(SRC_DIR)/bitbyte/foundation/tier2.cc
	@echo "[CC] $<"
	@mkdir -p ${@D}
	$(call c++) $(BITBYTE_FOUNDATION_TIER0_INCLUDES) $(BITBYTE_FOUNDATION_TIER0_DEFINES) $(BITBYTE_FOUNDATION_TIER0_CFLAGS) $(call cc-input,$<) $(call cc-output,$@)
	$(call c++) $(BITBYTE_FOUNDATION_TIER0_INCLUDES) $(BITBYTE_FOUNDATION_TIER0_DEFINES) $(BITBYTE_FOUNDATION_TIER0_CFLAGS) $(call cc-input,$<) -MM -MT $@ >$(patsubst %.o,%.d,$@)

$(TIER2): $(BITBYTE_FOUNDATION_TIER2_OBJECTS)
	@echo "[LD] $@"
	@mkdir -p ${@D}
ifeq ($(BITBYTE_FOUNDATION_TIER2_LINKAGE),statically)
	$(call ar++) $(BITBYTE_FOUNDATION_TIER2_ARFLAGS) $(call ar-output,$@) $(foreach input,$^,$(call ar-input,$(input)))
endif
ifeq ($(BITBYTE_FOUNDATION_TIER2_LINKAGE),dynamically)
	$(call ld++) $(call ld-shared) $(BITBYTE_FOUNDATION_TIER2_LDFLAGS) $(call ld-output,$@) $(foreach input,$^,$(call ld-input,$(input))) $(BITBYTE_FOUNDATION_TIER2_DEPENDENCIES)
endif
