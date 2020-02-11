#include "lib/leetlib.h"
#include <math.h>

int x[50];
int y[50];
int time=0;

struct bullet
{
	float BX,BY,BA;
	bullet() {BX=BY=BA=0;}
};

bullet bullets[10];

void Game()
{
	void *Text[]=
	{
		LoadSprite("gfx/slet.png"),
		LoadSprite("gfx/plet.png"),
		LoadSprite("gfx/alet.png"),
		LoadSprite("gfx/clet.png"),
		LoadSprite("gfx/elet.png"),
		0,
		LoadSprite("gfx/ilet.png"),
		LoadSprite("gfx/nlet.png"),
		LoadSprite("gfx/vlet.png"),
		LoadSprite("gfx/alet.png"),
		LoadSprite("gfx/dlet.png"),
		LoadSprite("gfx/elet.png"),
		LoadSprite("gfx/rlet.png"),
		LoadSprite("gfx/slet.png")
	};

	// SETUP
	int UX=400, UY=550;
	void *Enemy = LoadSprite("gfx/Little Invader.png");
	void *U = LoadSprite("gfx/Big Invader.png");
	void *bull = LoadSprite("gfx/bullet.png");
	for(int n=0;n<50;++n)
	{
		x[n]=(n%10)*60+120;
		y[n]=(n/10)*60+70;
	}
end:
	++time;
	if(WantQuit()) return;
	if(IsKeyDown(VK_ESCAPE)) return;
	for(int n=0;n<50;++n)
	{
		int xo=0,yo=0;
		int n1=time+n*n+n*n*n;
		int n2=time+n+n*n+n*n*n*3;
		if(((n1>>6)&0x7)==0x7)xo+=(1-cos((n1&0x7f)/64.0f*2.f*3.141592))*(20+((n*n)%9));
		if(((n1>>6)&0x7)==0x7)yo+=(sin((n1&0x7f)/64.0f*2.f*3.141592))*(20+((n*n)%9));
		if(((n2>>8)&0xf)==0xf)yo+=(1-cos((n2&0xff)/256.0f*2.f*3.141592))*(150+((n*n)%9));
		DrawSprite(Enemy, x[n]+xo, y[n]+yo, (10+((n)%17)), (10+((n)%17)), 0, 0xffffffff);
	}
	
	DrawSprite(U, UX+=IsKeyDown(VK_LEFT)?-7:IsKeyDown(VK_RIGHT)?7:0, UY, 50, 50, 3.141592+sin(time*0.1)*0.1, 0xffffffff);

	// FIRE
	static int b=0;
	static int count=0;
	if(count) --count;
	if(!IsKeyDown(VK_SPACE)) count=0;
	if(IsKeyDown(VK_SPACE) && count==0) {bullets[b].BX=UX; bullets[b].BY=UY; b=(b+1)%10; count=15;}

	for(int n=0;n<10;++n)
	{
		DrawSprite(bull, bullets[n].BX, bullets[n].BY-=4, 10, 10, bullets[n].BA+=0.1f, 0xffffffff);
	}

	for(int n=0;n<strlen("space invaders");++n) if(n!=5)DrawSprite(Text[n], n*40+150,30,20,20,sin(time*0.1)*n*0.01);

	Flip();
    
	goto end;
}

void OldGame()
{
	void *sprite = LoadSprite("sprite.png");
	float size=10;
	float angle=0;
	while (!WantQuit() && !IsKeyDown(VK_ESCAPE))
	{
		angle+=0.01f;
		float mx,my;
		GetMousePos(mx,my);
		DWORD col=0xffffffff; // white
		if (IsKeyDown(VK_LBUTTON)) col=0xffff0000; // solid red
		if (IsKeyDown(VK_RBUTTON)) col=0x8000ff00; // 50% transparent green
		if (IsKeyDown(VK_UP)) size++;
		if (IsKeyDown(VK_DOWN)) size--;
		
		DrawSprite(sprite,400,300,100,100, angle);
		DrawSprite(sprite, mx,my, size,size, 0, col);	
		Flip();
	}
}
