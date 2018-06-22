# Bower

## 使用Visual Studio Code
* 类似于NuGet，用于管理各种依赖库
* 在已经安装Git的前提下安装Bower插件
* 新建.bowerrc文件，设置包管理路径
```
{
    "directory": "lib"
}
```
* 新建bower.json文件，配置依赖项
```
{
    "name": "learn-web",
    "private": true,
    "dependencies": {
        "react": "latest",
        "babel": "latest",
        "babel-standalone": "latest",
        "jquery": "latest",
        "semantic-ui": "latest"
    }
}
```
* 安装依赖项 `Bower Install`
