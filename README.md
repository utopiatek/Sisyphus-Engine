# Sisyphus Engine
Game Engine

## 存储库
* 文件夹结构
	```
	Sisyphus Engine
	+---Build
	|	+---Bin
	|	+---Object
	+---Document
	+---Dependency
	+---Source
		+---Core
		+---Math
		+---Test
	```
* ~~解决方案~~
	* ~~添加共享项目：Build/Source/Core.vcxitems~~
	* ~~添加共享项目：Build/Source/Test.vcxitems~~
	* ~~添加控制台项目：Build/Project/System/Test.vcxproj~~
		> ~~引用共享项目：Build/Source/Test.vcxitems~~

		> ~~设置输出目录：$(SolutionDir)Temp\Link\$(Platform)\$(Configuration)\~~

		> ~~设置中间目录：$(SolutionDir)Temp\Compile\$(Platform)\$(Configuration)\~~

		> ~~设置附加包含目录：$(SolutionDir)..\Src\~~

		> ~~设置后期生成事件：xcopy /y "$(OutDir)$(TargetFileName)" "$(SolutionDir)Bin\$(Platform)\$(Configuration)\"~~