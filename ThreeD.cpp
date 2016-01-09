#include"stdafx.h"
#include <GL/glut.h>
#include <windows.h>
#include <math.h>
#include"ThreeD.h"
#include "ArcBall.h"

ThreeD::ThreeD()
{
	x = 0.0f;  //x轴坐标原点
	y = 0.0f;  //y轴坐标原点
	z = 0.0f; //z轴坐标原点
	n = 1000;
	RB = 0.43f; //身体半径
	Pi = 3.1415926536f; //圆周率
	RE = 0.039f; //眼睛半径
	RM = 0.1f; //嘴巴半径
	RA = 0.13f;//角半径
	RF = 0.0966667;//翅膀半
	site = 1;

	sx = 1.0f; //x轴缩放参数
	sy = 1.0f; //y轴缩放参数
	sz = 1.0f; //z轴缩放参数

	rx = 0.0f;
	ry = 0.0f;
	rz = 0.0f;

	rl = 0.0f;//平移的计数
	rr = 0.0f;
	ru = 0.0f;
	rd = 0.0f;
	rf = 0.0f;
	rb = 0.0f;
}

ThreeD::ThreeD(GLfloat x0, GLfloat y0, GLfloat z0)
{
	x = x0;  //x轴坐标原点
	y = y0;  //y轴坐标原点
	z = z0; //z轴坐标原点
	n = 1000;
	RB = 0.43f; //身体半径
	Pi = 3.1415926536f; //圆周率
	RE = 0.039f; //眼睛半径
	RM = 0.1f; //嘴巴半径
	RA = 0.13f;//角半径
	RF = 0.0966667;//翅膀半
	site = 1;

	sx = 1.0f; //x轴缩放参数
	sy = 1.0f; //y轴缩放参数
	sz = 1.0f; //z轴缩放参数

	rx = 0.0f;
	ry = 0.0f;
	rz = 0.0f;

	rl = 0.0f;//平移的计数
	rr = 0.0f;
	ru = 0.0f;
	rd = 0.0f;
	rf = 0.0f;
	rb = 0.0f;
}

void ThreeD::setMatrix()
{
	/*
	for (int i = 0;i < n / 4;i++)
	{
	for (int j = 0;j < n / 4; ++j)
	{
	matrix[n/4 * i + j][0] = RB*1.2*cos(2 * Pi / n*j) *cos(2 * Pi / n*i)+ x;
	matrix[n/4 * i + j][1] = RB*1.1*sin(2 * Pi / n*j) *cos(2 * Pi / n*i) + y;
	}
	}
	for (int i = 0;i < n / 4;i++)
	{
	matrixZ[i] = RB*0.6*sin(2 * Pi / n * i);
	}
	*/
}

