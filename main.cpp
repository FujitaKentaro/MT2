#include "DxLib.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Affin.h"
#include "Easing.h"
#include <cstring>
#include <vector>


//�֐��v���g�^�C�v�錾
int DrawCircle(Vector2 vec, int r, unsigned int color);

// ��
int DrawSphere3D(
	const Vector3& CenterPos,
	const float r,
	const int DivNum,
	const unsigned int DifColor,
	const unsigned int SpcColor,
	const int FillFlag);
// �~��
int DrawCone3D(
	const Vector3& TopPos,
	const Vector3& BottomPos,
	const float r,
	const int DivNum,
	const unsigned int DifColor,
	const unsigned int SpcColor,
	const int FillFlag);
// ����
int DrawLine3D(
	const Vector3& pos1,
	const Vector3& pos2,
	const unsigned int Coloer);
// �J�����̈ʒu�Ǝp���̐ݒ�
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,
	const Vector3& cameraTarget,
	const Vector3& cameraUp
);
// ���f���̍��W�ϊ��p�s��Z�b�g
int MV1SetMatrix(
	const int MHandle,
	const Matrix4 matrix);

// �֐��v���g�^�C�v�錾
void DrawAxis3D(const float length);
void DrawKeyOperation();

const Vector3 Lerp(const Vector3& start, const Vector3& end, const float t);

Vector3 splinePosition(const std::vector<Vector3>& points, size_t startIndex, float t);






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

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	Vector3 cameraPosition(-20.0f, 20.0f, -200.0f);
	Vector3 cameraTarget(0.0f, 0.0f, 0.0f);
	Vector3 cameraUp(0.0f, 1.0f, 0.0f);


	//	�N���b�v��	��		��
	SetCameraNearFar(1.0f, 1000.0f);// �J�����̗L���͈͂�ݒ�
	SetCameraScreenCenter(			// ��ʂ̒��S���J�����̒��S�ɍ��킹��
		WIN_WIDTH / 2.0f,
		WIN_HEIGHT / 2.0f);
	SetCameraPositionAndTargetAndUpVec(
		cameraPosition,
		cameraTarget,
		cameraUp);

	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	bool isHit = false;
	Vector2 lineStart = { 20 ,20 },
		lineEnd = { 120, 20 };
	int circleR = 50;
	Vector2 circlePos = { WIN_WIDTH / 2,WIN_HEIGHT / 2 };


	Vector2 lineVec, lineEndCirclVec, lineStartCirclVec, normLineVec;
	float distance, vectorDistance , StartVecDot, EndVecDot;

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
		isHit = false;

		if (keys[KEY_INPUT_W])
		{
			lineStart.y -= 10;
			lineEnd.y -= 10;
		}
		if (keys[KEY_INPUT_S])
		{
			lineStart.y += 10;
			lineEnd.y += 10;
		}
		if (keys[KEY_INPUT_A])
		{
			lineStart.x -= 10;
			lineEnd.x -= 10;
		}
		if (keys[KEY_INPUT_D])
		{
			lineStart.x += 10;
			lineEnd.x += 10;
		}


		lineVec = lineEnd - lineStart;
		lineEndCirclVec = circlePos- lineEnd;
		lineStartCirclVec = circlePos - lineStart;
		normLineVec = lineVec.nomalize();

		StartVecDot = lineStartCirclVec.dot(lineVec);
		EndVecDot = lineEndCirclVec.dot(lineVec);

		if (StartVecDot * EndVecDot <= 0)
		{
			isHit = true;
		}
		if (lineEndCirclVec.length() < circleR || lineStartCirclVec.length() < circleR)
		{
			isHit = true;
		}

		// �`�揈��
		// ��ʃN���A
		ClearDrawScreen();
		//DrawAxis3D(500.0f);

		DrawLine(lineStart.x, lineStart.y, lineEnd.x, lineEnd.y, GetColor(255, 255, 255));

		if (isHit){
			DrawCircle(circlePos, circleR, GetColor(255, 0, 0));
		}else
		{
			DrawCircle(circlePos, circleR, GetColor(255, 255, 255));
		}


		//DrawKeyOperation();

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
int DrawCircle(Vector2 vec, int r, unsigned int color) {
	return DrawCircle(static_cast<int>(vec.x), static_cast<int>(vec.y), r, color);
}

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
int DrawCone3D(
	const Vector3& TopPos,
	const Vector3& BottomPos,
	const float r,
	const int DivNum,
	const unsigned int DifColor,
	const unsigned int SpcColor,
	const int FillFlag) {
	VECTOR topPos = { TopPos.x,TopPos.y,TopPos.z };
	VECTOR bottomPos = { BottomPos.x,BottomPos.y,BottomPos.z };


	return DrawCone3D(topPos, bottomPos, r, DivNum, DifColor, SpcColor, FillFlag);
}

