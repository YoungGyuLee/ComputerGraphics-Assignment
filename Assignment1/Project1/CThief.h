#pragma once
#include "global.h"
class CThief
{
private:
	//������ ��ǥ. ��� ���� �÷��̾ �̵��� �־ ������ ���� ������ ���� ����.
	float positionX;
	float positionY;
	
	//���簢���̶� ��, �Ʒ� ������ ����. Ȥ�� ���߿� ������ �ٲ۴ٸ� �̰� �������� ��.
	float thiefSize;
	int pose;
public:
	CThief();
	~CThief();

	//��� ������ �������� �ٲ� ���� ��� get�� ����.
	//void setTheifPositionX(float positionX);
	float getTheifPositionX();
	float getTheifPositionY();



	void setTheifPose(int pose);
	int getTheifPose();

	float getThiefSize();

};

