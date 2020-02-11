//-----------------------------------------------------------------------------
// File: tea2.cpp
//
// Desc: In this tutorial, we are rendering some tea2. This introduces the
//       concept of the vertex buffer, a Direct3D object used to store
//       tea2. tea2 can be defined any way we want by defining a
//       custom structure and a custom FVF (flexible vertex format). In this
//       tutorial, we are using tea2 that are transformed (meaning they
//       are already in 2D window coordinates) and lit (meaning we are not
//       using Direct3D lighting, but are supplying our own colors).
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#pragma warning(disable:4995)
#include "leetlib.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <strsafe.h>
#include <math.h>
#include <map>
#include <direct.h>
#include <malloc.h>
//#include "resource.h"

//#include "joypad.h"


#include "fmod/api/inc/fmod.h"
#pragma comment(lib,"lib/fmod/api/lib/fmodvc.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")


#pragma warning(disable:4244)

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D       = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB        = NULL; // Buffer to hold tea2
bool fullscreen;
// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw; // The transformed position for the vertex
    DWORD color;        // The vertex color
	float u,v;
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

/*
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::map<int, LPD3DXFONT> fonts;
int lasttextwidth,lasttextheight;
int intextbatch=0;
LPD3DXSPRITE fontsprite;
#define MA_RELEASE(x) {int c=0;if (x) c=(x)->Release();x=NULL;}
void ReleaseFonts();
typedef unsigned int u32;

void StartTextBatch(int size=0);
//int DrawText(int x, int y, int size, u32 col, bool cenetered, const char *pFormat, ...);


void EndTextBatch();

LPD3DXFONT FindFont(int size)
{
	std::map<int, LPD3DXFONT>::iterator fit=fonts.find(size);
	if (fit==fonts.end())
	{
		LPD3DXFONT m_pFont=NULL;
		D3DXCreateFont(g_pd3dDevice,size,0,FW_NORMAL,0,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Lucida Console"), &m_pFont );
		fit=fonts.insert(std::pair<int,LPD3DXFONT>(size,m_pFont)).first;
		//if (intextbatch) fit->second->Begin();
	}
	if (fit!=fonts.end())
	{
		return fit->second;
	}
	else return NULL;
}

void ReleaseFonts()
{
	if (intextbatch) EndTextBatch();
	for (std::map<int, LPD3DXFONT>::iterator it=fonts.begin();it!=fonts.end();++it)
	{
		MA_RELEASE(it->second);
	}
	fonts.clear();
	MA_RELEASE(fontsprite);
	intextbatch=0;
}

void StartTextBatch(int size)
{
	if (intextbatch) EndTextBatch();
	intextbatch=1;
	if (size) FindFont(size);
	if (!fontsprite) 
	{
		D3DXCreateSprite( g_pd3dDevice, &fontsprite);
	}
	if (fontsprite)
	{
		fontsprite->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE );
	}
	//for (std::map<int, LPD3DXFONT>::iterator fit=fonts.begin();fit!=fonts.end();++fit) fit->second->Begin();


}

void EndTextBatch()
{
	if (intextbatch)
	{
		intextbatch=0;
		if (fontsprite)
		{			
			fontsprite->End();
		}
		//for (std::map<int, LPD3DXFONT>::iterator fit=fonts.begin();fit!=fonts.end();++fit) fit->second->End();		
	}
}



int DrawSomeText(int x, int y, int size, int col, bool centered, const char *pFormat, ...)
{
	char debugText[8192];
	va_list	parameter;
	va_start(parameter,pFormat);
	vsprintf(debugText,pFormat,parameter);

	LPD3DXFONT m_pFont=FindFont(size);
	if (!m_pFont) return 0;
	RECT r={x,y,x+100,y+100};	
	
	m_pFont->DrawText(intextbatch?fontsprite:NULL,debugText,-1,&r,DT_CALCRECT,0);
	int wid=r.right-r.left;
	if (centered) r.left-=wid/2;
	if (centered) r.right-=wid/2;
	m_pFont->DrawText(intextbatch?fontsprite:NULL,debugText,-1,&r,DT_TOP|DT_LEFT,col);
	lasttextheight=r.bottom-r.top;
	lasttextwidth=r.right-r.left;
	return lasttextheight;


}

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = !fullscreen;
	d3dpp.SwapEffect = fullscreen? D3DSWAPEFFECT_FLIP : D3DSWAPEFFECT_DISCARD;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE ;
	d3dpp.BackBufferFormat = fullscreen ? D3DFMT_A8R8G8B8 : D3DFMT_UNKNOWN;
	d3dpp.BackBufferWidth=800;
	d3dpp.BackBufferHeight=600;
	d3dpp.FullScreen_RefreshRateInHz = fullscreen? 60 : 0;

    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Device state would normally be set here

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitVB()
// Desc: Creates a vertex buffer and fills it with our tea2. The vertex
//       buffer is basically just a chuck of memory that holds tea2. After
//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
//       also uses index buffers. The special thing about vertex and index
//       buffers is that they can be created in device memory, allowing some
//       cards to process them in hardware, resulting in a dramatic
//       performance gain.
//-----------------------------------------------------------------------------
HRESULT InitVB()
{
  
    if( FAILED( g_pd3dDevice->CreateVertexBuffer( 4*sizeof(CUSTOMVERTEX),
                                                  D3DUSAGE_DYNAMIC, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
    {
        return E_FAIL;
    }

   

	//D3DXCreateTextureFromFile(g_pd3dDevice,"bg.jpg",&g_bgtex);
	//D3DXCreateTextureFromFile(g_pd3dDevice,"arrow.png",&g_arrow);


    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    if( g_pVB != NULL )        
        g_pVB->Release();

    if( g_pd3dDevice != NULL ) 
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )       
        g_pD3D->Release();

	
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------

/*
float RotateU(float u, float v, float a)
{
	u=u-0.5;
	v=v-0.5;
	return u*cos(a)-v*sin(a)+0.5;
}

float RotateV(float u, float v, float a)
{
	u=u-0.5;
	v=v-0.5;
	return u*sin(a)+v*cos(a)+0.5;
}

void DrawQuad(float x1, float y1, float x2, float y2, DWORD col=0xffffffff, float a=0)
{

	CUSTOMVERTEX tea2[] =
	{
		{ x1, y1, 0.5f, 1.0f, col, RotateU(0,0,a), RotateV(0,0,a) }, // x, y, z, rhw, color
		{ x2, y1, 0.5f, 1.0f, col, RotateU(1,0,a), RotateV(1,0,a)},
		{ x1, y2, 0.5f, 1.0f, col, RotateU(0,1,a), RotateV(0,1,a)},
		{ x2, y2, 0.5f, 1.0f, col, RotateU(1,1,a), RotateV(1,1,a)},
	};

	VOID* ptea2;
	if( FAILED( g_pVB->Lock( 0, sizeof(tea2), (void**)&ptea2, D3DLOCK_DISCARD ) ) )
		return ;
	memcpy( ptea2, tea2, sizeof(tea2) );
	g_pVB->Unlock();


	g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
}

void DrawTri(float x1, float y1, float x2, float y2, float x3, float y3, DWORD col=0xffffffff)
{
	//OutputDebugString("triangle!");

	CUSTOMVERTEX tea2[] =
	{
		{ x1, y1, 0.5f, 1.0f, col, 0,0 }, // x, y, z, rhw, color
		{ x2, y2, 0.5f, 1.0f, col, 0,0},
		{ x3, y3, 0.5f, 1.0f, col, 0,0},		
		{ x3, y3, 0.5f, 1.0f, col, 0,0},	
	};

	VOID* ptea2=NULL;
	if( FAILED( g_pVB->Lock( 0, sizeof(tea2), (void**)&ptea2, D3DLOCK_DISCARD ) ) )
	{
		OutputDebugString("lock failed");
		return ;
	}
	memcpy( ptea2, tea2, sizeof(tea2) );
	g_pVB->Unlock();


	if (FAILED(g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 1 )))
	{
		OutputDebugString("draw failed");
	}
}



/*
VOID Render()
{
    // Clear the backbuffer to a blue color
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(128,128,128), 1.0f, 0 );
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
	
	g_pd3dDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	g_pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_DIFFUSE);
	g_pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_TEXTURE);
	g_pd3dDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);

	g_pd3dDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_DIFFUSE);
	g_pd3dDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_TEXTURE);
	g_pd3dDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	

	static float spinpos=0;
	static float spinv=0;
	static bool spinning=false;
	static bool nomorespin=false;
	srand(GetTickCount());
    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        // Draw the triangles in the vertex buffer. This is broken into a few
        // steps. We are passing the tea2 down a "stream", so first we need
        // to specify the source of that stream, which is our vertex buffer. Then
        // we need to let D3D know what vertex shader to use. Full, custom vertex
        // shaders are an advanced topic, but in most cases the vertex shader is
        // just the FVF, so that D3D knows what type of tea2 we are dealing
        // with. Finally, we call DrawPrimitive() which does the actual rendering
        // of our geometry (in this case, just one triangle).
        g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );
        g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
        
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		g_pd3dDevice->SetTexture(0,g_bgtex);
		DrawQuad(0,0,1280,1024);
		

		
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_DESTCOLOR);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_SRCCOLOR);
		g_pd3dDevice->SetTexture(0,NULL);

		float totw=0;
		float temp[10];
		for (int n=0;n<numpeople;n++)
		{
			// ratio weights: 
			if (GetAsyncKeyState('R')<0)
			{
				temp[n]= (1.f+teas[n].consumed) / (1.f+teas[n].madecups);
			}
			else
			{
				// dave weights
				temp[n]= powf(1.2f, teas[n].consumed - teas[n].madecups - teas[n].maderounds);
			}
			
			
			totw+=temp[n];
		}
		angles[0]=0;
		for (int n=0;n<numpeople;n++)
		{
			temp[n]=temp[n]/totw*PI*2;
			angles[n+1]=angles[n]+temp[n];
		}
		angles[numpeople]=PI*2;

		for (int n=0;n<numpeople;n++)
		{
			int red=sinf(n*PI*2/numpeople)*100+128;
			int green=sinf(n*PI*2/numpeople+PI*2/3)*100+128;
			int blue=sinf(n*PI*2/numpeople+PI*4/3)*100+128;
			DWORD col=(red<<16)+(green<<8)+(blue);
			float t1=0,t2=0;
			for (int i=0;i<16;i++)
			{
				t1=(i/16.f)*temp[n]+angles[n];
				t2=((i+1)/16.f)*temp[n]+angles[n];
				
				DrawTri(640,512,640+500*sinf(t1),512-500*cosf(t1),640+500*sinf(t2),512-500*cosf(t2),col|0xff000000);

			}
		}

		//exit(1);

		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
		g_pd3dDevice->SetTexture(0,g_arrow);

		for (int n=0;n<numpeople;n++)
		{			
			float t1=(0.5)*temp[n]+angles[n];
			DrawText(642+300*sinf(t1),514-300*cosf(t1),40,0xcf000000,true,teas[n].name);
			DrawText(640+300*sinf(t1),512-300*cosf(t1),40,0xffffffff,true,teas[n].name);
		}
		for (int c1=0;c1<64;c1++)
		{
			float arrowsize=384;
			DrawQuad(640-arrowsize,512-arrowsize,640+arrowsize,512+arrowsize,0x08ffffff, -spinpos-spinv*c1/64.f);
		}
		//if (GetAsyncKeyState(VK_ESCAPE)&1) PostQuitMessage(0);
		if (GetAsyncKeyState(VK_BACK)<0)
		{
			spinv*=0.8;
		}
		if (GetAsyncKeyState(VK_SPACE)<0)
		{
			if (nomorespin==false) spinv+=0.01+rand()/3276800.f;
			if (spinv>0.2) spinning=true;
		}
		else if (spinning) nomorespin=true;
		spinpos+=spinv;
		spinv*=0.99f;
		if (spinv<0.001f) 
		{
			spinv=0;
			if (spinning)
			{
				spinning=0;
				while (spinpos<0) spinpos+=PI*2;
				while (spinpos>=PI*2) spinpos-=PI*2;
				int winner=0;
				for (winner=0;winner<numpeople;winner++) if (spinpos>=angles[winner] && spinpos<angles[winner+1]) break;				
				winner=(winner%numpeople);

				
				
				sprintf(winnerbuf,"%s is the winner! MAKE SOME TEA BITCH!",teas[winner].name);
				if (DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG1),NULL,(DLGPROC)mydialogproc)==IDOK && numcups>0)
							
				//if (MessageBox(GetForegroundWindow(),buf,"tea!",MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
				{
					teas[winner].maderounds++;
					teas[winner].madecups+=numcups;
					writetea();
				}

				nomorespin=false;
			}
		}
		if (spinpos>PI*2) spinpos-=PI*2;

		if (GetAsyncKeyState(VK_SHIFT)<0)
		{		
			for (int c1=0;c1<numpeople;c1++)
			{
				char buf[1024];sprintf(buf,"%9s made %2d rounds, %3d cups, drank %3d cups",teas[c1].name,teas[c1].maderounds,teas[c1].madecups,teas[c1].consumed);
				DrawText(2,2+c1*24,20,0x80000000,false,buf);
				DrawText(0,0+c1*24,20,0xffffffff,false,buf);

			}
		}
		else
		{
			DrawText(0, 0,20,0xffffffff,false,"Press SPACE to spin!");
			DrawText(0,24,20,0xffffffff,false,"Press BACKSPACE to brake");
			DrawText(0,48,20,0xffffffff,false,"Press SHIFT for stats");
			
		}

        // End the scene
        g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
	Sleep(10);
}

*/


