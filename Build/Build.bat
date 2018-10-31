
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
echo %cd%

::TOTAL_MEMORY=1024*1024*1024
::ALLOW_MEMORY_GROWTH=1 会影响一些性能优化
call emcc -O3 libCore.so libGraphics.so libTest.so -s USE_WEBGL2=1 -s FULL_ES3=1 -s TOTAL_MEMORY=536870912 -s WASM=1 -o index.html

echo "==2======================================"
pause