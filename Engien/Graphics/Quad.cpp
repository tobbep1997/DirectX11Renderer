#include "Quad.h"



void Quad::_createQuad()
{
	quad[0].pos = DirectX::XMFLOAT4(-0.5, 0.5, 0, 1);
	quad[0].normal = DirectX::XMFLOAT3(0, 0, -1);
	quad[0].uv = DirectX::XMFLOAT2(0, 0);
	
	quad[1].pos = DirectX::XMFLOAT4(.5, -.5, 0, 1);
	quad[1].normal = DirectX::XMFLOAT3(0, 0, -1);
	quad[1].uv = DirectX::XMFLOAT2(1, 1);
	
	quad[2].pos = DirectX::XMFLOAT4(-.5, -.5, 0, 1);
	quad[2].normal = DirectX::XMFLOAT3(0, 0, -1);
	quad[2].uv = DirectX::XMFLOAT2(0, 1);

	quad[3].pos = DirectX::XMFLOAT4(-.5, .5, 0, 1);
	quad[3].normal = DirectX::XMFLOAT3(0, 0, -1);
	quad[3].uv = DirectX::XMFLOAT2(0, 1);

	quad[4].pos = DirectX::XMFLOAT4(.5, .5, 0, 1);
	quad[4].normal = DirectX::XMFLOAT3(0, 0, -1);
	quad[4].uv = DirectX::XMFLOAT2(0, 1);

	quad[5].pos = DirectX::XMFLOAT4(.5, -.5, 0, 1);
	quad[5].normal = DirectX::XMFLOAT3(0, 0, -1);
	quad[5].uv = DirectX::XMFLOAT2(0, 1);
}

Quad::Quad() : Drawable()
{
	quad = new VERTEX[6];
	this->_createQuad();
	this->_createBuffer(quad, 6);
}


Quad::~Quad()
{
	delete[] quad;
}
