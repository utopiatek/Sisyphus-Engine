# CMake

## 安装
* 下载，运行[cmake-3.11.3-win64-x64.msi](https://cmake.org/download/)安装程序

## 样例
* Source/Core/CMakeLists.txt
    ```
    PROJECT(Core)
	AUX_SOURCE_DIRECTORY(./Src DIR_SRC)
	ADD_DEFINITIONS(-DSE_DLL)
	ADD_LIBRARY(Core SHARED ${DIR_SRC})
    ```
* Source/Math/CMakeLists.txt
    ```
    PROJECT(Math)
	AUX_SOURCE_DIRECTORY(./Src DIR_SRC)
	ADD_DEFINITIONS(-DSE_DLL)
	ADD_LIBRARY(Math SHARED ${DIR_SRC})
	TARGET_LINK_LIBRARIES(Math Core)
    ```
* Source/Test/CMakeLists.txt
    ```
	PROJECT(Test)
	AUX_SOURCE_DIRECTORY(./Src DIR_SRC)
	if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	ADD_LIBRARY(Test SHARED ${DIR_SRC})
	else()
	ADD_EXECUTABLE(Test ${DIR_SRC})
	endif()
	TARGET_LINK_LIBRARIES(Test Core Math)
    ```
* Source/CMakeLists.txt
    ```
	CMAKE_MINIMUM_REQUIRED(VERSION 3.8)
	PROJECT(Sysphus3D)
	SET(CMAKE_VERBOSE_MAKEFILE ON)
	SET(CMAKE_CXX_STANDARD 11)
	SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../Build/Bin/${CMAKE_SYSTEM_NAME})
	SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../Build/Bin/${CMAKE_SYSTEM_NAME})
	LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})
	INCLUDE_DIRECTORIES(./)
	ADD_SUBDIRECTORY(Core)
	ADD_SUBDIRECTORY(Math)
	ADD_SUBDIRECTORY(Test)
    ```
* Build/Build.bat
    ```
	@echo off

	title Build Sysphus3D

	echo "==SET EMSDK ENVIRONMENT=================================="
	echo.

	call emsdk_env.bat

	set cwd=%cd%
	set build_dir=%cd%"/Object"
	set bin_dir=%cd%"/Bin/Emscripten"

	if not exist %build_dir% (
		md %build_dir%
	)

	cd %build_dir%

	call emconfigure cmake -G"NMake Makefiles" -DCMAKE_BUILD_TYPE=Release %cwd%"/../Source/"
	call emmake nmake -f Makefile

	cd %bin_dir%

	call emcc libCore.so libMath.so libTest.so -o Out.html
	::emcc -s BINARYEN_ASYNC_COMPILATION=0 -s WASM=1 -s SIDE_MODULE=1 libCore.so -o Out

	pause
    ```
## 使用Visual Studio 2017
