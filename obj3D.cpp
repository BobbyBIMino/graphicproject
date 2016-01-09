#include "stdafx.h"

#include "obj3D.h"
#include<string>
#include "TextureManager.h"
#include<vector>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include "ArcBall.h"
GLuint texture[3];

using namespace std;

void obj3D::parse(const char * objpath,const char*mtlpath)
{

	string s;
	ifstream fin(objpath);
	if (!fin)
		return;
	//处理obj文件
	while (fin >> s)
	{
		if (s == "v")
		{
			vertex v;
			fin >> v.x >> v.y >> v.z;
			if (v.x > max)
			{
				max = v.x;
			}else  if (v.y> max)
				{
					max = v.y;
				}
				else if (v.z > max)
				{
					max = v.z;
				}
			if (v.x < min)
			{
				min = v.x;
			}
			else  if (v.y< min)
			{
				min = v.y;
			}
			else if (v.z < min)
			{
				min = v.z;
			}
			this->vetexes.push_back(v);
		}
		else if (s == "vn")
		{
			vertex vn;
			fin >> vn.x >> vn.y >>vn.z;
			this->vn.push_back(vn);
		}
		else if (s == "vt")
		{
			vertex vtr;
			fin >> vtr.x >> vtr.y ;
			this->vt.push_back(vtr);
		}
		
		else  if (s == "usemtl")
		{
			mtl mtlD;
			fin >> mtlD.name;
			mtlD.startface = faces.size();
			mtlF.push_back(mtlD);
		}
		else if (s == "f")
		{
			face f;
			string v, vn, vt;
			string all;
			string vv;
			getline(fin, all);
			int index0;
			int index, index2;

			while (all != "")
			{
				index0 = all.find(' ');
				if (index0 == -1)
				{
					vv = all;
					all = "";
				}
				else if (index0 == 0)
				{
					all = all.substr(index0 + 1);
					index0 = all.find(' ');
					vv = all.substr(0, index0 );
					all = all.substr(index0 + 1);

				}
				else {
					vv = all.substr(0, index0 );
					all = all.substr(index0 + 1);
				}
				


				index = vv.find('/');
				v = vv.substr(0, index);
				index2 = vv.find('/', index + 1);
				vt = vv.substr(index + 1, index2 - index - 1);
				vn = vv.substr(index2 + 1);
				if (v[0] == '-')
				{
					v = v.substr(1);
				}
				if (vt[0] == '-')
				{
					vt = vt.substr(1);
				}
				if (vn[0] == '-')
				{
					vn = vn.substr(1);
				}
				f.v.push_back(atoi(v.c_str()));
				f.vt.push_back(atoi(vt.c_str()));
				f.vn.push_back(atoi(vn.c_str()));


				
			}
			faces.push_back(f);

		}
		else {
			continue;
		}
	}
	mtl mtlA;
	mtlA.startface = faces.size();
	mtlF.push_back(mtlA);
	//处理mtl文件
	for (int i = 0;i < mtlF.size();i++ )
	{
		for (int j = 0;j < 3;j++)
		{
			mtlF[i].ambient[j] = 0.4;
			mtlF[i].diffuse[j] = 0.4;
			mtlF[i].specular[j] = 0.4;
		}
		mtlF[i].ambient[3] = 1;
		mtlF[i].diffuse[3] = 1;
		mtlF[i].specular[3] = 1;
	}
	ifstream mtlin(mtlpath);
	if (!mtlin)
		return;
	while (mtlin >> s)
	{
		vector<int > mtlll;
		if (s == "newmtl")
		{
			string name1;
			mtl mtlD;
			mtlin >> name1;
			while (name1 == "")
			{
				mtlin >> name1;
			}
			int i = 0;
			for ( i ;i < mtlF.size();i++)
			{
				if (name1 == mtlF[i].name)
				{
					mtlll.push_back(i);
				}
			}
			mtlin >> s;
			
			if (s == "Ka")
			{
				mtlin >> mtlF[mtlll[0]].ambient[0] >> mtlF[mtlll[0]].ambient[1] >> mtlF[mtlll[0]].ambient[2];
				mtlF[mtlll[0]].ambient[3] = 1;
				for (int i = 1;i < mtlll.size();i++)
				{
					mtlF[mtlll[i]].ambient[0] = mtlF[mtlll[0]].ambient[0];
					mtlF[mtlll[i]].ambient[1] = mtlF[mtlll[0]].ambient[1];
					mtlF[mtlll[i]].ambient[2] = mtlF[mtlll[0]].ambient[2];
					mtlF[mtlll[0]].ambient[3] = 1;
				}
				mtlin >> s;
			}
			if (s == "Kd")
			{
				mtlin >> mtlF[mtlll[0]].diffuse[0] >> mtlF[mtlll[0]].diffuse[1] >> mtlF[mtlll[0]].diffuse[2];
				mtlF[mtlll[0]].diffuse[3] = 1;
				for (int i = 1;i < mtlll.size();i++)
				{
					mtlF[mtlll[i]].diffuse[0] = mtlF[mtlll[0]].diffuse[0];
					mtlF[mtlll[i]].diffuse[1] = mtlF[mtlll[0]].diffuse[1];
					mtlF[mtlll[i]].diffuse[2] = mtlF[mtlll[0]].diffuse[2];
					mtlF[mtlll[0]].diffuse[3] = 1;
				}
				mtlin >> s;
			}
			if (s == "Ks")
			{
				mtlin >> mtlF[mtlll[0]].specular[0] >> mtlF[mtlll[0]].specular[1] >> mtlF[mtlll[0]].specular[2];
				mtlF[mtlll[0]].specular[3] = 1;
				for (int i = 1;i < mtlll.size();i++)
				{
					mtlF[mtlll[i]].specular[0] = mtlF[mtlll[0]].specular[0];
					mtlF[mtlll[i]].specular[1] = mtlF[mtlll[0]].specular[1];
					mtlF[mtlll[i]].specular[2] = mtlF[mtlll[0]].specular[2];
					mtlF[mtlll[0]].specular[3] = 1;
				}
			}
			for (i = 0;i < mtlF.size();i++)
			{
				mtlF[i].emission[0] = 0;
				mtlF[i].emission[1] = 0;
				mtlF[i].emission[2] = 0;
				mtlF[i].emission[3] = 1;
				mtlF[i].shininess[0] = 0;
			}
		
		}
	 else {
		 continue;
	 }
	}
}

