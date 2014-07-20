//-----------------------------------------------------------------------------
// File: Vertices.cpp
//
// Desc: In this tutorial, we are rendering some vertices. This introduces the
//       concept of the vertex buffer, a Direct3D object used to store
//       vertices. Vertices can be defined any way we want by defining a
//       custom structure and a custom FVF (flexible vertex format). In this
//       tutorial, we are using vertices that are transformed (meaning they
//       are already in 2D window coordinates) and lit (meaning we are not
//       using Direct3D lighting, but are supplying our own colors).
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) 
#include <iostream>
using namespace std;
#include<stdlib.h>
#include <time.h>
#include <d3dx9.h>
#include <fstream>




//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D       = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB;// Buffer to hold vertices
LPDIRECT3DVERTEXBUFFER9 g_floor;// Buffer to hold vertices
LPDIRECT3DVERTEXBUFFER9 foodVB       = NULL; //bu
LPDIRECT3DTEXTURE9      g_pTexture[6]  ;
LPDIRECT3DTEXTURE9      g_psnowTexture[9];
LPDIRECT3DTEXTURE9      g_num[10]  ;//number texture
LPDIRECT3DTEXTURE9      g_pfloor  ;//floor texture
LPDIRECT3DTEXTURE9      g_pslide  ;//floor texture
LPDIRECT3DTEXTURE9      g_pbigslide  ;//big slide texture
LPDIRECT3DTEXTURE9      g_plift  ;//lift texture
LPDIRECT3DTEXTURE9      g_pfood  ;//food texture
LPDIRECT3DTEXTURE9      g_iTexture   = NULL; // Our texture - contains the INSTRUCTIONS
LPDIRECT3DTEXTURE9      g_final   = NULL; // Our texture - contains the INSTRUCTIONS

LPDIRECT3DTEXTURE9      g_pTexture2[6]  ;
int r3=0;
int pot=0,c=0,i=0;
int arr[100][2];
int roll=0;
int fwd=301;
int updwn=0;
char dir='r';
int inc=0;
int inc2=0;
int dontdraw=0;
int k=0;
int mov=0;
int diff=0;
char liftmov;
int diffa=0;
int brbase,brtop;
char ins='a';
char store;
int x1=100,x2=130,vai1=100,vai2=190,z1=160,z2=190,w1=160,w2=130;
int randfood,randfood2;
int currtexsnow=0,collided=0;
int currtex=0,currtex2=0;
int a1,a2,c1,c2,b1,b2,d1,d2;
int rand3=0,stop=1,q=0,randir;
float acc,acc2;
int diffheightballbear;
int point=0;
int life,totlife=6,nxtlif=0;
int show_end=0;
wchar_t ani[][50]   =
                {
					L"bear\\1.bmp",
					L"bear\\22.bmp",
					L"bear\\33.bmp",
					L"bear\\44.bmp",
					L"bear\\55.bmp",
					L"bear\\66.bmp",
                };
wchar_t sani[][50]   =
                {
					L"bear\\s1.bmp",
					L"bear\\s2.bmp",
					L"bear\\s3.bmp",
					L"bear\\s4.bmp",
					L"bear\\s5.bmp",
					L"bear\\s6.bmp",
					L"bear\\s7.bmp",
					L"bear\\s8.bmp",
					L"bear\\s9.bmp",

			    };
wchar_t numbers[][50]   =
                {   
					
					L"0.bmp",
					L"1.bmp",
					L"2.bmp",
					L"3.bmp",
					L"4.bmp",
					L"5.bmp",
					L"6.bmp",
					L"7.bmp",
					L"8.bmp",
					L"9.bmp",
                };
