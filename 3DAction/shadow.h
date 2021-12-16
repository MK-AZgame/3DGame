//========================================================
//							�e
//========================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
} Shadow;

//�v���g�^�C�v�錾
void InitShadow(void);										//�e����������
void UninitShadow(void);									//�e�I������
void UpdataShadow(void);									//�e�X�V����
void DrawShadow(void);										//�e�`�揈��
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//�e�̐ݒ菈��
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);	//�e�̍��W�X�V�̏���

#endif 

