//========================================================
//						�v���C���[
//========================================================
#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "meshfield.h"

//�}�N����`
#define PLAYER_SIZE (20.0f)								//�v���C���[�̃T�C�Y
#define PLAYER_MOVE (1.0f)								//�v���C���[�̈ړ���
#define PLAYER_ROTSPEED (0.1f)							//�v���C���[�̉�]�̌�����
#define ROT_PLAYERVIEW (0.175f)							//�v���C���[�̉�]�ɔ����J�����̉�]��

//�O���[�o���ϐ�
LPD3DXMESH g_pMeshPlayer = NULL;
LPD3DXBUFFER g_pBuffMatPlayer = NULL;
DWORD g_nNumMatPlayer = 0;									
int g_nIdxShadow;
Player g_player;										//�v���C���[�̏����i�[

//========================================================
//					�v���C���[����������
//========================================================
void InitPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/Head000.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatPlayer, NULL, &g_nNumMatPlayer, &g_pMeshPlayer);

	//�ʒu�E�����̏�����
	g_player.pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);		//�ʒu�̏�����
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏�����

	g_player.rotDest.y = 0;								//�ړI�̊p�x�̏�����

	//�e�̐ݒ�
	g_nIdxShadow = SetShadow(D3DXVECTOR3(g_player.pos.x, 0.1f, g_player.pos.z), g_player.rot);
}

//========================================================
//					�v���C���[�I������
//========================================================
void UninitPlayer(void)
{
	//���b�V���̔j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//========================================================
//					�v���C���[�X�V����
//========================================================
void UpdataPlayer(void)
{
	Camera *pCamera = GetCamera();

	//�e�̔���
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetBullet(g_player.pos, D3DXVECTOR3(-sinf(g_player.rot.y), 0.0f, -cosf(g_player.rot.y)));
	}

	//�v���C���[�̈ړ�
	if (GetKeyboardPress(DIK_UP))
	{//�����L�[�̏オ�����ꂽ
		if (GetKeyboardPress(DIK_RIGHT))
		{//�E�΂�
			g_player.pos.x += sinf(pCamera->rot.y + (D3DX_PI * 0.25f)) * PLAYER_MOVE;
			g_player.pos.z += cosf(pCamera->rot.y + (D3DX_PI * 0.25f)) * PLAYER_MOVE;
			g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI * -0.75f));
			pCamera->rotDest.y = pCamera->rot.y + (D3DX_PI * ROT_PLAYERVIEW);
		}
		else if (GetKeyboardPress(DIK_LEFT))
		{//���΂�
			g_player.pos.x += sinf(pCamera->rot.y + (D3DX_PI * -0.25f)) * PLAYER_MOVE;
			g_player.pos.z += cosf(pCamera->rot.y + (D3DX_PI * -0.25f)) * PLAYER_MOVE;
			g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI * 0.75f));
			pCamera->rotDest.y = pCamera->rot.y + (D3DX_PI * -ROT_PLAYERVIEW);
		}
		else
		{//�O
			g_player.pos.x += sinf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.pos.z += cosf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI));
		}
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{//�����L�[�̉��������ꂽ
		if (GetKeyboardPress(DIK_RIGHT))
		{//�E�΂�
			g_player.pos.x += sinf(pCamera->rot.y + (D3DX_PI * 0.75f)) * PLAYER_MOVE;
			g_player.pos.z += cosf(pCamera->rot.y + (D3DX_PI * 0.75f)) * PLAYER_MOVE;
			//g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI * -ROT_PLAYERVIEW));
		}
		else if (GetKeyboardPress(DIK_LEFT))
		{//���΂�
			g_player.pos.x += sinf(pCamera->rot.y + (D3DX_PI * -0.75f)) * PLAYER_MOVE;
			g_player.pos.z += cosf(pCamera->rot.y + (D3DX_PI * -0.75f)) * PLAYER_MOVE;
			//g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI * ROT_PLAYERVIEW));
		}
		else
		{//���
			g_player.pos.x -= sinf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.pos.z -= cosf(pCamera->rot.y) * PLAYER_MOVE;
		}
	}
	else if (GetKeyboardPress(DIK_LEFT))
	{//��
		g_player.pos.x += sinf(pCamera->rot.y + (D3DX_PI * -0.5f)) * PLAYER_MOVE;
		g_player.pos.z += cosf(pCamera->rot.y + (D3DX_PI * -0.5f)) * PLAYER_MOVE;
		g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI * 0.5f));
		pCamera->rotDest.y = pCamera->rot.y + (D3DX_PI * -ROT_PLAYERVIEW);
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{//�E
		g_player.pos.x += sinf(pCamera->rot.y + (D3DX_PI * 0.5f)) * PLAYER_MOVE;
		g_player.pos.z += cosf(pCamera->rot.y + (D3DX_PI * 0.5f)) * PLAYER_MOVE;
		g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI * -0.5f));
		pCamera->rotDest.y = pCamera->rot.y + (D3DX_PI * ROT_PLAYERVIEW);
	}

	////��]�̐��K��
	//�ړI�̊p�x���傫�������菬���������肵�����̌v�Z
	if (g_player.rotDest.y - g_player.rot.y > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rotDest.y - g_player.rot.y < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}

	//�����̌v�Z
	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * PLAYER_ROTSPEED;

	//�v�Z���ʂ��傫�������菬���������肵�����̒���
	if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}

	//�e�̍X�V
	SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_player.pos.x, 0.1f, g_player.pos.z));

	//�s���͈͐���(�ǂƂ̓����蔻��)
	if (g_player.pos.x + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
	{//�E
		if (g_player.pos.z + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
		{//�E��
			g_player.pos.x = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
			g_player.pos.z = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
		}
		else if (g_player.pos.z - PLAYER_SIZE <= -MESHFIELD_SIZE * 2)
		{//�E��O
			g_player.pos.x = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
			g_player.pos.z = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
		}
		else
		{
			g_player.pos.x = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
		}
	}
	else if (g_player.pos.x - PLAYER_SIZE <= -MESHFIELD_SIZE * 2)
	{//��
		if (g_player.pos.z + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
		{//����
			g_player.pos.x = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
			g_player.pos.z = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
		}
		else if (g_player.pos.z - PLAYER_SIZE <= -MESHFIELD_SIZE * 2)
		{//�E��O
			g_player.pos.x = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
			g_player.pos.z = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
		}
		else
		{
			g_player.pos.x = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
		}
	}
	else if (g_player.pos.z + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
	{//��
		g_player.pos.z = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
	}
	else if (g_player.pos.z - PLAYER_SIZE <= (-MESHFIELD_SIZE * 2))
	{//��O
		g_player.pos.z = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
	}
}

//========================================================
//					�v���C���[�`�揈��
//========================================================
void DrawPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//�����𔽓]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�v���C���[�p�[�c�̕`��
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//�ێ����Ă����}�e���A����Ԃ�
	pDevice->SetMaterial(&matDef);
}

//========================================================
//				�v���C���[���̎擾
//========================================================
Player *GetPlayer(void)
{
	return &g_player;
}