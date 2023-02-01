#include "GameObject.h"



GameObject::~GameObject()
{
    for (auto images : renderer)
    {
        delete images;
    }

}


