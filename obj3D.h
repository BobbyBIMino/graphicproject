#pragma once

#include "stdafx.h"
#include "TextureManager.h"
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<vector>
#include <GL/glut.h>
using namespace std;


class obj3D
{
	struct vertex
	{
		double x;
		double y;
		double z;

	};
	

	struct face {
		vector <int> v;
		vector <int> vn;
		vector <int> vt;
	};
	struct mtl {
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat emission[4];
		GLfloat shininess[1];
		int startface;
		string name;
	};
public:
	vector<vertex> vetexes;
	vector<face> faces;
	vector<vertex> vn;
	vector<vertex> vt;
	GLfloat max;
	GLfloat min;
	vector<mtl> mtlF;
	


	void parse(const char* objpath,const char* mtlpath);
	void display();
    void init();


	obj3D();

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