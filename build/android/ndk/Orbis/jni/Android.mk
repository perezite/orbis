LOCAL_PATH := $(call my-dir)

# Orbis Dependencies
#####################
include $(LOCAL_PATH)/Modules.mk

# Orbis Module
#####################
include $(CLEAR_VARS)
include $(LOCAL_PATH)/Libraries.mk
LOCAL_MODULE := Orbis
MY_CODE_PATH := ../../../../../src
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../include \
    $(LOCAL_PATH)/../../../../common/include
LOCAL_SRC_FILES := $(MY_CODE_PATH)/Orbis/SDL_main.cpp \
    $(MY_CODE_PATH)/Orbis/CheesyHelper.cpp
LOCAL_SHARED_LIBRARIES := $(ORBIS_SHARED_LIBS)
LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog
include $(BUILD_SHARED_LIBRARY)