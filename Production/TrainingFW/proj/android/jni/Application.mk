APP_STL := gnustl_static 
APP_ABI := x86
APP_CPPFLAGS := -frtti
APP_CPPFLAGS += -fexceptions \
				-DOS_ANDROID \
				-D_ANDROID

NDK_TOOLCHAIN_VERSION := 4.8