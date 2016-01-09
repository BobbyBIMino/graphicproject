#include"stdafx.h"
#include"ThreeD.h"
#include <GL/glut.h>
#include <math.h>
#include "ArcBall.h"
#include <stdio.h>
#include "obj3D.h"

GLint mx; //鼠标x轴坐标
GLint my; //鼠标y轴坐标
GLfloat eyex[3] = { 0.0, 0.0, 0.0 }; //观察者位置
GLfloat eyey[3] = { 1.0, 0.0, 0.0 };
GLfloat eyez[3] = { 3.0, 0.0, 0.0 };
GLfloat atx[3] = { 0.0, 0.0, 0.0 }; //观察对象位置
GLfloat aty[3] = { 0.0, 0.0, 0.0 };
GLfloat atz[3] = { 0.0, 0.0, 0.0 };

GLfloat light0_pos[] = { 0.0, 0.9, 0.0, 1.0 };//可见光源0的位置
GLfloat diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };//漫反射分量
GLfloat ambient0[] = { 2.0, 1.0, 2.0, 1.0 };//环境光分量
GLfloat specular0[] = { 0.0, 0.0, 0.0, 1.0 };//镜面光反射分量

GLfloat light1_pos[] = { 0.5, 0.5, 0.0, 1.0 };//不可见光源1的位置
GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };//漫反射分量
GLfloat ambient1[] = { 2.0, 0.0, 2.0, 1.0 };//环境光分量
GLfloat specular1[] = { 0.0, 0.0, 0.0, 1.0 };//镜面光反射分量

GLfloat zhui_mat_ambient[4] = { 0.0f, 2.0f, 0.0f, 1.0f };//地板环境光
GLfloat zhui_mat_diffuse[4] = { 0.0f, 0.0f, 0.0f, 1.0f };//地板漫反射
GLfloat zhui_mat_specular[4] = { 0.0f, 1.0f, 0.0f, 1.0f };//地板镜面光
GLfloat zhui_mat_emission[4] = { 0.0f, 1.0f, 1.0f, 1.0f };//地板自发光
GLfloat zhui_mat_shininess[4] = { 5.0f };//地板粗糙程度

GLfloat theta[3] = { 0.0, 0.0, 0.0 }; //第一只蝙蝠每个轴的旋转角
GLfloat theta2[3] = { 0.0, 0.0, 0.0 }; //第二只蝙蝠每个轴的旋转角
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
	glEnable(GL_LIGHTING);//启用光照
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);//灯环境光
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);//灯漫反射
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);//灯镜面反射	
	glEnable(GL_LIGHT0);//打开灯源0
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);//灯环境光
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);//灯漫反射
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);//灯镜面反射	
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
	glEnable(GL_LIGHT1);//打开灯源1

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
	glTranslated(0.5, 0, 0);//将图形向+X轴移动0.5
	glRotatef(-90, 1, 0, 0);
	glScalef(0.1, 0.1, 0.1);
	Draw_Triangle();
	glEnable(GL_LIGHTING);
	glPopMatrix();

}

void drawSun()
{
	glRotatef((GLfloat)yRot, 0, 1, 0);    //灯源的旋转
	glTranslatef(light0_pos[0], light0_pos[1], light0_pos[2]);    //灯源位置
	glColor3f(ambient0[0], ambient0[1], ambient0[2]);
	glutSolidSphere(0.05, 60, 32);//利用库函数绘制一个半径为1的球体。表示光源在这里	
}

