# Git

## 安装
* 下载，运行[GIT](https://git-scm.com/download/win)安装程序

## 使用Visual Studio Code
* 克隆仓库到本地
    > git clone repository-url local-path
* 配置GIT用户信息
    > git config --global user.name "name"

    > git config --global user.email "email"
* 修改文件
    > 被修改文件会有“M”已修改标志，点击“M”显示修改前后对比
* 暂存更改
    > 点击放弃更改相当于撤销
    
    > 点击“+”号暂存更改，点击“-”号取消暂存更改
* 提交更改
    > 点击“√”提交更改
* 同步
    > 点击同步，输入账号密码，代码同步到GitHub
* 配置.gitignore文件
```
/.git/
/.vs/
/Build/Bin/
/Build/Object/
```

## 使用Visual Studio 2017、Github
* 安装Github插件
	> 工具 \> 扩展和更新 \> 联机 \> Github Extension for Visual Studio \> 下载 \> 安装
* 克隆存储库
	> 团队资源管理器-管理连接-GitHub \> Connect \> Sign In \> Clone
* 打开解决方案
	> 团队资源管理器-管理连接-本地GIT存储库 \> 双击存储库 \> 团队资源管理器-主页-解决方案 \> 显示文件夹视图 \> 解决方案资源管理器

	> 解决方案资源管理器 \> 解决方案和文件夹 \> 切换管理器模式
* 更新文件
	> 文件 \> 高级保存选项 \> Unicode（UTF-8 带签名）- 代码页 65001

	> 团队资源管理器-主页-项目 \> 更改 \> 全部提交

	> 团队资源管理器-主页-项目 \> 同步 \> 传出提交-推送
