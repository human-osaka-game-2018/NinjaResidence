#pragma once
/**
* @file XinputDevice.h
* @brief XinputDevice関連処理を行う
* @author Toshiya Matsuoka
*/
#include<Xinput.h>


/**
* @enum PADSTATE
* ボタンの押下状態
*/
enum PADSTATE
{
	//! 押されていない
	PadOff,
	//! 押されている
	PadOn,
	//! 押し続けている
	PadPush,
	//! 離された
	PadRelease
};
/**
* @enum ButtonIndex
* パッドのボタンの列挙
*/
enum ButtonIndex
{
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY,
	//! R1ボタン
	ButtonRB,
	//! L1ボタン
	ButtonLB,
	ButtonStart,
	ButtonBack,
	ButtonUP,
	ButtonDOWN,
	ButtonLEFT,
	ButtonRIGHT,
	//!L3ボタン
	ButtonLeftThumb,
	//!R3ボタン
	ButtonRightThumb,
	ButtomIndexMAX
};

/**
* @enum Analog
* アナログスティックの傾き方向
*/
enum Analog
{
	ANALOGUP,
	ANALOGDOWN,
	ANALOGLEFT,
	ANALOGRIGHT,
	//!横方向
	ANALOG_X,
	//!縦方向
	ANALOG_Y,
	ANALOGMAX
};
/**
* @enum AnalogTrigger
* 左右のトリガー識別
*/
enum AnalogTrigger
{
	LEFT_TRIGGER,
	RIGHT_TRIGGER
};

class XinputDevice {
	
public:

	/**
	* @brief XinputDeviceでゲームパッドデバイスの取得
	* @param GamePadNumber パッド番号（0ベース）
	*/
	void GetControl(int GamePadNumber = 0);

	/**
	* @brief XinputDeviceでゲームパッドの入力取得
	* @param index 取得したいボタンの配列番号
	* @return PADSTATEの値
	* @sa enum PADSTATE
	*/
	PADSTATE GetButton(ButtonIndex index);

	/**
	* @brief 全てのボタンに対してCheckButtonStateを行う
	* @sa CheckButtonState(WORD ButtomID, int ButtomIndex)
	*/
	void BottonCheck();

	/**
	* @brief GetControlとBottonCheckを纏めて行う
	* @param GamePadNumber パッド番号（0ベース）
	* @sa GetControl
	* @sa BottonCheck
	*/

	void DeviceUpdate(int GamePadNumber = 0);
	/**
	* @brief XinputDeviceでゲームパッドの左アナログスティック入力取得
	* @param Trigger トリガーの左右認識番号
	* @return 0〜255の値、押してなければ0
	* @sa enum AnalogTrigger
	*/
	int GetAnalogTrigger(AnalogTrigger Trigger);

	/**
	* @brief XinputDeviceでゲームパッドの左アナログスティック入力取得
	* @param AnalogState スティックの方向け先番号
	* @return 傾いていればTrue、そうでなければFalse
	* @sa enum Analog
	*/
	bool GetAnalogL(Analog AnalogState);

	/**
	* @brief  XinputDeviceでゲームパッドの右アナログスティック入力取得
	* @param AnalogState スティックの方向け先番号
	* @return 傾いていればTrue、そうでなければFalse
	* @sa enum Analog
	*/
	bool GetAnalogR(Analog AnalogState);

	/**
	* @brief  XinputDeviceでゲームパッドの左アナログスティック入力取得
	* @param AnalogState スティックの方向け先番号
	* @return 傾き具合の数値　MAX＝32767　MIN＝-32768
	* @sa enum Analog
	*/
	int GetAnalogLValue(Analog AnalogState);

	/**
	* @brief  XinputDeviceでゲームパッドの右アナログスティック入力取得
	* @param AnalogState スティックの方向け先番号
	* @return 傾き具合の数値　MAX＝32767　MIN＝-32768
	* @sa enum Analog
	*/
	int GetAnalogRValue(Analog AnalogState);

	/**
	* @brief Dinputでキーボードの状態取得
	* @param ButtomID 取得したいXInputボタン番号
	* @param ButtomIndex 取得したいボタンの配列番号
	* @sa enum ButtonIndex
	* @details 使用時には　PadState[ButtomID]　の中身を確認すること
	*/
	void CheckButtonState(WORD ButtomID, ButtonIndex ButtomIndex);

	XinputDevice() {};
	~XinputDevice() {};
private:
	XINPUT_STATE m_Xinput = { NULL };
	PADSTATE PadState[ButtomIndexMAX] = { PadOff };
	PADSTATE PadOldState[ButtomIndexMAX] = { PadOff };

};
