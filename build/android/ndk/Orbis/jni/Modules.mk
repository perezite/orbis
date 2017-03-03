# OpenGLEngine module
##################
include $(CLEAR_VARS)
LOCAL_MODULE := openGLSharedLibrary
LOCAL_SRC_FILES := ../../../lib/OpenGLEngine/$(TARGET_ARCH_ABI)/libOpenGLEngine.so
include $(PREBUILT_SHARED_LIBRARY)

# SDL2 module
##################
include $(CLEAR_VARS)
LOCAL_MODULE := SDL2
LOCAL_SRC_FILES := ../../../lib/SDL2/$(TARGET_ARCH_ABI)/libSDL2.so
include $(PREBUILT_SHARED_LIBRARY)

# Base module
##################
include $(CLEAR_VARS)
LOCAL_MODULE := Base
LOCAL_SRC_FILES := ../../../lib/Base/libs/$(TARGET_ARCH_ABI)/libBase.so
include $(PREBUILT_SHARED_LIBRARY)
