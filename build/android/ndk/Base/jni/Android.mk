LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
CODE_PATH := ../../../../../src/Base
LOCAL_MODULE := Base
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(CODE_PATH)/Math
LOCAL_SRC_FILES := $(CODE_PATH)/Math/Vector2D.cpp
include $(BUILD_SHARED_LIBRARY)
