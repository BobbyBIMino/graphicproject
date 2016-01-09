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
	GLfloat RB; //����뾶
	GLfloat Pi; //Բ����
	GLfloat RE; //�۾��뾶
	GLfloat  RM; //��Ͱ뾶
	GLfloat RA;//�ǰ뾶
	GLfloat  RF;//���뾶
	GLfloat x;  //x������ԭ��
	GLfloat y;  //y������ԭ��
	GLfloat z; //z������ԭ��
	GLfloat sx; //x�����Ų���
	GLfloat sy; //y�����Ų���
	GLfloat sz; //z�����Ų���
	GLfloat site;

	GLfloat rx; //��ת�ļ���
	GLfloat ry;
	GLfloat rz;

	GLfloat rl;//ƽ�Ƶļ���
	GLfloat rr;
	GLfloat ru;
	GLfloat rd;
	GLfloat rf;
	GLfloat rb;


};