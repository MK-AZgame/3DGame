//========================================================
//						プレイヤー
//========================================================
#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "meshfield.h"

//マクロ定義
#define PLAYER_SIZE (20.0f)								//プレイヤーのサイズ
#define PLAYER_MOVE (1.0f)								//プレイヤーの移動量
#define PLAYER_ROTSPEED (0.1f)							//プレイヤーの回転の減衰量
#define ROT_PLAYERVIEW (0.175f)							//プレイヤーの回転に伴うカメラの回転量

//グローバル変数
LPD3DXMESH g_pMeshPlayer = NULL;
LPD3DXBUFFER g_pBuffMatPlayer = NULL;
DWORD g_nNumMatPlayer = 0;									
int g_nIdxShadow;
Player g_player;										//プレイヤーの情報を格納

//========================================================
//					プレイヤー初期化処理
//========================================================
void InitPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/Head000.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatPlayer, NULL, &g_nNumMatPlayer, &g_pMeshPlayer);

	//位置・向きの初期化
	g_player.pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);		//位置の初期化
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期化

	g_player.rotDest.y = 0;								//目的の角度の初期化

	//影の設定
	g_nIdxShadow = SetShadow(D3DXVECTOR3(g_player.pos.x, 0.1f, g_player.pos.z), g_player.rot);
}

//========================================================
//					プレイヤー終了処理
//========================================================
void UninitPlayer(void)
{
	//メッシュの破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//========================================================
//					プレイヤー更新処理
//========================================================
void UpdataPlayer(void)
{
	Camera *pCamera = GetCamera();

	//弾の発射
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetBullet(g_player.pos, D3DXVECTOR3(-sinf(g_player.rot.y), 0.0f, -cosf(g_player.rot.y)));
	}

	//プレイヤーの移動
	if (GetKeyboardPress(DIK_UP))
	{//方向キーの上が押された
		if (GetKeyboardPress(DIK_RIGHT))
		{//右斜め
			g_player.pos.x += sinf(pCamera->rot.y + (D3DX_PI * 0.25f)) * PLAYER_MOVE;
			g_player.pos.z += cosf(pCamera->rot.y + (D3DX_PI * 0.25f)) * PLAYER_MOVE;
			g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI * -0.75f));
			pCamera->rotDest.y = pCamera->rot.y + (D3DX_PI * ROT_PLAYERVIEW);
		}
		else if (GetKeyboardPress(DIK_LEFT))
		{//左斜め
			g_player.pos.x += sinf(pCamera->rot.y + (D3DX_PI * -0.25f)) * PLAYER_MOVE;
			g_player.pos.z += cosf(pCamera->rot.y + (D3DX_PI * -0.25f)) * PLAYER_MOVE;
			g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI * 0.75f));
			pCamera->rotDest.y = pCamera->rot.y + (D3DX_PI * -ROT_PLAYERVIEW);
		}
		else
		{//前
			g_player.pos.x += sinf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.pos.z += cosf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI));
		}
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{//方向キーの下が押された
		if (GetKeyboardPress(DIK_RIGHT))
		{//右斜め
			g_player.pos.x += sinf(pCamera->rot.y + (D3DX_PI * 0.75f)) * PLAYER_MOVE;
			g_player.pos.z += cosf(pCamera->rot.y + (D3DX_PI * 0.75f)) * PLAYER_MOVE;
			//g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI * -ROT_PLAYERVIEW));
		}
		else if (GetKeyboardPress(DIK_LEFT))
		{//左斜め
			g_player.pos.x += sinf(pCamera->rot.y + (D3DX_PI * -0.75f)) * PLAYER_MOVE;
			g_player.pos.z += cosf(pCamera->rot.y + (D3DX_PI * -0.75f)) * PLAYER_MOVE;
			//g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI * ROT_PLAYERVIEW));
		}
		else
		{//後ろ
			g_player.pos.x -= sinf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.pos.z -= cosf(pCamera->rot.y) * PLAYER_MOVE;
		}
	}
	else if (GetKeyboardPress(DIK_LEFT))
	{//左
		g_player.pos.x += sinf(pCamera->rot.y + (D3DX_PI * -0.5f)) * PLAYER_MOVE;
		g_player.pos.z += cosf(pCamera->rot.y + (D3DX_PI * -0.5f)) * PLAYER_MOVE;
		g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI * 0.5f));
		pCamera->rotDest.y = pCamera->rot.y + (D3DX_PI * -ROT_PLAYERVIEW);
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{//右
		g_player.pos.x += sinf(pCamera->rot.y + (D3DX_PI * 0.5f)) * PLAYER_MOVE;
		g_player.pos.z += cosf(pCamera->rot.y + (D3DX_PI * 0.5f)) * PLAYER_MOVE;
		g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI * -0.5f));
		pCamera->rotDest.y = pCamera->rot.y + (D3DX_PI * ROT_PLAYERVIEW);
	}

	////回転の正規化
	//目的の角度が大きすぎたり小さすぎたりした時の計算
	if (g_player.rotDest.y - g_player.rot.y > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rotDest.y - g_player.rot.y < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}

	//慣性の計算
	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * PLAYER_ROTSPEED;

	//計算結果が大きすぎたり小さすぎたりした時の調整
	if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}

	//影の更新
	SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_player.pos.x, 0.1f, g_player.pos.z));

	//行動範囲制限(壁との当たり判定)
	if (g_player.pos.x + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
	{//右
		if (g_player.pos.z + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
		{//右奥
			g_player.pos.x = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
			g_player.pos.z = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
		}
		else if (g_player.pos.z - PLAYER_SIZE <= -MESHFIELD_SIZE * 2)
		{//右手前
			g_player.pos.x = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
			g_player.pos.z = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
		}
		else
		{
			g_player.pos.x = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
		}
	}
	else if (g_player.pos.x - PLAYER_SIZE <= -MESHFIELD_SIZE * 2)
	{//左
		if (g_player.pos.z + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
		{//左奥
			g_player.pos.x = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
			g_player.pos.z = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
		}
		else if (g_player.pos.z - PLAYER_SIZE <= -MESHFIELD_SIZE * 2)
		{//右手前
			g_player.pos.x = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
			g_player.pos.z = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
		}
		else
		{
			g_player.pos.x = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
		}
	}
	else if (g_player.pos.z + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
	{//奥
		g_player.pos.z = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
	}
	else if (g_player.pos.z - PLAYER_SIZE <= (-MESHFIELD_SIZE * 2))
	{//手前
		g_player.pos.z = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
	}
}

//========================================================
//					プレイヤー描画処理
//========================================================
void DrawPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//向きを反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//プレイヤーパーツの描画
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//保持していたマテリアルを返す
	pDevice->SetMaterial(&matDef);
}

//========================================================
//				プレイヤー情報の取得
//========================================================
Player *GetPlayer(void)
{
	return &g_player;
}