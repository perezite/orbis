LOCAL_PATH := $(call my-dir)

# OpenGLEngine module
##################
include $(CLEAR_VARS)
LOCAL_MODULE := openGLSharedLibrary
LOCAL_SRC_FILES := ../../lib/OpenGLEngine/$(TARGET_ARCH_ABI)/libOpenGLEngine.so
include $(PREBUILT_SHARED_LIBRARY)

# SDL2 module
##################
include $(CLEAR_VARS)
LOCAL_MODULE := SDL2
LOCAL_SRC_FILES := ../../lib/SDL2/$(TARGET_ARCH_ABI)/libSDL2.so
include $(PREBUILT_SHARED_LIBRARY)

# Base module
##################
include $(CLEAR_VARS)
include $(LOCAL_PATH)/Utils.mk
LOCAL_MODULE := Base
CODE_PATH := $(LOCAL_PATH)/../../../../src/Base
FILE_LIST := $(call walksources, $(CODE_PATH))
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
include $(BUILD_SHARED_LIBRARY)

# Orbis Module
#####################
include $(CLEAR_VARS)
include $(LOCAL_PATH)/Utils.mk
LOCAL_MODULE := Orbis
MY_CODE_PATH := $(LOCAL_PATH)/../../../../src/Orbis
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../include \
    $(LOCAL_PATH)/../../../common/include
FILE_LIST = $(call walksources, $(MY_CODE_PATH))
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_SHARED_LIBRARIES := Base SDL2 openGLSharedLibrary
LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog
include $(BUILD_SHARED_LIBRARY)

# Application Module
#####################
include $(CLEAR_VARS)
include $(LOCAL_PATH)/Utils.mk
LOCAL_MODULE := main
MY_CODE_PATH := $(LOCAL_PATH)/../../../../src/ExampleGame
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../include \
    $(LOCAL_PATH)/../../../common/include
FILE_LIST := $(call walksources, $(MY_CODE_PATH))
PROJECT_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES := SDL_android_main.c \
    $(PROJECT_FILES)
LOCAL_SHARED_LIBRARIES := Orbis Base SDL2 openGLSharedLibrary
include $(BUILD_SHARED_LIBRARY)