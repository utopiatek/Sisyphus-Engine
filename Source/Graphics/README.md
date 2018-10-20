

// 一个默认表面（默认是高效的），多个用户自定义表面（通常用于一些后期特效）
// 创建RenderTarget，绑定RenderTarget，绑定null为默认RenderTarget
// RenderTarget创建后可以重新附着贴图。
// RenderTarget之间可以 共享颜色，深度，模板缓冲区
// https://blog.csdn.net/hi_zhengjian/article/details/48780867
用函数glDrawBuffers来对着色器输出进行路由
//http://docs.gl/es3/glDrawBuffers

GL_PIXEL_UNPACK_BUFFER有两种主要的使用PBO提高传输像素数据的方式：上传到纹理和从帧缓冲区中进行异步回读。
但是WEBGL没有MAP函数，所以上传数据到纹理不会高效


注意如果GPU仍使用此缓冲区对象，glMapBufferARB()不会返回，直到GPU完成了对对应缓冲区对象的操作。为了避免等待，在使用glMapBufferARB之前，使用glBufferDataARB，并传入参数NULL。
然后，OpenGL将废弃旧的缓冲区，为缓冲区分配新的内存。 缓冲区对象必须取消映射,可使用glUnmapBufferARB()。如果成功，glUnmapBufferARB()返回GL_TRUE 否则返回GL_FALSE。
例子:Streaming Texture Uploads
https://blog.csdn.net/dreamcs/article/details/7708018