//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
bool g_keydown[256];
int g_keyhit[256];
int g_mb;
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
	case WM_LBUTTONDOWN:
		SetCapture(hWnd);
		g_mb|=1;
		g_keydown[VK_LBUTTON]=true;
		g_keyhit[VK_LBUTTON]++;
		break;
	case WM_RBUTTONDOWN:
		SetCapture(hWnd);
		g_keydown[VK_RBUTTON]=true;
		g_keyhit[VK_RBUTTON]++;
		g_mb|=2;
		break;
	case WM_MBUTTONDOWN:
		SetCapture(hWnd);
		g_mb|=4;
		g_keydown[VK_MBUTTON]=true;
		g_keyhit[VK_MBUTTON]++;
		break;
	case WM_LBUTTONUP:
		ReleaseCapture();
		g_mb&=~1;
		g_keydown[VK_LBUTTON]=false;
		break;
	case WM_RBUTTONUP:
		ReleaseCapture();
		g_mb&=~2;
		g_keydown[VK_RBUTTON]=false;
		break;
	case WM_MBUTTONUP:
		ReleaseCapture();
		g_mb&=~4;
		g_keydown[VK_MBUTTON]=false;
		break;
		
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		g_keydown[wParam&255]=true;
		g_keyhit[wParam&255]++;
		return 0;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		g_keydown[wParam&127]=false;
		break;

    case WM_DESTROY:
        Cleanup();
        PostQuitMessage( 0 );
        return 0;
	case WM_ACTIVATEAPP:
		if (!wParam)
		{
			memset(g_keydown,0,sizeof(g_keydown));
		}
		break;

	case WM_ACTIVATE:
		if( WA_INACTIVE != wParam )
		{
			// Make sure the device is acquired, if we are gaining focus.
			
		}
		break;
    }


    return DefWindowProc( hWnd, msg, wParam, lParam );
}

