LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

# 遍历目录及子目录的函数  
define walk  
    $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))  
endef  

# 遍历Classes目录  
ALLFILES = $(call walk, $(LOCAL_PATH)/../../../Classes)  

#$(info $(ALLFILES))  #用来打印信息# 
FILE_LIST := hellocpp/main.cpp  
# 从所有文件中提取出所有.cpp文件  
FILE_LIST += $(filter %.cpp, $(ALLFILES))
#$(info $(FILE_LIST))  #用来打印信息# 

LOCAL_SRC_FILES := FILE_LIST
                  # hellocpp/main.cpp \
                  # ../../../Classes/AppDelegate.cpp 
                  # ../../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static\
                          android_support

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,android/support)#添加android iconv库

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
