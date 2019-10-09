#pragma once

#include <d3d9.h>

typedef enum 
{
    TEXTURE_INDEX_YUKIDARUMA,
	TEXTURE_INDEX_MENUSTART,
	TEXTURE_INDEX_MENUEXIT,

    TEXTURE_INDEX_MAX
}TextureIndex;

int Texture_Load(HWND hWnd); //������
void Texture_Release(void); //�I������
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index);
int Texture_GetWidth(TextureIndex index);
int Texture_GetHeight(TextureIndex index);