LARGE_INTEGER starttime;
LARGE_INTEGER freq;
extern HWND hWnd;
HWND hWnd;

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR cmd, INT )
{
	int id = MessageBox(NULL,"fullscreen?","answer me!",MB_YESNOCANCEL);
	if (id==IDCANCEL) return 0;
	fullscreen=(id==IDYES);

    // Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "crapcrap", NULL };
    RegisterClassEx( &wc );

	RECT r={0,0,800,600};
	int style = fullscreen ? WS_POPUP : WS_OVERLAPPEDWINDOW;
	style|=WS_VISIBLE;
AdjustWindowRect(&r,style,false);

    // Create the application's window
     hWnd = CreateWindow( "crapcrap", "crap crap",
                              style, 0,0,r.right-r.left,r.bottom-r.top,
                              GetDesktopWindow(), NULL, wc.hInstance, NULL );
	
	 FSOUND_Init(44100, 42, 0);

	QueryPerformanceCounter(&starttime);
	QueryPerformanceFrequency(&freq);
    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        // Create the vertex buffer
        if( SUCCEEDED( InitVB() ) )
        {
			//SetWindowPos(hWnd,NULL,0,0,1024,768,SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOMOVE|SWP_ASYNCWINDOWPOS);
			SetCursor(LoadCursor(NULL,IDC_ARROW));

            // Show the window
            ShowWindow( hWnd, SW_SHOWDEFAULT );
            UpdateWindow( hWnd );

			//InitDirectInput( hWnd );			
			
            Game();
        }
    }

    UnregisterClass( "crapcrap", wc.hInstance );
    return 0;
}

