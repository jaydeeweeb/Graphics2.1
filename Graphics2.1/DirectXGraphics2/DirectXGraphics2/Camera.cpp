#include "Camera.h"



XMMATRIX cameraMovement(XMMATRIX posititon, float delta)
{
	XMMATRIX temp;
	bool directionflag = true;

	float speed = 10.0f;
	temp = posititon;

	if (GetAsyncKeyState('W')) //W
	{
		temp = XMMatrixMultiply(XMMatrixTranslation(0, 0, speed * delta), temp);
	}
	if (GetAsyncKeyState('S')) //S
	{
		temp = XMMatrixMultiply(XMMatrixTranslation(0, 0, -speed * delta), temp);
	}
	if (GetAsyncKeyState('A')) //A
	{
		temp = XMMatrixMultiply(XMMatrixTranslation(-speed * delta, 0, 0), temp);
	}
	if (GetAsyncKeyState('D')) //A
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
	if (GetAsyncKeyState(VK_RIGHT))
	{
		temp = XMMatrixMultiply(XMMatrixRotationY(speed * delta), temp);
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		temp = XMMatrixMultiply(XMMatrixRotationY(-speed * delta), temp);
	}
	return temp;
}
