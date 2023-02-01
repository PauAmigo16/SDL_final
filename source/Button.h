#pragma once
#include"Object.h"
#include<vector>
#include"GameObject.h"
#include"TextObject.h"


class Button : public GameObject {
private:
	TextObject* text;
public:
	Button() = default;
	virtual void Update() = 0;
	virtual void Render() = 0;




};