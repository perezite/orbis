LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Base

CODE_PATH := ../../../../../src/Base

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(CODE_PATH)/Math

LOCAL_SRC_FILES := $(CODE_PATH)/Math/Vector2D.cpp

include $(BUILD_SHARED_LIBRARY)
