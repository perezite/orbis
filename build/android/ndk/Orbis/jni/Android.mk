LOCAL_PATH := $(call my-dir)

# Libraries
include $(LOCAL_PATH)/Libraries.mk

# Orbis Module
#####################
include $(CLEAR_VARS)
LOCAL_MODULE := Orbis
MY_CODE_PATH := ../../../../../src
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../include \
    $(LOCAL_PATH)/../../../../common/include
LOCAL_SRC_FILES := $(MY_CODE_PATH)/Orbis/SDL_main.cpp \
    $(MY_CODE_PATH)/Orbis/CheesyHelper.cpp
LOCAL_SHARED_LIBRARIES := SDL2 openGLSharedLibrary Base
LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog
include $(BUILD_SHARED_LIBRARY)