#ifndef DRAWABLE_H_
#define DRAWABLE_H_
#include <d3d11.h>
#include <DirectXMath.h>
#include "../Window/Structs.h"
#include "Texture\Material.h"
#include <vector>

using namespace DirectX;
class Drawable
{
private:
	DirectX::XMFLOAT4A	_position;
	DirectX::XMFLOAT4A	_scale;
	DirectX::XMFLOAT4A	_rotation;
	DirectX::XMFLOAT4X4A _worldMatrix;

	std::vector<ID3D11Buffer *>	_vertexBuffer;
	std::vector<Material *>		_material;
	std::vector<UINT>			_meshSize;
	//UINT _objectSize;


	void _buildMatrix();
protected:
	void _createBuffer(VERTEX * V, const int& size);
	void _createMultBuffer(MESH mesh);

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

	void LoadTexture(const std::string& path);

	std::vector<ID3D11Buffer *>	getVertexBuffer();
	std::vector<Material *>		GetMaterial();
	size_t			getObjectSize();
	UINT *			getVertexSize();

	DirectX::XMFLOAT4X4A& getWorldMatrix();

};

#endif