void ThreeD::display()
{
	glLineWidth(4.5);
	//glLoadIdentity();  //加载单位矩阵  
	//gluLookAt(eyex,eyey,eyez,centerx,centery,centerz,0,1,0);

	//左翅


	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (int i = 234; i < 387; ++i)
		glVertex2f((2.155172414*RF*cos(2 * Pi / n*i) - 0.541666667)*site, 2.931034483*RF*sin(2 * Pi / n*i) - 0.29);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 440; i < 512; ++i)
		glVertex2f((1.862068966*RF*cos(2 * Pi / n*i) - 0.516666667)*site, 3.189655172*RF*sin(2 * Pi / n*i) - 0.075);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 315; i < 397; ++i)
		glVertex2f((4.206896552*RF*cos(2 * Pi / n*i) - 0.516666667)*site, 2.672413793*RF*sin(2 * Pi / n*i) - 0.205);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 339; i < 493; ++i)
		glVertex2f((5 * RF*cos(2 * Pi / n*i) - 0.346666667)*site, 4.172413793*RF*sin(2 * Pi / n*i) - 0.073333333);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 441; i < 739; ++i)
		glVertex2f((1 * RF*cos(2 * Pi / n*i) - 0.506666667)*site, 1.517241379*RF*sin(2 * Pi / n*i) + 0.23);
	glEnd();

	//右翅
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (int i = -239; i < 59; ++i)
		glVertex2f((1 * RF*cos(2 * Pi / n*i) + 0.506666667)*site, 1.517241379*RF*sin(2 * Pi / n*i) + 0.23);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 7; i < 161; ++i)
		glVertex2f((5 * RF*cos(2 * Pi / n*i) + 0.346666667)*site, 4.172413793*RF*sin(2 * Pi / n*i) - 0.073333333);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 103; i < 185; ++i)
		glVertex2f((4.206896552*RF*cos(2 * Pi / n*i) + 0.516666667)*site, 2.672413793*RF*sin(2 * Pi / n*i) - 0.205);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = -12; i < 60; ++i)
		glVertex2f((1.862068966*RF*cos(2 * Pi / n*i) + 0.516666667)*site, 3.189655172*RF*sin(2 * Pi / n*i) - 0.075);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 113; i < 266; ++i)
		glVertex2f((2.155172414*RF*cos(2 * Pi / n*i) + 0.541666667)*site, 2.931034483*RF*sin(2 * Pi / n*i) - 0.29);
	glEnd();


	//左角
	glPushMatrix();
	glTranslatef(-0.31, 0.22, 0);
	glColor3f(232.0 / 255, 48.0 / 255, 21.0 / 255);
	glRotatef(270, 1, 0, 0);
	glutSolidCone(RA*0.8, 0.35, 1000, 1000);

	glPopMatrix();

	//右角

	glPushMatrix();
	glTranslatef(0.31, 0.22, 0);
	glColor3f(232.0 / 255, 48.0 / 255, 21.0 / 255);
	glRotatef(270, 1, 0, 0);
	glutSolidCone(RA*0.8, 0.35, 1000, 1000);

	glPopMatrix();

	//身体
	glPushMatrix();
	glScalef(1.2f, 1.1f, 0.45f);
	glColor3f(120.0 / 255, 120.0 / 255, 120.0 / 255);
	glutSolidSphere(RB, 1100, 1100);

	glPopMatrix();

	//右眼
	glPushMatrix();
	glTranslatef(0.27, 0.15, 0.15);
	glScalef(1.1f, 1.7f, 0.45f);
	glColor3f(0, 0, 0);
	glutSolidSphere(RE, 1100, 1100);
	glPopMatrix();

	//左眼
	glPushMatrix();
	glTranslatef(-0.27, 0.15, 0.15);
	glScalef(1.1f, 1.7f, 0.45f);
	glColor3f(0, 0, 0);
	glutSolidSphere(RE, 1100, 1100);
	glPopMatrix();


	//左牙齿
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);

	for (int i = n * 4 / 8; i < n * 6 / 8; ++i)
	{
		double a = -0.19 + RE*cos(2 * Pi / n*i);
		double b = -0.178 + RE*1.6*sin(2 * Pi / n*i);
		glVertex3f(-0.19 + RE*cos(2 * Pi / n*i), -0.178 + RE*1.6*sin(2 * Pi / n*i), GLfloat(sqrt((RB*RB - a*a / (1.2*1.2) - b*b / (1.1*1.1)) * (0.45*0.45))));
	}
	glVertex3f(-0.18, -0.18, GLfloat(sqrt((RB*RB - 0.18*0.18 / (1.2*1.2) - 0.18*0.18 / (1.1*1.1)) * (0.45*0.45))));
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);

	for (int i = n * 4 / 8; i < n * 6 / 8; ++i)
	{
		double a = -0.19 + RE*cos(2 * Pi / n*i);
		double b = -0.178 + RE*1.6*sin(2 * Pi / n*i);
		glVertex3f(-0.19 + RE*cos(2 * Pi / n*i), -0.178 + RE*1.6*sin(2 * Pi / n*i), GLfloat(sqrt((RB*RB - a*a / (1.2*1.2) - b*b / (1.1*1.1)) * (0.45*0.45))));
	}

	glVertex3f(-0.18, -0.18, GLfloat(sqrt((RB*RB - 0.18*0.18 / (1.2*1.2) - 0.18*0.18 / (1.1*1.1)) * (0.45*0.45))));
	glEnd();

	//右牙齿
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);

	glVertex3f(0.10, -0.19, GLfloat(sqrt((RB*RB - 0.10*0.10 / (1.2*1.2) - 0.19*0.19 / (1.1*1.1)) * (0.45*0.45))));
	for (int i = n * 6 / 8; i < n * 8 / 8; ++i)
	{
		double a = 0.12 + RE*cos(2 * Pi / n*i);
		double b = -0.178 + RE*1.6*sin(2 * Pi / n*i);
		glVertex3f(0.12 + RE*cos(2 * Pi / n*i), -0.178 + RE*1.6*sin(2 * Pi / n*i), GLfloat(sqrt((RB*RB - 0.18*0.18 / (1.2*1.2) - 0.18*0.18 / (1.1*1.1)) * (0.45*0.45))));
	}
	glEnd();


	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);

	glVertex3f(0.10, -0.19, GLfloat(sqrt((RB*RB - 0.1*0.1 / (1.2*1.2) - 0.19*0.19 / (1.1*1.1)) * (0.45*0.45))));
	for (int i = n * 6 / 8; i < n * 8 / 8; ++i)
	{
		double a = 0.12 + RE*cos(2 * Pi / n*i);
		double b = -0.178 + RE*1.6*sin(2 * Pi / n*i);
		glVertex3f(0.12 + RE*cos(2 * Pi / n*i), -0.178 + RE*1.6*sin(2 * Pi / n*i), GLfloat(sqrt((RB*RB - 0.18*0.18 / (1.2*1.2) - 0.18*0.18 / (1.1*1.1)) * (0.45*0.45))));
	}
	glEnd();

	//嘴巴
	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINE_STRIP);
	for (int i = n * 5 / 8; i < n * 3.0 / 4; ++i)
	{
		double a = RM*3.4*cos(2 * Pi / n*i);
		double b = -0.1 + RM *sin(2 * Pi / n*i);
		glVertex3f(a, b, GLfloat(sqrt((RB*RB - a*a / (1.2*1.2) - b*b / (1.1*1.1)) * (0.45*0.45))));
	}

	for (int i = n * 3.0 / 4; i < n * 7 / 8; ++i)
	{
		double a = RM * 2.5* cos(2 * Pi / n*i);
		double b = -0.1 + RM *sin(2 * Pi / n*i);
		glVertex3f(a, b, GLfloat(sqrt((RB*RB - a*a / (1.2*1.2) - b*b / (1.1*1.1)) * (0.45*0.45))));
	}
	glEnd();



	//左脚
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.35, -0.31);
	glVertex2f(-0.44, -0.35);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.44, -0.35);
	glVertex2f(-0.43, -0.43);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.44, -0.35);
	glVertex2f(-0.53, -0.34);
	glEnd();

	//右脚
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.35, -0.31);
	glVertex2f(0.44, -0.35);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(0.44, -0.35);
	glVertex2f(0.43, -0.43);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2f(0.44, -0.35);
	glVertex2f(0.53, -0.34);
	glEnd();
	glutSwapBuffers();


}

