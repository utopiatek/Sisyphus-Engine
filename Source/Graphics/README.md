

// һ��Ĭ�ϱ��棨Ĭ���Ǹ�Ч�ģ�������û��Զ�����棨ͨ������һЩ������Ч��
// ����RenderTarget����RenderTarget����nullΪĬ��RenderTarget
// RenderTarget������������¸�����ͼ��
// RenderTarget֮����� ������ɫ����ȣ�ģ�建����
// https://blog.csdn.net/hi_zhengjian/article/details/48780867
�ú���glDrawBuffers������ɫ���������·��
//http://docs.gl/es3/glDrawBuffers

GL_PIXEL_UNPACK_BUFFER��������Ҫ��ʹ��PBO��ߴ����������ݵķ�ʽ���ϴ�������ʹ�֡�������н����첽�ض���
����WEBGLû��MAP�����������ϴ����ݵ��������Ч


ע�����GPU��ʹ�ô˻���������glMapBufferARB()���᷵�أ�ֱ��GPU����˶Զ�Ӧ����������Ĳ�����Ϊ�˱���ȴ�����ʹ��glMapBufferARB֮ǰ��ʹ��glBufferDataARB�����������NULL��
Ȼ��OpenGL�������ɵĻ�������Ϊ�����������µ��ڴ档 �������������ȡ��ӳ��,��ʹ��glUnmapBufferARB()������ɹ���glUnmapBufferARB()����GL_TRUE ���򷵻�GL_FALSE��
����:Streaming Texture Uploads
https://blog.csdn.net/dreamcs/article/details/7708018
https://www.cnblogs.com/rainbow70626/p/8719818.html

/// ���������ʽ
/// �ڲ���ʽ ��ʽ����������ͣ� ���ͣ�����ĸ�ʽ��
/// ��ȷ����С�ڲ���ʽ��Ч���
{GL_LUMINANCE, GL_LUMINANCE, GL_UNSIGNED_BYTE}, // ESE_FORMAT_L8_UINT
{GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE}, // ESE_FORMAT_A8_UINT
{GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE}, // ESE_FORMAT_L8A8_UINT

{GL_RGB565, GL_RGB, GL_UNSIGNED_SHORT_5_6_5}, // ESE_FORMAT_R5G6B5_UNORM
{GL_RGB5_A1, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1}, // ESE_FORMAT_R5G5B5A1_UNORM
{GL_RGBA4, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4}, // ESE_FORMAT_R4G4B4A4_UNORM
{GL_RGB10_A2, GL_RGBA, GL_UNSIGNED_INT_2_10_10_10_REV}, // ESE_FORMAT_R10G10B10A2_UNORM

{GL_R11F_G11F_B10F, GL_RGB, GL_UNSIGNED_INT_10F_11F_11F_REV}, // ESE_FORMAT_R11G11B10_FLOAT
{GL_RGB9_E5, GL_RGB, GL_UNSIGNED_INT_5_9_9_9_REV}, // ESE_FORMAT_R9G9B9E5_FLOAT

{GL_SRGB8, GL_RGB, GL_UNSIGNED_BYTE}, // ESE_FORMAT_SR8G8B8_FLOAT
{GL_SRGB8_ALPHA8, GL_RGBA, GL_UNSIGNED_BYTE}, // ESE_FORMAT_SR8G8B8A8_FLOAT

{GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT}, // ESE_FORMAT_D16_FLOAT
{GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT}, // ESE_FORMAT_D24_FLOAT
{GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT}, // ESE_FORMAT_D32_FLOAT
{GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8}, // ESE_FORMAT_D24_UNORM_S8_UINT

{GL_RGB, GL_RGB, GL_UNSIGNED_BYTE}, // ��֧��
{GL_RGB, GL_RGB, GL_UNSIGNED_SHORT_5_6_5}, // ��֧��
{GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE}, // ��֧��
{GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4}, // ��֧��
{GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1}, // ��֧��
			
		
/// ȷ����С���ڲ���ʽ������ģ�
{GL_RGB565, GL_RGB, GL_UNSIGNED_BYTE}, // ��֧��
{GL_RGB5_A1, GL_RGBA, GL_UNSIGNED_BYTE}, // ��֧��
{GL_RGBA4, GL_RGBA, GL_UNSIGNED_BYTE}, // ��֧��

{GL_RGB10_A2UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT_2_10_10_10_REV}, // ��֧��
{GL_R11F_G11F_B10F, GL_RGB, GL_HALF_FLOAT}, // ��֧��
{GL_R11F_G11F_B10F, GL_RGB, GL_FLOAT},  // ��֧��
{GL_RGB9_E5, GL_RGB, GL_HALF_FLOAT},  // ��֧��
{GL_RGB9_E5, GL_RGB, GL_FLOAT},  // ��֧��

{GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT}, // ��֧��
{GL_DEPTH32F_STENCIL8, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV}, // ��֧��

