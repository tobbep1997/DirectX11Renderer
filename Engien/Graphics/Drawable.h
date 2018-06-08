#ifndef DRAWABLE_H_
#define DRAWABLE_H_
#include <d3d11.h>
#include <DirectXMath.h>
#include "../Window/Structs.h"

using namespace DirectX;
class Drawable
{
private:
	DirectX::XMFLOAT4A	_position;
	DirectX::XMFLOAT4A	_scale;
	DirectX::XMFLOAT4A	_rotation;

	DirectX::XMFLOAT4X4A _worldMatrix;

	ID3D11Buffer *	_vertexBuffer;

	UINT _meshSize;

	void _buildMatrix();

protected:
	void _createBuffer(VERTEX * V, const int& size);
public:
	Drawable();
	virtual ~Drawable();
	
	void Draw();
	void SetPosition(float x, float y, float z, float w = 1);
	void SetRotation(float x, float y, float z, float w = 1);
	void SetScale(float x, float y, float z, float w = 1);
	void SetPosition(DirectX::XMFLOAT4A);
	void SetRotation(DirectX::XMFLOAT4A);
	void SetScale(DirectX::XMFLOAT4A);

	DirectX::XMFLOAT4A GetPosition() const;
	DirectX::XMFLOAT4A GetRotation() const;
	DirectX::XMFLOAT4A GetScale() const;


	ID3D11Buffer *	getVertexBuffer();
	UINT			getVertexSize();

	DirectX::XMFLOAT4X4A& getWorldMatrix();
};

#endif