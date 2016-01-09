#include"stdafx.h"
#include"ThreeD.h"
#include <GL/glut.h>
#include <math.h>
#include "ArcBall.h"
#include <stdio.h>
#include "obj3D.h"

GLint mx; //���x������
GLint my; //���y������
GLfloat eyex[3] = { 0.0, 0.0, 0.0 }; //�۲���λ��
GLfloat eyey[3] = { 1.0, 0.0, 0.0 };
GLfloat eyez[3] = { 3.0, 0.0, 0.0 };
GLfloat atx[3] = { 0.0, 0.0, 0.0 }; //�۲����λ��
GLfloat aty[3] = { 0.0, 0.0, 0.0 };
GLfloat atz[3] = { 0.0, 0.0, 0.0 };

GLfloat light0_pos[] = { 0.0, 0.9, 0.0, 1.0 };//�ɼ���Դ0��λ��
GLfloat diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };//���������
GLfloat ambient0[] = { 2.0, 1.0, 2.0, 1.0 };//���������
GLfloat specular0[] = { 0.0, 0.0, 0.0, 1.0 };//����ⷴ�����

GLfloat light1_pos[] = { 0.5, 0.5, 0.0, 1.0 };//���ɼ���Դ1��λ��
GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };//���������
GLfloat ambient1[] = { 2.0, 0.0, 2.0, 1.0 };//���������
GLfloat specular1[] = { 0.0, 0.0, 0.0, 1.0 };//����ⷴ�����

GLfloat zhui_mat_ambient[4] = { 0.0f, 2.0f, 0.0f, 1.0f };//�ذ廷����
GLfloat zhui_mat_diffuse[4] = { 0.0f, 0.0f, 0.0f, 1.0f };//�ذ�������
GLfloat zhui_mat_specular[4] = { 0.0f, 1.0f, 0.0f, 1.0f };//�ذ徵���
GLfloat zhui_mat_emission[4] = { 0.0f, 1.0f, 1.0f, 1.0f };//�ذ��Է���
GLfloat zhui_mat_shininess[4] = { 5.0f };//�ذ�ֲڳ̶�

GLfloat theta[3] = { 0.0, 0.0, 0.0 }; //��һֻ����ÿ�������ת��
GLfloat theta2[3] = { 0.0, 0.0, 0.0 }; //�ڶ�ֻ����ÿ�������ת��
obj3D animal;
obj3D animal2;
//ThreeD animal2(0, 0, 0);
int mode = 1;
int view = 0;
int yRot = 0;
const double Pi = 3.1415926;


Matrix4fT   Transform = { 1.0f,  0.0f,  0.0f,  0.0f,				// NEW: Final Transform
0.0f,  1.0f,  0.0f,  0.0f,
0.0f,  0.0f,  1.0f,  0.0f,
0.0f,  0.0f,  0.0f,  1.0f };

Matrix3fT   LastRot = { 1.0f,  0.0f,  0.0f,					// NEW: Last Rotation
0.0f,  1.0f,  0.0f,
0.0f,  0.0f,  1.0f };

Matrix3fT   ThisRot = { 1.0f,  0.0f,  0.0f,					// NEW: This Rotation
0.0f,  1.0f,  0.0f,
0.0f,  0.0f,  1.0f };

ArcBallT    ArcBall(640.0f, 480.0f);				                // NEW: ArcBall Instance
Point2fT    MousePt;												// NEW: Current Mouse Point
bool        isClicked = false;										// NEW: Clicking The Mouse?
bool        isLClicked = false;										// NEW: Clicking The Left Mouse Button?
bool        isDragging = false;					                    // NEW: Dragging The Mouse?



void init()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eyex[view], eyey[view], eyez[view], atx[view], aty[view], atz[view], 0.0, 1.0, 0.0);
	glEnable(GL_LIGHTING);//���ù���
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);//�ƻ�����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);//��������
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);//�ƾ��淴��	
	glEnable(GL_LIGHT0);//�򿪵�Դ0
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);//�ƻ�����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);//��������
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);//�ƾ��淴��	
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glEnable(GL_LIGHT1);//�򿪵�Դ1

	glBegin(GL_LINES);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, zhui_mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, zhui_mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, zhui_mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, zhui_mat_shininess);
	//glMaterialfv(GL_FRONT, GL_EMISSION, zhui_mat_emission);
	float i, j;
	for (i = -50; i <= 50; i = i + 0.2)
	{
		glVertex3f(i, -0.25, -50);
		glVertex3f(i, -0.25, 50);
	}
	for (j = -50; j <= 50; j += 0.2)
	{
		glVertex3f(-50, -0.25, j);
		glVertex3f(50, -0.25, j);
	}
	glEnd();
}



