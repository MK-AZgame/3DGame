//========================================================
//					プレイヤー
//========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 rotDest;
} Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdataPlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);

#endif