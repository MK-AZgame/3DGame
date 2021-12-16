//========================================================
//					�v���C���[
//========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//�v���C���[�\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 rotDest;
} Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdataPlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);

#endif