#pragma once

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include "XTime.h"
#include <ctime>
#include <DirectXMath.h>
using namespace DirectX;

XMMATRIX temp;
bool directionflag = true;


XMMATRIX cameraMovement(XMMATRIX posititon, float delta)
{

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


	return temp;
}
