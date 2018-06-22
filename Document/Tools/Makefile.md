# Makefile

## 样例
* 编辑math.cpp代码
    ```
    #define API extern "C"

    API int square(int x)
    {
	    return x * x;
    }
    ```
* 编辑Makefile.txt文件
    ```
    CC=emcc
    CPPFLAGS=-g -std=gnu++11 -Wall -Wno-gnu-zero-variadic-macro-arguments -pedantic
    EMFLAGS = -s BINARYEN_ASYNC_COMPILATION=0 -s WASM=1 -s SIDE_MODULE=1

    DIR_INC = -I./
    DIR_SRC = ./

    sources=math.cpp
    objects=$(sources:.cpp=.o)
    dependence=$(sources:.cpp=.d)

    all: $(objects)
        $(CC) $(CPPFLAGS) $(EMFLAGS) $(objects) -o math.wasm

    #include $(dependence)

    {$(DIR_SRC)}.cpp.o:
        $(CC) $(CPPFLAGS) $< $(DIR_INC) -o $@

    %.d : %.cpp
        @set -e; \
        rm -f $@; \
        $(CC) -M $(CPPFLAGS) $(EMFLAGS) $< > $@.$$$$; \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
        rm -f $@.$$$$

    .PHONY : clean

    clean :
        -rm all $(dependence) $(objects)
    ```