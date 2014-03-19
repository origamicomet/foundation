#=== bitbyte/foundation/tier3.mk ==============================================#
#                                                                              #
#  Foundation                                                                  #
#                                                                              #
#  This file is distributed under the terms described in LICENSE.              #
#                                                                              #
#  Author(s):                                                                  #
#   Michael Williams <mwilliams@bitbyte.ca>                                    #
#                                                                              #
#===------------------------------------------------------------------------===#

## @file bitbyte/foundation/tier3.mk
## @brief ...
##

BITBYTE_FOUNDATION_TIER3_CONFIGURATION := $(BITBYTE_FOUNDATION_CONFIGURATION)
BITBYTE_FOUNDATION_TIER3_LINKAGE := $(BITBYTE_FOUNDATION_LINKAGE)
BITBYTE_FOUNDATION_TIER3_CFLAGS  := $(BITBYTE_FOUNDATION_CFLAGS)
BITBYTE_FOUNDATION_TIER3_LDFLAGS := $(BITBYTE_FOUNDATION_LDFLAGS)
BITBYTE_FOUNDATION_TIER3_ARFLAGS := $(BITBYTE_FOUNDATION_ARFLAGS)

#==============================================================================#
# Rules
#

ifeq ($(BITBYTE_FOUNDATION_TIER3_LINKAGE),statically)
  TIER3 := lib/$(STATIC_LIB_PREFIX)tier3$(STATIC_LIB_SUFFIX)$(STATIC_LIB_EXTENSION)
endif
ifeq ($(BITBYTE_FOUNDATION_TIER3_LINKAGE),dynamically)
  TIER3 := bin/$(SHARED_LIB_PREFIX)tier3$(SHARED_LIB_SUFFIX)$(SHARED_LIB_EXTENSION)
endif

ifeq ($(TOOLCHAIN),msvc)
  TIER3_IMPORT_LIB := $(STATIC_LIB_PREFIX)tier3$(STATIC_LIB_SUFFIX)
else
  TIER3_IMPORT_LIB := $(SHARED_LIB_PREFIX)tier3$(SHARED_LIB_SUFFIX)
endif

BITBYTE_FOUNDATION_TIER3_INCLUDES := $(call cc-includes,include)
BITBYTE_FOUNDATION_TIER3_DEPENDENCIES := $(call ld-link,$(TIER2_IMPORT_LIB))

BITBYTE_FOUNDATION_TIER3_SOURCES := $(shell find src/bitbyte/foundation/tier3 -name '*.cc')
BITBYTE_FOUNDATION_TIER3_OBJECTS := $(addprefix obj/, $(subst src/,,$(BITBYTE_FOUNDATION_TIER3_SOURCES:%.cc=%.o)))
BITBYTE_FOUNDATION_TIER3_OBJECTS += obj/bitbyte/foundation/tier3.o

BITBYTE_FOUNDATION_TIER3_DEFINES := $(call cc-define,BITBYTE_FOUNDATION_TIER3_COMPILING)

-include $(BITBYTE_FOUNDATION_TIER3_OBJECTS:%.o=%.d)
obj/bitbyte/foundation/tier3/%.o: src/bitbyte/foundation/tier3/%.cc
	@echo "[CC] $<"
	@mkdir -p ${@D}
	$(call c++) $(BITBYTE_FOUNDATION_TIER3_INCLUDES) $(BITBYTE_FOUNDATION_TIER3_DEFINES) $(BITBYTE_FOUNDATION_TIER3_CFLAGS) $(call cc-input,$<) $(call cc-output,$@)
	$(call c++) $(BITBYTE_FOUNDATION_TIER3_INCLUDES) $(BITBYTE_FOUNDATION_TIER3_DEFINES) $(BITBYTE_FOUNDATION_TIER3_CFLAGS) $(call cc-input,$<) -MM -MT $@ >$(patsubst %.o,%.d,$@)

obj/bitbyte/foundation/tier3.o: src/bitbyte/foundation/tier3.cc
	@echo "[CC] $<"
	@mkdir -p ${@D}
	$(call c++) $(BITBYTE_FOUNDATION_TIER0_INCLUDES) $(BITBYTE_FOUNDATION_TIER0_DEFINES) $(BITBYTE_FOUNDATION_TIER0_CFLAGS) $(call cc-input,$<) $(call cc-output,$@)
	$(call c++) $(BITBYTE_FOUNDATION_TIER0_INCLUDES) $(BITBYTE_FOUNDATION_TIER0_DEFINES) $(BITBYTE_FOUNDATION_TIER0_CFLAGS) $(call cc-input,$<) -MM -MT $@ >$(patsubst %.o,%.d,$@)

$(TIER3): $(BITBYTE_FOUNDATION_TIER3_OBJECTS)
	@echo "[LD] $@"
	@mkdir -p ${@D}
ifeq ($(BITBYTE_FOUNDATION_TIER3_LINKAGE),statically)
	$(call ar++) $(BITBYTE_FOUNDATION_TIER3_ARFLAGS) $(call ar-output,$@) $(foreach input,$^,$(call ar-input,$(input)))
endif
ifeq ($(BITBYTE_FOUNDATION_TIER3_LINKAGE),dynamically)
	$(call ld++) $(call ld-shared) $(BITBYTE_FOUNDATION_TIER3_LDFLAGS) $(call ld-output,$@) $(foreach input,$^,$(call ld-input,$(input))) $(BITBYTE_FOUNDATION_TIER3_DEPENDENCIES)
endif
