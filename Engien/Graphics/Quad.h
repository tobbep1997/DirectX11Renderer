#pragma once
#include "Drawable.h"
#include "../Window/Structs.h"
class Quad :
	public Drawable
{
private:
	VERTEX * quad;
	void _createQuad();
public:
	Quad();
	~Quad();
};

