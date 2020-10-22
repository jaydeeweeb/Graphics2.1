#include "Camera.h"

void GramSchmidtProcess(XMMATRIX& existingMat);

XMMATRIX cameraMovement(XMMATRIX posititon, float delta)
{
	XMMATRIX temp;
	bool directionflag = true;

	float speed = 20.0f;
	float turnSpeed = 0.02f;
	temp = posititon;

	if (GetAsyncKeyState('W')) //W
	{
		temp = XMMatrixMultiply(XMMatrixTranslation(0, 0, speed * delta), temp);
	}
	if (GetAsyncKeyState('S'))
	{
		temp = XMMatrixMultiply(XMMatrixTranslation(0, 0, -speed * delta), temp);
	}
	if (GetAsyncKeyState('A')) 
	{
		temp = XMMatrixMultiply(XMMatrixTranslation(-speed * delta, 0, 0), temp);
	}
	if (GetAsyncKeyState('D')) 
	{
		temp = XMMatrixMultiply(XMMatrixTranslation(speed * delta, 0, 0), temp);
	}


	if (GetAsyncKeyState(VK_UP))
	{
		temp = XMMatrixMultiply(XMMatrixTranslation(0, speed * delta, 0), temp);
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		temp = XMMatrixMultiply(XMMatrixTranslation(0, -speed * delta, 0), temp);
	}

	//TEMPORARY
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	static POINT prevCursorPos = cursorPos;
	int deltaX = cursorPos.x - prevCursorPos.x;
	int deltaY = cursorPos.y - prevCursorPos.y;
	prevCursorPos = cursorPos;
	
	//Multiply delta x and delta y by turn speed and adjust turn speed. Only 1 x and 1 y case
	if(GetAsyncKeyState(VK_LBUTTON))
	{
		if (deltaX != 0)
		{
			temp = XMMatrixMultiply(XMMatrixRotationY(turnSpeed * deltaX), temp);
		}
		if (deltaY != 0)
		{
			temp = XMMatrixMultiply(XMMatrixRotationX(turnSpeed * deltaY), temp);
		}
	}
	//if (GetAsyncKeyState(VK_RIGHT))
	//{
	//	temp = XMMatrixMultiply(XMMatrixRotationY(turnSpeed * delta), temp);
	//}
	//if (GetAsyncKeyState(VK_LEFT))
	//{
	//	temp = XMMatrixMultiply(XMMatrixRotationY(-turnSpeed * delta), temp);
	//}
	//if (GetAsyncKeyState(VK_UP))
	//{
	//	temp = XMMatrixMultiply(XMMatrixRotationX(-turnSpeed * delta), temp);
	//}
	//if (GetAsyncKeyState(VK_DOWN))
	//{
	//	temp = XMMatrixMultiply(XMMatrixRotationX(turnSpeed * delta), temp);
	//}

	GramSchmidtProcess(temp);
	return temp;
}

void GramSchmidtProcess(XMMATRIX& existingMat)
{
	XMVECTOR existingZ = existingMat.r[2];
	XMVECTOR newX = XMVector3Cross(XMVECTOR{ 0,1,0 }, existingZ);
	XMVECTOR newY = XMVector3Cross(existingZ, newX);

	newX = XMVector3Normalize(newX);
	newY = XMVector3Normalize(newY);
	existingZ = XMVector3Normalize(existingZ);

	existingMat.r[0] = newX;
	existingMat.r[1] = newY;
	existingMat.r[2] = existingZ;


}