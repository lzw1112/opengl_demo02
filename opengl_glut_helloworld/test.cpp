#ifdef _DEBUG
#pragma comment(lib,"C:\\opengl_lib\\glutdlls37beta\\glut32.lib")
#else
#pragma comment(lib,"..\\release\\LedCtrlBoard.lib")
#endif
#include "glut.h"
#include<Windows.h>					// wglUseFontBitmaps��Windowsϵͳ���еĺ�����������ʹ��ǰ��Ҫ����ͷ�ļ�
#define MAX_CHAR 128				// ASCII�ַ��ܹ�ֻ��0��127��һ��128���ַ�
#include <iostream>
void drawString(const char* str)	// ��Ļ�������庯��
{
	static int isFirstCall = 1;
	static GLuint lists;

	glViewport(0, 0, 600, 400);		// ���õ�ǰ���ӿ�
	glColor3f(1.0f, 0.0f, 0.0f);	// ����������ɫ[��ɫ]
	glRasterPos2f(0, 0);			// glRasterPos2f(x,y)������ʾ[����]ʱ�����ַ�����ʼλ��

	if (isFirstCall) {					// ����ǵ�һ�ε��ã�ִ�г�ʼ��

		isFirstCall = 0;				// ����MAX_CHAR����������ʾ�б���
		lists = glGenLists(MAX_CHAR);	// �б��ʼ��

		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);	// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
		/*
			����˵����
			Windowsϵͳ�У�����ʹ��wglUseFontBitmaps�����������Ĳ�����ʾ�ַ��õ���ʾ�б��������ĸ�������

			��һ��������ʾ��HDC��ѧ��Windows GDI������Ӧ�û���Ϥ��������û��ѧ������Ҳû��ϵ��ֻҪ֪������wglGetCurrentDC�������Ϳ��Եõ�һ��HDC��

			�ڶ���������ʾ��һ��Ҫ�������ַ�����Ϊ����Ҫ����0��127���ַ�����ʾ�б�����������0��

			������������ʾҪ�����ַ����ܸ�������Ϊ����Ҫ����0��127���ַ�����ʾ�б��ܹ���128���ַ���������������� MAX_CHAR(�궨��)��

			���ĸ�������ʾ��һ���ַ�����Ӧ��ʾ�б�ı�š�����������1000�����һ���ַ��Ļ��������װ����1000����ʾ�б��ڶ����ַ��Ļ��������װ����1001����ʾ�б��������ơ�
			���ǿ�������glGenLists����128����������ʾ�б��ţ�Ȼ��ѵ�һ����ʾ�б����������
		*/
	}

	for (; *str != '\0'; ++str)			// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
	{
		glCallList(lists + *str);
	}
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// ʹ�� glClearColor ��ָ����ֵ�趨��ɫ��������ֵ�����������е�ÿһ����������Ϊ����ɫ

	drawString("Hello, World!");	// ������Hello, World!��

	glFlush();						// ���OpenGL���������ǿ��ִ���������������OpenGL����
	/*
		����˵����
		OpenGL�ڲ�ʹ����Ⱦ����������������У�OpenGL����ִ����Щ����֮ǰ����Щ�������������
		����״̬��Ҳ�������Ŷӡ���Ϊ��Ⱦ��Ҫ��Ӳ���򽻵�������Ӳ�����н�����Ч�ʷǳ��ͣ�����һ
		���Դ���һ��������ݿ�Զ�ȶ�δ���һ�����ǳ�С�����ݿ��Ч�ʸߵĶ�Ķࡣ
		��Ļ�ϵĸ������صļ����ǲ��д���ġ�
	*/
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);							// ʹ��glut����Ҫ���г�ʼ��

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);	// GLUT_SINGLE ����˼��ʹ�õ������崰�ڣ��������崰�ڵ���˼�����еĻ�������ڴ��ڻ��Ƶ�ʱ��һ��
	// ��ִ��.�ɹ�ѡ��Ļ���GLUT_DOUBLE�������ʽʵ������һ����̨���建����������Ⱦ����Ľ������ȫ��
	// ���ʱ���ٵĺ���Ļ������н�������������������Ч����

	glutCreateWindow("opengl windows��");			// ���ô�������
	glutPositionWindow(100, 100);					// ���ô��ڵ�λ�á�(x��y)��ʾ �ô������Ͻ� ����� ������Ļ���Ͻ� �����λ�á�
	glutReshapeWindow(600, 400);						// ���ô��ڵĳ��Ϳ�

	glClearColor(0.05f, 0.35f, 0.7f, 1.0f);			// ������������������������[����ǳ��ɫ]
	// ԭ����  void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	// GLclampf ��OpenGL�����һ��float�������� ����(0,1)֮��ĸ�������ʹ���ĸ�GLclampf��
	// ����������ʾ��ͬ����ɫ����windows�ϵ�RGBA��ʾ���ƣ���ͬ����windowsʹ��(0,255)������
	// ����ʾ����ͬ�� windows�ܱ�ʾ 255*255*255 ��Լ 16ǧ�� ������ɫ��

	glutDisplayFunc(RenderScene);					// �趨һ����Ⱦʱ��(�ص�)����RenderScene��GLUT���ڴ�����Ҫ�����κλ��Ƶ�ʱ��������(�ص�)����
	// �ڴ��ڵĳߴ�仯�����ٴξ۽��ô��ڵ�ʱ��Ҳ���������ص�����

	glutMainLoop();									// �������������GLUT��ܡ�����һ��֮ǰ���Ĳ����൱���������ԣ���δִ�С�glutMainLoopֻ��Ҫ������
	// һ�Σ�Ȼ���ڴ��ڹر�֮ǰ�ǻ�һֱѭ��ִ�С����ᴦ�����в���ϵͳ�ṩ����Ϣ����������ȵȣ�ֱ��������
	// �رճ���
	return 0;
}
