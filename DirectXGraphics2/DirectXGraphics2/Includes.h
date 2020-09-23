#pragma once

//#include "stdafx.h"
//#include "D3D11Sample.h"
#include "framework.h"
#include "DirectXGraphics2.h"
#include <iostream>
#include <d3d11.h>
#include <fstream>
#pragma comment(lib, "d3d11.lib")

#include <DirectXMath.h>
#include <vector>
using namespace DirectX;
using namespace std;
#include "MyPShader.csh"
#include "MyVShader.csh"
#include "MyMeshVShader.csh"
#include "SpaceShipVS.csh"
#include "SpaceShipPS.csh"
#include "Camera.h"
#include "DDSTextureLoader.h"
#include "SpaceBoxVS.csh"
#include "SpaceBoxPS.csh"

//Mesh
#include"Assets/StoneHenge.h"

//For init
ID3D11Device* myDev; //Create other objects in API
IDXGISwapChain* mySwap; //Takes the contents of what we want to draw and actually draws it to the window (nternally contains a texture "format buffer")
ID3D11DeviceContext* myCon; //Sets resources and executes draw commands

//For drawing
ID3D11RenderTargetView* myRtv; //Pointer to a resource that can be used for drawing
D3D11_VIEWPORT myPort;
float aspectR = 1;

ID3D11Buffer* vBuff;  //Used to hold stuff
ID3D11InputLayout* vLayout;
ID3D11VertexShader* vShader; //HLSL
ID3D11PixelShader* pShader;
ID3D11ShaderResourceView* StonehengeTexture;
ID3D11ShaderResourceView* ShipTexture;
ID3D11InputLayout* ShipvLayout;
ID3D11VertexShader* ShipvShader; //HLSL
ID3D11PixelShader* ShippShader;
ID3D11VertexShader* SpaceBoxV;
ID3D11PixelShader* SpaceBoxP;
ID3D11ShaderResourceView* SpaceBoxTex;

//Shader variables
ID3D11Buffer* cBuff;

//mesh data
ID3D11Buffer* vBuffMesh; //vertex buff
ID3D11Buffer* iBuffMesh; //index buffer
ID3D11Buffer* vshipBuffer; //vertex buff
ID3D11Buffer* ishipBuffer; //index buffer
ID3D11Buffer* vskyBoxBuffer; //vertex buff
ID3D11Buffer* iskyBoxBuffer; //index buffer

//Mesh vertex data
ID3D11VertexShader* vMeshShader;
ID3D11InputLayout* vMeshLayout;

//Z buffer for depth
ID3D11Texture2D* zBuffer;
ID3D11DepthStencilView* zBufferView;

XMMATRIX camera;

//Math stuff

struct MyVertex //Where 2 lines meet
{
    float xyzw[4];
    float rgba[4];
};
unsigned int numVerts = 0;

struct WVP //World View Projection
{
    XMFLOAT4X4 wMatrix; //storage type
    XMFLOAT4X4 vMatrix;
    XMFLOAT4X4 pMatrix;
}myMatricies;

struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT3 Normal;
    XMFLOAT2 Tex;
};

struct SimpleMesh
{
    vector<SimpleVertex> vertexList;
    vector<int> indicesList;
};

SimpleMesh shipMesh;
SimpleMesh skyBox;


void releaseData()
{
    //Release D3D11 interfaces (TO MAKE SURE ALL INTERFACES ARE RELEASED CHECK OUTPUT WINDOW FOR "LIVE OBJECTS"
    myRtv->Release();
    vBuff->Release();
    myCon->Release();
    mySwap->Release();
    vShader->Release();
    pShader->Release();
    ShippShader->Release();
    ShipvShader->Release();
    vLayout->Release();
    myDev->Release();
    cBuff->Release();
    vBuffMesh->Release();
    iBuffMesh->Release();
    vMeshShader->Release();
    vMeshLayout->Release();
    zBuffer->Release();
    zBufferView->Release();
    ShipvLayout->Release();
}