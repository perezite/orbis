LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(LOCAL_PATH)/../../Utils.mk
LOCAL_MODULE := Base
CODE_PATH := $(LOCAL_PATH)/../../../../../src/Base
#LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(CODE_PATH)/Math
FILE_LIST := $(call walksources, $(CODE_PATH))
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
include $(BUILD_SHARED_LIBRARY)
