#include "Main.h"
#define PlMove 4
bool isSurface = true;
BYTE KeyOldState[256];
BYTE KeyState[256];
int isRight = -1;
CENTRAL_STATE ninja={20, 300, 50, 100};
CENTRAL_STATE water = {  WIDTH/2.f,730, WIDTH / 2.f, 137 };
CENTRAL_STATE stoneWall = { 1000,300, 40, 300 };
CENTRAL_STATE shuriken = { 0,0,40,40 };
CENTRAL_STATE rope[2]{
	{ 1100,30,50,20 },
	{1100,30,50,20 }
};
CENTRAL_STATE rock = {1100,80,40,40};
CENTRAL_STATE dokan = { 1200,650,60,80 };
CENTRAL_STATE dokancover = { 1120,650,20,80 };
CENTRAL_STATE button = { 1100,430,40,30 };
void Gravity();
bool BrokenCover = false;
bool isClear = false;
bool DONDENGAESHI = false;
bool isThrow = false;
bool isShurikenUpper = false;
bool isShurikenDowner = false;
void BuckGroundControl();
void SurfaceControl();
void NinjaControl(int* isRight);
bool waterUp = false;
bool isWallUp = false;
bool canCall[4] = { true,true,true,true };
bool fallenRock = false;
bool BtoBContact(CENTRAL_STATE* central1, CENTRAL_STATE* central2) {
	if ((central1->x- central1->scaleX <= central2->x + central2->scaleX) && (central2->x -central2->scaleX<= central1->x + central1->scaleX)
		&& (central1->y- central1->scaleY <= central2->y + central2->scaleY) && (central2->y-central2->scaleY <= central1->y + central1->scaleY)) {
		return true;
	}
	else return false;
}

