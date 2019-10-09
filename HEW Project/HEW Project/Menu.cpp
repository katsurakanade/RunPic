#include "Menu.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"

Menu::Menu(int arrow)
{
	Arrow = arrow;

	select_now = 0;
}

Menu::~Menu()
{

}

int Menu::UpdateSelectMenu() {

	if (select_now < Arrow - 1) {
		if (Keyboard_IsTrigger(DIK_DOWNARROW)) {
			select_now++;
		}
	}

	else if (select_now> 0) {
		if (Keyboard_IsTrigger(DIK_UPARROW)) {
			select_now--;
		}
	}

	if (Keyboard_IsPress(DIK_RETURN)) {
		return  select_now;
	}

	return 10000;
}

void Menu::Draw(LPDIRECT3DTEXTURE9 texturearray[],int sx,int sy,int interval,int tx,int tw) {

	for (int i = 0; i <= Arrow -1 ; i++) {

		if (select_now == i) {
			Sprite_SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
		}

		else if (select_now != i) {
			Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		}

		Sprice_Draw_Menu(texturearray[i], sx, sy + (interval  * i),tx,tw);
	}

	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}