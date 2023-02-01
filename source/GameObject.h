#pragma once
#include"Object.h"
#include<vector>
#include"ImageRenderer.h"


class GameObject : public Object {
protected:
	std::vector<ImageRenderer*> renderers;

public:
	GameObject() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual ~GameObject() override;
};