//////////////////////////////////

bool WantQuit(DWORD clearcol)
{
	// Enter the message loop
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	while ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
		if (msg.message==WM_QUIT) return true;
	}	

	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, clearcol, 1.0f, 0 );
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE,false);

	g_pd3dDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	g_pd3dDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	g_pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_DIFFUSE);
	g_pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_TEXTURE);
	g_pd3dDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);

	g_pd3dDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_DIFFUSE);
	g_pd3dDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_TEXTURE);
	g_pd3dDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);

	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING,false);
	//g_pd3dDevice->SetTexture(0,NULL);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);

	D3DVIEWPORT9 vp={ 0,0, 800, 600, 0, 1};
	//g_pd3dDevice->SetViewport(&vp);

	g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );

	// Begin the scene
	g_pd3dDevice->BeginScene() ;

	//UpdateDirectInput();

	return false;
}
int	GetTimeInMS() // ...since start of program
{
	LARGE_INTEGER arse;
	QueryPerformanceCounter(&arse);
	return ((arse.QuadPart-starttime.QuadPart)*1000) / freq.QuadPart;
}

void Flip()
{
	
	static int lastflip=0;
	if (lastflip==0) lastflip = GetTimeInMS();
	g_pd3dDevice->EndScene();

	// Present the backbuffer contents to the display
	
	//while (GetTimeInMS()<lastflip+1000/60) ;// Sleep(0); // clamp to max of 60hz
	lastflip=GetTimeInMS();

	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
	Sleep(0);
	memset(g_keyhit,0,sizeof(g_keyhit));
	SetCursor(LoadCursor(NULL,IDC_ARROW));
	
}




