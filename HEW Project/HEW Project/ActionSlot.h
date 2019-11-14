#pragma once
#include "GameObject.h"
#include "main.h"
#include "input.h"

// �A�N�V�����Q�[�W���
typedef enum {

	ACTIONSLOT_OVER,
	ACTIONSLOT_GREAT,
	ACTIONSLOT_GOOD,
	ACTIONSLOT_BAD,

}ACTIONSLOT_STATE_INDEX;

// �A�N�V�����Q�[�W
class ActionSlot
{
private:

	// ���
	int State;
	// �l
	float Value;
	// ���΃I�u�W�F�N�g
	GameObject Fire;
	// ��I�u�W�F�N�g
	GameObject Hand;

public:

	// ���W
	D3DXVECTOR2 Pos;
	
	void Load();

	void Update();

	void Draw();

	ActionSlot();

	~ActionSlot();

	void AddValue(float value);

	int GetState();

	float GetValue();

	GameObject GetFire();

	GameObject GetHand();

};
