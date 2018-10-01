

// 一个默认表面（默认是高效的），多个用户自定义表面（通常用于一些后期特效）
// 创建RenderTarget，绑定RenderTarget，绑定null为默认RenderTarget
// RenderTarget创建后可以重新附着贴图。
// RenderTarget之间可以 共享颜色，深度，模板缓冲区
// https://blog.csdn.net/hi_zhengjian/article/details/48780867
用函数glDrawBuffers来对着色器输出进行路由
//http://docs.gl/es3/glDrawBuffers

