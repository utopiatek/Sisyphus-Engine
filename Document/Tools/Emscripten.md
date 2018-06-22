# Emscripten

## 安装
* 下载安装GIT
    > 下载，运行[GIT](https://git-scm.com/download/win)安装程序
* 下载安装Python
    > 下载安装Python2.7

    > 拷贝python\2.7.5.3_64bit文件夹到Emsdk文件夹下

    > Emscripten SDK需要使用python2.7进行安装
* 下载安装Emscripten SDK
    > 下载，解压[EMSDK](https://github.com/juj/emsdk)程序包到Emsdk文件夹下，当前版本1.38.5

    > 以管理员身份运行控制台，切换到Emsdk文件夹

    > 执行命令`emsdk install latest --vs2017`

    > 执行命令`emsdk activate latest`

    > 注意：在使用EMSDK前需要调用emsdk_env命令来设置环境变量

    > EMSDK提供命令提示符“emcmdprompt.bat”，启动后自动设置环境变量
* 安装支持WASM的浏览器
    > 下载安装[Chrome](https://www.google.cn/intl/zh-CN/chrome/browser/thankyou.html?standalone=1&statcb=1&installdataindex=defaultbrowser#)

## 编译Makefile
* 启动“emcmdprompt.bat”
* 执行命令：`emmake nmake -f Makefile.txt`