void obj3D::display()
{


	if (mtlF.size() > 1)
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//绑定纹理
		TextureManager::Inst()->BindTexture(texture[0]);
	for (int j = 0;j < mtlF.size()-1;j++)
	{

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mtlF[j].ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mtlF[j].diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mtlF[j].specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, mtlF[j].shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, mtlF[j].emission);
			glColor3d(0, 1, 0);
			for (int i = mtlF[j].startface;i < mtlF[j + 1].startface;i++)
			{
				glBegin(GL_POLYGON);
				for (int k = 0;k < faces[i].v.size();k++)
				{
					vertex v = vetexes[faces[i].v[k] - 1];
					vertex vtt = vt[faces[i].vt[k] - 1];
					glNormal3f(vtt.x, vtt.y, vtt.z);
					glTexCoord2f(vtt.x, vtt.y);
					glVertex3f(v.x / (max), v.y / (max), v.z / (max));

				}
				glEnd();
			
			}
		}
	glFlush();

	glutSwapBuffers();
	}
	else {
		//glPushMatrix();
		//glEnable(GL_TEXTURE_2D);


		//glPopMatrix();


		//绑定纹理
		TextureManager::Inst()->BindTexture(texture[0]);

		//渲染
		for (int i = 0;i < faces.size();i++)
		{
			glBegin(GL_POLYGON);
			for (int k = 0;k < faces[i].v.size();k++)
			{
				vertex v = vetexes[faces[i].v[k] - 1];
				vertex vtt = vt[faces[i].vt[k] - 1];
				//glNormal3f(vtt.x, vtt.y, vtt.z);
				glTexCoord2d(vtt.x,vtt.y);
				glVertex3f(v.x / (max), v.y / (max), v.z / (max));
			}
			glEnd();
		}
	}
}

