#pragma once
#include "SingletonBase.h"

#define KEY_MAX 256

class KeyManager : public SingletonBase <KeyManager>
{
private:
	//BOOL _keyUp[KEY_MAX];
	//BOOL _keyDown[KEY_MAX];

	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;

public:
	HRESULT init(void);

	//키가 한번만 눌렸는지
	bool isOnceKeyDown(int key);
	//한번 누르고 띄었는지
	bool isOnceKeyUp(int key);
	//키가 계속 눌려있는지
	bool isStayKeyDown(int key);
	// 토글키
	bool isToggleKey(int key);


	//bitset을 이용한 get, set
	bitset<KEY_MAX> getKeyUp(void) { return _keyUp; }
	bitset<KEY_MAX> getKeyDown(void) { return _keyDown; }

	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }

	KeyManager() {};
	~KeyManager() {};
};