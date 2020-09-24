// DirectXGraphics2.cpp : Defines the entry point for the application.
//

#include "Includes.h"
void LoadMesh(const char* meshFileName, SimpleMesh& mesh);

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DIRECTXGRAPHICS2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DIRECTXGRAPHICS2));

    MSG msg;

    XTime timer;
    timer.Restart();


    // Main message loop: This is where the drawing happens
    while (true)//GetMessage(&msg, nullptr, 0, 0))
    {
        timer.Signal();
        PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (msg.message == WM_QUIT)
            break;

        //Render here
        float color[] = { 0, 1.0f, 1.0f, 1.0f };  //ARGB
        myCon->ClearRenderTargetView(myRtv, color);

        myCon->ClearDepthStencilView(zBufferView, D3D11_CLEAR_DEPTH, 1, 0);
        //Set up pipeline
        //myCon->OMSetRenderTargets();


        //Output merger
        ID3D11RenderTargetView* tempRTV[] = { myRtv }; //Making our Render target view an array of pointers because the funtion below
        myCon->OMSetRenderTargets(1, tempRTV, zBufferView);
        //Rasterizer
        myCon->RSSetViewports(1, &myPort);
        //Input assembler
        myCon->IASetInputLayout(vLayout);

        myCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        //Make triangle 3D
        static float rotate = 0; rotate += 0.001;
        XMMATRIX temp = XMMatrixIdentity(); //Using XMMATRIX temp for high perfomance
        temp = XMMatrixTranslation(0, 5, 2);
        XMMATRIX temp2rotate = XMMatrixRotationY(rotate);
        temp = XMMatrixMultiply(temp2rotate, temp); //flip these if you want the object to spin around world space
        XMStoreFloat4x4(&myMatricies.wMatrix, temp); //Storing matrix

        //view camera
        camera = cameraMovement(camera, timer.Delta());
        XMStoreFloat4x4(&myMatricies.vMatrix, XMMatrixInverse(nullptr, camera)); //Storing matrix

        //projection
        temp = XMMatrixPerspectiveFovLH(3.14f / 2.0f, aspectR, 0.1f, 1000);
        XMStoreFloat4x4(&myMatricies.pMatrix, temp); //Storing matrix

        D3D11_MAPPED_SUBRESOURCE gpuBuffer;
        HRESULT hr = myCon->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
        *((WVP*)(gpuBuffer.pData)) = myMatricies;
        //memcpy(gpuBuffer.pData, &myMatricies, sizeof(WVP));
        myCon->Unmap(cBuff, 0);

        //Connect const buffer to pipeline
        //HLSL matricies are column major (we need to make it row major)
        ID3D11Buffer* constants[] = { cBuff };
        myCon->VSSetConstantBuffers(0, 1, constants);

        //Immediate context
        //Get a more complex mesh (FBX, obj, header)
        //Load it onto the card (vertex buffer, index buffer)
        //Make sure our shaders can proccess it
        //Place it somewhere else

        //SkyBox setup
        UINT mesh_strides1[] = { sizeof(SimpleVertex) };
        UINT mesh_offsets1[] = { 0 };
        myCon->IASetVertexBuffers(0, 1, &vskyBoxBuffer, mesh_strides1, mesh_offsets1);
        myCon->IASetIndexBuffer(iskyBoxBuffer, DXGI_FORMAT_R32_UINT, 0);
        myCon->VSSetShader(SpaceBoxV, 0, 0);
        myCon->PSSetShader(SpaceBoxP, 0, 0);
        myCon->IASetInputLayout(ShipvLayout);

        temp = XMMatrixIdentity(); //Using XMMATRIX temp for high perfomance
        temp = XMMatrixTranslation(camera.r[3].m128_f32[0], camera.r[3].m128_f32[1], camera.r[3].m128_f32[2]);
        XMStoreFloat4x4(&myMatricies.wMatrix, temp); //Storing matrix

        hr = myCon->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
        *((WVP*)(gpuBuffer.pData)) = myMatricies;
        myCon->Unmap(cBuff, 0);
        //Pixel shader resources (3rd parameter expects an array: bypass with &)
        myCon->PSSetShaderResources(0, 1, &SpaceBoxTex);
        //Draw it
        myCon->DrawIndexed(skyBox.indicesList.size(), 0, 0);
        myCon->ClearDepthStencilView(zBufferView, D3D11_CLEAR_DEPTH, 1, 0);

        UINT strides[] = { sizeof(MyVertex) };
        UINT offsets[] = { 0 };
        ID3D11Buffer* tempVB[] = { vBuff };

        myCon->IASetVertexBuffers(0, 1, tempVB, strides, offsets);

        //Vertex shader stage
        myCon->VSSetShader(vShader, 0, 0);
        //Pixel shader stage
        myCon->PSSetShader(pShader, 0, 0);
        //Pixel shader resources (3rd parameter expects an array: bypass with &)
        myCon->PSSetShaderResources(0, 1, &StonehengeTexture);

        //Set pipeline for stonehenge
        UINT mesh_strides[] = { sizeof(_OBJ_VERT_) };
        UINT mesh_offsets[] = { 0 };
        ID3D11Buffer* meshVB[] = { vBuffMesh };
        myCon->IASetVertexBuffers(0, 1, meshVB, mesh_strides, mesh_offsets);
        myCon->IASetIndexBuffer(iBuffMesh, DXGI_FORMAT_R32_UINT, 0);
        myCon->VSSetShader(vMeshShader,0,0);
        myCon->IASetInputLayout(vMeshLayout);

        //Setting the world matrix to not spin after anything that is drawn here
        temp = XMMatrixIdentity();
        XMStoreFloat4x4(&myMatricies.wMatrix, temp); //Storing matrix
        //Telling the video card to refresh
         hr = myCon->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
        *((WVP*)(gpuBuffer.pData)) = myMatricies;
        myCon->Unmap(cBuff, 0);
        //Draw it
        myCon->DrawIndexed(2532, 0, 0);




        //Immediate context
      //Get a more complex mesh (FBX, obj, header)
      //Load it onto the card (vertex buffer, index buffer)
      //Make sure our shaders can proccess it
      //Place it somewhere else

      //Set pipeline for spaceship
        mesh_strides[0] = { sizeof(SimpleVertex) };
        mesh_offsets[0] = { 0 };
        meshVB[0] = { vshipBuffer };
        myCon->IASetVertexBuffers(0, 1, meshVB, mesh_strides, mesh_offsets); //CHANGE
        myCon->IASetIndexBuffer(ishipBuffer, DXGI_FORMAT_R32_UINT, 0); //CHANGE
        myCon->VSSetShader(ShipvShader, 0, 0);
        myCon->PSSetShader(ShippShader, 0, 0);
        myCon->IASetInputLayout(ShipvLayout);

        temp = XMMatrixIdentity(); //Using XMMATRIX temp for high perfomance
        temp = XMMatrixTranslation(0, 2, 0);
        XMStoreFloat4x4(&myMatricies.wMatrix, temp); //Storing matrix

        //Setting the world matrix to not spin after anything that is drawn here
        temp = XMMatrixIdentity();
        temp = XMMatrixTranslation(0, 3, 0); // Move it
        temp = XMMatrixMultiply(XMMatrixScaling(6, 6, 6), temp); //Make it larger
        temp = XMMatrixMultiply(temp2rotate, temp); //flip these if you want the object to spin around world space
        XMStoreFloat4x4(&myMatricies.wMatrix, temp); 
        //Telling the video card to refresh
        hr = myCon->Map(cBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &gpuBuffer);
        *((WVP*)(gpuBuffer.pData)) = myMatricies;
        myCon->Unmap(cBuff, 0);
        //Pixel shader resources (3rd parameter expects an array: bypass with &)
        myCon->PSSetShaderResources(0, 1, &ShipTexture);
        //Draw it
        myCon->DrawIndexed(shipMesh.indicesList.size(), 0, 0);






      mySwap->Present(0, 0); // Telling the backbuffer (the cleared 2d texture) to swap with the front buffer
    }
    //Release D3D11 interfaces (TO MAKE SURE ALL INTERFACES ARE RELEASED CHECK OUTPUT WINDOW FOR "LIVE OBJECTS"
    releaseData();

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIRECTXGRAPHICS2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DIRECTXGRAPHICS2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);


   //Swap chain parameters
   RECT myWinR;
   GetClientRect(hWnd, &myWinR);

   D3D_FEATURE_LEVEL dx11 = D3D_FEATURE_LEVEL_11_0;
   //Things with "desc" at the end of them are descriptors, they are structs meant to shorten parameters
   DXGI_SWAP_CHAIN_DESC swap;
   ZeroMemory(&swap, sizeof(DXGI_SWAP_CHAIN_DESC)); //Zeros out swap chain
   swap.BufferCount = 1;
   swap.OutputWindow = hWnd;
   swap.Windowed = true;
   swap.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
   swap.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
   swap.BufferDesc.Width = myWinR.right - myWinR.left;
   swap.BufferDesc.Height = myWinR.bottom - myWinR.top;
   swap.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
   swap.SampleDesc.Count = 1;
    
   aspectR = swap.BufferDesc.Width / float(swap.BufferDesc.Height);

   HRESULT hr; // This little guy that you see everywhere catches if the function fails

   //Create sawap chain
   hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, &dx11, 1, D3D11_SDK_VERSION, &swap, &mySwap, &myDev, 0, &myCon);

   //Chooses what surface to place the 2d texture onto for the swap chain to decide where it needs to draw
   ID3D11Resource* backBuffer;
   hr = mySwap->GetBuffer(0, __uuidof(backBuffer), (void**)&backBuffer); //Buffercount increases here so we release it to set it back to 0 before the loop executes again
   hr = myDev->CreateRenderTargetView(backBuffer, NULL, &myRtv);

   backBuffer->Release();

   myPort.Width = swap.BufferDesc.Width;
   myPort.Height = swap.BufferDesc.Height;
   myPort.TopLeftX = myPort.TopLeftY = 0;
   myPort.MinDepth = 0;
   myPort.MaxDepth = 1;

   

   MyVertex tri[] = //NDC space (Z space is from 0-1)
   {
       //xyzw, rgba
       //Front face
       {{0, 1, 0, 1},{1,0,0,1}},
       {{0.25f, -0.25f, -0.25f, 1},{1,1,0,1}},
       {{-0.25f, -0.25f, -0.25f, 1},{1,1,1,1}},
       //Right face
       {{0, 1, 0, 1},{1,0,0,1}},
       {{0.25f, -0.25f, 0.25f, 1},{1,1,0,1}},
       {{0.25f, -0.25f, -0.25f, 1},{1,1,1,1}},
       //Back face
       {{0, 1, 0, 1},{1,0,0,1}},
       {{-0.25f, -0.25f, 0.25f, 1},{1,1,0,1}},
       {{0.25f, -0.25f, 0.25f, 1},{1,1,1,1}},
       //Left face
       {{0, 1, 0, 1},{1,0,0,1}},
       {{-0.25f, -0.25f, -0.25f, 1},{1,1,0,1}},
       {{-0.25f, -0.25f, 0.25f, 1},{1,1,1,1}}
   };

   numVerts = ARRAYSIZE(tri);

   //Load onto grapics card
   D3D11_BUFFER_DESC bDesc;
   D3D11_SUBRESOURCE_DATA subData;
   ZeroMemory(&bDesc, sizeof(bDesc));
   ZeroMemory(&subData, sizeof(subData));

   bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
   bDesc.ByteWidth = sizeof(MyVertex) * numVerts;
   bDesc.CPUAccessFlags = 0;
   bDesc.MiscFlags = 0;
   bDesc.StructureByteStride = 0;
   bDesc.Usage = D3D11_USAGE_IMMUTABLE;

   subData.pSysMem = tri;

   hr = myDev->CreateBuffer(&bDesc, &subData, &vBuff);

   //Write, compile and load shaders

   hr = myDev->CreateVertexShader(MyVShader, sizeof(MyVShader), nullptr, &vShader);
   hr = myDev->CreatePixelShader(MyPShader, sizeof(MyPShader), nullptr, &pShader);
   //Convert dds into logic
   hr = CreateDDSTextureFromFile(myDev, L"./Assets/StoneHenge.dds", nullptr, &StonehengeTexture);

    //Describe vertex to D3D11
   D3D11_INPUT_ELEMENT_DESC ieDesc[] =
   {
       {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
       {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0}
   };

   hr = myDev->CreateInputLayout(ieDesc, 2, MyVShader, sizeof(MyVShader), &vLayout );

   //Create const buffer
   ZeroMemory(&bDesc, sizeof(bDesc));

   bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
   bDesc.ByteWidth = sizeof(WVP);
   bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
   bDesc.MiscFlags = 0;
   bDesc.StructureByteStride = 0;
   bDesc.Usage = D3D11_USAGE_DYNAMIC;

   hr = myDev->CreateBuffer(&bDesc, nullptr, &cBuff);


   //Load complex meshes
   bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
   bDesc.ByteWidth = sizeof(StoneHenge_data);
   bDesc.CPUAccessFlags = 0;
   bDesc.MiscFlags = 0;
   bDesc.StructureByteStride = 0;
   bDesc.Usage = D3D11_USAGE_IMMUTABLE; //IMMUTABLE = Not modifiable

   subData.pSysMem = StoneHenge_data;
   hr = myDev->CreateBuffer(&bDesc, &subData, &vBuffMesh); //Mesh vertex buffer
   
   //Index buffer complex mesh
   bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
   bDesc.ByteWidth = sizeof(StoneHenge_indicies);
   subData.pSysMem = StoneHenge_indicies;
   hr = myDev->CreateBuffer(&bDesc, &subData, &iBuffMesh);

   ZeroMemory(&bDesc, sizeof(bDesc));


   //Load mesh shader
   hr = myDev->CreateVertexShader(MyMeshVShader, sizeof(MyMeshVShader), nullptr, &vMeshShader);
   
   //Make matching input layout
   D3D11_INPUT_ELEMENT_DESC meshInputDesc[] =
   {
       {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
       {"TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
       {"NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
   };
   hr = myDev->CreateInputLayout(meshInputDesc, 3, MyMeshVShader, sizeof(MyMeshVShader), &vMeshLayout);


   hr = myDev->CreateVertexShader(SpaceShipVS, sizeof(SpaceShipVS), nullptr, &ShipvShader);
   hr = myDev->CreatePixelShader(SpaceShipPS, sizeof(SpaceShipPS), nullptr, &ShippShader);

   //Make matching input layout for ship
   LoadMesh("./Assets/WorkingShipMesh", shipMesh);
   hr = CreateDDSTextureFromFile(myDev, L"./Assets/vette_color.dds", nullptr, &ShipTexture);  //Loading texture

   D3D11_INPUT_ELEMENT_DESC meshShipInputDesc[] =
   {
       {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
       {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
       {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}

   };
   hr = myDev->CreateInputLayout(meshShipInputDesc, 3, SpaceShipVS, sizeof(SpaceShipVS), &ShipvLayout);

   //For skybox
   hr = myDev->CreateVertexShader(SpaceBoxVS, sizeof(SpaceBoxVS), nullptr, &SpaceBoxV);
   hr = myDev->CreatePixelShader(SpaceBoxPS, sizeof(SpaceBoxPS), nullptr, &SpaceBoxP);

   LoadMesh("./Assets/SpaceSkyBox", skyBox);
   hr = CreateDDSTextureFromFile(myDev, L"./Assets/Space.dds", nullptr, &SpaceBoxTex);  //Loading texture

   //TODO: make vertex and index buffer for spaceship using shipMesh
      //Load complex meshes
   bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
   bDesc.ByteWidth = sizeof(SimpleVertex) * skyBox.vertexList.size();
   bDesc.CPUAccessFlags = 0;
   bDesc.MiscFlags = 0;
   bDesc.StructureByteStride = 0;
   bDesc.Usage = D3D11_USAGE_IMMUTABLE; //IMMUTABLE = Not modifiable
   subData.pSysMem = skyBox.vertexList.data();
   hr = myDev->CreateBuffer(&bDesc, &subData, &vskyBoxBuffer); //Mesh vertex buffer

   //Index buffer complex mesh
   bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
   bDesc.ByteWidth = sizeof(unsigned int) * (skyBox.indicesList.size());
   subData.pSysMem = skyBox.indicesList.data();
   hr = myDev->CreateBuffer(&bDesc, &subData, &iskyBoxBuffer);

   //TODO: make vertex and index buffer for spaceship using shipMesh
      //Load complex meshes
   bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
   bDesc.ByteWidth = sizeof(SimpleVertex) * shipMesh.vertexList.size();
   bDesc.CPUAccessFlags = 0;
   bDesc.MiscFlags = 0;
   bDesc.StructureByteStride = 0;
   bDesc.Usage = D3D11_USAGE_IMMUTABLE; //IMMUTABLE = Not modifiable
   subData.pSysMem = shipMesh.vertexList.data();
   hr = myDev->CreateBuffer(&bDesc, &subData, &vshipBuffer); //Mesh vertex buffer

   //Index buffer complex mesh
   bDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
   bDesc.ByteWidth = sizeof(unsigned int) * (shipMesh.indicesList.size());
   subData.pSysMem = shipMesh.indicesList.data();
   hr = myDev->CreateBuffer(&bDesc, &subData, &ishipBuffer);

   //Setting up camera
   camera = XMMatrixInverse(nullptr, XMMatrixLookAtLH({ 0, 10, -50 }, { 0,0,0 }, { 0,1,0 }));

   //Zbuffer
   D3D11_TEXTURE2D_DESC zDesc;
   ZeroMemory(&zDesc, sizeof(zDesc));
   zDesc.ArraySize = 1;
   zDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
   zDesc.Width = swap.BufferDesc.Width;
   zDesc.Height = swap.BufferDesc.Height;
   zDesc.Format = DXGI_FORMAT_D32_FLOAT;
   zDesc.Usage = D3D11_USAGE_DEFAULT;
   zDesc.MipLevels = 1;
   zDesc.SampleDesc.Count = 1;

   hr = myDev->CreateTexture2D(&zDesc, nullptr, &zBuffer);

   myDev->CreateDepthStencilView(zBuffer, nullptr, &zBufferView);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

string fileName1 = " ";
void LoadMesh(const char* meshFileName, SimpleMesh& mesh)
{

    std::fstream file{ meshFileName, std::ios_base::in | std::ios_base::binary };

    assert(file.is_open());

    uint32_t player_index_count;
    file.read((char*)&player_index_count, sizeof(uint32_t));

    mesh.indicesList.resize(player_index_count);

    file.read((char*)mesh.indicesList.data(), sizeof(uint32_t) * player_index_count);

    uint32_t player_vertex_count;
    file.read((char*)&player_vertex_count, sizeof(uint32_t));

    mesh.vertexList.resize(player_vertex_count);

    file.read((char*)mesh.vertexList.data(), sizeof(SimpleVertex) * player_vertex_count);

    // Example mesh conditioning if needed - this flips handedness
    for (auto& v : mesh.vertexList)
    {
        v.Pos.x = -v.Pos.x;
        v.Normal.x = -v.Normal.x;
        v.Tex.y = 1.0f - v.Tex.y;
    }

    int tri_count = (int)(mesh.indicesList.size() / 3);

    for (int i = 0; i < tri_count; ++i)
    {
        int* tri = mesh.indicesList.data() + i * 3;

        int temp = tri[0];
        tri[0] = tri[2];
        tri[2] = temp;
    }

    file.close();
}