int DrawTexCube(GLfloat width, GLfloat height, GLfloat depth)									//
{
	GLfloat x = width / 2, y = height / 2, z = depth / 2;
	glPushMatrix();
	// Front Face
	glBegin(GL_QUADS);
	glVertex3f(-x, -y, z);//Front
	glVertex3f(x, -y, z);
	glVertex3f(x, y, z);
	glVertex3f(-x, y, z);
	glEnd();
	// Back Face
	glBegin(GL_QUADS);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, -y, -z);
	glEnd();
	// Top Face
	glBegin(GL_QUADS);
	glVertex3f(-x, y, -z);
	glVertex3f(-x, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, y, -z);
	glEnd();
	// Bottom Face
	glBegin(GL_QUADS);
	glVertex3f(-x, -y, -z);
	glVertex3f(x, -y, -z);
	glVertex3f(x, -y, z);
	glVertex3f(-x, -y, z);
	glEnd();
	// Right face
	glBegin(GL_QUADS);
	glVertex3f(x, -y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, y, z);
	glVertex3f(x, -y, z);
	glEnd();
	// Left Face
	glBegin(GL_QUADS);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, y, z);
	glVertex3f(-x, y, -z);
	glEnd();
	glPopMatrix();
	return true;
}


void Draw_Triangle() // This function draws a triangle with RGB colors
{
	glPushMatrix();
	glTranslatef(0, 0, 4 + 1);
	glRotatef(90, 1, 0, 0);
	glutSolidTeapot(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	DrawTexCube(5, 4, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	DrawTexCube(1, 1, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	DrawTexCube(1, 1, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	DrawTexCube(1, 1, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	DrawTexCube(1, 1, 3);
	glPopMatrix();
}


void drawTable()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslated(0.5, 0, 0);//��ͼ����+X���ƶ�0.5
	glRotatef(-90, 1, 0, 0);
	glScalef(0.1, 0.1, 0.1);
	Draw_Triangle();
	glEnable(GL_LIGHTING);
	glPopMatrix();

}

void drawSun()
{
	glRotatef((GLfloat)yRot, 0, 1, 0);    //��Դ����ת
	glTranslatef(light0_pos[0], light0_pos[1], light0_pos[2]);    //��Դλ��
	glColor3f(ambient0[0], ambient0[1], ambient0[2]);
	glutSolidSphere(0.05, 60, 32);//���ÿ⺯������һ���뾶Ϊ1�����塣��ʾ��Դ������	
}

void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	init();
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glMultMatrixf(Transform.M);
	glTranslated(-0.5, 0, 0);//��ͼ����X���ƶ�0.5
	glRotatef(90, 0, 1, 0);
	glScaled(1, 1, 1);//�Ŵ�ǰ��x,y,z��
	animal.display();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	drawTable();


	/*��Դ*/
	glPushMatrix();        //ѹ�������趨��Դ��λ��
	glDisable(GL_LIGHTING);
	drawSun();
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glPopMatrix();

	glutSwapBuffers();

	glFlush();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mouse1(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON) {
		switch (state) {
		case GLUT_DOWN:                        isClicked = true;
			printf_s("startmotion: x = %d, y = %d\n", x, y);             break;
		case GLUT_UP:             isClicked = false;             isDragging = false;
			printf_s("stopmotion: x = %d, y = %d\n", x, y);             break;
		}
	}
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		Matrix3fSetIdentity(&LastRot);                                // Reset Rotation         
		Matrix3fSetIdentity(&ThisRot);                                // Reset Rotation 
		Matrix4fSetRotationFromMatrix3f(&Transform, &ThisRot);        // Reset Rotation         
		glutPostRedisplay();
	}
}

void mouseMotion(int x, int y) {
	MousePt.s.X = x;
	MousePt.s.Y = y;
	if (!isDragging)                                                // Not Dragging     
	{
		if (isClicked)                                                // First Click         
		{
			isDragging = true;                                        // Prepare For Dragging 
			LastRot = ThisRot;                                        // Set Last Static Rotation To Last Dynamic One            
			ArcBall.click(&MousePt);                                // Update Start Vector And Prepare For Dragging         
		}
	}
	else
	{
		if (isClicked)                                                // Still Clicked, So Still Dragging         
		{
			Quat4fT   ThisQuat;
			ArcBall.drag(&MousePt, &ThisQuat);                        // Update End Vector And Get Rotation As Quaternion 
			Matrix3fSetRotationFromQuat4f(&ThisRot, &ThisQuat);        // Convert Quaternion Into Matrix3fT 
			Matrix3fMulMatrix3f(&ThisRot, &LastRot);                // Accumulate Last Rotation Into This One 
			Matrix4fSetRotationFromMatrix3f(&Transform, &ThisRot);    // Set Our Final Transform's Rotation From This One         
		}
	}
	glutPostRedisplay();
}

void mouse(int x, int y)
{
	animal.mouse(x, y);
}

void mykey(unsigned char key, int ax, int ay)
{
	int count = 0;

	if (key == 'A')///����
	{
		eyex[1] -= 0.05;
		atx[1] -= 0.05;
		init();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//��ͼ����X���ƶ�0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//�Ŵ�ǰ��x,y,z��
		animal.moveLeft(mode);
		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();

	}
	
	if (key == 'D')//����
	{
		eyex[1] += 0.05;
		atx[1] += 0.05;
		init();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//��ͼ����X���ƶ�0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//�Ŵ�ǰ��x,y,z��
		animal.moveRight(mode);
		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();
	}

	if (key == 'W')//����
	{
		eyey[1] += 0.05;
		aty[1] += 0.05;
		init();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//��ͼ����X���ƶ�0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//�Ŵ�ǰ��x,y,z��
		animal.moveUp(mode);
		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();


	}

	if (key == 'S')//����
	{
		eyey[1] -= 0.05;
		aty[1] -= 0.05;
		init();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//��ͼ����X���ƶ�0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//�Ŵ�ǰ��x,y,z��
		animal.moveDown(mode);

		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();
	}
	if (key == 'Z')//��ǰ
	{
		eyez[1] += 0.05;
		atz[1] += 0.05;
		init();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//��ͼ����X���ƶ�0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//�Ŵ�ǰ��x,y,z��
		animal.movefoward(mode);
		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();

	}
	if (key == 'X')//���
	{
		eyez[1] -= 0.05;
		atz[1] -= 0.05;
		init();

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//��ͼ����X���ƶ�0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//�Ŵ�ǰ��x,y,z��
		animal.moveBackward(mode);

		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();

	}

	if (key == 'Q')//��Xת
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		init();
		glPushMatrix();
		//glLoadIdentity();
		glTranslated(-0.5, 0, 0);
		glScaled(0.5, 0.5, 0.5);
		animal.RotateX(mode);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//��ͼ����X���ƶ�0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//�Ŵ�ǰ��x,y,z��
		animal.RotateX(mode);

		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();
	}

	if (key == 'E')//��Yת
	{

		
		//��һ�˳�
		eyex[1] = (eyex[1] - (-0.5 + animal.getrl()))*cos(10 * Pi / 180) + (eyez[1] - animal.getrf())*sin(10 * Pi / 180) - 0.5 + animal.getrl();
		eyez[1] = -(eyex[1] - (-0.5 + animal.getrl()))*sin(10 * Pi / 180) + (eyez[1] - animal.getrf())*cos(10 * Pi / 180) + animal.getrf();
		atx[1] = (eyex[1] - (-0.5 + animal.getrl()))*cos(10 * Pi / 180) + (eyez[1] - animal.getrf())*sin(10 * Pi / 180) - 0.5 + animal.getrl();
		atz[1] = -(eyex[1] - (-0.5 + animal.getrl()))*sin(10 * Pi / 180) + (eyez[1] - animal.getrf())*cos(10 * Pi / 180) + animal.getrf();
		init();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//��ͼ����X���ƶ�0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//�Ŵ�ǰ��x,y,z��
		animal.RotateY(mode);


		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();
	}

	if (key == 'R')//��Zת
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		init();

		glPushMatrix();
		//glLoadIdentity();
		glTranslated(-0.5, 0, 0);
		glScaled(0.5, 0.5, 0.5);
		animal.RotateZ(mode);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();
	}


	if (key == '1')//�۲����ı䣬������
	{
		atx[view] -= 0.01f;
		glutPostRedisplay();//��Ҫ���»��ƴ���
	}
	if (key == '2')//�۲����ı䣬������
	{
		atx[view] += 0.01f;
		glutPostRedisplay();//��Ҫ���»��ƴ���
	}
	if (key == '3')//�۲����ı䣬������
	{
		aty[view] += 0.01f;
		glutPostRedisplay();//��Ҫ���»��ƴ���
	}
	if (key == '4')//�۲����ı䣬������
	{
		aty[view] -= 0.01f;
		glutPostRedisplay();//��Ҫ���»��ƴ���
	}
	if (key == '5')//�����λ�øı䣬������
	{
		eyex[view] -= 0.01f;
		glutPostRedisplay();//��Ҫ���»��ƴ���
	}
	if (key == '6')//�����λ�øı䣬������
	{
		eyex[view] += 0.01f;
		glutPostRedisplay();//��Ҫ���»��ƴ���
	}
	if (key == '7')//�����λ�øı䣬������
	{
		eyey[view] += 0.01f;
		glutPostRedisplay();//��Ҫ���»��ƴ���
	}
	if (key == '8')//�����λ�øı䣬������
	{
		eyey[view] -= 0.01f;
		glutPostRedisplay();//��Ҫ���»��ƴ���
	}
	if (key == '9')//�����λ�øı䣬�����
	{
		eyez[view] += 0.01f;
		glutPostRedisplay();//��Ҫ���»��ƴ���
	}
	if (key == '0')//�����λ�øı䣬��ǰ��
	{
		eyez[view] -= 0.01f;
		glutPostRedisplay();//��Ҫ���»��ƴ���
	}

	if (key == 'B')
	{
		light0_pos[0] += 0.2f;  //����
		glutPostRedisplay();
	}
	if (key == 'b')    //����
	{
		light0_pos[0] -= 0.2f;
		glutPostRedisplay();
	}
	if (key == 'C')   //��
	{
		light0_pos[1] += 0.2f;
		glutPostRedisplay();
	}
	if (key == 'c')   //��
	{
		light0_pos[1] -= 0.2f;
		glutPostRedisplay();
	}
	if (key == 'F')  //ǰ
	{
		light0_pos[2] += 0.2f;
		glutPostRedisplay();
	}
	if (key == 'f')   //��
	{
		light0_pos[2] -= 0.2f;
		glutPostRedisplay();
	}
	if (key == 'G')   //ƽ�й�
	{
		light0_pos[3] = 0;
		glutPostRedisplay();
	}
	if (key == 'g')   //���
	{
		light0_pos[3] = 1;
		glutPostRedisplay();
	}
	if (key == 'H')   //��ת
	{
		yRot = (yRot + 15) % 360;
		glutPostRedisplay();
	}



	/*������*/
	if (key == 'I')//���ɷּ�
	{
		ambient0[0] += 3;
		glutPostRedisplay();
	}
	if (key == 'i')//���ɷּ�
	{
		ambient0[0] -= 3;
		glutPostRedisplay();
	}
	if (key == 'J')//�̹�ɷּ�
	{
		ambient0[1] += 3;
		glutPostRedisplay();
	}
	if (key == 'j')//�̹�ɷּ�
	{
		ambient0[1] -= 3;
		glutPostRedisplay();
	}
	if (key == 'K')//����ɷּ�
	{
		ambient0[2] += 3;
		glutPostRedisplay();
	}
	if (key == 'k')//�����
	{
		ambient0[2] -= 3;
		glutPostRedisplay();
	}
	if (key == 'M')//������͸���ȼ�
	{
		ambient0[3] += 1;
		glutPostRedisplay();
	}
	if (key == 'm')//������͸���ȼ�
	{
		ambient0[3] -= 1;
		glutPostRedisplay();
	}


}

