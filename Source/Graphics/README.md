

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