void ThreeD::moveLeft(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{
		rl -= 0.1;
		//rr = 0;
		//glTranslatef(rr, 0, 0);
		glTranslatef(0, ru, 0);
		//glTranslatef(0, ru, 0);
		glTranslatef(0, 0, rf);
		//glTranslatef(0, 0, rb);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		glTranslatef(rl, 0, 0);

		/*
		//第一人称
		GLfloat diffX;
		GLfloat diffZ;

		diffX = centerx - eyex;
		diffZ = centerz - eyez;
		GLfloat length = diffX*diffX + diffZ*diffZ;
		GLfloat radio = sqrt(0.1*0.1 / length);
		eyex -= diffZ*radio;
		eyez -= -diffX*radio;
		*/
		glPopMatrix();
	}
	if (mode == 2)
	{
		rl -= 0.1;
		glTranslatef(rl, 0, 0);
		glTranslatef(rr, 0, 0);
		glTranslatef(0, rd, 0);
		glTranslatef(0, ru, 0);
		glTranslatef(0, 0, rf);
		glTranslatef(0, 0, rb);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		glPopMatrix();

	}
}

void ThreeD::moveRight(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{
		rl += 0.1;
		//rl = 0;
		//glTranslatef(rl, 0, 0);

		glTranslatef(0, ru, 0);
		//glTranslatef(0, ru, 0);
		glTranslatef(0, 0, rf);
		//glTranslatef(0, 0, rb);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		glTranslatef(rl, 0, 0);
		/*
		//第一人称
		GLfloat diffX;
		GLfloat diffZ;

		diffX = centerx - eyex;
		diffZ = centerz - eyez;
		GLfloat length = diffX*diffX + diffZ*diffZ;
		GLfloat radio = sqrt(0.1*0.1 / length);
		eyex -=- diffZ*radio;
		eyez -= diffX*radio;
		*/

		display();
		glPopMatrix();

	}
	if (mode == 2)
	{
		rr += 0.1;
		glTranslatef(rl, 0, 0);
		glTranslatef(rr, 0, 0);
		glTranslatef(0, rd, 0);
		glTranslatef(0, ru, 0);
		glTranslatef(0, 0, rf);
		glTranslatef(0, 0, rb);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		display();
		glPopMatrix();

	}
}

