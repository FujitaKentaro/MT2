#include "DxLib.h"
#include "Vector2.h"
#include "Vector3.h"

//関数プロトタイプ宣言
//int DrawCircle(Vector2 vec, int r, unsigned int color);
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);
int DrawLine3D(const Vector3& pos1, const Vector3& pos2, const unsigned int Coloer);

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

	// 画像などのリソースデータの変数宣言と読み込み

	//	クリップ面	近		遠
	SetCameraNearFar(1.0f, 1000.0f);// カメラの有効範囲を設定
	SetCameraScreenCenter(			// 画面の中心をカメラの中心に合わせる
		WIN_WIDTH / 2.0f,
		WIN_HEIGHT / 2.0f);
	SetCameraPositionAndTargetAndUpVec(
		VGet(0.0f, 0.0f, -100.0f), // カメラ位置
		VGet(0.0f, 0.0f,    0.0f), // カメラ注視点
		VGet(0.0f, 1.0f,    0.0f));// カメラの上の向き


	// ゲームループで使う変数の宣言

	Vector3 position(0, 0, 100);					//位置
	Vector3 velocity(0.0f, 0.0f, 0.5f);			//速度

	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);

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
		position += velocity;



		// 描画処理
		// 画面クリア
		ClearDrawScreen();
		DrawSphere3D(position, 80.0f, 32,GetColor(255, 0, 0),GetColor(255,255,255),TRUE);


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
//int DrawCircle(Vector2 vec, int r, unsigned int color) {
//	return DrawCircle(static_cast<int>(vec.x), static_cast<int>(vec.y), r, color);
//}

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

int DrawLine3D(const Vector3& pos1, const Vector3& pos2, const unsigned int Coloer) {
	
	VECTOR p1 = { pos1.x,pos1.y,pos1.z };
	VECTOR p2 = { pos2.x,pos2.y,pos2.z };

	return DrawLine3D(p1, p2, Coloer);
}