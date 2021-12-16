//========================================================
//						カメラ
//========================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//カメラ構造体
typedef struct
{
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posR;
	D3DXVECTOR3 posVDest;
	D3DXVECTOR3 posRDest;
	D3DXVECTOR3 vecU;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXMATRIX  mtxProjection;
	D3DXMATRIX  mtxView;
	float fDistance;
} Camera;

//プロトタイプ宣言
void InitCamera(void);				//カメラ初期化処理
void UninitCamera(void);			//カメラ終了処理
void UpdataCamera(void);			//カメラ更新処理
void SetCamera(void);				//カメラ設定処理
Camera *GetCamera(void);

#endif