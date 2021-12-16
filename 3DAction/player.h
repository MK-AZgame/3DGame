//========================================================
//
//					�v���C���[
//					AUTHOR:�z�{���V
//
//========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//�v���C���[�\����
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 rot;					//����
	D3DXMATRIX mtxWorld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 rotDest;				//�ړI�̌���
} Player;

//�v���g�^�C�v�錾
void InitPlayer(void);					//�v���C���[�̏���������
void UninitPlayer(void);				//�v���C���[�̏I������
void UpdataPlayer(void);				//�v���C���[�̍X�V����
void DrawPlayer(void);					//�v���C���[�̕`�揈��
Player *GetPlayer(void);				//�v���C���[�̏��̎擾

#endif