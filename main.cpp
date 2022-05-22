#include "DxLib.h"
#include "Vector2.h"
#include "Vector3.h"

//�֐��v���g�^�C�v�錾
//int DrawCircle(Vector2 vec, int r, unsigned int color);
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);
int DrawLine3D(const Vector3& pos1, const Vector3& pos2, const unsigned int Coloer);

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LE2B_21_�t�W�^�P���^���E:�^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 1024;

// �E�B���h�E�c��
const int WIN_HEIGHT = 576;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x64);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���

	//	�N���b�v��	��		��
	SetCameraNearFar(1.0f, 1000.0f);// �J�����̗L���͈͂�ݒ�
	SetCameraScreenCenter(			// ��ʂ̒��S���J�����̒��S�ɍ��킹��
		WIN_WIDTH / 2.0f,
		WIN_HEIGHT / 2.0f);
	SetCameraPositionAndTargetAndUpVec(
		VGet(0.0f, 0.0f, -100.0f), // �J�����ʒu
		VGet(0.0f, 0.0f,    0.0f), // �J���������_
		VGet(0.0f, 1.0f,    0.0f));// �J�����̏�̌���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	Vector3 position(0, 0, 100);					//�ʒu
	Vector3 velocity(0.0f, 0.0f, 0.5f);			//���x

	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}


		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		position += velocity;



		// �`�揈��
		// ��ʃN���A
		ClearDrawScreen();
		DrawSphere3D(position, 80.0f, 32,GetColor(255, 0, 0),GetColor(255,255,255),TRUE);


		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}

//�I�[�o�[���[�h�֐�
//�\���ʒu�Ɂ@�x�N�g���iVector2�j�@���w��ł���悤�ɂ���
//int DrawCircle(Vector2 vec, int r, unsigned int color) {
//	return DrawCircle(static_cast<int>(vec.x), static_cast<int>(vec.y), r, color);
//}

//�\���ʒu�Ɂ@�x�N�g���iVector3�j�@���w��ł���悤�ɂ���
int DrawSphere3D(
	const Vector3& CenterPos,
	const float r,
	const int DivNum,
	const unsigned int DifColor,
	const unsigned int SpcColor,
	const int FillFlag) {

	VECTOR centerPos = { CenterPos.x,CenterPos.y,CenterPos.z };

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);

}

int DrawLine3D(const Vector3& pos1, const Vector3& pos2, const unsigned int Coloer) {
	
	VECTOR p1 = { pos1.x,pos1.y,pos1.z };
	VECTOR p2 = { pos2.x,pos2.y,pos2.z };

	return DrawLine3D(p1, p2, Coloer);
}