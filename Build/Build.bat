
@echo off

title Build Sysphus3D

echo "==SET EMSDK ENVIRONMENT=================================="
echo.

call emsdk_env.bat

set cwd=%cd%
set build_dir=%cd%"/Object"
set build_source=%build_dir%"/Sysphus3D"
set build_thirdparty=%build_dir%"/Thirdparty"
set bin_dir=%cd%"/Bin/Emscripten"
set file_dir=%cd%"/../Source/Engine/Res/@/"

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
::libFreeImage.so
call emcc -O3 libCore.so libMath.so libGraphics.so libEngine.so libTest.so -s USE_WEBGL2=1 -s FULL_ES3=1 -s TOTAL_MEMORY=268435456 -s ASSERTIONS=1 -s WASM=1 -o index.html --preload-file %file_dir%

echo "==2======================================"
pause