
//http://10.0.0.19/Emscripten/Out.html

// 3+3+3=9+3=12
// 1024 * 1024 * 12 = 12M 一百万个面，for循环最多128次
// 最极限，点被半球包围，半径128米，128*3.14，精度3.14米，样点数128*128
// 样点数太多，动态场景问题，体素化，只能应用辐射度
// 1024 * 1024 * 128 = 128M;
// 光线追踪效果最好，需要每个角度去检测（球谐），每个点都要有一个环境贴图

// 球谐函数+稀疏体素八叉树，球谐记录射线距离，基于距离在体素中查找相应的相交点，求面积分可以获取环境光遮蔽信息
// 体素细分方法，空旷区域细分较粗，狭隘区域细分较细
// 按三角形划分，最小精度1米，最大精度2厘米，子节点超过4个，则对子节点进行细分
// 查找，基于坐标，找到叶子节点；
// 查找优化：根节点是平面图，垂直上进行二叉树划分


// 渲染组件、网格组件
// 


/*
设计：
组件可以自定义：比如地形网格组件，地形网格渲染组件；
组件自定义需要使用到引擎提供的一些部件：比如顶点缓存；
组件有自己的内存管理手段；
组件有自己的动态管理方法，比如读写，变换反馈；

封装：
缓存对象：常量缓存，顶点缓存，索引缓存，变换反馈缓存
顶点缓存有两种，结构数组、数组结构

数组结构：
顶点不同属性分别赋值，保存在不同缓存中，使用顶点数组对象打包；
结构数组（效率更高）：
不支持，特别是在其它语言中内存布局不好处理（或者支持设置整段数据块，同时设置布局）
能不能不同网格共用缓存：
配置顶点数组对象时指针含义为第一个元素的偏移量
绘制函数可以指定索引偏移
结论：不同网格对象可共用一个VAO

// 获取活动常量缓存索引：可以获取活动常量缓存数量，再遍历索引获取名称，也可以通过名称获取索引
// 将常量缓存索引映射到一个插槽，通过插槽绑定数据
// 映射是一个常量缓存的绑定对多个着色器都有效
// 常量访问不需指定块名
// 资源工厂可以配置默认常量缓存绑定映射（名称->插槽）
// 创建着色器程序时，追加没有的绑定映射（名称->插槽），将名称与插槽绑定
// 通过名称查找到插槽，在通过插槽绑定常量缓存
// 通过GL_MAX_UNIFORM_BUFFER_BINDINGS查询可以绑定点数，一般为36
// https://blog.csdn.net/csxiaoshui/article/details/32101977
// http://www.zwqxin.com/archives/shaderglsl/communication-between-opengl-glsl-2.html
// https://developer.mozilla.org/en-US/docs/Web/API/WebGL2RenderingContext#Uniform_buffer_objects
// A0 B1
// A0 C1
// A0 B1 C？
// 基于以上可知不可分配全局绑定点，分全局绑定点和局部绑定点，全局针对摄像机数据这些，局部针对材质，着色器这些。
配置文件声明若干常量缓存块，着色器只能使用已声明的这些常量缓存块
用户可自定义其中两个常量缓存块，一个时着色器常量，一个是材质常量


OpenGL加载图片作为纹理需要依赖其它库
之前有实现加载DDS，WEBGL支持以下压缩格式：
glCompressedTexImage2D加载：
ETC2（不支持3D纹理）、EAC（不支持3D纹理）
glCompressedTexImage3D加载厂商专用3D纹理压缩格式：


// 缓存对象。

 304 306 303 325 324
*/

// DirectXMath
// https://www.cnblogs.com/X-Jun/p/9041966.html
// https://github.com/Microsoft/DirectXMath/blob/master/Inc/DirectXMath.h

// note that currently - 2018-7-11 - only asm.js supports SIMD


#define _XM_NO_INTRINSICS_
#include "DirectXMath/Inc/DirectXMath.h"

// 下载最新DirectXMath库
// 拷贝sal.h和concurrencysal.h文件
// 定义_XM_NO_INTRINSICS_
// 设置fdeclspec编译宏
// -Wignored-attributes

	DirectX::XMFLOAT3  position;
	position.x = 155.8f;

	DirectX::XMVECTOR myVector = XMLoadFloat3(&position);

	DirectX::XMFLOAT3  position2;
	DirectX::XMStoreFloat3(&position2, myVector);


	Opengl下载： https://www.khronos.org/registry/OpenGL/
	<GL/glext.h>：扩展头文件。因为微软公司对OpenGL的支持不太积极，VC系列编译器虽然有<GL/gl.h>这个头文件，但是里面只有OpenGL 1.1版本中所规定的内容，
	而没有OpenGL 1.2及其以后版本。对当前的计算机配置而言，几乎都支持OpenGL 1.4版本，更高的则到1.5, 2.0, 2.1，而VC无法直接使用这些功能。
	为了解决这一问题，就有了<GL/glext.h>头文件。这个头文件提供了高版本OpenGL所需要的各种常数声明以及函数指针声明。

	OPENGL 调试工具 RenderDoc https://www.khronos.org/opengl/wiki/Debugging_Tools https://renderdoc.org/
	https://developer.nvidia.com/nsight-visual-studio-edition
	https://www.cnblogs.com/minggoddess/p/5465075.html
	需要调用wglSwapLayerBuffers(m_hDC, 0);调试器才能捕捉到信息

	CMAKE一些问题：https://www.jianshu.com/p/5ad9934f3e98

	WGL： http://www.mamicode.com/info-detail-2118543.html
	https://blog.csdn.net/SUKHOI27SMK/article/details/82492946

	引用类型传参：Transform->Position(SSEFloat3()); 参数声明必须带CONST：SEVoid Position(SEConst SSEFloat3& mPosition)

	声明precision mediump float;如果两个着色器声明相同类型的常量缓存块会导致链接失败，使用precision highp float;

	左手坐标系：X向右，Y向上，Z向前。
	矩阵变换，在C++中从左往右乘，在GLSL中从右往左乘
	旋转使用弧度，旋转轴朝里，逆时针旋转为正


	如果没有自定义拷贝构造函数，系统会提供一个缺省的拷贝构造函数，缺省的拷贝构造函数对于基本类型的成员变量，按字节复制，对于类类型成员变量，调用其相应类型的拷贝构造函数

	struct A
{
public:
	A(int _a)
		:a(_a)
	{
		printf("--------------------------\n");
	}
	/// 自定义拷贝构造函数，缺省拷贝构造函数是浅拷贝
	A(const A& a_)
	{
		a = 4;
		printf("2--------------------------\n");
	};
	~A()
	{
		printf("~~~~~~~~~~~\n");
	}
	int a;
};


A CloneA(A a) 
{
	/// 存在一个拷贝构造
	return a;
}

/// 构造直接赋值跟参数，不是构造一个对象在拷贝赋值参数
A a = CloneA(A(2));
/// 存在一个拷贝构造
A b = CloneA(b);


// https://blog.csdn.net/u010780613/article/details/54923139
// https://blog.csdn.net/jadeshu/article/details/21254587