void Control(int* isRight) {
	AcquireKeyBoardState();
	Gravity();
	if (KeyRelease == GetSpecificKeyState(DIK_O)) {
		DONDENGAESHI = true;
		soundsManager.Start("DONDENGAESHI", false);
	}

	NinjaControl(isRight);
	if (isSurface) {
		SurfaceControl();
	}
	else {
		BuckGroundControl();
	}
}
void NinjaControl(int* isRight) {
	static bool isJump = false;
	static int JumpCount = 0;
	static float prevNinjaY;
	//‰ŠúˆÊ’u‚É–ß‚·
	if (KeyRelease == GetSpecificKeyState(DIK_TAB)) {
		ninja = { 20, 300, 50, 100 };
		water = { WIDTH / 2.f,730, WIDTH / 2.f, 120 };
		stoneWall = { 1000,300, 40, 300 };
		dokancover = { 1120,650,20,80 };
		rope[0] = { 1100,30,50,20 };
		rock.y = 80;
		waterUp = false;
		isWallUp = false;
		isClear = false;
		BrokenCover = false;
		memset(canCall,4,true);
		
		fallenRock = false;
	}
	if (KeyOn == GetSpecificKeyState(DIK_S)) {
		ninja.y += 2;
	}
	if (KeyOn == GetSpecificKeyState(DIK_A)) {
		ninja.x -= PlMove;
		*isRight = 1;
	}
	if (KeyOn == GetSpecificKeyState(DIK_D)) {
		ninja.x += PlMove;
		*isRight = -1;
	}
	//Žè— Œ•‚Ü‚Á‚·‚®“Š‚°‚é
	if (KeyRelease == GetSpecificKeyState(DIK_E)) {
		if (!isThrow) {
			soundsManager.Start("THROW", false);
			shuriken.x = ninja.x;
			shuriken.y = ninja.y;
		}
		isThrow = true;
		isShurikenUpper = false;
		isShurikenDowner = false;
	}
	//Žè— Œ•ãŽÎ‚ß‚É“Š‚°‚é
	if (KeyRelease == GetSpecificKeyState(DIK_R)) {
		if (!isThrow) {
			soundsManager.Start("THROW", false);
			shuriken.x = ninja.x;
			shuriken.y = ninja.y;
		}
		isThrow = true;
		isShurikenUpper = true;
	}
	//Žè— Œ•‰ºŽÎ‚ß‚É“Š‚°‚é
	if (KeyRelease == GetSpecificKeyState(DIK_T)) {
		if (!isThrow) {
			soundsManager.Start("THROW", false);
			shuriken.x = ninja.x;
			shuriken.y = ninja.y;
		}
		isThrow = true;
		isShurikenDowner = true;
	}

	if (KeyRelease == GetSpecificKeyState(DIK_W)) {
		if (ninja.y > 373) {
			isJump = true;
			if (!JumpCount) {
				prevNinjaY = ninja.y;
			}
			JumpCount++;
		}
	}

	if (isJump) {

		ninja.y -= 10;
		if (prevNinjaY - ninja.y>150) {
			isJump = false;
			JumpCount = 0;
		}
	}
	if (isThrow) {
		
		if (isShurikenUpper) {
			shuriken.x += ((PlMove * 3)*0.5f*sqrt(2));
			shuriken.y -= ((PlMove * 2)*0.5f*sqrt(2));
		}
		else if (isShurikenDowner) {
			shuriken.x += ((PlMove * 3)*0.5f*sqrt(2));
			shuriken.y += ((PlMove * 2)*0.5f*sqrt(2));
		}
		else {
			shuriken.x += PlMove * 2;
		}
	}
	if (shuriken.x > WIDTH || shuriken.y < 0) {
		isThrow = false;
		isShurikenUpper = false;
		isShurikenDowner = false;
	}

}
void SurfaceControl(){

	if (KeyOn == GetSpecificKeyState(DIK_P)) {
		isWallUp = true;
	}

	if (KeyRelease == GetSpecificKeyState(DIK_Z)) {
		waterUp = true;
	}
	if ((waterUp) && (water.y>600)) {
		water.y -= 3;
	}
	if (isWallUp) {
		stoneWall.y -= 3;
	}
	if (BtoBContact(&ninja, &stoneWall)) {
		ninja.x = stoneWall.x - stoneWall.scaleX - ninja.scaleX;
	}
	if (BtoBContact(&ninja, &water) && (ninja.x < 240.f || ninja.x > 700.f)) {
		NinjaTexture = "NINJA";
	}
	else if (BtoBContact(&ninja, &water)) {
		NinjaTexture = "MIZUGUMO";
		ninja.y = water.y - water.scaleY - ninja.scaleY;
	}
	else {
		NinjaTexture = "NINJA";
	}
	if (ninja.x>WIDTH) {
		isClear = true;
		if (canCall[2]) {
			soundsManager.Start("CLEAR", false);
			canCall[2] = false;
		}
	}
}
void BuckGroundControl() {
	
	if (KeyOn == GetSpecificKeyState(DIK_P)) {
		isWallUp = true;
	}
	if (BtoBContact(&shuriken,&rope[0])) {
		if (canCall[3]) {
			soundsManager.Start("SLASH", false);
			canCall[3] = false;
		}
		fallenRock = true;
	}
	if (rock.y < 420.f&&fallenRock) {
		rope[0].y += 3;
		rock.y += 3;
	}
	else {
		fallenRock = false;
	}
	if (rock.y == 422) {
		isWallUp = true;
		if (rope[0].y<430) {
			rope[0].y += 1;
			rope[0].scaleX -= 0.5;
		}
		if (canCall[0]) {
			soundsManager.Start("DECISION", false);
			canCall[0] = false;
		}
	}
	if (BtoBContact(&shuriken, &dokancover)) {
		waterUp = true;
		isThrow = false;
		shuriken.x = -10;
		BrokenCover = true;
		if (canCall[1]) {
			soundsManager.Start("SLASH", false);
			soundsManager.Start("DECISION2", false);
			canCall[1] = false;
		}
	}
	if (ninja.x > 1190) {
		ninja.x = 1190;
	}
	if (BrokenCover) {
		static float jar = 3;
		dokancover.y += 2;
		jar = jar * -1;
		dokancover.x += jar;
	}
}
void AcquireKeyBoardState() {
	HRESULT hr = g_pKeyDevice->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE)) {
		g_pKeyDevice->GetDeviceState(sizeof(KeyState), &KeyState);
		for (int i = 0; i < 256; i++) {
			if (KeyState[i] & 0x80)
			{
				if (KeyOldState[i] == KeyOn)
				{
					KeyOldState[i] = KeyOn;
					KeyState[i] = KeyOn;
				}
				else
				{
					KeyOldState[i] = KeyOn;
					KeyState[i] = KeyPush;
				}
			}
			else
			{
				if (KeyOldState[i] == KeyOn)
				{
					KeyOldState[i] = KeyOff;
					KeyState[i] = KeyRelease;
				}
				else
				{
					KeyOldState[i] = KeyOff;
					KeyState[i] = KeyOff;
				}
			}
		}
	}
}

int GetSpecificKeyState(int KeyName) {
	return KeyState[KeyName];
}

void Gravity() {
	if (ninja.x < 240.f || ninja.x > 700.f) {
		if (ninja.y > 373.f) {
			ninja.y -= 2.f;

			if (ninja.x < 240.f&&ninja.y > 374.f) {
				ninja.x = 250.f;
			}
			if (ninja.x > 700.f&&ninja.y > 374.f) {
				ninja.x = 690;
			}
		}
	}
	if (ninja.y < HEIGHT - ninja.scaleY) {
		ninja.y += 2.f;
	}
}