/*wchar_t ani2[][50]   =
                {
					L"D:\\cprogs\\bear\\7.bmp",
					L"D:\\cprogs\\bear\\8.bmp",
					L"D:\\cprogs\\bear\\9.bmp",
					L"D:\\cprogs\\bear\\10.bmp",
					L"D:\\cprogs\\bear\\11.bmp",
					L"D:\\cprogs\\bear\\12.bmp",
                };
*/
// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw; // The transformed position for the vertex
    DWORD color;        // The vertex color

	FLOAT       tu, tv;   // The texture coordinates
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)




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
	/*
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	*/
	
    d3dpp.Windowed = FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = 1024;
	d3dpp.BackBufferHeight = 768;
	
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Device state would normally be set here
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
   
     for(int r3=0;r3<6;r3++)
	{
        // load the bear
	     D3DXCreateTextureFromFileEx( g_pd3dDevice, (LPCWSTR)	ani[r3],     
		 0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_pTexture[r3]);
    
	}

	 for(int r=0;r<9;r++)

	{    
	     //load the snow texture
		 D3DXCreateTextureFromFileEx( g_pd3dDevice, (LPCWSTR)	sani[r],     
		 0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_psnowTexture[r]);

	}
	   
      for(int r2=0;r2<10;r2++)
	 {
	 // load the number textures
	 D3DXCreateTextureFromFileEx( g_pd3dDevice, (LPCWSTR)	numbers[r2],     
	 0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_num[r2]);
	} 
	 

    
	
	
	
	 D3DXCreateTextureFromFileEx( g_pd3dDevice, L"kwalkgame\\floor2.bmp",     
		0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_pfloor); 


	 D3DXCreateTextureFromFileEx( g_pd3dDevice, L"kwalkgame\\slide.bmp",     
		0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_pslide); 


	  D3DXCreateTextureFromFileEx( g_pd3dDevice, L"kwalkgame\\lift.bmp",     
		0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_plift); 

	  
	  D3DXCreateTextureFromFileEx( g_pd3dDevice, L"kwalkgame\\bearfood.bmp",     
		0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_pfood); 


	   D3DXCreateTextureFromFileEx( g_pd3dDevice, L"kwalkgame\\bigslide.bmp",     
		0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_pbigslide); 
												
		D3DXCreateTextureFromFileEx( g_pd3dDevice, L"kwalkgame\\instructions.bmp",     
		0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_iTexture);										
		D3DXCreateTextureFromFileEx( g_pd3dDevice, L"kwalkgame\\end scene.bmp",     
		0, 0,1, 0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,D3DX_DEFAULT , D3DX_DEFAULT ,D3DCOLOR_XRGB(77,77,77), 0,0, &g_final);										

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitVB()
// Desc: Creates a vertex buffer and fills it with our vertices. The vertex
//       buffer is basically just a chunk of memory that holds vertices. After
//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
//       also uses index buffers. The special thing about vertex and index
//       buffers is that they can be created in device memory, allowing some
//       cards to process them in hardware, resulting in a dramatic
//       performance gain.
//-----------------------------------------------------------------------------




HRESULT InitVB()
{   

    // Create the vertex buffer. Here we are allocating enough memory
    // (from the default pool) to hold all our 3 custom vertices. We also
    // specify the FVF, so the vertex buffer knows what data it contains.
	 g_pd3dDevice->CreateVertexBuffer( 300*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_pVB, NULL );
    

	g_pd3dDevice->CreateVertexBuffer( 300*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_floor, NULL );

	g_pd3dDevice->CreateVertexBuffer( 300*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT,&foodVB , NULL );
   



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

	if( g_floor != NULL )        
        g_floor->Release();
	  

    

    if( g_pd3dDevice != NULL ) 
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )       
        g_pD3D->Release();
}


int i2=0,j=0,k2=0,arr2[3];
void drawscore()
{

g_pd3dDevice->SetTexture(0, g_num[k2]);
g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST,114,2);
g_pd3dDevice->SetTexture(0, g_num[j]);
g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST,120,2);
g_pd3dDevice->SetTexture(0, g_num[i2]);
g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST,126,2);

}
void setscore()
{

 if(k2<=9)
 {
    arr2[0]=i2;
    arr2[1]=j;
    arr2[2]=k;
    k2=k2+1;
 }
 if(point%10==0)
    {
     j=j+1;
     k2=0;
    }
  if(point%100==0)
    {
     i2=i2+1;
     j=0;
     k2=0;
   }


drawscore();


}

