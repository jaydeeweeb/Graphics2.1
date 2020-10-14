#pragma once

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include "XTime.h"
#include <ctime>
#include <DirectXMath.h>
using namespace DirectX;



XMMATRIX cameraMovement(XMMATRIX posititon, float delta);
