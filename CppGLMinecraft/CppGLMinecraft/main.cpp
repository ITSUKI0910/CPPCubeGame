//https://qiita.com/narupo/items/0f24ad84141ce68fa757
//https://qiita.com/mechamogera/items/57793435553f0815063d
#include <GSGame.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <string>

static GLFWwindow* aWindow;
static int aWidth = 640;
static int aHeight = 480;
static std::string aTitle = "Cube";

//�L���[�u�̒��_���
static const GLdouble aCubeVertex[][3] = {
	{ 0.0, 0.0, 0.0 },
{ 1.0, 0.0, 0.0 },
{ 1.0, 1.0, 0.0 },
{ 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 1.0 },
{ 1.0, 0.0, 1.0 },
{ 1.0, 1.0, 1.0 },
{ 0.0, 1.0, 1.0 }
};
//�L���[�u�̖�
static const int aCubeFace[][4] = {
	{ 0, 1, 2, 3 },
    { 1, 5, 6, 2 },
    { 5, 4, 7, 6 },
    { 4, 0, 3, 7 },
    { 4, 5, 1, 0 },
    { 3, 2, 6, 7 }
};
//�L���[�u�ɑ΂���@���x�N�g��
static const GLdouble aCubeNormal[][3] = {
	{ 0.0, 0.0,-1.0 },
{ 1.0, 0.0, 0.0 },
{ 0.0, 0.0, 1.0 },
{ -1.0, 0.0, 0.0 },
{ 0.0,-1.0, 0.0 },
{ 0.0, 1.0, 0.0 }
};
//�L���[�u�̍ގ��@�����̐F�ƍ��킹�ĉe��������
static const GLfloat aCubeMaterial[] = { 0.8,0.2,0.2,1.0 };
//����
static const GLfloat aLightColor[] = { 0.2,0.2,0.8,1.0 };//�F
static const GLfloat aLight0pos[] = { 0.0,3.0,5.0,1.0 };//�����O�̈ʒu
static const GLfloat aLight1pos[] = { 5.0,3.0,0.0,1.0 };//�����P�̈ʒu

//�L���[�u��`�悷��֐�
static void drawCube();
int main()
{
	//GLFW������
	if (!glfwInit())
	{
		std::cerr << "glfwInit faild." << std::endl;
		exit(EXIT_FAILURE);
		//�L���[�u��`��A�L���[�u��`��A�L���[�u��`��@�ꔭ�Ō�������܋�100�~
	}
	//�E�B���h�E�̐���
	aWindow = glfwCreateWindow(aWidth, aHeight, aTitle.c_str(), nullptr, nullptr);
	if (!aWindow)
	{
		std::cerr << "gldwCreateWindow failed." << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(aWindow);
	/*OpenGL�̏�����*/
	glEnable(GL_DEPTH_TEST);// �f�v�X�o�b�t�@�̗L�����B
	glEnable(GL_CULL_FACE);// �J�����O�̗L�����B
	glEnable(GL_LIGHTING);// ���C�e�B���O�̗L�����B
	glEnable(GL_LIGHT0);// ����0 ��L�����B
	glEnable(GL_LIGHT1);// ����1 ��L�����B
	glCullFace(GL_FRONT);// �J�����O�B
	glLightfv(GL_LIGHT1, GL_DIFFUSE, aLightColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, aLightColor);
	glClearColor(1, 1, 1, 1);
	/*���C�����[�v*/
	while (!glfwWindowShouldClose(aWindow))
	{
		//��ʂ̃N���A
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//�ϊ��s��̏�����
		glLoadIdentity();

		/*�X�V*/
		int width, height;
		//���݂̃E�B���h�E�̑傫��
		glfwGetFramebufferSize(aWindow, &width, &height);
		//�r���[�{�[�g�̍X�V
		glViewport(0, 0, width, height);
		//�������e
		gluPerspective(30.0, (double)width / (double)height, 1.0, 100.0);
		glTranslated(0.0, 0.0, -2.0);
		gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glLightfv(GL_LIGHT0, GL_POSITION, aLight0pos);
		glLightfv(GL_LIGHT1, GL_POSITION, aLight1pos);

		drawCube();
		glfwSwapBuffers(aWindow);
		glfwPollEvents();
	}
	//GLFW3�̏I��
	glfwTerminate();
	return EXIT_SUCCESS;
}
static void drawCube()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, aCubeMaterial);
	glBegin(GL_QUADS);
	for (size_t i = 0; i < 6; i++)
	{
		glNormal3dv(aCubeNormal[i]);
		for (size_t j = 0; j < 4; j++)
		{
			glVertex3dv(aCubeVertex[aCubeFace[i][j]]);
		}
	}
	glEnd();
}
