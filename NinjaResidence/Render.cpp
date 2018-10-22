#include "Main.h"
string NinjaTexture = "NINJA";
const int blockWidth = 40;
void CreateSquareVertex(CUSTOMVERTEX* Vertex, CENTRAL_STATE Central, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1) {
	Vertex[0] = { Central.x - Central.scaleX, Central.y - Central.scaleY, 1.f, 1.f, color, tu, tv };
	Vertex[1] = { Central.x + Central.scaleX, Central.y - Central.scaleY, 1.f, 1.f, color, tu + scaleTu, tv };
	Vertex[2] = { Central.x + Central.scaleX, Central.y + Central.scaleY, 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { Central.x - Central.scaleX, Central.y + Central.scaleY, 1.f, 1.f, color, tu, tv + scaleTv };
}
//文字設定
void SetUpFont(int WordHeight, int WordWidth, string FontKey, LPCSTR FontName, int CharSet) {
	g_pFont[FontKey] = NULL;
	D3DXCreateFontA(
		g_pD3Device,
		WordHeight,
		WordWidth,
		FW_DEMIBOLD,
		NULL,
		FALSE,
		CharSet,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		FIXED_PITCH | FF_SCRIPT,
		FontName,
		&g_pFont[FontKey]);
}
//描画設定
void WriteWord(LPCSTR Texts, RECT Vertex, string FontKey,int TextFormat = DT_LEFT, int color = 0xff000000) {
	g_pFont[FontKey]->DrawTextA(
		NULL,
		Texts,					// 描画テキスト
		-1,								// 全て表示
		&Vertex,							// 表示範囲
		TextFormat,
		color
	);
}

void LoadTexture() {
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"woodWall.jpg",
		&g_pTexture["WoodWall"]);
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"stoneWall.jpg",
		&g_pTexture["StoneWall"]);
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"rock.png",
		&g_pTexture["Rock"]);
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"チップ＿袋＿カラー.bmp",
		&g_pTexture["Test"]);
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"ninja_hashiru.png",
		&g_pTexture["NINJA"]);
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"water_00089.png",
		&g_pTexture["Water"]);
	D3DXCreateTextureFromFile(
		g_pD3Device,
		"ninja_mizugumo.png",
		&g_pTexture["MIZUGUMO"]);

}

void DrowTexture(CUSTOMVERTEX* Vertex, string TexKey) {
	g_pD3Device->SetTexture(0, g_pTexture[TexKey]);
	g_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, Vertex, sizeof(CUSTOMVERTEX));
}
void EasyCreateSquareVertex(float Left, float Top, float Right, float Bottom, string TexKey, DWORD  color = 0xffffffff, float tu = 0, float tv = 0, float scaleTu = 1, float scaleTv = 1){
	CUSTOMVERTEX Vertex[4];


	Vertex[0] = { Left,  Top, 1.f, 1.f, color, tu, tv };
	Vertex[1] = { Right, Top, 1.f, 1.f, color, tu + scaleTu, tv };
	Vertex[2] = { Right, Bottom, 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { Left,  Bottom, 1.f, 1.f, color, tu, tv + scaleTv };

	DrowTexture(Vertex, TexKey);
}
void Render(HWND* hWnd, D3DPRESENT_PARAMETERS* g_D3dPresentParameters, HINSTANCE hInstance) {
	static float Rad = 0;
	if (DONDENGAESHI) {
		Rad -= (D3DX_PI / 120);
	}
	if ((Rad/D3DX_PI * -180) > 180) {
		DONDENGAESHI = false;
		Rad = 0;
	}
	CUSTOMVERTEX Ninja[4];
		RECT rect = { 20,20,1000,600 };
		CreateSquareVertex(Ninja, ninja, 0xffffffff, 0 + isRight, 0, isRight, 1);
	if (!isBackStage) {
		CUSTOMVERTEX Water[4];
		CreateSquareVertex(Water, water);
		CUSTOMVERTEX StoneWall[4];
		CreateSquareVertex(StoneWall, stoneWall, 0xffffffff, 0, 0, 1, 4);

		//画面の消去
		if (WinMode) {
			g_pD3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);
		}
		else g_pD3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x80, 0x80, 0x80), 1.0, 0);
		//描画の開始
		g_pD3Device->BeginScene();

		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 20; j++) {
				CENTRAL_STATE backgraund = { i*blockWidth, j*blockWidth, blockWidth/2, blockWidth/2 };

				CUSTOMVERTEX backGround[4];
				CreateSquareVertex(backGround, backgraund);
				if (DONDENGAESHI) {
					if ((i + j)==0) {
						RevolveY(backGround, Rad, backgraund);
					}
					if (((i + j) % 2)==0) {
						RevolveY(backGround, -Rad*2, backgraund);
					}
					else {
						RevolveY(backGround, Rad, backgraund);
					}
				}
				if ((i <= 5 || i > 13) && (j >= 12)) {
					DrowTexture(backGround, "StoneWall");
				}
				else DrowTexture(backGround, "WoodWall");
			}
		}
		if (DONDENGAESHI) {
			RevolveY(StoneWall, Rad*3, stoneWall, 0, 0, 1, 4);
			RevolveY(Water, Rad, water);
		}
		DrowTexture(StoneWall, "StoneWall");
		DrowTexture(Water, "Water");
		//EasyCreateSquareVertex(0, 0, WIDTH, HEIGHT, "Test", 0xffffffff, 0, 0, 16, 9);
	}
		DrowTexture(Ninja, NinjaTexture);
		char test[20];
		sprintf_s(test, 20, "%.2f", ninja.x);
		WriteWord(test, rect, "DEBUG_FONT");
		sprintf_s(test, 20, "\n%.2f", ninja.y);
		WriteWord(test, rect, "DEBUG_FONT");
	
	//描画の終了
	g_pD3Device->EndScene();
	//表示
	g_pD3Device->Present(NULL, NULL, NULL, NULL);

}