void ThreeD::moveDown(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{

		ru -= 0.1;
		//ru = 0;
		glTranslatef(rl, 0, 0);
		//glTranslatef(rr, 0, 0);

		//glTranslatef(0, ru, 0);
		glTranslatef(0, 0, rf);
		//glTranslatef(0, 0, rb);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		glTranslatef(0, ru, 0);
		/*
		eyey -= 0.1;
		centery -= 0.1;*/
		display();
		glPopMatrix();
	}
	if (mode == 2)
	{
		rd -= 0.1;
		glTranslatef(rl, 0, 0);
		glTranslatef(rr, 0, 0);
		glTranslatef(0, rd, 0);
		glTranslatef(0, ru, 0);
		glTranslatef(0, 0, rf);
		glTranslatef(0, 0, rb);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		display();
		glPopMatrix();

	}
}

void ThreeD::moveUp(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{

		ru += 0.1;
		//rd = 0;
		glTranslatef(rl, 0, 0);
		//glTranslatef(rr, 0, 0);
		//glTranslatef(0, ru, 0);

		glTranslatef(0, 0, rf);
		//glTranslatef(0, 0, rb);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		glTranslatef(0, ru, 0);
		/*
		eyey += 0.1;
		centery += 0.1;
		*/
		display();

		glPopMatrix();
	}
	if (mode == 2)
	{
		ru += 0.1;
		glTranslatef(rl, 0, 0);
		glTranslatef(rr, 0, 0);
		glTranslatef(0, rd, 0);
		glTranslatef(0, ru, 0);
		glTranslatef(0, 0, rf);
		glTranslatef(0, 0, rb);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		display();
		glPopMatrix();

	}
}

void ThreeD::movefoward(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{
		/*
		GLfloat diffX;
		GLfloat diffZ;
		*/
		rf += 0.1;

		glTranslatef(rl, 0, 0);
		glTranslatef(0, ru, 0);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		glTranslatef(0, 0, rf);
		/*
		//第一人称
		diffX = centerx - eyex;
		diffZ = centery - eyey;
		GLfloat length = diffX*diffX + diffZ*diffZ;
		GLfloat radio = sqrt(0.1*0.1 / length);
		eyex += diffX*radio;
		eyez += diffZ*radio;
		*/
		display();
		glPopMatrix();
	}
	if (mode == 2)
	{
		rf += 0.1;
		glTranslatef(rl, 0, 0);
		glTranslatef(rr, 0, 0);
		glTranslatef(0, rd, 0);
		glTranslatef(0, ru, 0);
		glTranslatef(0, 0, rf);
		glTranslatef(0, 0, rb);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		display();
		glPopMatrix();

	}
}