void myDelay() {
		int delay1=2, delay2=2;
		for(int j=0;j<1900000;j++)
		{
			delay1 = 2+2;
			delay2 = delay1+delay2;
		}
}
void highscores()
{
 
ofstream result;
		    result.open("score.txt",ios::app);
		    result<<"\n";
	        result<<point;
	       //result<<hello;
	        result.close();
			
           show_end=1;
       
				

		


   

} 
int bearnumber=0;
int bearnumber2=0;






int abso(int x)
  {
	  if(x<0)
	  {return (-1*x);}

     
     return x; 

  } 
void levelbear()

{
  

  if(brbase>650)
  {brbase=730;}
  if(dir=='l'||dir=='r')
    {
      if(brbase<400)
	  {
        brbase=190;
	  }

	  if(brbase>=400&&brbase<600)
	  {
       brbase=460;
	  }

	  
    }


	brtop=brbase-152;


}

void snowroll()
{
if(rand3==0)
		 {
         
		 if(b1>571&&b1<751)
		 {
          roll=1030;         
         }
		 //due to some reason the ball texure coordinates were given as inverted,so an iverted image forms but as its a circle no visible affect
		 else
		 a2=210; b2=110;c2=110; d2=210; 	
		 }
		 if(rand3==1)
		 {
         if(b1>300&&b1<450)
		 {
         roll=1050;
		 }
		 else
		 a2=480; b2=380; c2=380; d2=480;
		 }
		   if(rand3==2)
		 {
		 a2=750; b2=650; c2=650; d2=750;
		 }
		


		 if(currtexsnow>8)
		 {
           currtexsnow=0;
		 }
		 g_pd3dDevice->SetTexture(0, g_psnowTexture[currtexsnow]);
	     g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 84,2);  
		 myDelay();
		 myDelay();
		 if(q%2==0)
		 currtexsnow++;
		
		 if(randir==0)
		 {
		 a1=roll-20,b1=roll-20,c1=80+roll,d1=80+roll;
		 roll=roll+8;
		 }
         if(randir==1)
		 {
         a1=924+roll,b1=924+roll,c1=1024+roll,d1=1024+roll;
		 roll=roll-8;  
		 }
}
void snowballs()
{
         srand( (unsigned)time( NULL ) );



		   snowroll();        

		   
			
		 
		 
}
	    
