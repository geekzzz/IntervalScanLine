#include <iostream>
#include "glm/glm.hpp"
//#include <GL/glut.h> 
#include <GL\glut.h>
#include "OBJ.h"
#include "Interval_scanline.h"
#include <ctime>
using namespace std;

void show();
void loop();
Interval_scanline *scl = new Interval_scanline();


int main(int argc, char *argv[])
{
	OBJ *obj = new OBJ();
	char c1,c2,c3;
	string path = "../models/bunny.obj";
	cout << "��ѡ��ģ�ͣ�" << endl;
	cout << "1 ����" << endl << "2 ά��˹" << endl << "3 ���" << endl << "4 ��" << endl << "5 bunny��" << endl << "6 �ᴩ�壨��֤�ᴩЧ����" << endl;
	cin >> c1;
	switch (c1)
	{
	case '1':
		path = "../models/dolphins.obj";
		break;
	case '2':
		path = "../models/venus.obj";
		break;
	case '3':
		path = "../models/teapot.obj";
		break;
	case '4':
		path = "../models/rose+vase.obj";
		break;
	case '5':
		path = "../models/bunny.obj";
		break;
	case '6':
		path = "../models/cross.obj";
		break;
	default:
		path = "../models/dolphins.obj";
	}
	cout << "��ѡ���ӽǣ�" << endl;
	cout << "1 ����" << endl << "2 ����" << endl << "3 ����"<< endl;
	cin >> c2;
	switch (c2)
	{
	case '1':
		obj->lookat = 0;
		break;
	case '2':
		obj->lookat = 1;
		break;
	case '3':
		obj->lookat = 2;
		break;
	default:
		obj->lookat = 0;
	}
	cout << "��ѡ����ɫ��ʽ��" << endl;
	cout << "1 ʹ�����ֵ������ɫ" << endl << "2 ʹ�÷��߷��������ɫ"  << endl;
	cin >> c3;
	switch (c3)
	{
	case '1':
		scl->rendermode = 0;
		break;
	case '2':
		scl->rendermode = 1;
		break;
	default:
		scl->rendermode = 0;
	}

	clock_t start1,start2;
	start1 = clock();
	obj->load(path);
	cout << "ģ�ͼ���ʱ��:" << float(clock() - start1) << "ms" << endl;
	start2 = clock();
	scl->Fit_screen(*obj);
	scl->Create_ET_PT(*obj);
	scl->Scan();
	cout << "����ɨ���߻���ʱ��:" << float(clock() - start2) << "ms" << endl;
	show();
	getchar();
	return 0;
}


void loop()
{
	int width = 800, height = 600;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);

	glBegin(GL_POINTS);
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			glColor3f(scl->colorbuffer[x][y].r, scl->colorbuffer[x][y].g, scl->colorbuffer[x][y].b);
			glVertex2i(x, y);
		}
	}
	glEnd();

	glFinish();
}

void show()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 80);
	glutCreateWindow("CG_geekzzz");
	glutDisplayFunc(loop);
	glutMainLoop();
}