
//http://10.0.0.19/Emscripten/Out.html

// 3+3+3=9+3=12
// 1024 * 1024 * 12 = 12M һ������棬forѭ�����128��
// ��ޣ��㱻�����Χ���뾶128�ף�128*3.14������3.14�ף�������128*128
// ������̫�࣬��̬�������⣬���ػ���ֻ��Ӧ�÷����
// 1024 * 1024 * 128 = 128M;
// ����׷��Ч����ã���Ҫÿ���Ƕ�ȥ��⣨��г����ÿ���㶼Ҫ��һ��������ͼ

// ��г����+ϡ�����ذ˲�������г��¼���߾��룬���ھ����������в�����Ӧ���ཻ�㣬������ֿ��Ի�ȡ�������ڱ���Ϣ
// ����ϸ�ַ������տ�����ϸ�ֽϴ֣���������ϸ�ֽ�ϸ
// �������λ��֣���С����1�ף���󾫶�2���ף��ӽڵ㳬��4��������ӽڵ����ϸ��
// ���ң��������꣬�ҵ�Ҷ�ӽڵ㣻
// �����Ż������ڵ���ƽ��ͼ����ֱ�Ͻ��ж���������


// ��Ⱦ������������
// 


/*
��ƣ�
��������Զ��壺��������������������������Ⱦ�����
����Զ�����Ҫʹ�õ������ṩ��һЩ���������綥�㻺�棻
������Լ����ڴ�����ֶΣ�
������Լ��Ķ�̬�������������д���任������

��װ��
������󣺳������棬���㻺�棬�������棬�任��������
���㻺�������֣��ṹ���顢����ṹ

����ṹ��
���㲻ͬ���Էֱ�ֵ�������ڲ�ͬ�����У�ʹ�ö��������������
�ṹ���飨Ч�ʸ��ߣ���
��֧�֣��ر����������������ڴ沼�ֲ��ô�������֧�������������ݿ飬ͬʱ���ò��֣�
�ܲ��ܲ�ͬ�����û��棺
���ö����������ʱָ�뺬��Ϊ��һ��Ԫ�ص�ƫ����
���ƺ�������ָ������ƫ��
���ۣ���ͬ�������ɹ���һ��VAO

// ��ȡ������������������Ի�ȡ����������������ٱ���������ȡ���ƣ�Ҳ����ͨ�����ƻ�ȡ����
// ��������������ӳ�䵽һ����ۣ�ͨ����۰�����
// ӳ����һ����������İ󶨶Զ����ɫ������Ч
// �������ʲ���ָ������
// ��Դ������������Ĭ�ϳ��������ӳ�䣨����->��ۣ�
// ������ɫ������ʱ��׷��û�еİ�ӳ�䣨����->��ۣ������������۰�
// ͨ�����Ʋ��ҵ���ۣ���ͨ����۰󶨳�������
// ͨ��GL_MAX_UNIFORM_BUFFER_BINDINGS��ѯ���԰󶨵�����һ��Ϊ36
// https://blog.csdn.net/csxiaoshui/article/details/32101977
// http://www.zwqxin.com/archives/shaderglsl/communication-between-opengl-glsl-2.html
// https://developer.mozilla.org/en-US/docs/Web/API/WebGL2RenderingContext#Uniform_buffer_objects
// A0 B1
// A0 C1
// A0 B1 C��
// �������Ͽ�֪���ɷ���ȫ�ְ󶨵㣬��ȫ�ְ󶨵�;ֲ��󶨵㣬ȫ����������������Щ���ֲ���Բ��ʣ���ɫ����Щ��
�����ļ��������ɳ�������飬��ɫ��ֻ��ʹ������������Щ���������
�û����Զ�������������������飬һ��ʱ��ɫ��������һ���ǲ��ʳ���


OpenGL����ͼƬ��Ϊ������Ҫ����������
֮ǰ��ʵ�ּ���DDS��WEBGL֧������ѹ����ʽ��
glCompressedTexImage2D���أ�
ETC2����֧��3D������EAC����֧��3D����
glCompressedTexImage3D���س���ר��3D����ѹ����ʽ��


// �������

 304 306 303 325 324
*/

