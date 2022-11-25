#include "DxLib.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Affin.h"
#include "Easing.h"
#include <cstring>
#include <vector>


//関数プロトタイプ宣言
int DrawCircle(Vector2 vec, int r, unsigned int color);

// 球
int DrawSphere3D(
	const Vector3& CenterPos,
	const float r,
	const int DivNum,
	const unsigned int DifColor,
	const unsigned int SpcColor,
	const int FillFlag);
// 円錐
int DrawCone3D(
	const Vector3& TopPos,
	const Vector3& BottomPos,
	const float r,
	const int DivNum,
	const unsigned int DifColor,
	const unsigned int SpcColor,
	const int FillFlag);
// 線分
int DrawLine3D(
	const Vector3& pos1,
	const Vector3& pos2,
	const unsigned int Coloer);
// カメラの位置と姿勢の設定
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,
	const Vector3& cameraTarget,
	const Vector3& cameraUp
);
// モデルの座標変換用行列セット
int MV1SetMatrix(
	const int MHandle,
	const Matrix4 matrix);

// 関数プロトタイプ宣言
void DrawAxis3D(const float length);
void DrawKeyOperation();

const Vector3 Lerp(const Vector3& start, const Vector3& end, const float t);

Vector3 splinePosition(const std::vector<Vector3>& points, size_t startIndex, float t);






// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LE2B_21_フジタケンタロウ:タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 1024;

// ウィンドウ縦幅
const int WIN_HEIGHT = 576;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x64);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	// 画像などのリソースデータの変数宣言と読み込み
	Vector3 cameraPosition(-20.0f, 20.0f, -200.0f);
	Vector3 cameraTarget(0.0f, 0.0f, 0.0f);
	Vector3 cameraUp(0.0f, 1.0f, 0.0f);


	//	クリップ面	近		遠
	SetCameraNearFar(1.0f, 1000.0f);// カメラの有効範囲を設定
	SetCameraScreenCenter(			// 画面の中心をカメラの中心に合わせる
		WIN_WIDTH / 2.0f,
		WIN_HEIGHT / 2.0f);
	SetCameraPositionAndTargetAndUpVec(
		cameraPosition,
		cameraTarget,
		cameraUp);

	// ゲームループで使う変数の宣言

	bool isHit = false;
	Vector2 lineStart = { 20 ,20 },
		lineEnd = { 120, 20 };
	int circleR = 50;
	Vector2 circlePos = { WIN_WIDTH / 2,WIN_HEIGHT / 2 };


	Vector2 lineVec, lineEndCirclVec, lineStartCirclVec, normLineVec;
	float distance, vectorDistance , StartVecDot, EndVecDot;

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}


		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);


		//---------  ここからプログラムを記述  ----------//

		// 更新処理
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

		// 描画処理
		// 画面クリア
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

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}

//オーバーロード関数
//表示位置に　ベクトル（Vector2）　を指定できるようにする
int DrawCircle(Vector2 vec, int r, unsigned int color) {
	return DrawCircle(static_cast<int>(vec.x), static_cast<int>(vec.y), r, color);
}

//表示位置に　ベクトル（Vector3）　を指定できるようにする
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

// カメラの位置と姿勢の設定
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
// モデルの座標変換用行列セット
int MV1SetMatrix(
	const int MHandle,
	const Matrix4 Matrix
) {
	MATRIX matrix;
	std::memcpy(&matrix, &Matrix, sizeof MATRIX);

	return MV1SetMatrix(MHandle, matrix);
}

// 関数プロトタイプ宣言
void DrawAxis3D(const float length) {
	// 軸の線の描画
	DrawLine3D(Vector3(-length, 0, 0), Vector3(+length, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(Vector3(0, -length, 0), Vector3(0, +length, 0), GetColor(0, 255, 0));
	DrawLine3D(Vector3(0, 0, -length), Vector3(0, 0, +length), GetColor(0, 0, 255));

	// 軸の先の描画
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

	DrawFormatString(10, 20 * 1, white, "  [W][E][R]  R : リセット");
	DrawFormatString(10, 20 * 2, white, "[A][S][D]   AD : y軸回りの回転");
	DrawFormatString(10, 20 * 3, white, " [Z]        WS : x軸回りの回転");
	DrawFormatString(10, 20 * 4, white, "            EZ : z軸回りの回転");

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

	// 補間すべき点の数
	size_t n = points.size() - 2;

	if (startIndex > n)return points[n];	// Pnの値を返す
	if (startIndex < 1)return points[1];	// P1の値を返す

	// ｐ0～ｐ３ の制御点を取得する ※ ｐ1～ｐ2
	Vector3 p0 = points[startIndex - 1];
	Vector3 p1 = points[startIndex];
	Vector3 p2 = points[startIndex + 1];
	Vector3 p3 = points[startIndex + 2];

	// Catmull-Rom の式による補間
	Vector3 position;
	position = {
	2 * p1 + (-p0 + p2) * t +
	(2 * p0 - 5 * p1 + 4 * p2 - p3) * (t * t) +
	(-p0 + 3 * p1 - 3 * p2 + p3) * (t * t * t) };

	return position * 0.5f;
}
