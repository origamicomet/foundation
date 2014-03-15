#=== bitbyte/foundation.mk ====================================================#
#                                                                              #
#  Foundation                                                                  #
#                                                                              #
#  This file is distributed under the terms described in LICENSE.              #
#                                                                              #
#  Author(s):                                                                  #
#   Michael Williams <mwilliams@bitbyte.ca>                                    #
#                                                                              #
#===------------------------------------------------------------------------===#

## @file bitbyte/foundation.mk
## @brief ...
##

BITBYTE_FOUNDATION_CONFIGURATION := $(CONFIGURATION)
BITBYTE_FOUNDATION_LINKAGE := $(LINKAGE)

BITBYTE_FOUNDATION_CFLAGS  :=
BITBYTE_FOUNDATION_LDFLAGS :=
BITBYTE_FOUNDATION_ARFLAGS :=

ifeq ($(HOST_ARCHITECTURE),x86)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_HOST_ARCHITECTURE=0)
endif
ifeq ($(HOST_ARCHITECTURE),x86-64)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_HOST_ARCHITECTURE=1)
endif
ifeq ($(HOST_PLATFORM),windows-mingw)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_HOST_PLATFORM=0)
endif
ifeq ($(HOST_PLATFORM),macosx)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_HOST_PLATFORM=1)
endif
ifeq ($(HOST_PLATFORM),linux)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_HOST_PLATFORM=2)
endif

ifeq ($(BITBYTE_FOUNDATION_LINKAGE),statically)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_TIER0_LINKAGE=1)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_TIER1_LINKAGE=1)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_TIER2_LINKAGE=1)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_TIER3_LINKAGE=1)
endif
ifeq ($(BITBYTE_FOUNDATION_LINKAGE),dynamically)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_TIER0_LINKAGE=2)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_TIER1_LINKAGE=2)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_TIER2_LINKAGE=2)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_TIER3_LINKAGE=2)
endif

ifeq ($(BITBYTE_FOUNDATION_CONFIGURATION),debug)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_CONFIGURATION=1)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-debug)
  BITBYTE_FOUNDATION_LDFLAGS += $(call ld-debug)
  BITBYTE_FOUNDATION_ARFLAGS += $(call ar-debug)
endif
ifeq ($(BITBYTE_FOUNDATION_CONFIGURATION),development)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_CONFIGURATION=2)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-development)
  BITBYTE_FOUNDATION_LDFLAGS += $(call ld-development)
  BITBYTE_FOUNDATION_ARFLAGS += $(call ar-development)
endif
ifeq ($(BITBYTE_FOUNDATION_CONFIGURATION),release)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-define,BITBYTE_FOUNDATION_CONFIGURATION=3)
  BITBYTE_FOUNDATION_CFLAGS += $(call cc-release)
  BITBYTE_FOUNDATION_LDFLAGS += $(call ld-release)
  BITBYTE_FOUNDATION_ARFLAGS += $(call ar-release)
endif

#==============================================================================#
# Sub-projects
#

include $(SRC_DIR)/bitbyte/foundation/tier0.mk
include $(SRC_DIR)/bitbyte/foundation/tier1.mk
include $(SRC_DIR)/bitbyte/foundation/tier2.mk
