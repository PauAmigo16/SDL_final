#include "GameObject.h"

GameObject::~GameObject()
{
    for (auto images : renderers)
    {
        delete images;
    }

}