void GetMousePos(float &x, float &y) // 0,0 is top left; 800,600 is bottom right
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hWnd, &p);
	x=p.x;
	y=p.y;	
}

bool IsKeyDown(int key) // use windows VK_ codes for special keys, eg VK_LEFT; use capital chars for letter keys eg 'A', '0'
{
	return g_keydown[key&255];
}

/*bool IsKeyHitSinceLastFlip(int key)
{
	return g_keyhit[key&255] > 0;
}
*/

// 'sprite output' 
void *LoadSprite(const char *fname)
{
	IDirect3DTexture9 *tex = NULL;
	D3DXCreateTextureFromFile(g_pd3dDevice,fname,&tex);
	return tex;
}

void SetCurrentTexture(void *tex )
{
	IDirect3DTexture9 *t = (IDirect3DTexture9 *)tex;
	g_pd3dDevice->SetTexture(0,t);
}

/*
void DrawRectangle(float x1, float y1, float x2, float y2, DWORD col )
{
	CUSTOMVERTEX tea2[] =
	{
		{ x1, y1, 0.5f, 1.0f, col, 0,0, }, // x, y, z, rhw, color
		{ x2, y1, 0.5f, 1.0f, col, 1,0, },
		{ x1, y2, 0.5f, 1.0f, col, 0,1, },
		{ x2, y2, 0.5f, 1.0f, col, 1,1, },
	};
	g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, tea2, sizeof(CUSTOMVERTEX));

}
*/
void DrawSprite(void *sprite, float xcentre, float ycentre, float xsize, float ysize, float angle, DWORD col )
{
	SetCurrentTexture(sprite);
	float c=cosf(angle);
	float s=sinf(angle);
#define ROTATE(xx,yy) xcentre+(xx)*c+(yy)*s,ycentre+(yy)*c-(xx)*s 
	CUSTOMVERTEX tea2[] =
	{

		///{ xcentre+xsize*c+ysize*s,ycentre+ysize*c-xsize*s , 0.5f, 1.0f, col, 0,0, }, // x, y, z, rhw, color
		
		{ ROTATE(-xsize,-ysize), 0.5f, 1.0f, col, 0,0, }, // x, y, z, rhw, color
		{ ROTATE( xsize,-ysize), 0.5f, 1.0f, col, 1,0, },
		{ ROTATE(-xsize, ysize), 0.5f, 1.0f, col, 0,1, },
		{ ROTATE( xsize, ysize), 0.5f, 1.0f, col, 1,1, },
	};
	g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, tea2, sizeof(CUSTOMVERTEX));
}

