#pragma once
/**
* @file XinputDevice.h
* @brief XinputDevice�֘A�������s��
* @author Toshiya Matsuoka
*/
#include<Xinput.h>


/**
* @enum PADSTATE
* �{�^���̉������
*/
enum PADSTATE
{
	//! ������Ă��Ȃ�
	PadOff,
	//! ������Ă���
	PadOn,
	//! ���������Ă���
	PadPush,
	//! �����ꂽ
	PadRelease
};
/**
* @enum ButtonIndex
* �p�b�h�̃{�^���̗�
*/
enum ButtonIndex
{
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY,
	//! R1�{�^��
	ButtonRB,
	//! L1�{�^��
	ButtonLB,
	ButtonStart,
	ButtonBack,
	ButtonUP,
	ButtonDOWN,
	ButtonLEFT,
	ButtonRIGHT,
	//!L3�{�^��
	ButtonLeftThumb,
	//!R3�{�^��
	ButtonRightThumb,
	ButtomIndexMAX
};

/**
* @enum Analog
* �A�i���O�X�e�B�b�N�̌X������
*/
enum Analog
{
	ANALOGUP,
	ANALOGDOWN,
	ANALOGLEFT,
	ANALOGRIGHT,
	//!������
	ANALOG_X,
	//!�c����
	ANALOG_Y,
	ANALOGMAX
};
/**
* @enum AnalogTrigger
* ���E�̃g���K�[����
*/
enum AnalogTrigger
{
	LEFT_TRIGGER,
	RIGHT_TRIGGER
};

class XinputDevice {
	
public:

	/**
	* @brief XinputDevice�ŃQ�[���p�b�h�f�o�C�X�̎擾
	* @param GamePadNumber �p�b�h�ԍ��i0�x�[�X�j
	*/
	void GetControl(int GamePadNumber = 0);

	/**
	* @brief XinputDevice�ŃQ�[���p�b�h�̓��͎擾
	* @param index �擾�������{�^���̔z��ԍ�
	* @return PADSTATE�̒l
	* @sa enum PADSTATE
	*/
	PADSTATE GetButton(ButtonIndex index);

	/**
	* @brief �S�Ẵ{�^���ɑ΂���CheckButtonState���s��
	* @sa CheckButtonState(WORD ButtomID, int ButtomIndex)
	*/
	void BottonCheck();

	/**
	* @brief GetControl��BottonCheck��Z�߂čs��
	* @param GamePadNumber �p�b�h�ԍ��i0�x�[�X�j
	* @sa GetControl
	* @sa BottonCheck
	*/

	void DeviceUpdate(int GamePadNumber = 0);
	/**
	* @brief XinputDevice�ŃQ�[���p�b�h�̍��A�i���O�X�e�B�b�N���͎擾
	* @param Trigger �g���K�[�̍��E�F���ԍ�
	* @return 0�`255�̒l�A�����ĂȂ����0
	* @sa enum AnalogTrigger
	*/
	int GetAnalogTrigger(AnalogTrigger Trigger);

	/**
	* @brief XinputDevice�ŃQ�[���p�b�h�̍��A�i���O�X�e�B�b�N���͎擾
	* @param AnalogState �X�e�B�b�N�̕�������ԍ�
	* @return �X���Ă����True�A�����łȂ����False
	* @sa enum Analog
	*/
	bool GetAnalogL(Analog AnalogState);

	/**
	* @brief  XinputDevice�ŃQ�[���p�b�h�̉E�A�i���O�X�e�B�b�N���͎擾
	* @param AnalogState �X�e�B�b�N�̕�������ԍ�
	* @return �X���Ă����True�A�����łȂ����False
	* @sa enum Analog
	*/
	bool GetAnalogR(Analog AnalogState);

	/**
	* @brief  XinputDevice�ŃQ�[���p�b�h�̍��A�i���O�X�e�B�b�N���͎擾
	* @param AnalogState �X�e�B�b�N�̕�������ԍ�
	* @return �X����̐��l�@MAX��32767�@MIN��-32768
	* @sa enum Analog
	*/
	int GetAnalogLValue(Analog AnalogState);

	/**
	* @brief  XinputDevice�ŃQ�[���p�b�h�̉E�A�i���O�X�e�B�b�N���͎擾
	* @param AnalogState �X�e�B�b�N�̕�������ԍ�
	* @return �X����̐��l�@MAX��32767�@MIN��-32768
	* @sa enum Analog
	*/
	int GetAnalogRValue(Analog AnalogState);

	/**
	* @brief Dinput�ŃL�[�{�[�h�̏�Ԏ擾
	* @param ButtomID �擾������XInput�{�^���ԍ�
	* @param ButtomIndex �擾�������{�^���̔z��ԍ�
	* @sa enum ButtonIndex
	* @details �g�p���ɂ́@PadState[ButtomID]�@�̒��g���m�F���邱��
	*/
	void CheckButtonState(WORD ButtomID, ButtonIndex ButtomIndex);

	XinputDevice() {};
	~XinputDevice() {};
private:
	XINPUT_STATE m_Xinput;
	PADSTATE PadState[ButtomIndexMAX] = { PadOff };
	PADSTATE PadOldState[ButtomIndexMAX] = { PadOff };

};
