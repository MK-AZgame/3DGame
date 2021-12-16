//========================================================
//					エフェクト
//========================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//エフェクトの構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fRadius;
	D3DXCOLOR	col;
	D3DXMATRIX mtxWorld;
	int nLife;
	bool bUse;
} Effect;

//プロトタイプ宣言
void InitEffect(void);										//エフェクト初期化処理
void UninitEffect(void);									//エフェクト終了処理
void UpdataEffect(void);									//エフェクト更新処理
void DrawEffect(void);										//エフェクト描画処理
void SetEffect(D3DXVECTOR3 pos);							//エフェクトの設定処理

#endif 