// DirectXMath
// https://www.cnblogs.com/X-Jun/p/9041966.html
// https://github.com/Microsoft/DirectXMath/blob/master/Inc/DirectXMath.h

// note that currently - 2018-7-11 - only asm.js supports SIMD


#define _XM_NO_INTRINSICS_
#include "DirectXMath/Inc/DirectXMath.h"

// ��������DirectXMath��
// ����sal.h��concurrencysal.h�ļ�
// ����_XM_NO_INTRINSICS_
// ����fdeclspec�����
// -Wignored-attributes

	DirectX::XMFLOAT3  position;
	position.x = 155.8f;

	DirectX::XMVECTOR myVector = XMLoadFloat3(&position);

	DirectX::XMFLOAT3  position2;
	DirectX::XMStoreFloat3(&position2, myVector);


	Opengl���أ� https://www.khronos.org/registry/OpenGL/
	<GL/glext.h>����չͷ�ļ�����Ϊ΢��˾��OpenGL��֧�ֲ�̫������VCϵ�б�������Ȼ��<GL/gl.h>���ͷ�ļ�����������ֻ��OpenGL 1.1�汾�����涨�����ݣ�
	��û��OpenGL 1.2�����Ժ�汾���Ե�ǰ�ļ�������ö��ԣ�������֧��OpenGL 1.4�汾�����ߵ���1.5, 2.0, 2.1����VC�޷�ֱ��ʹ����Щ���ܡ�
	Ϊ�˽����һ���⣬������<GL/glext.h>ͷ�ļ������ͷ�ļ��ṩ�˸߰汾OpenGL����Ҫ�ĸ��ֳ��������Լ�����ָ��������

	OPENGL ���Թ��� RenderDoc https://www.khronos.org/opengl/wiki/Debugging_Tools https://renderdoc.org/
	https://developer.nvidia.com/nsight-visual-studio-edition
	https://www.cnblogs.com/minggoddess/p/5465075.html
	��Ҫ����wglSwapLayerBuffers(m_hDC, 0);���������ܲ�׽����Ϣ

	CMAKEһЩ���⣺https://www.jianshu.com/p/5ad9934f3e98

	WGL�� http://www.mamicode.com/info-detail-2118543.html
	https://blog.csdn.net/SUKHOI27SMK/article/details/82492946

	�������ʹ��Σ�Transform->Position(SSEFloat3()); �������������CONST��SEVoid Position(SEConst SSEFloat3& mPosition)

	����precision mediump float;���������ɫ��������ͬ���͵ĳ��������ᵼ������ʧ�ܣ�ʹ��precision highp float;

	��������ϵ��X���ң�Y���ϣ�Z��ǰ��
	����任����C++�д������ҳˣ���GLSL�д��������
	��תʹ�û��ȣ���ת�ᳯ���ʱ����תΪ��


	���û���Զ��忽�����캯����ϵͳ���ṩһ��ȱʡ�Ŀ������캯����ȱʡ�Ŀ������캯�����ڻ������͵ĳ�Ա���������ֽڸ��ƣ����������ͳ�Ա��������������Ӧ���͵Ŀ������캯��

	struct A
{
public:
	A(int _a)
		:a(_a)
	{
		printf("--------------------------\n");
	}
	/// �Զ��忽�����캯����ȱʡ�������캯����ǳ����
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
	/// ����һ����������
	return a;
}

/// ����ֱ�Ӹ�ֵ�����������ǹ���һ�������ڿ�����ֵ����
A a = CloneA(A(2));
/// ����һ����������
A b = CloneA(b);


// https://blog.csdn.net/u010780613/article/details/54923139
// https://blog.csdn.net/jadeshu/article/details/21254587