void ThreeD::moveBackward(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{
		/*
		GLfloat diffX;
		GLfloat diffZ;
		*/
		rf -= 0.1;
		//rf = 0;
		glTranslatef(rl, 0, 0);
		//glTranslatef(rr, 0, 0);
		//glTranslatef(0, rd, 0);
		glTranslatef(0, ru, 0);
		//glTranslatef(0, 0, rf);

		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		glTranslatef(0, 0, rf);
		/*
		diffX = centerx - eyex;
		diffZ = centery - eyey;
		GLfloat length = diffX*diffX + diffZ*diffZ;
		GLfloat radio = sqrt(0.1*0.1 / length);
		eyex -= diffX*radio;
		eyez -= diffZ*radio;

		display();
		glPopMatrix();
		*/
	}
	if (mode == 2)
	{
		rb -= 0.1;
		glTranslatef(rl, 0, 0);
		glTranslatef(rr, 0, 0);
		glTranslatef(0, rd, 0);
		glTranslatef(0, ru, 0);
		glTranslatef(0, 0, rf);
		glTranslatef(0, 0, rb);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		display();
		glPopMatrix();

	}
}

void ThreeD::RotateX(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{
		rx += 10;
		glTranslatef(rl, 0, 0);
		glTranslatef(rr, 0, 0);
		glTranslatef(0, rd, 0);
		glTranslatef(0, ru, 0);
		glTranslatef(0, 0, rf);
		glTranslatef(0, 0, rb);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		display();
		glPopMatrix();
	}
	if (mode == 2)
	{

	}
}

void ThreeD::RotateY(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{
		ry += 10;
		glTranslatef(rl, 0, 0);
		glTranslatef(rr, 0, 0);
		glTranslatef(0, rd, 0);
		glTranslatef(0, ru, 0);
		glTranslatef(0, 0, rf);
		glTranslatef(0, 0, rb);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		display();
		glPopMatrix();

	}
	if (mode == 2)
	{

	}
}

void ThreeD::RotateZ(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{
		rz += 10;
		glTranslatef(rl, 0, 0);
		glTranslatef(rr, 0, 0);
		glTranslatef(0, rd, 0);
		glTranslatef(0, ru, 0);
		glTranslatef(0, 0, rf);
		glTranslatef(0, 0, rb);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		display();
		glPopMatrix();

	}
	if (mode == 2)
	{

	}
}

void ThreeD::show()
{
	glViewport(0, 0, 600, 600);
	display();
	glViewport(600, 0, 600, 600);
	display();
	glFlush();
}

void ThreeD::mouse(int a, int b)
{

}

void ThreeD::init()
{

}



/*void ThreeD::fly()
{
sx = 0.99;
sy = 0.99;
sz = 0.99;
glScalef(sx, sy, 0.0);
glPushMatrix();
display();
Sleep(255);
glPopMatrix();

for (int i = 0; i <= 2; i++)
{
sx += 0.01;
sy += 0.01;
sz += 0.01;
site = 0.90;

glScalef(sx, sy, 0.0);
glPushMatrix();
display();
Sleep(255);
glPopMatrix();

sx += 0.01;
sy += 0.01;
sz += 0.01;
site = 1;
glScalef(sx, sy, 0.0);
glPushMatrix();
display();
Sleep(255);
glPopMatrix();
}

sx = 1;
sy = 1;
sz = 1;

}*/

void ThreeD::bigger()
{
	sx += 0.05;
	sy += 0.05;
	sz += 0.05;
	glScalef(sx, sy, sz);
	glPushMatrix();
	display();
	glPopMatrix();
}


void ThreeD::smaller()
{
	sx -= 0.05;
	sy -= 0.05;
	sz -= 0.05;
	glScalef(sx, sy, sz);
	glPushMatrix();
	display();
	glPopMatrix();
}

GLfloat ThreeD::getrl()
{
	return rl;
}

GLfloat ThreeD::getru()
{
	return ru;
}

GLfloat ThreeD::getrf()
{
	return rf;
}

GLfloat ThreeD::getrx()
{
	return rx;
}

GLfloat ThreeD::getry()
{
	return ry;
}

GLfloat ThreeD::getrz()
{
	return rz;
}

