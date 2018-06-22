#include "MeshLoader.h"


#include <iostream>
MESH MeshLoader::_loadMesh(const wchar_t * path)
{
	std::vector <DirectX::XMFLOAT4*>	position;
	std::vector <DirectX::XMFLOAT3*>	normal;
	std::vector <DirectX::XMFLOAT2*>	texPos;
	std::vector <std::vector<FACE *>>	face;
	std::vector	<std::wstring>			mtlName;

	std::wstring p = std::wstring(path);
	size_t t = p.find_last_of(L'/');
	p = p.substr(0, t + 1);
	std::wifstream in(path);


	bool firstObject = false;

	if (!in.is_open())
	{
		std::cout << "Didn't find file" << std::endl;
		return MESH();

	}

	//std::vector<std::wstring*> input;
	DirectX::XMFLOAT4 tmp;
	FACE * f;
	std::vector<FACE *> f_v;
	MESH m;
	std::wstring mtllib;

	wchar_t input[256];
	wchar_t cInput[256];
	while (!in.eof())
	{
		in.getline(input, 256);

		if (input[0] == L'#') {}
		else if (input[0] == L'v' && input[1] == L' ') {
			swscanf_s(input, L"%*s %f %f %f", &tmp.x, &tmp.y, &tmp.z);
			position.push_back(new DirectX::XMFLOAT4(tmp.x, tmp.y, tmp.z, 1.0f));
		}
		else if (input[0] == L'v' && input[1] == L't') {
			swscanf_s(input, L"%*s %f %f", &tmp.x, &tmp.y);
			texPos.push_back(new DirectX::XMFLOAT2(tmp.x, tmp.y));
		}
		else if (input[0] == L'v' && input[1] == L'n') {
			swscanf_s(input, L"%*s %f %f %f", &tmp.x, &tmp.y, &tmp.z);
			normal.push_back(new DirectX::XMFLOAT3(tmp.x, tmp.y, tmp.z));
		}
		else if ((input[0] == L'g' || input[0] == L'o') && input[1] == L' ') {
			if (f_v.size() > 0)
			{
				face.push_back(f_v);
				f_v.clear();
			}
			
		}
		else if (input[0] == L'f' && input[1] == L' ' && std::count(&input[0], &input[256], '/') == 8)
		{
			f = new FACE();
			swscanf_s(input, L"%*s %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &f->v1, &f->t1, &f->n1, &f->v2, &f->t2, &f->n2, &f->v3, &f->t3, &f->n3, &f->v4, &f->t4, &f->n4);
			f->quad = true;
			f_v.push_back(f);
		}
		else if (input[0] == L'f' && input[1] == L' ' && std::count(&input[0], &input[256], '/') == 6)
		{
			f = new FACE();
			swscanf_s(input, L"%*s %d/%d/%d %d/%d/%d %d/%d/%d", &f->v1, &f->t1, &f->n1, &f->v2, &f->t2, &f->n2, &f->v3, &f->t3, &f->n3);
			f->quad = false;
			f_v.push_back(f);
		}
		else if (input[0] == L'm' && input[1] == L't') {
			swscanf_s(input, L"%*ls %s", cInput, 256);			
			mtllib = std::wstring(cInput);
		}
		else if (input[0] == L'u' && input[1] == L's') {
			swscanf_s(input, L"%*ls %s", cInput, 256);
			m.material.push_back(new Material(p + mtllib, std::wstring(cInput)));
		}
		for (size_t i = 0; i < 256; i++)
		{
			input[i] = NULL;
			cInput[i] = NULL;
		}
	}
	in.close();

	face.push_back(f_v);

	std::vector<std::vector<VERTEX>> v;
	std::vector<VERTEX> v_v;
	for (size_t i = 0; i < face.size(); i++)
	{
		for (size_t j = 0; j < face[i].size(); j++)
		{

			if (face[i][j]->quad)
			{
				v_v.push_back(VERTEX(*position[face[i][j]->v1 - 1], *normal[face[i][j]->n1 - 1], *texPos[face[i][j]->t1 - 1]));
				v_v.push_back(VERTEX(*position[face[i][j]->v2 - 1], *normal[face[i][j]->n2 - 1], *texPos[face[i][j]->t2 - 1]));
				v_v.push_back(VERTEX(*position[face[i][j]->v3 - 1], *normal[face[i][j]->n3 - 1], *texPos[face[i][j]->t3 - 1]));

				v_v.push_back(VERTEX(*position[face[i][j]->v1 - 1], *normal[face[i][j]->n1 - 1], *texPos[face[i][j]->t1 - 1]));
				v_v.push_back(VERTEX(*position[face[i][j]->v3 - 1], *normal[face[i][j]->n3 - 1], *texPos[face[i][j]->t3 - 1]));
				v_v.push_back(VERTEX(*position[face[i][j]->v4 - 1], *normal[face[i][j]->n4 - 1], *texPos[face[i][j]->t4 - 1]));
			}
			else
			{
				v_v.push_back(VERTEX(*position[face[i][j]->v1 - 1], *normal[face[i][j]->n1 - 1], *texPos[face[i][j]->t1 - 1]));
				v_v.push_back(VERTEX(*position[face[i][j]->v2 - 1], *normal[face[i][j]->n2 - 1], *texPos[face[i][j]->t2 - 1]));
				v_v.push_back(VERTEX(*position[face[i][j]->v3 - 1], *normal[face[i][j]->n3 - 1], *texPos[face[i][j]->t3 - 1]));
			}
		}
		if (face[i].size() > 0)
			v.push_back(v_v);
		v_v.clear();
	}

	for (size_t i = 0; i < position.size(); i++)	
		delete position[i];	
	for (size_t i = 0; i < normal.size(); i++)
		delete normal[i];	
	for (size_t i = 0; i < texPos.size(); i++)	
		delete texPos[i];	
	for (size_t i = 0; i < face.size(); i++)
		for (size_t j = 0; j < face[i].size(); j++)
			delete face[i][j];
	
	m.vertex = v;

	_calcTangents(&m);

	return m;
}

void MeshLoader::_calcTangents(MESH * m)
{
	for (size_t mS = 0; mS < m->vertex.size(); mS++)
		for (int i = 0; i < m->vertex[mS].size() - 2; i += 3)
		{
			int j = i + 1;
			int k = i + 2;

			DirectX::XMVECTOR v1 = DirectX::XMVectorSet(m->vertex[mS][j].pos.x, m->vertex[mS][j].pos.y, m->vertex[mS][j].pos.z, NULL);
			DirectX::XMVECTOR v2 = DirectX::XMVectorSet(m->vertex[mS][k].pos.x, m->vertex[mS][k].pos.y, m->vertex[mS][k].pos.z, NULL);
			DirectX::XMVECTOR v0 = DirectX::XMVectorSet(m->vertex[mS][i].pos.x, m->vertex[mS][i].pos.y, m->vertex[mS][i].pos.z, NULL);

			DirectX::XMVECTOR edge1 = DirectX::XMVectorSubtract(v1, v0);
			DirectX::XMVECTOR edge2 = DirectX::XMVectorSubtract(v2, v0);

			float deltaU1 = m->vertex[mS][j].uv.x - m->vertex[mS][i].uv.x;
			float deltaV1 = m->vertex[mS][j].uv.y - m->vertex[mS][i].uv.y;
			float deltaU2 = m->vertex[mS][k].uv.x - m->vertex[mS][i].uv.x;
			float deltaV2 = m->vertex[mS][k].uv.y - m->vertex[mS][i].uv.y;

			DirectX::XMFLOAT3 tangent;

			tangent.x = deltaV2 * DirectX::XMVectorGetX(edge1) - deltaV1 * DirectX::XMVectorGetX(edge2);
			tangent.y = deltaV2 * DirectX::XMVectorGetY(edge1) - deltaV1 * DirectX::XMVectorGetY(edge2);
			tangent.z = deltaV2 * DirectX::XMVectorGetZ(edge1) - deltaV1 * DirectX::XMVectorGetZ(edge2);

			DirectX::XMVECTOR vTangent;

			vTangent = DirectX::XMVector3Normalize(XMLoadFloat3(&tangent));

			for (int counter = 0; counter < 3; counter++)
			{
				int index = i + counter;
				m->vertex[mS][index].tangent.x = DirectX::XMVectorGetX(vTangent);
				m->vertex[mS][index].tangent.y = DirectX::XMVectorGetY(vTangent);
				m->vertex[mS][index].tangent.z = DirectX::XMVectorGetZ(vTangent);
			}
		}
}

MeshLoader::MeshLoader()
{
}

MeshLoader::~MeshLoader()
{
}

MESH MeshLoader::LoadMesh(const std::string & path)
{
	std::wstring wstr = std::wstring(path.begin(), path.end());

	return _loadMesh(wstr.c_str());
	
}