int DrawLine3D(const Vector3& pos1, const Vector3& pos2, const unsigned int Coloer) {

	VECTOR p1 = { pos1.x,pos1.y,pos1.z };
	VECTOR p2 = { pos2.x,pos2.y,pos2.z };

	return DrawLine3D(p1, p2, Coloer);
}

// �J�����̈ʒu�Ǝp���̐ݒ�
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,
	const Vector3& cameraTarget,
	const Vector3& cameraUp
) {
	VECTOR position = { cameraPosition.x,cameraPosition.y,cameraPosition.z };
	VECTOR target = { cameraTarget.x,cameraTarget.y,cameraTarget.z };
	VECTOR up = { cameraUp.x,cameraUp.y,cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}
// ���f���̍��W�ϊ��p�s��Z�b�g
int MV1SetMatrix(
	const int MHandle,
	const Matrix4 Matrix
) {
	MATRIX matrix;
	std::memcpy(&matrix, &Matrix, sizeof MATRIX);

	return MV1SetMatrix(MHandle, matrix);
}

// �֐��v���g�^�C�v�錾
void DrawAxis3D(const float length) {
	// ���̐��̕`��
	DrawLine3D(Vector3(-length, 0, 0), Vector3(+length, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(Vector3(0, -length, 0), Vector3(0, +length, 0), GetColor(0, 255, 0));
	DrawLine3D(Vector3(0, 0, -length), Vector3(0, 0, +length), GetColor(0, 0, 255));

	// ���̐�̕`��
	const float coneSize = 10.0f;
	DrawCone3D(
		Vector3(length, 0, 0),
		Vector3(length - coneSize, 0, 0),
		coneSize / 2,
		16,
		GetColor(255, 0, 0),
		GetColor(255, 255, 255),
		TRUE);
	DrawCone3D(
		Vector3(0, length, 0),
		Vector3(0, length - coneSize, 0),
		coneSize / 2,
		16,
		GetColor(0, 255, 0),
		GetColor(255, 255, 255),
		TRUE);
	DrawCone3D(
		Vector3(0, 0, length),
		Vector3(0, 0, length - coneSize),
		coneSize / 2,
		16,
		GetColor(0, 0, 255),
		GetColor(255, 255, 255),
		TRUE);


}
void DrawKeyOperation() {
	const unsigned white = GetColor(255, 255, 255);

	DrawFormatString(10, 20 * 1, white, "  [W][E][R]  R : ���Z�b�g");
	DrawFormatString(10, 20 * 2, white, "[A][S][D]   AD : y�����̉�]");
	DrawFormatString(10, 20 * 3, white, " [Z]        WS : x�����̉�]");
	DrawFormatString(10, 20 * 4, white, "            EZ : z�����̉�]");

}

const Vector3 Lerp(const Vector3& start, const Vector3& end, const float t) {
	/*float y = t;
	return start * (1.0f - y) + end * y;*/
	//return start * (1.0f - t) + end * t;

	//return start * (1.0f - t*t*t*t*t*t) + end * t;
	Vector3 x = start * (1.0f - t) + end * t;

	return x;

}

Vector3 splinePosition(const std::vector<Vector3>& points, size_t startIndex, float t) {

	// ��Ԃ��ׂ��_�̐�
	size_t n = points.size() - 2;

	if (startIndex > n)return points[n];	// Pn�̒l��Ԃ�
	if (startIndex < 1)return points[1];	// P1�̒l��Ԃ�

	// ��0�`���R �̐���_���擾���� �� ��1�`��2
	Vector3 p0 = points[startIndex - 1];
	Vector3 p1 = points[startIndex];
	Vector3 p2 = points[startIndex + 1];
	Vector3 p3 = points[startIndex + 2];

	// Catmull-Rom �̎��ɂ����
	Vector3 position;
	position = {
	2 * p1 + (-p0 + p2) * t +
	(2 * p0 - 5 * p1 + 4 * p2 - p3) * (t * t) +
	(-p0 + 3 * p1 - 3 * p2 + p3) * (t * t * t) };

	return position * 0.5f;
}
