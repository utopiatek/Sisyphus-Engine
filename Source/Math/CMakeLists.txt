PROJECT(Math)
AUX_SOURCE_DIRECTORY(./Src DIR_SRC)
ADD_DEFINITIONS(-DSE_DLL)
if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
ADD_DEFINITIONS(-fdeclspec) #����DirectXMath
ADD_DEFINITIONS(-Wno-ignored-attributes) #����DirectXMath������__fastcall����Լ���Ƴ�����
endif()
ADD_LIBRARY(Math SHARED ${DIR_SRC})
TARGET_LINK_LIBRARIES(Math Core)