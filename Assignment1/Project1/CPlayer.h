#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "global.h"
using namespace std;

class CPlayer
{
private:
	float positionX;
	float positionY;
	//position[2]
	int pose;
	float playerSize;
public:
	CPlayer();
	~CPlayer();
	//player�� ��� X��ǥ ���� �ٲ�.
	void setPlayerPositionX(float positionX);
	float getPlayerPositionX();

	//Y��ǥ�� ��� ó�� ������ �� �״�� �������� ���� ������X
	float getPlayerPositionY();

	void setPlayerPose(int pose);
	int getPlayerPose();
	float getPlayerSize();
};