void checkcollision()
{

diffheightballbear=abso((brtop+95)-b2);
if(((150+fwd<d1&&a1<150+fwd)||(a1<300+fwd&&a1>150+fwd))&&diffheightballbear<50)
{
fwd=0;
if(brbase<300)
{updwn=520;}
else
updwn=-10;
dir='r';
totlife=totlife-2;

}

}
void check_if_ate()
{

for(k=0;k<10;k++)
{
diffheightballbear=abso((brtop+95)-arr[k][1]);
if(((arr[k][0]+40<300+fwd&&arr[k][0]+40>150+fwd))&&diffheightballbear<50)

    {
       arr[k][0]=-400;
       point=point+1;
	   setscore();
    }
 
}


}
void sethoney()
{

  srand( (unsigned)time( NULL ) );
  
  for(i=0;i<10;i++)
     {
         randfood2=rand()%1000;
         randfood=rand()%3;
	    if(randfood==0)
           {
            x2=130;
           }
         if(randfood==1)
           {
            x2=400;
            }
        if(randfood==2)
           {
            x2=670;
           }

      x1=randfood2;
      arr[i][0]=x1;
	  arr[i][1]=x2;
     }
}
void checkifdead()
{
 if(totlife==-2&&show_end!=1)
 {
  highscores();
 
 }

}
void food()
{

 /*
    g_pd3dDevice->SetTexture(0, g_pfood);   
    g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST,120,2);  
 */
 

  CUSTOMVERTEX food[10];
 
for(i=0;i<10;i++)
{       

	    check_if_ate();
		
        food[0].x = arr[i][0] ;
		food[0].y = arr[i][1]+60;
		food[0].z = 1;
		food[0].rhw = 1;
		food[0].color = D3DCOLOR_XRGB(255,255,255);
        food[0].tu=0;
        food[0].tv=1;

		food[1].x = arr[i][0] ;
		food[1].y = arr[i][1];
		food[1].z = 1;
		food[1].rhw = 1;
		food[1].color = D3DCOLOR_XRGB(255,255,255);
        food[1].tu=0;
        food[1].tv=0;



        food[2].x =  arr[i][0]+60;
		food[2].y =  arr[i][1]+60;;
		food[2].z = 1;
		food[2].rhw = 1;
		food[2].color = D3DCOLOR_XRGB(255,255,255);
        food[2].tu=1;
        food[2].tv=1;


        food[3].x = arr[i][0]+60;
		food[3].y =  arr[i][1];
		food[3].z = 1;
		food[3].rhw = 1;
		food[3].color = D3DCOLOR_XRGB(255,255,255);
        food[3].tu=1;
        food[3].tv=0;


        void *pVertices;
		g_pd3dDevice->SetStreamSource( 0, foodVB, 0, sizeof(CUSTOMVERTEX) );
	    g_pd3dDevice->SetTexture(0, g_pfood);
        foodVB->Lock( 0, sizeof(food), (void**)&pVertices, 0 );
        memcpy( pVertices, food, sizeof(food) );
        foodVB->Unlock();

        g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0,2);       

  }
    
}

