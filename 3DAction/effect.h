//========================================================
//					�G�t�F�N�g
//========================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//�G�t�F�N�g�̍\����
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

//�v���g�^�C�v�錾
void InitEffect(void);										//�G�t�F�N�g����������
void UninitEffect(void);									//�G�t�F�N�g�I������
void UpdataEffect(void);									//�G�t�F�N�g�X�V����
void DrawEffect(void);										//�G�t�F�N�g�`�揈��
void SetEffect(D3DXVECTOR3 pos);							//�G�t�F�N�g�̐ݒ菈��

#endif 