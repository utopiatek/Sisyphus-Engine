# Sisyphus Engine
Game Engine

### Visual Studio 2017
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

### 存储库
* 文件夹结构
	```
	Sisyphus Engine
	+---Build
	|	+---Project
	|	|	+---Module
	|   |	+---System
	|	+---Source
	+---Document
	+---Dependency
	+---Source
		+---Core
		+---Test
	```
* 解决方案
	* 添加共享项目：Build/Source/Core.vcxitems
	* 添加共享项目：Build/Source/Test.vcxitems
	* 添加控制台项目：Build/Project/System/Test.vcxproj
		> 引用共享项目：Build/Source/Test.vcxitems

		> 设置输出目录：$(SolutionDir)Temp\Link\$(Platform)\$(Configuration)\

		> 设置中间目录：$(SolutionDir)Temp\Compile\$(Platform)\$(Configuration)\

		> 设置附加包含目录：$(SolutionDir)..\Src\

		> 设置后期生成事件：xcopy /y "$(OutDir)$(TargetFileName)" "$(SolutionDir)Bin\$(Platform)\$(Configuration)\"