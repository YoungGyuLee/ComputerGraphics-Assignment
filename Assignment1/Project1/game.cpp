#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "game.h"
#include <math.h>

using namespace std;



void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);
	startTickCount = GetTickCount64();
	//totlaWall.reserve(0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	//glColor3f(1.0, 1.0, 1.0);
	//glBegin(GL_LINE_LOOP);


	//�Ʒ��� ��
	/*double rad = 0.1;
	for (int i = 0; i < 3600; i++) {
		double angle = i * 3.141592 / 180;
		double x = rad * cos(angle);
		double y = rad * sin(angle);
		glVertex2f(player->getPlayerPosition().at(0) + x, player->getPlayerPosition().at(1) + y);

	}*/
	//glVertex2f(rectangle.x, rectangle.y + rectangle.height);
	//glVertex2f(rectangle.x + rectangle.width, rectangle.y + rectangle.height);
	//glVertex2f(rectangle.x + rectangle.width, rectangle.y);


	//�Ʒ��� �簢��
	//setWallColor(wall.getWallColor());

	//�Ʒ��� ����..?
	glBegin(GL_QUADS);
	setObjectColor(BLACK);
	glVertex2f(0,0);
	glVertex2f(0, 1);
	glVertex2f(10, 1);
	glVertex2f(10, 0);
	glEnd();


	//�÷��̾� ��ġ, ���� ����
	glBegin(GL_QUADS);
	setObjectColor(player.getPlayerPose());
	glVertex2f(player.getPlayerPositionX(), player.getPlayerPositionY());
	glVertex2f(player.getPlayerPositionX(), player.getPlayerPositionY() + player.getPlayerSize());
	glVertex2f(player.getPlayerPositionX() + player.getPlayerSize(), player.getPlayerPositionY() + player.getPlayerSize());
	glVertex2f(player.getPlayerPositionX() + player.getPlayerSize(), player.getPlayerPositionY());
	glEnd();

	//���� ��ġ, ���� ����
	glBegin(GL_QUADS);
	setObjectColor(thief.getTheifPose());
	glVertex2f(thief.getTheifPositionX(), thief.getTheifPositionY());
	glVertex2f(thief.getTheifPositionX(), thief.getTheifPositionY() + thief.getThiefSize());
	glVertex2f(thief.getTheifPositionX() + thief.getThiefSize(), thief.getTheifPositionY() + thief.getThiefSize());
	glVertex2f(thief.getTheifPositionX() + thief.getThiefSize(), thief.getTheifPositionY());
	glEnd();
	
	//�� ��ġ, ���� ����
	glBegin(GL_QUADS);
	currentTickCount = GetTickCount64();

	//�� ���� Ÿ�̹� ��� ���� �κ�.
	if (currentTickCount - startTickCount >= interval) {
		wall[total].setWallPositionX(wall[total].getWallPositionX() + interval/1000.0 * total);
		startTickCount = currentTickCount;
		total++;
	}

	if (total <= 50) {
		for (int i = front; i < total; i++) {
			setObjectColor(wall[i].getWallColor());

			glVertex2f(wall[i].getWallPositionX(), wall[i].getWallPositionY());
			//(0,1)
			glVertex2f(wall[i].getWallPositionX(),
				wall[i].getWallPositionY() + wall[i].getWallHeight());
			//(1,1)
			glVertex2f(wall[i].getWallPositionX() + wall[i].getWallWidth(),
				wall[i].getWallPositionY() + wall[i].getWallHeight());
			//(1,0)
			glVertex2f(wall[i].getWallPositionX() + wall[i].getWallWidth(),
				wall[i].getWallPositionY());
			//cout << i << ", " << wall[i].getWallPositionX() << endl;
		}
	}


	if (thief.getTheifPositionX() <= player.getPlayerPositionX() + player.getPlayerSize())
		message(true);


	glEnd();
	glutSwapBuffers();
	glFlush();
}

void setObjectColor(int color) {
	switch (color)
	{
	case RED:
		glColor3f(1.0, 0.0, 0.0);
		break;
	case GREEN:
		glColor3f(0.0, 1.0, 0.0);
		break;
	case BLUE:
		glColor3f(0.0, 0.0, 1.0);
		break;
	case YELLOW:
		glColor3f(1.0, 1.0, 0.0);
		break;
	case BLACK:
		glColor3f(0.0, 0.0, 0.0);
		break;
	default:
		glColor3f(0.0, 0.0, 0.0);
		break;
	}
}


void reshape(int w, int h) {
	glViewport(0, 0, 1000, 500);
//	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 10, 0, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void moveWall() {
	//wall[i].setWallPositionX(wall[i].getWallPositionX() + 5 * i);
	
	for (int i = 0; i < total; i++) {
		wall[i].setWallPositionX(wall[i].getWallPositionX() - velocity);
		if (wall[i].getWallPositionX() + wall[i].getWallWidth() < 0) {
			wall[i].setWallPositionX(-10);
			front = i;
		}
	}

	//�Ʒ� �� if�� GameMain Ŭ������ �ű� ����

	if (wall[now].getWallPositionX() <= (thief.getTheifPositionX() + thief.getThiefSize())) {
		wall[now].setWallColor(thief.getTheifPose());
		thief.setTheifPose(rand() % 4);
		now++;
	}

	if (wall[previous].getWallPositionX() <= (player.getPlayerPositionX() + player.getPlayerSize())) {
		if (player.getPlayerPose() == wall[previous].getWallColor()) {
			cout << "Pass" << endl;
			velocity += 0.01;
			interval -= 250;
			previousPlayerPosition = player.getPlayerPositionX();
			pass = true;
		}
		else {
			cout << "����" << endl;
			failCount++;
			if (failCount >= 3)
				message(false);
			pass = false;
		}
		previous++;
	}


	//�Ʒ��� �÷��̾� ������ �ִϸ��̼� ����κ�(�߿��� �κ��� �ƴ�)
	if (pass) {
		player.setPlayerPositionX(player.getPlayerPositionX() + playerDistance);
		if ((player.getPlayerPositionX() - previousPlayerPosition) >= 1.0) {
			previousPlayerPosition = 0.0;
			pass = false;
		}
	}


	glutPostRedisplay();
}

void message(bool success) {
	HWND hwnd;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	hwnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	if (success) 
		MessageBoxA(hwnd, "����", "����", MB_OK);
	else 
		MessageBoxA(hwnd, "����", "����", MB_OK);

	exit(0);
}

void play(char **argv) {
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();

	//�� �� �״�� �����ִ� �Լ�
	glutDisplayFunc(display);

	glutReshapeFunc(reshape);

	//������ �� ó��
	glutIdleFunc(moveWall);


	//Ű���� �Է�
	glutSpecialFunc(selectPose);


	glutMainLoop();

}

void selectPose(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT://�� -> RED
		player.setPlayerPose(RED);
		break;
	case GLUT_KEY_RIGHT://�� -> GREEN
		player.setPlayerPose(GREEN);
		break;
	case GLUT_KEY_UP://�� -> BLUE
		player.setPlayerPose(BLUE);
		break;
	case GLUT_KEY_DOWN://�� ->YELLOW
		player.setPlayerPose(YELLOW);
		break;
	}
	//gameMain.selectPose(key, x, y);
	glutPostRedisplay();
}

void main(int argc, char** argv) {
	// inspect array elements and print to console
/*	const float* probe = &position[0].x;
	for (size_t i = 0; i < position.size() * 3; i++) {
		std::cout << probe[i] << std::endl;
	}*/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	
	play(argv);
}