void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	init();
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glMultMatrixf(Transform.M);
	glTranslated(-0.5, 0, 0);//将图形向负X轴移动0.5
	glRotatef(90, 0, 1, 0);
	glScaled(1, 1, 1);//放大当前的x,y,z轴
	animal.display();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	drawTable();


	/*灯源*/
	glPushMatrix();        //压缩矩阵，设定光源的位置
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

	if (key == 'A')///向左
	{
		eyex[1] -= 0.05;
		atx[1] -= 0.05;
		init();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//将图形向负X轴移动0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//放大当前的x,y,z轴
		animal.moveLeft(mode);
		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();

	}
	
	if (key == 'D')//向右
	{
		eyex[1] += 0.05;
		atx[1] += 0.05;
		init();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//将图形向负X轴移动0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//放大当前的x,y,z轴
		animal.moveRight(mode);
		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();
	}

	if (key == 'W')//向上
	{
		eyey[1] += 0.05;
		aty[1] += 0.05;
		init();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//将图形向负X轴移动0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//放大当前的x,y,z轴
		animal.moveUp(mode);
		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();


	}

	if (key == 'S')//向下
	{
		eyey[1] -= 0.05;
		aty[1] -= 0.05;
		init();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//将图形向负X轴移动0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//放大当前的x,y,z轴
		animal.moveDown(mode);

		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();
	}
	if (key == 'Z')//向前
	{
		eyez[1] += 0.05;
		atz[1] += 0.05;
		init();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//将图形向负X轴移动0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//放大当前的x,y,z轴
		animal.movefoward(mode);
		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();

	}
	if (key == 'X')//向后
	{
		eyez[1] -= 0.05;
		atz[1] -= 0.05;
		init();

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//将图形向负X轴移动0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//放大当前的x,y,z轴
		animal.moveBackward(mode);

		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();

	}

	if (key == 'Q')//绕X转
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
		glTranslated(-0.5, 0, 0);//将图形向负X轴移动0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//放大当前的x,y,z轴
		animal.RotateX(mode);

		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();
	}

	if (key == 'E')//绕Y转
	{

		
		//第一人称
		eyex[1] = (eyex[1] - (-0.5 + animal.getrl()))*cos(10 * Pi / 180) + (eyez[1] - animal.getrf())*sin(10 * Pi / 180) - 0.5 + animal.getrl();
		eyez[1] = -(eyex[1] - (-0.5 + animal.getrl()))*sin(10 * Pi / 180) + (eyez[1] - animal.getrf())*cos(10 * Pi / 180) + animal.getrf();
		atx[1] = (eyex[1] - (-0.5 + animal.getrl()))*cos(10 * Pi / 180) + (eyez[1] - animal.getrf())*sin(10 * Pi / 180) - 0.5 + animal.getrl();
		atz[1] = -(eyex[1] - (-0.5 + animal.getrl()))*sin(10 * Pi / 180) + (eyez[1] - animal.getrf())*cos(10 * Pi / 180) + animal.getrf();
		init();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glMultMatrixf(Transform.M);
		glTranslated(-0.5, 0, 0);//将图形向负X轴移动0.5
		glRotatef(90, 0, 1, 0);
		glScaled(1, 1, 1);//放大当前的x,y,z轴
		animal.RotateY(mode);


		glEnable(GL_LIGHTING);
		glPopMatrix();
		drawTable();
		drawSun();
		glutSwapBuffers();
	}

	if (key == 'R')//绕Z转
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


	if (key == '1')//观察对象改变，向左移
	{
		atx[view] -= 0.01f;
		glutPostRedisplay();//需要重新绘制窗口
	}
	if (key == '2')//观察对象改变，向右移
	{
		atx[view] += 0.01f;
		glutPostRedisplay();//需要重新绘制窗口
	}
	if (key == '3')//观察对象改变，向上移
	{
		aty[view] += 0.01f;
		glutPostRedisplay();//需要重新绘制窗口
	}
	if (key == '4')//观察对象改变，向下移
	{
		aty[view] -= 0.01f;
		glutPostRedisplay();//需要重新绘制窗口
	}
	if (key == '5')//摄像机位置改变，向左移
	{
		eyex[view] -= 0.01f;
		glutPostRedisplay();//需要重新绘制窗口
	}
	if (key == '6')//摄像机位置改变，向右移
	{
		eyex[view] += 0.01f;
		glutPostRedisplay();//需要重新绘制窗口
	}
	if (key == '7')//摄像机位置改变，向上移
	{
		eyey[view] += 0.01f;
		glutPostRedisplay();//需要重新绘制窗口
	}
	if (key == '8')//摄像机位置改变，向下移
	{
		eyey[view] -= 0.01f;
		glutPostRedisplay();//需要重新绘制窗口
	}
	if (key == '9')//摄像机位置改变，向后移
	{
		eyez[view] += 0.01f;
		glutPostRedisplay();//需要重新绘制窗口
	}
	if (key == '0')//摄像机位置改变，向前移
	{
		eyez[view] -= 0.01f;
		glutPostRedisplay();//需要重新绘制窗口
	}

	if (key == 'B')
	{
		light0_pos[0] += 0.2f;  //右移
		glutPostRedisplay();
	}
	if (key == 'b')    //左移
	{
		light0_pos[0] -= 0.2f;
		glutPostRedisplay();
	}
	if (key == 'C')   //上
	{
		light0_pos[1] += 0.2f;
		glutPostRedisplay();
	}
	if (key == 'c')   //下
	{
		light0_pos[1] -= 0.2f;
		glutPostRedisplay();
	}
	if (key == 'F')  //前
	{
		light0_pos[2] += 0.2f;
		glutPostRedisplay();
	}
	if (key == 'f')   //后
	{
		light0_pos[2] -= 0.2f;
		glutPostRedisplay();
	}
	if (key == 'G')   //平行光
	{
		light0_pos[3] = 0;
		glutPostRedisplay();
	}
	if (key == 'g')   //点光
	{
		light0_pos[3] = 1;
		glutPostRedisplay();
	}
	if (key == 'H')   //旋转
	{
		yRot = (yRot + 15) % 360;
		glutPostRedisplay();
	}



	/*环境光*/
	if (key == 'I')//红光成分加
	{
		ambient0[0] += 3;
		glutPostRedisplay();
	}
	if (key == 'i')//红光成分减
	{
		ambient0[0] -= 3;
		glutPostRedisplay();
	}
	if (key == 'J')//绿光成分加
	{
		ambient0[1] += 3;
		glutPostRedisplay();
	}
	if (key == 'j')//绿光成分减
	{
		ambient0[1] -= 3;
		glutPostRedisplay();
	}
	if (key == 'K')//蓝光成分加
	{
		ambient0[2] += 3;
		glutPostRedisplay();
	}
	if (key == 'k')//蓝光减
	{
		ambient0[2] -= 3;
		glutPostRedisplay();
	}
	if (key == 'M')//环境光透明度加
	{
		ambient0[3] += 1;
		glutPostRedisplay();
	}
	if (key == 'm')//环境光透明度减
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

		glutPostRedisplay();//需要重新绘制窗口
		break;
	case 6:
		view = 2;
		eyex[view] = 0.5 + 0.01*sin(animal2.getry() * Pi / 180);
		eyey[view] = 0 + 0.3;
		eyez[view] = 0 + 0.01*sin(animal2.getry()  * Pi / 180);

		atx[view] = eyex[view] + sin(animal2.getry()  * Pi / 180);
		aty[view] = eyey[view];
		atz[view] = eyez[view] + cos(animal2.getry()  * Pi / 180);

		glutPostRedisplay();//需要重新绘制窗口
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
	//gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);//角度，宽高比，沿z轴方向的两裁面之间的距离的近处，沿z轴方向的两裁面之间的距离的远处
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
	glutCreateWindow("图形学");
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


	glutAddMenuEntry("第一人称", 5);
	glutAddMenuEntry("第三人称", 4);

	glutAddMenuEntry("关闭窗口", 1);
	//glutPassiveMotionFunc(passiveMotion);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}