void RevolveY(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, DWORD  color, float tu, float tv, float scaleTu, float scaleTv) {

	float CharVertexX[4];

	CharVertexX[0] = Central.x - Central.scaleX;
	CharVertexX[1] = Central.x + Central.scaleX;
	CharVertexX[2] = Central.x + Central.scaleX;
	CharVertexX[3] = Central.x - Central.scaleX;


	for (int RoteCnt = 0; RoteCnt < 4; RoteCnt++) {

		CharVertexX[RoteCnt] -= Central.x;
		Vertex[RoteCnt].z -= 1;

		float KEEPER = CharVertexX[RoteCnt];

		CharVertexX[RoteCnt] = (CharVertexX[RoteCnt] * cos(-Rad)) - (Vertex[RoteCnt].z * sin(-Rad));
		Vertex[RoteCnt].z = (Vertex[RoteCnt].z * cos(-Rad)) + (KEEPER * sin(-Rad));

		CharVertexX[RoteCnt] += Central.x;
		Vertex[RoteCnt].z += 1;

	}

	Vertex[0] = { CharVertexX[0], Central.y - Central.scaleY, Vertex[0].z, 1.f, color, tu, tv };
	Vertex[1] = { CharVertexX[1], Central.y - Central.scaleY, Vertex[1].z, 1.f, color, tu + scaleTu, tv };
	Vertex[2] = { CharVertexX[2], Central.y + Central.scaleY, Vertex[2].z, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { CharVertexX[3], Central.y + Central.scaleY, Vertex[3].z, 1.f, color, tu, tv + scaleTv };

}
void RevolveZ(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, DWORD  color, float tu, float tv, float scaleTu, float scaleTv) {

	float CharVertexX[4];
	float CharVertexY[4];

	CharVertexX[0] = Central.x - Central.scaleX;
	CharVertexX[1] = Central.x + Central.scaleX;
	CharVertexX[2] = Central.x + Central.scaleX;
	CharVertexX[3] = Central.x - Central.scaleX;

	CharVertexY[0] = Central.y - Central.scaleY;
	CharVertexY[1] = Central.y - Central.scaleY;
	CharVertexY[2] = Central.y + Central.scaleY;
	CharVertexY[3] = Central.y + Central.scaleY;

	for (int RoteCnt = 0; RoteCnt < 4; RoteCnt++) {

		CharVertexX[RoteCnt] -= Central.x;
		CharVertexY[RoteCnt] -= Central.y;

		float KEEPER = CharVertexX[RoteCnt];

		CharVertexX[RoteCnt] = (CharVertexX[RoteCnt] * cos(-Rad)) - (CharVertexY[RoteCnt] * sin(-Rad));
		CharVertexY[RoteCnt] = (CharVertexY[RoteCnt] * cos(-Rad)) + (KEEPER * sin(-Rad));

		CharVertexX[RoteCnt] += Central.x;
		CharVertexY[RoteCnt] += Central.y;

	}

	Vertex[0] = { CharVertexX[0], CharVertexY[0], 1.f, 1.f, color, tu, tv };
	Vertex[1] = { CharVertexX[1], CharVertexY[1], 1.f, 1.f, color, tu + scaleTu, tv };
	Vertex[2] = { CharVertexX[2], CharVertexY[2], 1.f, 1.f, color, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { CharVertexX[3], CharVertexY[3], 1.f, 1.f, color, tu, tv + scaleTv };

}
//ZŽ²@‰ñ“]Ž²Žw’è
void RevolveZEX(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float RevolvingShaftX, float RevolvingShaftY, float tu, float tv, float scaleTu, float scaleTv) {

	float CharVertexX[4];
	float CharVertexY[4];

	CharVertexX[0] = Central.x - Central.scaleX;
	CharVertexX[1] = Central.x + Central.scaleX;
	CharVertexX[2] = Central.x + Central.scaleX;
	CharVertexX[3] = Central.x - Central.scaleX;

	CharVertexY[0] = Central.y - Central.scaleY;
	CharVertexY[1] = Central.y - Central.scaleY;
	CharVertexY[2] = Central.y + Central.scaleY;
	CharVertexY[3] = Central.y + Central.scaleY;

	for (int RoteCnt = 0; RoteCnt < 4; RoteCnt++) {

		CharVertexX[RoteCnt] -= RevolvingShaftX;
		CharVertexY[RoteCnt] -= RevolvingShaftY;

		float KEEPER = CharVertexX[RoteCnt];

		CharVertexX[RoteCnt] = (CharVertexX[RoteCnt] * cos(-Rad)) - (CharVertexY[RoteCnt] * sin(-Rad));
		CharVertexY[RoteCnt] = (CharVertexY[RoteCnt] * cos(-Rad)) + (KEEPER * sin(-Rad));

		CharVertexX[RoteCnt] += RevolvingShaftX;
		CharVertexY[RoteCnt] += RevolvingShaftY;

	}

	Vertex[0] = { CharVertexX[0], CharVertexY[0], 1.f, 1.f, 0xffffffff, tu, tv };
	Vertex[1] = { CharVertexX[1], CharVertexY[1], 1.f, 1.f, 0xffffffff, tu + scaleTu, tv };
	Vertex[2] = { CharVertexX[2], CharVertexY[2], 1.f, 1.f, 0xffffffff, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { CharVertexX[3], CharVertexY[3], 1.f, 1.f, 0xffffffff, tu, tv + scaleTv };

}
