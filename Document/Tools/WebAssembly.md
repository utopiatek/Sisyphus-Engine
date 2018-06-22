# WebAssembly

## 资料
* [官网](https://webassembly.org/)
* [中文官网](https://wasm-cn.org/)
* [中文MDN](https://developer.mozilla.org/zh-CN/docs/WebAssembly)
* [在线开发工具](https://webassembly.studio/)

## 样例
* 编辑math.c代码
    ```
    int square (int x)
    {
    return x * x;
    }
    ```
* 编译math.c代码为math.wasm代码
    > 启动“emcmdprompt.bat”

    > 执行命令：`emcc math.c -Os -s BINARYEN_ASYNC_COMPILATION=0 -s WASM=1 -s SIDE_MODULE=1 -o math.wasm`
* 编辑loader.js代码
    ```
    function Config() {
    var pImports = {
        env: {
        memoryBase: 0,
        tableBase: 0,
        memory: new WebAssembly.Memory({ initial: 256, maximum: 1024 }),
        table: new WebAssembly.Table({ initial: 2, maximum: 8, element: 'anyfunc' }),
        DYNAMICTOP_PTR: 0,
        tempDoublePtr: 0,
        ABORT: 0,
        abortStackOverflow: function (allocSize) { },
        nullFunc_X: function () { },
        abort: function () { }
        },
        global: {
        NaN: 0,
        Infinity: 0
        }
    };

    pImports.env.table.set(0, null);
    pImports.env.table.set(0, null);

    return pImports;
    }

    function LoadWASM(pFileName, pImports = {}) {
    return fetch(pFileName)
        .then(response => response.arrayBuffer())
        .then(buffer => WebAssembly.compile(buffer))
        .then(bytes => WebAssembly.instantiate(bytes, pImports))
        .catch(console.error);
    }
    ```
* 在HTML在中载入WASM代码并调用函数
    ```
    <script src="loader.js"></script>
    <script>
        LoadWASM('math.wasm', Config())
        .then(instance => {
            const square = instance.exports._square;
            alert('2 * 2 = '+ square(2));
        })
    </script>
    ```