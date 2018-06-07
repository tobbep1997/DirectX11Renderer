#ifndef DRAWABLE_H_
#define DRAWABLE_H_
#include <d3d11.h>
#include <DirectXMath.h>
#include "../Window/Structs.h"

using namespace DirectX;
class Drawable
{
private:	//TEMP
	VERTEX v[3];
private:
	DirectX::XMFLOAT4A	_position;
	DirectX::XMFLOAT4A	_scale;
	DirectX::XMFLOAT4A	_roation;

	DirectX::XMFLOAT4X4A _worldMatrix;

	ID3D11Buffer *	_vertexBuffer;

	UINT _meshSize;

	void _buildMatrix();

protected:
public:
	Drawable();
	~Drawable();


	void Draw();
	void SetPosition(DirectX::XMFLOAT4A);
	void SetRotation(DirectX::XMFLOAT4A);
	void SetScale(DirectX::XMFLOAT4A);

	ID3D11Buffer *	getVertexBuffer();
	UINT			getVertexSize();

};

#endif