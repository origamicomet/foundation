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

BITBYTE_FOUNDATION_TIER0_CONFIGURATION := $(BITBYTE_FOUNDATION_CONFIGURATION)
BITBYTE_FOUNDATION_TIER0_LINKAGE := $(BITBYTE_FOUNDATION_LINKAGE)
BITBYTE_FOUNDATION_TIER0_CFLAGS  := $(BITBYTE_FOUNDATION_CFLAGS)
BITBYTE_FOUNDATION_TIER0_LDFLAGS := $(BITBYTE_FOUNDATION_LDFLAGS)
BITBYTE_FOUNDATION_TIER0_ARFLAGS := $(BITBYTE_FOUNDATION_ARFLAGS)

#==============================================================================#
# Rules
#

ifeq ($(BITBYTE_FOUNDATION_TIER0_LINKAGE),statically)
  TIER0 := lib/$(STATIC_LIB_PREFIX)tier0$(STATIC_LIB_SUFFIX)$(STATIC_LIB_EXTENSION)
endif
ifeq ($(BITBYTE_FOUNDATION_TIER0_LINKAGE),dynamically)
  TIER0 := bin/$(SHARED_LIB_PREFIX)tier0$(SHARED_LIB_SUFFIX)$(SHARED_LIB_EXTENSION)
endif

ifeq ($(TOOLCHAIN),msvc)
  TIER0_IMPORT_LIB := $(STATIC_LIB_PREFIX)tier0$(STATIC_LIB_SUFFIX)
else
  TIER0_IMPORT_LIB := $(SHARED_LIB_PREFIX)tier0$(SHARED_LIB_SUFFIX)
endif

BITBYTE_FOUNDATION_TIER0_INCLUDES := $(call cc-includes,include)
BITBYTE_FOUNDATION_TIER0_DEPENDENCIES :=

BITBYTE_FOUNDATION_TIER0_SOURCES := $(shell find src/bitbyte/foundation/tier0 -name '*.cc')
BITBYTE_FOUNDATION_TIER0_OBJECTS := $(addprefix obj/, $(subst src/,,$(BITBYTE_FOUNDATION_TIER0_SOURCES:%.cc=%.o)))
BITBYTE_FOUNDATION_TIER0_OBJECTS += obj/bitbyte/foundation/tier0.o

BITBYTE_FOUNDATION_TIER0_DEFINES := $(call cc-define,BITBYTE_FOUNDATION_TIER0_COMPILING)

-include $(BITBYTE_FOUNDATION_TIER0_OBJECTS:%.o=%.d)

obj/bitbyte/foundation/tier0/%.o: src/bitbyte/foundation/tier0/%.cc
	@echo "[CC] $<"
	@mkdir -p ${@D}
	$(call c++) $(BITBYTE_FOUNDATION_TIER0_INCLUDES) $(BITBYTE_FOUNDATION_TIER0_DEFINES) $(BITBYTE_FOUNDATION_TIER0_CFLAGS) $(call cc-input,$<) $(call cc-output,$@)
	$(call c++) $(BITBYTE_FOUNDATION_TIER0_INCLUDES) $(BITBYTE_FOUNDATION_TIER0_DEFINES) $(BITBYTE_FOUNDATION_TIER0_CFLAGS) $(call cc-input,$<) -MM -MT $@ >$(patsubst %.o,%.d,$@)

obj/bitbyte/foundation/tier0.o: src/bitbyte/foundation/tier0.cc
	@echo "[CC] $<"
	@mkdir -p ${@D}
	$(call c++) $(BITBYTE_FOUNDATION_TIER0_INCLUDES) $(BITBYTE_FOUNDATION_TIER0_DEFINES) $(BITBYTE_FOUNDATION_TIER0_CFLAGS) $(call cc-input,$<) $(call cc-output,$@)
	$(call c++) $(BITBYTE_FOUNDATION_TIER0_INCLUDES) $(BITBYTE_FOUNDATION_TIER0_DEFINES) $(BITBYTE_FOUNDATION_TIER0_CFLAGS) $(call cc-input,$<) -MM -MT $@ >$(patsubst %.o,%.d,$@)

$(TIER0): $(BITBYTE_FOUNDATION_TIER0_OBJECTS)
	@echo "[LD] $@"
	@mkdir -p ${@D}
ifeq ($(BITBYTE_FOUNDATION_TIER0_LINKAGE),statically)
	$(call ar++) $(BITBYTE_FOUNDATION_TIER0_ARFLAGS) $(call ar-output,$@) $(foreach input,$^,$(call ar-input,$(input)))
endif
ifeq ($(BITBYTE_FOUNDATION_TIER0_LINKAGE),dynamically)
	$(call ld++) $(call ld-shared) $(BITBYTE_FOUNDATION_TIER0_LDFLAGS) $(call ld-output,$@) $(foreach input,$^,$(call ld-input,$(input))) $(BITBYTE_FOUNDATION_TIER0_DEPENDENCIES)
endif
