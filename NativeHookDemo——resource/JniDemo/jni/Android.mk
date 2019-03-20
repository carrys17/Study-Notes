
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := hook
LOCAL_SRC_FILES := inlineHook.c relocate.c hooktest.c

LOCAL_LDLIBS += -lz

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_LDLIBS += -llog


include $(BUILD_SHARED_LIBRARY)