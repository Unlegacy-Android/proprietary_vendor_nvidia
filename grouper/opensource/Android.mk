LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := \
	libnvos.c

LOCAL_CFLAGS := -Wall -Werror

LOCAL_MODULE := libnvos

include $(LOCAL_STATIC_LIBRARIES)