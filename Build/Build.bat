
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

::call emcc libCore.so libMath.so libTest.so -o Out.html
::TOTAL_MEMORY=1024*1024*1024
::ALLOW_MEMORY_GROWTH=1 会影响一些性能优化
call emcc -s TOTAL_MEMORY=1073741824 libCore.so libTest.so -o Out.html
::emcc -s BINARYEN_ASYNC_COMPILATION=0 -s WASM=1 -s SIDE_MODULE=1 libCore.so -o Out

echo "==2======================================"
pause