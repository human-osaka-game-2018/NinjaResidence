#include "Main.h"

BYTE KeyOldState[256];
BYTE KeyState[256];
int isRight = -1;
CENTRAL_STATE ninja={20, 300, 50, 100};
CENTRAL_STATE water = {  WIDTH/2.f,730, WIDTH / 2.f, 120 };
CENTRAL_STATE stoneWall = { 1000,300, 40, 300 };
bool isBackStage = false;
void Gravity();
bool DONDENGAESHI = false;
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
	static bool waterUp = false;
	static bool isJump = false;
	static bool isWallUp = false;
	static float prevNinjaY;
	static int JumpCount = 0;
	if (KeyRelease == GetSpecificKeyState(DIK_TAB)) {
		ninja = { 20, 300, 50, 100 };
	}
	if (KeyOn == GetSpecificKeyState(DIK_W)) {
		isWallUp = true;
	}
	if (KeyOn == GetSpecificKeyState(DIK_S)) {
		ninja.y += 10;
	}
	if (KeyOn == GetSpecificKeyState(DIK_A)) {
		ninja.x -= 2;
		*isRight = 1;
	}
	if (KeyOn == GetSpecificKeyState(DIK_D)) {
		ninja.x += 2;
		*isRight = -1;
	}
	if (KeyRelease == GetSpecificKeyState(DIK_SPACE)) {
		if (ninja.y > 373) {
			isJump = true;
			if (!JumpCount) {
				prevNinjaY = ninja.y;
			}
			JumpCount++;
		}
	}
	if (KeyRelease == GetSpecificKeyState(DIK_Z)) {
		waterUp = true;
	}
	if (isJump) {
		
		ninja.y -= 10;
		if (prevNinjaY- ninja.y>150) {
			isJump = false;
			JumpCount = 0;
		}
	}
	if ((waterUp) && (water.y>600)) {
		water.y -= 3;
	}
	if (isWallUp) {
		stoneWall.y -= 3;
	}
	if (BtoBContact(&ninja, &stoneWall)) {
		ninja.x = stoneWall.x - stoneWall.scaleX - 20;
	}
	if (BtoBContact(&ninja, &water)){
		NinjaTexture = "MIZUGUMO";
		ninja.y = water.y - water.scaleY - (ninja.scaleY / 3);
	}
	else {
		NinjaTexture = "NINJA";
	}
	if (KeyRelease == GetSpecificKeyState(DIK_O)) {
		DONDENGAESHI = true;
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
	if (ninja.x < 240.f || ninja.x > 540.f) {
		if (ninja.y > 373.f) {
			ninja.y -= 2.f;

			if (ninja.x < 240.f&&ninja.y > 374.f) {
				ninja.x = 240.f;
			}
			if (ninja.x > 540.f&&ninja.y > 374.f) {
				ninja.x = 540.f;
			}
		}
	}
	if (ninja.y < HEIGHT - ninja.scaleY) {
		ninja.y += 2;
	}
}

void RevolveY(CUSTOMVERTEX* Vertex, float Rad, CENTRAL_STATE Central, float tu, float tv, float scaleTu, float scaleTv) {

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

	Vertex[0] = { CharVertexX[0], Central.y - Central.scaleY, Vertex[0].z, 1.f, 0xffffffff, tu, tv };
	Vertex[1] = { CharVertexX[1], Central.y - Central.scaleY, Vertex[1].z, 1.f, 0xffffffff, tu + scaleTu, tv };
	Vertex[2] = { CharVertexX[2], Central.y + Central.scaleY, Vertex[2].z, 1.f, 0xffffffff, tu + scaleTu, tv + scaleTv };
	Vertex[3] = { CharVertexX[3], Central.y + Central.scaleY, Vertex[3].z, 1.f, 0xffffffff, tu, tv + scaleTv };

}