/*
// 'flat colour' output
void DrawLine(float x1, float y1, float x2, float y2, DWORD col ) // no texture
{
	IDirect3DBaseTexture9 *oldtex = NULL;
	g_pd3dDevice->GetTexture(0, &oldtex);
	g_pd3dDevice->SetTexture(0, NULL);
	CUSTOMVERTEX tea2[] =
	{
		{ x1, y1, 0.5f, 1.0f, col, 0,0, }, // x, y, z, rhw, color
		{ x2, y2, 0.5f, 1.0f, col, 1,0, }
	};
	g_pd3dDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, tea2, sizeof(CUSTOMVERTEX));

	g_pd3dDevice->SetTexture(0, oldtex);
}

void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, DWORD col ) // flat colored tri, no texture
{
	IDirect3DBaseTexture9 *oldtex = NULL;
	g_pd3dDevice->GetTexture(0, &oldtex);
	g_pd3dDevice->SetTexture(0, NULL);
	CUSTOMVERTEX tea2[] =
	{
		{ x1, y1, 0.5f, 1.0f, col, 0,0, }, // x, y, z, rhw, color
		{ x2, y2, 0.5f, 1.0f, col, 1,0, },
		{ x3, y3, 0.5f, 1.0f, col, 1,0, }
	};
	g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, tea2, sizeof(CUSTOMVERTEX));

	g_pd3dDevice->SetTexture(0, oldtex);
}


// 'advanced' output - for geeks only - for drawing arbitrarily textured triangles and line lists
void DrawTriangleList(Vertex *verts, int numtris)
{
	CUSTOMVERTEX *vs = (CUSTOMVERTEX *)alloca(sizeof(CUSTOMVERTEX) * numtris * 3);
	CUSTOMVERTEX *d=vs;
	for (int n=0;n<numtris*3;n++)
	{
		d->x=verts->x;
		d->y=verts->y;
		d->z=0.5;
		d->rhw=1;
		d->color=verts->colour;
		d->u=verts->u;
		d->v=verts->v;
		d++;
		verts++;
	}
	g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, numtris, vs, sizeof(CUSTOMVERTEX));
}

void DrawLineList(Vertex *verts, int numlines)
{
	CUSTOMVERTEX *vs = (CUSTOMVERTEX *)alloca(sizeof(CUSTOMVERTEX) * numlines * 2);
	CUSTOMVERTEX *d=vs;
	for (int n=0;n<numlines * 2;n++)
	{
		d->x=verts->x;
		d->y=verts->y;
		d->z=0.5;
		d->rhw=1;
		d->color=verts->colour;
		d->u=verts->u;
		d->v=verts->v;
		d++;
		verts++;
	}
	g_pd3dDevice->DrawPrimitiveUP(D3DPT_LINELIST, numlines, vs, sizeof(CUSTOMVERTEX));
}
*/

FSOUND_STREAM *music;

int PlayMusic(const char *fname, float volume)
{
	if (music) StopMusic();
	music = FSOUND_Stream_Open(fname,FSOUND_LOOP_NORMAL,0,0);
	int chan = FSOUND_Stream_Play(FSOUND_FREE,music);
	if (volume<=0) volume=0;
	if (volume>1) volume=1;
	FSOUND_SetVolume(chan, (int)(volume*255));
	return chan;
}

void StopMusic()
{
	if (music)
	{
		FSOUND_Stream_Close(music);
	}
	music=NULL;
}

void *LoadSnd(const char *fname, bool looped)
{
	int flags=0;
	if (looped) flags|=FSOUND_LOOP_NORMAL;
	return FSOUND_Sample_Load(FSOUND_FREE,fname,flags,0,0);
}

int PlaySnd(void *sound, float volume)
{
	if (!sound) return -1;
	if (volume<=0) volume=0;
	if (volume>1) volume=1;
	int chan = FSOUND_PlaySound(FSOUND_FREE,(FSOUND_SAMPLE*)sound);
	FSOUND_SetVolume(chan, (int)(volume*255));
	return chan;
}

void StopSnd(int handle)
{
	if (handle<=0) return ;
	FSOUND_StopSound(handle);
}

void ChangeVolume(int handle, float volume)
{
	if (handle<=0) return ;
	if (volume<=0) volume=0;
	if (volume>1) volume=1;
	FSOUND_SetVolume(handle, (int)(volume*255));
}
