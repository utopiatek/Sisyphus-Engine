# WebAssembly

## ����
* [����](https://webassembly.org/)
* [���Ĺ���](https://wasm-cn.org/)
* [����MDN](https://developer.mozilla.org/zh-CN/docs/WebAssembly)
* [���߿�������](https://webassembly.studio/)

## ����
* �༭math.c����
    ```
    int square (int x)
    {
    return x * x;
    }
    ```
* ����math.c����Ϊmath.wasm����
    > ������emcmdprompt.bat��

    > ִ�����`emcc math.c -Os -s BINARYEN_ASYNC_COMPILATION=0 -s WASM=1 -s SIDE_MODULE=1 -o math.wasm`
* �༭loader.js����
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
* ��HTML��������WASM���벢���ú���
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