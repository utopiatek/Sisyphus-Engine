PROJECT(Math)
AUX_SOURCE_DIRECTORY(./Src DIR_SRC)
ADD_DEFINITIONS(-DSE_DLL)
if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
ADD_DEFINITIONS(-fdeclspec) #编译DirectXMath
ADD_DEFINITIONS(-Wno-ignored-attributes) #编译DirectXMath，屏蔽__fastcall调用约定移除警告
endif()
ADD_LIBRARY(Math SHARED ${DIR_SRC})
TARGET_LINK_LIBRARIES(Math Core)