#pragma once

#include <GL/glut.h>
#include <windows.h>
#include <math.h>
class ThreeD {
public:
	ThreeD();
	ThreeD(GLfloat x0, GLfloat y0, GLfloat z0);
	void setMatrix();
	void display();

	void moveLeft(int mode);
	void moveRight(int mode);
	void moveDown(int mode);
	void moveUp(int mode);
	void  movefoward(int mode);
	void moveBackward(int mode);

	void RotateX(int mode);
	void RotateY(int mode);
	void RotateZ(int mode);
	void show();

	void mouse(int a, int b);
	void init();



	/*void fly();*/
	void bigger();
	void smaller();
	GLfloat getrl();
	GLfloat getru();
	GLfloat getrf();
	GLfloat getrx();
	GLfloat getry();
	GLfloat getrz();




private:
	int n;
	GLfloat RB; //身体半径
	GLfloat Pi; //圆周率
	GLfloat RE; //眼睛半径
	GLfloat  RM; //嘴巴半径
	GLfloat RA;//角半径
	GLfloat  RF;//翅膀半径
	GLfloat x;  //x轴坐标原点
	GLfloat y;  //y轴坐标原点
	GLfloat z; //z轴坐标原点
	GLfloat sx; //x轴缩放参数
	GLfloat sy; //y轴缩放参数
	GLfloat sz; //z轴缩放参数
	GLfloat site;

	GLfloat rx; //旋转的计数
	GLfloat ry;
	GLfloat rz;

	GLfloat rl;//平移的计数
	GLfloat rr;
	GLfloat ru;
	GLfloat rd;
	GLfloat rf;
	GLfloat rb;


};