#pragma once
#include"Object.h"
#include<vector>
#include"TextRenderer.h"


class TextObject : public Object {
private:
	TextRenderer renderer;

public:
	TextObject() = default;
	void Update() override;
	void Render() override;
	



};

