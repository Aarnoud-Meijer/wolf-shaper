#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#
# Modified by Patrick Desaulniers
#
# --------------------------------------------------------------
# Project name, used for binaries
#
# Set PLUGIN_NAME in Makefile.mk at the project's root directory
#

NAME = wolf-shaper

# --------------------------------------------------------------
# Plugin types to build

BUILD_LV2 ?= true
BUILD_VST2 ?= true
BUILD_JACK ?= true
BUILD_DSSI ?= true
BUILD_LADSPA ?= false

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	Common/Utils/src/Mathf.cpp \
	Common/Structures/src/Graph.cpp \
	Common/Structures/src/Oversampler.cpp \
	Common/Structures/src/ParamSmooth.cpp \
	Libs/DSPFilters/source/Butterworth.cpp \
	Libs/DSPFilters/source/Biquad.cpp \
	Libs/DSPFilters/source/Cascade.cpp \
	Libs/DSPFilters/source/Filter.cpp \
	Libs/DSPFilters/source/Param.cpp \
	Libs/DSPFilters/source/Butterworth.cpp \
	Libs/DSPFilters/source/PoleFilter.cpp \
	Libs/DSPFilters/source/RBJ.cpp \
	Libs/DSPFilters/source/Bessel.cpp \
	Libs/DSPFilters/source/RootFinder.cpp \
	WolfShaperPlugin.cpp

FILES_UI  = \
	Common/Utils/src/Mathf.cpp \
	Common/Structures/src/Graph.cpp \
	Common/Structures/src/Margin.cpp \
	Common/Structures/src/Animation.cpp \
	Common/Widgets/src/WolfWidget.cpp \
	Common/Widgets/src/GraphNode.cpp \
	Common/Widgets/src/GraphWidget.cpp \
	Common/Widgets/src/NanoSwitch.cpp \
	Common/Widgets/src/RemoveDCSwitch.cpp \
	Common/Widgets/src/NanoButton.cpp \
	Common/Widgets/src/ResetGraphButton.cpp \
	Common/Widgets/src/NanoWheel.cpp \
	Common/Widgets/src/OversampleWheel.cpp \
	Common/Widgets/src/NanoKnob.cpp \
	Common/Widgets/src/VolumeKnob.cpp \
	Common/Widgets/src/ResizeHandle.cpp \
	Common/Widgets/src/LabelBox.cpp \
	Common/Widgets/src/LabelBoxList.cpp \
	Common/Widgets/src/BipolarModeSwitch.cpp \
	Common/Widgets/src/LabelContainer.cpp \
	Common/Widgets/src/GlowingLabelsBox.cpp \
	Common/Widgets/src/NanoLabel.cpp \
	Common/Widgets/src/WidgetBar.cpp \
	Common/Widgets/src/ArrowButton.cpp \
	Common/Widgets/src/RightClickMenu.cpp \
	Config/src/Config.cpp \
	Libs/inih/ini.c \
	Libs/inih/INIReader.cpp \
	Resources/Fonts/chivo_bold.cpp \
	Resources/Fonts/chivo_italic.cpp \
	WolfShaperUI.cpp 

# --------------------------------------------------------------
# Do some magic

include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Additional flags

ADDITIONAL_INCLUDES=-I. -I../../dpf/distrho -I../../dpf/dgl -I./Common/Structures -I./Common/Widgets -I./Common/Utils -I./Resources -I./Config -I./Libs/inih -I./Libs/DSPFilters/include

BASE_FLAGS += $(ADDITIONAL_INCLUDES) -DDISTRHO_NAMESPACE=$(DISTRHO_NAMESPACE) -DDGL_NAMESPACE=$(DGL_NAMESPACE) -DPLUGIN_NAME=\"$(NAME)\"
LINK_FLAGS += -lpthread

ifeq ($(PARANOID_MODE),true)
BASE_FLAGS += -Wall -Wextra -Werror
endif

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(BUILD_JACK),true)
ifeq ($(HAVE_JACK),true)
TARGETS += jack
endif
endif

ifeq ($(BUILD_LADSPA),true)
TARGETS += ladspa
endif

ifeq ($(BUILD_DSSI),true)
ifeq ($(HAVE_DGL),true)
ifeq ($(HAVE_LIBLO),true)
TARGETS += dssi
endif
endif
endif

ifeq ($(BUILD_LV2),true)
ifeq ($(HAVE_DGL),true)
TARGETS += lv2_sep
else
TARGETS += lv2_dsp
endif
endif

ifeq ($(BUILD_VST2),true)
TARGETS += vst
endif

all: $(TARGETS)

# --------------------------------------------------------------