void mymenu(int id)
{
	switch (id)
	{
	case 1:exit(0);
		break;
	case 2:
		mode = 1;
		break;
	case 3:
		mode = 2;
		break;

	case 4:
		view = 0;
		glutPostRedisplay();
		break;

	case 5:
		view = 1;
		eyex[view] = -0.5 + 0.01*sin(animal.getry()* Pi / 180);
		eyey[view] = 0 + 0.3;
		eyez[view] = 0 + 0.01*sin(animal.getry()  * Pi / 180);

		atx[view] = eyex[view] + sin(animal.getry()  * Pi / 180);
		aty[view] = eyey[view];
		atz[view] = eyez[view] + cos(animal.getry()  * Pi / 180);

		glutPostRedisplay();//��Ҫ���»��ƴ���
		break;
	case 6:
		view = 2;
		eyex[view] = 0.5 + 0.01*sin(animal2.getry() * Pi / 180);
		eyey[view] = 0 + 0.3;
		eyez[view] = 0 + 0.01*sin(animal2.getry()  * Pi / 180);

		atx[view] = eyex[view] + sin(animal2.getry()  * Pi / 180);
		aty[view] = eyey[view];
		atz[view] = eyez[view] + cos(animal2.getry()  * Pi / 180);

		glutPostRedisplay();//��Ҫ���»��ƴ���
		break;
	case 7:
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.bigger();
		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.bigger();
		glFlush();
		break;
	case 8:
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.smaller();
		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.smaller();
		glFlush();
		break;
	case 9:

		break;
	case 10:
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.movefoward(mode);

		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.movefoward(mode);
		glFlush();
		break;
	case 11:
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.moveBackward(mode);

		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.moveBackward(mode);
		glFlush();
		break;
	case 12:

		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.RotateX(mode);

		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.RotateX(mode);
		glFlush();
		break;
	case 13:
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.RotateY(mode);

		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.RotateY(mode);
		glFlush();
		break;
	case 14:
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.RotateZ(mode);

		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.RotateZ(mode);
		glFlush();
		break;
	case 15:
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.moveUp(mode);

		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.moveUp(mode);
		glFlush();
		break;
	case 16:
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.moveDown(mode);

		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.moveDown(mode);
		glFlush();
		break;
	case 17:
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.moveLeft(mode);

		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.moveLeft(mode);
		glFlush();
		break;
	case 18:
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.moveRight(mode);

		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.moveRight(mode);
		glFlush();
		break;
	default:
		break;
	}
}

