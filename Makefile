ARCHS = arm64 #arm64e
INSTALL_TARGET_PROCESSES = SpringBoard
#INSTALL_TARGET_PROCESSES = Preferences
TARGET := iphone:clang:14.5:13.0
export SYSROOT = /Users/runner/theos/sdks/iPhoneOS14.5.sdk

include /Users/runner/theos/makefiles/common.mk

TWEAK_NAME = Cardculator

Cardculator_PRIVATE_FRAMEWORKS = SpringBoard SpringBoardServices SpringBoardFoundation MediaRemote MobileTimer SpringBoardUI
Cardculator_FILES = $(shell find Sources/Cardculator -name '*.swift') $(shell find Sources/CardculatorC -name '*.m' -o -name '*.c' -o -name '*.mm' -o -name '*.cpp')
Cardculator_SWIFTFLAGS = -ISources/CardculatorC/include
Cardculator_CFLAGS = -fobjc-arc -ISources/CardculatorC/include

include /Users/runner/theos/makefiles/tweak.mk
SUBPROJECTS += prefs
SUBPROJECTS += cardculatorccmodule
include /Users/runner/theos/makefiles/aggregate.mk
