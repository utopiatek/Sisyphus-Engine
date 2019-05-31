CMAKE_MINIMUM_REQUIRED(VERSION 3.8)
PROJECT(Thirdparty)
SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_CXX_STANDARD 14)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../Build/Bin/${CMAKE_SYSTEM_NAME})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../Build/Bin/${CMAKE_SYSTEM_NAME})
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})
if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
LINK_DIRECTORIES(../Thirdparty/Lib/32/)
else()
LINK_DIRECTORIES(../Thirdparty/Lib/64/)
endif()
#ADD_SUBDIRECTORY(FreeImage)

#GL: https://github.com/KhronosGroup/OpenGL-Registry
#GLEW: http://glew.sourceforge.net/
#EGL(KHR/khrplatform.h): https://github.com/KhronosGroup/EGL-Registry
#DirectXMath: https://github.com/Microsoft/DirectXMath
#FreeImage: http://freeimage.sourceforge.net/download.html