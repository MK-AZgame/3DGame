#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//プロトタイプ宣言
void Initbullet(void);
void Uninitbullet(void);
void Updatabullet(void);
void Drawbullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);

#endif
