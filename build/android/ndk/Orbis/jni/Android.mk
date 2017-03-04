LOCAL_PATH := $(call my-dir)

# Orbis Dependencies
#####################
include $(LOCAL_PATH)/Modules.mk

# Orbis Module
#####################
include $(CLEAR_VARS)
include $(LOCAL_PATH)/Libraries.mk
include $(LOCAL_PATH)/../../Utils.mk
LOCAL_MODULE := Orbis
MY_CODE_PATH := $(LOCAL_PATH)/../../../../../src/Orbis
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../include \
    $(LOCAL_PATH)/../../../../common/include
FILE_LIST = $(call walksources, $(MY_CODE_PATH))
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_SHARED_LIBRARIES := $(ORBIS_SHARED_LIBS)
LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog
include $(BUILD_SHARED_LIBRARY)