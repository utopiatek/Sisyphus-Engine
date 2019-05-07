
@echo off

title Build Sysphus3D

echo "==SET EMSDK ENVIRONMENT=================================="
echo.

echo "CUSTOM VAR: EMSDK_HOME, NMAKE_HOME, CMAKE_HOME"
set EMSDK_HOME=E:/Workplace/EMSDK
set VS_HOME=C:/Program Files (x86)/Microsoft Visual Studio/2019/Professional
set NMAKE_HOME=%VS_HOME%/VC/Tools/MSVC/14.20.27508/bin/Hostx64/x64
set CMAKE_HOME=%VS_HOME%/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin

call %EMSDK_HOME%/emsdk_env.bat

::等号两边不能有空格
::需要设置NMake和CMake的路径

set cwd=%cd%
set build_dir=%cd%"/Object"
set build_source=%build_dir%"/Sysphus3D"
set build_thirdparty=%build_dir%"/Thirdparty"
set bin_dir=%cd%"/Bin/Emscripten"
set file_dir=%cd%"/../Source/Engine/Res/@/"
set EMSDK_INC=%EMSDK%"/emscripten/1.38.30/system/include"
set PATH=%PATH%;%NMAKE_HOME%;%CMAKE_HOME%

if not exist %build_dir% (
    md %build_dir%
)
if not exist %build_source% (
    md %build_source%
)
if not exist %build_thirdparty% (
    md %build_thirdparty%
)

cd %build_source%
call emconfigure cmake -G"NMake Makefiles" -DCMAKE_BUILD_TYPE=Release %cwd%"/../Source/"
call emmake nmake -f Makefile

cd %build_thirdparty%
call emconfigure cmake -G"NMake Makefiles" -DCMAKE_BUILD_TYPE=Release %cwd%"/../Thirdparty/"
call emmake nmake -f Makefile

cd %bin_dir%
echo %cd%

::TOTAL_MEMORY=1024*1024*1024
::ALLOW_MEMORY_GROWTH=1 会影响一些性能优化
::X5只支持分配256内存
call emcc -O3 libCore.so libMath.so libGraphics.so libEngine.so libTest.so -s USE_WEBGL2=1 -s FULL_ES3=1 -s TOTAL_MEMORY=268435456 -s ASSERTIONS=1 -s WASM=1 -o index.html --preload-file %file_dir%

echo "==BUILD END=============================================="
pause