int count = 0;
void check_if_food_is_over()
{ 
  count=0;
  for(i=0;i<10;i++)
     {
	  if(arr[i][0]==-400)
	  {count=count++;}
   
     }
  if(count==10)
    {
	sethoney();
    }
}
//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
void Render() 
{

    
	
	q=q++;
	if(dir=='x'&& 300+fwd>1000)
	    {   
           
            brbase=720+mov;
			brtop=brbase-152;
			
    	}
	else
		
	{ 
      brbase=200+updwn;
      brtop=brbase-152;
	  
 	} 
    if(150+fwd>1024)
	  {
        fwd=-200;
	  }
	if(300+fwd<0)
      {
       fwd=800;
	  }
 
    levelbear();

	

    CUSTOMVERTEX vertices[] =
	{
       


		//mundu1
        { 150+fwd, brtop,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 150+fwd,  brbase, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 300+fwd,  brbase, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 150+fwd, brtop,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 300+fwd, brtop, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 300+fwd,  brbase, 0, 1.0f, 0xFFFFFFFF, 1,1},

       //mundu 2
		{150+fwd, brtop ,  0, 1.0f, 0xFFFFFFFF, 1,0}, // x, y, z, rhw, color,tex
        { 150+fwd,  brbase, 0, 1.0f, 0xFFFFFFFF, 1,1},
        { 300+fwd,  brbase, 0, 1.0f, 0xFFFFFFFF, 0,1},

        { 150+fwd,  brtop,  0, 1.0f,  0xFFFFFFFF, 1,0}, // x, y, z, rhw, color,tex
        { 300+fwd,  brtop, 0, 1.0f,  0xFFFFFFFF, 0,0},
        { 300+fwd, brbase, 0, 1.0f, 0xFFFFFFFF, 0,1},

		 //1stfloor
		{ 0, 160,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 0, 230, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 571, 230, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 0, 160,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 571,160, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 571,230, 0, 1.0f, 0xFFFFFFFF, 1,1},

		 //1stfloor
		{ 751, 160,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 751, 230, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 1024, 230, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 751, 160,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 1024,160, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 1024,230, 0, 1.0f, 0xFFFFFFFF, 1,1},

		 //slide1
		{ 490, 160,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 490, 430, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 730, 430, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 490, 160,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 730,160, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 730,430, 0, 1.0f, 0xFFFFFFFF, 1,1},
		
		//2nd floor
		{ 700, 430,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 700, 500, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 1024, 500, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 700, 430,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 1024,430, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 1024,500, 0, 1.0f, 0xFFFFFFFF, 1,1},
 
		{ 450, 430,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 450, 500, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 700, 500, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 450, 430,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 700,430, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 700,500, 0, 1.0f, 0xFFFFFFFF, 1,1},

		
		{ 0, 430,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 0, 500, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 300, 500, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 0, 430,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 300,430, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 300,500, 0, 1.0f, 0xFFFFFFFF, 1,1},

        //3rd floor
		{ 0, 700,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 0, 770, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 1024, 770, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 0, 700,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        {1024,700, 0, 1.0f,  0xFFFFFFFF, 1,0},
        {1024,770, 0, 1.0f, 0xFFFFFFFF, 1,1},

		 //slide2
		{ 280, 430,  0, 1.0f, 0xFFFFFFFF, 1,0}, // x, y, z, rhw, color,tex
        { 280, 700, 0, 1.0f, 0xFFFFFFFF, 1,1},
        { 520, 700, 0, 1.0f, 0xFFFFFFFF, 0,1},
 
        { 280, 430,  0, 1.0f, 0xFFFFFFFF, 1,0}, // x, y, z, rhw, color,tex
        { 520, 430, 0, 1.0f, 0xFFFFFFFF, 0,0},
        { 520, 700, 0, 1.0f, 0xFFFFFFFF, 0,1},


       
		//mundu1(rotated)
		{ 150+fwd+98, 200+updwn-116.45,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 150+fwd, 200+updwn, 0, 1.0f, 0xFFFFFFFF, 0,1},//to be kept same
        { 150+fwd+115, 200+updwn+97.7, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 150+fwd+98, 200+updwn-116.45,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 150+fwd+115+98, 200+updwn+116.45-97.7, 0, 1.0f,  0xFFFFFFFF, 1,0},//to be changed
        { 150+fwd+115, 200+updwn+97.7, 0, 1.0f, 0xFFFFFFFF, 1,1}, 
        

        	//mundu2( rotated)
			
       
	    { (200+fwd)-96.42, 50+updwn+115,  0, 1.0f,  0xFFFFFFFF, 1,0}, // x, y, z, rhw, color,tex
        {(200+fwd)+20.02, 50+updwn+212.6, 0, 1.0f, 0xFFFFFFFF, 1,1},
        {200+fwd+116.44, 50+updwn+97.7, 0, 1.0f, 0xFFFFFFFF, 0,1},

        { (200+fwd)-96.42, 50+updwn+115,  0, 1.0f,  0xFFFFFFFF, 1,0}, // x, y, z, rhw, color,tex
        { 200+fwd, 50+updwn, 0, 1.0f,  0xFFFFFFFF, 0,0},//to be kept same
        {200+fwd+116.44, 50+updwn+97.7, 0, 1.0f, 0xFFFFFFFF, 0,1},



		
		//lift
        { 853, 0+mov,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 853, 780+mov, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 1024, 780+mov, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 853, 0+mov,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 1024, 0+mov, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 1024, 780+mov, 0, 1.0f, 0xFFFFFFFF, 1,1},

		 //slide1
		{ -60, 480,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { -60, 760, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 300, 760, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { -60, 480,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 300,480, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 300,760, 0, 1.0f, 0xFFFFFFFF, 1,1},

        //snowball

		{ a1, a2,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { b1, b2, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { c1, c2, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { a1, a2,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { d1, d2, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { c1,  c2, 0, 1.0f, 0xFFFFFFFF, 1,1},


		//life1
        { 0, -30,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 0, 70, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 100,70, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 0, -30,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 100, -30, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 100, 70, 0, 1.0f, 0xFFFFFFFF, 1,1},

        //life2
		{ 100, -30,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 100, 70, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 200,70, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 100, -30,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 200, -30, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 200, 70, 0, 1.0f, 0xFFFFFFFF, 1,1},

        //life 3
		{ 200, -30,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 200, 70, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 300,70, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 200, -30,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 300, -30, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 300, 70, 0, 1.0f, 0xFFFFFFFF, 1,1},

        /*
		//life 4  
		{ 300, -30,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 300, 70, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 400,70, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 300, -30,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 400, -30, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 400, 70, 0, 1.0f, 0xFFFFFFFF, 1,1},



		//life 5
		{ 400, -30,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 400, 70, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { 500,70, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { 400, -30,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 500, -30, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 500, 70, 0, 1.0f, 0xFFFFFFFF, 1,1},


         
         //food
  		{ x1, x2,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { vai1, vai2, 0, 1.0f, 0xFFFFFFFF, 0,1},
        { z1, z2, 0, 1.0f, 0xFFFFFFFF, 1,1},

        { x1, x2,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { w1, w2, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { z1,  z2, 0, 1.0f, 0xFFFFFFFF, 1,1},
		*/

		//instruction screen
		 { 0, 0,  0, 1.0f,0xFFFFFFFF , 0,0}, // x, y, z, rhw, color,tex
        {  0,768, 0, 1.0f,0xFFFFFFFF , 0,1},
        { 1024,768, 0, 1.0f,0xFFFFFFFF , 1,1},

        { 0, 0,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 1024, 0, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 1024, 768, 0, 1.0f, 0xFFFFFFFF, 1,1},

		
			//score ones
		{ 983, 0,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 983, 41,  0, 1.0f, 0xFFFFFFFF, 0,1},
        { 1024,41,  0, 1.0f, 0xFFFFFFFF, 1,1},

        { 983, 0,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 1024,0, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 1024,41,  0, 1.0f, 0xFFFFFFFF, 1,1},

		//score tens
		{ 945, 0,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 945, 41,  0, 1.0f, 0xFFFFFFFF, 0,1},
        { 986,41,  0, 1.0f, 0xFFFFFFFF, 1,1},

        { 945, 0,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 986,0, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 986,41,  0, 1.0f, 0xFFFFFFFF, 1,1},

		//score hundreds
		{ 907, 0,  0, 1.0f, 0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 907, 41,  0, 1.0f, 0xFFFFFFFF, 0,1},
        { 948,41,  0, 1.0f, 0xFFFFFFFF, 1,1},

        { 907, 0,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 948,0, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 948,41,  0, 1.0f, 0xFFFFFFFF, 1,1},

		//End score screen
		 { 0, 0,  0, 1.0f,0xFFFFFFFF , 0,0}, // x, y, z, rhw, color,tex
        {  0,768, 0, 1.0f,0xFFFFFFFF , 0,1},
        { 1024,768, 0, 1.0f,0xFFFFFFFF , 1,1},

        { 0, 0,  0, 1.0f,  0xFFFFFFFF, 0,0}, // x, y, z, rhw, color,tex
        { 1024, 0, 0, 1.0f,  0xFFFFFFFF, 1,0},
        { 1024, 768, 0, 1.0f, 0xFFFFFFFF, 1,1},



	
        
	};


 
     

	

    // Now we fill the vertex buffer. To do this, we need to Lock() the VB to
    // gain access to the vertices. This mechanism is required becuase vertex
    // buffers may be in device (GPU) memory.
    VOID* pVertices;
	

	g_pVB->Lock( 0, sizeof(vertices), (void**)&pVertices, 0 );

    memcpy( pVertices, vertices, sizeof(vertices) );

    g_pVB->Unlock();





	g_floor->Lock( 0, sizeof(vertices), (void**)&pVertices, 0 );

    memcpy( pVertices, vertices, sizeof(vertices) );

    g_floor->Unlock();
	

	
   
    





	// Clear the backbuffer to a blue color
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(138,217,255), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        // Draw the triangles in the vertex buffer. This is broken into a few
        // steps. We are passing the vertices down a "stream", so first we need
        // to specify the source of that stream, which is our vertex buffer. Then
        // we need to let D3D know what vertex shader to use. Full, custom vertex
        // shaders are an advanced topic, but in most cases the vertex shader is
        // just the FVF, so that D3D knows what type of vertices we are dealing
        // with. Finally, we call DrawPrimitive() which does the actual rendering
        // of our geometry (in this case, not just one triangle).
        

          g_pd3dDevice->SetTexture(0, g_pslide);
	     g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 54,2);       
		 g_pd3dDevice->SetStreamSource( 0, g_floor, 0, sizeof(CUSTOMVERTEX) );
		   g_pd3dDevice->SetTexture(0, g_pslide);
		  g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 24,2); 
		 g_pd3dDevice->SetTexture(0, g_pfloor);
         g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 12,4 ); 
		 g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 30,8); 

		 g_pd3dDevice->SetTexture(0, g_plift);
         g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 72,2 ); 

		  g_pd3dDevice->SetTexture(0, g_pbigslide);
         g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 78,2 ); 

			

//lifes
           
		  if(totlife>=0)
		  {
 		  g_pd3dDevice->SetTexture(0, g_pTexture[0]);
          g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 90 ,totlife );
		  }
		    
		
        if(c1<1040&&ins=='n')
		 {
		 
		 snowballs();
		 }	 
        
         check_if_food_is_over();
		 food();
         checkcollision();
		 checkifdead();
		
		
 

          if(rand()%7==3&&(c1>=1040||c1<0))
		  { 
           randir=rand()%2;
		   rand3=rand()%3;
           c1=0,a1=0,b1=0,d1=0,roll=0;  
		  }
		
		

       	

		
		

        
		g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );
        g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
         	ofstream result;
	    result.open("score.txt",ios.app);
		if(dir=='x')
		{
        
		 g_pd3dDevice->SetTexture(0, g_pTexture[currtex]);
         g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST,0,2 );
		}
             
        if(dir=='r')

		   {   
			if(300+fwd>650&&300+fwd<900&&200+updwn<450&&200+updwn>160)
			{
             g_pd3dDevice->SetTexture(0, g_pTexture[currtex]);
             g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 60,2 );

			       fwd=fwd+inc;
				   updwn=updwn+inc;
				   inc=inc+4;
			

		  }
			else

			{
			inc=0;
            
			g_pd3dDevice->SetTexture(0, g_pTexture[currtex]);
            g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST,0,2 );
			}
	    }

			
		if(dir=='l')

		{

		

          if(300+fwd<540&&200+updwn>400&&200+updwn<730)
		 
		    { 
			 g_pd3dDevice->SetTexture(0, g_pTexture[currtex]);
             g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 66,2 );
             
			
	
	        
	        
			       fwd=fwd-inc2;
				   updwn=updwn+inc2;
				   inc2=inc2+4;


		    }
		  else
		  {
		  //
          inc2=0;
		  g_pd3dDevice->SetTexture(0, g_pTexture[currtex2]);
          g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 6,2 );
		  }
		}
           
		 //draw instructions
		
         if(ins!='n')
	     {
          g_pd3dDevice->SetTexture(0, g_iTexture);
          g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST,108,2 );
         } 


        
		myDelay();
        
        
        if(show_end==1)
		{
          g_pd3dDevice->SetTexture(0, g_final);
          g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST,108,2 );

		}	
		drawscore();
		// End the scene
        g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{


			 if(stop==1)
				  {
					  acc=0;
					  acc2=0;
				  }

			
			stop=1;
			 
    switch( msg )
    {
        case WM_DESTROY:
			
            Cleanup();
            PostQuitMessage( 0 );
            return 0;

            
			 
	
        
		case WM_KEYDOWN:
			 ins='n';
             stop=0;   
			if(wParam == VK_ESCAPE) {
            //highscores();
			
            
				Cleanup();
				PostQuitMessage( 0 );
				return 0;
			}
			 if(show_end==1)
			   {
				wParam=VK_LBUTTON;//SO VALUE OF wPARAM is changed and no input is taken
			   } 
			

			store=dir;
			
		
			if(wParam == VK_RIGHT)
			  {   
                  bearnumber++;
				  if(bearnumber>5) bearnumber=0;
				
				
                       //if((300+fwd>650&&48+updwn<230&&300+fwd<800)||(300+fwd<540&&200+updwn>400&&200+updwn<730)||(dir=='x'))   
                        if((300+fwd>650&&48+updwn<230&&300+fwd<800)||(300+fwd<540&&300+fwd>360&&200+updwn>400&&200+updwn<730)||(dir=='x')) 
				       {}

				 else {
					    fwd=fwd+acc;
						if(acc<14&&q%4==0)
						acc=acc+2;
						
				        dir='r';
						
				      }
				  currtex=bearnumber;
               

			  }  

			if(wParam == VK_LEFT)
               { 
                  bearnumber2++;
				  if(bearnumber2>5) bearnumber2=0;
			       // if((300+fwd>650&&48+updwn<230&&300+fwd<900)||(300+fwd<540&&200+updwn>400&&200+updwn<730)||(dir=='x'))   
				   if((300+fwd>650&&48+updwn<230&&300+fwd<900)||(300+fwd<540&&300+fwd>370&&200+updwn>400&&200+updwn<730)||(dir=='x'))   
				  {}

				   else {
                         
 					     fwd=fwd-acc2;
						if(acc2<14&&q%4==0)
						acc2=acc2+2;
				         dir='l';
						 
				        }

                 
				  currtex2=bearnumber2;
				

			  } 

			
            diffa=(780+mov)-(200+updwn);  
			diff=abso(diffa);
			
			if(wParam == VK_UP&&780+mov<=780)
			  {

                
                   
               if(300+fwd >1000 && diff <50)

			   {
                 updwn=updwn-10;

                 if((730+mov>-2000&&730+mov<160)||(730+mov>190&&730+mov<430)||(730+mov>450&&730+mov<700))
				     {dir='x';}

				  else {
					  dir='l';
					  
				        }
			   }

               liftmov='u';
			    mov=mov-10;             
			  }

			   
                 
				if(wParam == VK_DOWN&&780+mov<780)
			  {

				 if(  300+fwd >1000 && diff < 50)

			   {
                    updwn=updwn+10;

                  if((730+mov>-2000&&730+mov<160)||(730+mov>190&&730+mov<430)||(730+mov>450&&730+mov<700))
				     
				  { dir='x';}
				  else 
				  {
					  dir='l';
					  
					  
				  }

			  }
			  
               liftmov='d';
			   mov=mov+10;
			                
			   /*if(store=='x'&&dir!='x')
			   {
                fwd=300;
			   }
			  */
			   
			
				}


          


				
				
			





			return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{   

	
    // Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      L"D3D Tutorial", NULL };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"D3D Tutorial", L"D3D Tutorial 02: Vertices",
                              WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
                              NULL, NULL, wc.hInstance, NULL );
    



     // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        // Create the vertex buffer
        if( SUCCEEDED( InitVB() ) )
        {
            // Show the window
            ShowWindow( hWnd, SW_SHOWDEFAULT );
            UpdateWindow( hWnd );
            sethoney();
            // Enter the message loop
            MSG msg;
            ZeroMemory( &msg, sizeof(msg) );
            while( msg.message!=WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
					
                }
				
				else
				{   
					
 					Render();
				}
            }
        }
    }

    UnregisterClass( L"D3D Tutorial", wc.hInstance );
    return 0;
	
}
