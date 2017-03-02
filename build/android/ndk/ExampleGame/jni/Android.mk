LOCAL_PATH := $(call my-dir)

# Orbis Libraries
##################
include $(LOCAL_PATH)/../../Orbis/jni/Libraries.mk

# Orbis module
##################
include $(CLEAR_VARS)
LOCAL_MODULE := Orbis
LOCAL_SRC_FILES := ../../../lib/Orbis/libs/$(TARGET_ARCH_ABI)/libOrbis.so
include $(PREBUILT_SHARED_LIBRARY)

# Application Module
#####################
include $(CLEAR_VARS)
LOCAL_MODULE := main
MY_CODE_PATH := ../../../../../src
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../include \
    $(LOCAL_PATH)/../../../../common/include
LOCAL_SRC_FILES := SDL_android_main.c \
    $(MY_CODE_PATH)/ExampleGame/Main.cpp
LOCAL_SHARED_LIBRARIES := Base Orbis SDL2 openGLSharedLibrary
# LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog
include $(BUILD_SHARED_LIBRARY)