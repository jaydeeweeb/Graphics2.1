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
#include "SunVS.csh"
#include "SunPS.csh"

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

//ID3D11InputLayout* vLayout;
ID3D11InputLayout* shipVLayout;
ID3D11VertexShader* vShader;
ID3D11VertexShader* shipVShader;
ID3D11VertexShader* spaceBoxV;
ID3D11VertexShader* earthVShader;
ID3D11VertexShader* moonVShader;
ID3D11VertexShader* sunVShader;
ID3D11PixelShader* pShader;
ID3D11PixelShader* shipPShader;
ID3D11PixelShader* spaceBoxPShader;
ID3D11PixelShader* earthPShader;
ID3D11PixelShader* moonPShader;
ID3D11PixelShader* sunPShader;
ID3D11ShaderResourceView* stonehengeTexture;
ID3D11ShaderResourceView* shipTexture;
ID3D11ShaderResourceView* spaceBoxTex;
ID3D11ShaderResourceView* earthTex;
ID3D11ShaderResourceView* moonTex;
ID3D11ShaderResourceView* sunTex;



//Shader variables
ID3D11Buffer* cBuff;
ID3D11Buffer* cBuffLighting;


//Buffers
//ID3D11Buffer* vBuff;  //Used to hold stuff
ID3D11Buffer* vBuffMesh; //vertex buff
ID3D11Buffer* iBuffMesh; //index buffer
ID3D11Buffer* vshipBuffer; //vertex buff
ID3D11Buffer* ishipBuffer; //index buffer
ID3D11Buffer* vskyBoxBuffer; //vertex buff
ID3D11Buffer* iskyBoxBuffer; //index buffer
ID3D11Buffer* vEarthBuffer; //vertex buff
ID3D11Buffer* iEarthBuffer; //index buffer
ID3D11Buffer* vmoonBuffer; //vertex buff
ID3D11Buffer* imoonBuffer; //index buffer
ID3D11Buffer* vsunBuffer; //vertex buff
ID3D11Buffer* isunBuffer; //index buffer


//Mesh vertex data
ID3D11VertexShader* vMeshShader;
ID3D11InputLayout* vMeshLayout;

//Z buffer for depth
ID3D11Texture2D* zBuffer;
ID3D11DepthStencilView* zBufferView;

XMMATRIX camera;
XMMATRIX dirLight;
XMMATRIX pointLight;


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

struct LightingBufferData
{
    XMFLOAT4 pointLightPosition;
    XMFLOAT4 pointLightColor;
    XMFLOAT4 dirLightDirection;
    XMFLOAT4 dirLightColor;
    XMFLOAT4 camPos;
    XMFLOAT4 padding;
}lightingMatricies;

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

SimpleVertex starsArray[1000];

SimpleMesh shipMesh;
SimpleMesh skyBox;
SimpleMesh earth;
SimpleMesh moon;
SimpleMesh sun;


void releaseData()
{
    //Release D3D11 interfaces (TO MAKE SURE ALL INTERFACES ARE RELEASED CHECK OUTPUT WINDOW FOR "LIVE OBJECTS"
    myDev->Release();
        mySwap->Release();
        myCon->Release();
        myRtv->Release();
        //myPort->Release();  ???
        //vLayout->Release();
        shipVLayout->Release();
        vShader->Release();
        shipVShader->Release();
        spaceBoxV->Release();
        earthVShader->Release();
        moonVShader->Release();
        sunVShader->Release();
        pShader->Release();
        shipPShader->Release();
        spaceBoxPShader->Release();
        earthPShader->Release();
        moonPShader->Release();
        sunPShader->Release();
        stonehengeTexture->Release();
        shipTexture->Release();
        spaceBoxTex->Release();
        earthTex->Release();
        moonTex->Release();
        sunTex->Release();
        cBuff->Release();
        cBuffLighting->Release();
        //vBuff->Release();
        vBuffMesh->Release();
        iBuffMesh->Release();
        vshipBuffer->Release();
        ishipBuffer->Release();
        vskyBoxBuffer->Release();
        iskyBoxBuffer->Release();
        vEarthBuffer->Release();
        iEarthBuffer->Release();
        vmoonBuffer->Release();
        imoonBuffer->Release();
        vsunBuffer->Release();
        isunBuffer->Release();
        vMeshShader->Release();
        vMeshLayout->Release();
        zBuffer->Release();
        zBufferView->Release();



}