void obj3D::init()
{
	//将2D贴图状态打开
	glEnable(GL_TEXTURE_2D);

	//单件贴图管理
	//如果加载带路径的文件最好选用.\\这样的格式
	TextureManager::Inst()->LoadTexture("1.jpg", texture[0]);

	//线性过滤一定要放到加载纹理的后面
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // 线性滤波
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // 线性滤波

	glClearColor(0.5, 0.5, 0.5, 0.5);

}

obj3D::obj3D()
{
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

void obj3D::moveLeft(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{
		rl -= 0.1;
		glTranslatef(0, ru, 0);
		glTranslatef(0, 0, rf);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);	

		glPushMatrix();
		glTranslatef(rl, 0, 0);
		display();
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
		display();
		glPopMatrix();

	}
}

void obj3D::moveRight(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{
		rl += 0.1;

		glTranslatef(0, ru, 0);
		glTranslatef(0, 0, rf);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);

		glPushMatrix();
		glTranslatef(rl, 0, 0);
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

void obj3D::moveDown(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{

		ru -= 0.1;
		glTranslatef(rl, 0, 0);
		glTranslatef(0, 0, rf);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);

		glPushMatrix();
		glTranslatef(0, ru, 0);
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

void obj3D::moveUp(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{

		ru += 0.1;
		glTranslatef(rl, 0, 0);
		glTranslatef(0, 0, rf);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);

		glPushMatrix();
		glTranslatef(0, ru, 0);
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

void obj3D::movefoward(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{

		rf += 0.1;
		glTranslatef(rl, 0, 0);
		glTranslatef(0, ru, 0);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);
		glPushMatrix();
		glTranslatef(0, 0, rf);
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

void obj3D::moveBackward(int mode)
{
	if (mode == 1)//以运动物体为参考系
	{
		rf -= 0.1;
		glTranslatef(rl, 0, 0);
		glTranslatef(0, ru, 0);
		glRotatef(rx, 1, 0, 0);
		glRotatef(ry, 0, 1, 0);
		glRotatef(rz, 0, 0, 1);

		glPushMatrix();
		glTranslatef(0, 0, rf);
		display();
		glPopMatrix();
	}
	if (mode == 2)
	{
		rf -= 0.1;
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

void obj3D::RotateX(int mode)
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

void obj3D::RotateY(int mode)
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

void obj3D::RotateZ(int mode)
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

void obj3D::show()
{
	glViewport(0, 0, 600, 600);
	display();
	glViewport(600, 0, 600, 600);
	display();
	glFlush();
}

void obj3D::mouse(int a, int b)
{

}




/*void obj3D::fly()
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

void obj3D::bigger()
{
	sx += 0.05;
	sy += 0.05;
	sz += 0.05;
	glScalef(sx, sy, sz);
	glPushMatrix();
	display();
	glPopMatrix();
}


void obj3D::smaller()
{
	sx -= 0.05;
	sy -= 0.05;
	sz -= 0.05;
	glScalef(sx, sy, sz);
	glPushMatrix();
	display();
	glPopMatrix();
}

GLfloat obj3D::getrl()
{
	return rl;
}

GLfloat obj3D::getru()
{
	return ru;
}

GLfloat obj3D::getrf()
{
	return rf;
}

GLfloat obj3D::getrx()
{
	return rx;
}

GLfloat obj3D::getry()
{
	return ry;
}

GLfloat obj3D::getrz()
{
	return rz;
}