void mymenu1(int id)
{
	switch (id)
	{
	case 1:

		break;
	case 2:
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.bigger();
		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.display();
		glFlush();

		break;
	case 3:
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.smaller();
		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.display();
		glFlush();

		break;
	case 4:

		break;
	default:
		break;
	}
}

void mymenu2(int id)
{
	switch (id)
	{
	case 1:
		/*glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.display();
		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.fly();
		glFlush();*/
		break;
	case 2:
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.display();
		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.bigger();
		glFlush();

		break;
	case 3:
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0, 0, 600, 600);
		animal.display();
		glLoadIdentity();
		glViewport(600, 0, 600, 600);
		animal2.smaller();
		glFlush();

		break;
	case 4:

		break;
	default:
		break;
	}
}

void reshape(int w, int h)
{
	//if (h == 0)
	//	h = 1;

	//glViewport(0, 0, w, h);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);//�Ƕȣ���߱ȣ���z�᷽���������֮��ľ���Ľ�������z�᷽���������֮��ľ����Զ��
	//glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, GLsizei(w), GLsizei(h));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLdouble)w / (GLdouble)h, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char *argv[])
{


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(1000, 1000);
	animal.parse("1.obj", "");
	glutCreateWindow("ͼ��ѧ");
	animal.init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutKeyboardFunc(mykey);
	glRotatef(0, 0, 1, 0);
	//glRotatef(40, 1, 0, 0);
	//glRotatef(20, 0, 0, 1);
	glutMotionFunc(mouse);

	glutMouseFunc(mouse1);
	glutMotionFunc(mouseMotion);

	int  submenu1, submenu2, mune_id;
	submenu1 = glutCreateMenu(mymenu1);


	submenu2 = glutCreateMenu(mymenu2);


	mune_id = glutCreateMenu(mymenu);


	glutAddMenuEntry("��һ�˳�", 5);
	glutAddMenuEntry("�����˳�", 4);

	glutAddMenuEntry("�رմ���", 1);
	//glutPassiveMotionFunc(passiveMotion);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}
