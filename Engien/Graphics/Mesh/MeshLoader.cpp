#include "MeshLoader.h"


#include <iostream>
std::vector<std::vector<VERTEX>> MeshLoader::_loadMesh(const wchar_t * path)
{
	std::vector <DirectX::XMFLOAT4*>	position;
	std::vector <DirectX::XMFLOAT3*>	normal;
	std::vector <DirectX::XMFLOAT2*>	texPos;
	std::vector <std::vector<FACE *>>	face;

	std::wifstream in(path);

	bool firstObject = false;

	if (!in.is_open())
	{
		std::cout << "Didn't find file" << std::endl;
		return std::vector<std::vector<VERTEX>>();

	}
	//std::vector<std::wstring*> input;
	DirectX::XMFLOAT4 tmp;
	FACE * f;
	std::vector<FACE *> f_v;
	wchar_t input[256];
	while (!in.eof())
	{
		in.getline(input, 256);
		//input.push_back(new std::wstring(buff));
	
	//for (size_t i = 0; i < input.size(); i++)
	//{
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
		else if (input[0] == L'g' && input[1] == L' ') {
			if (f_v.size() > 0)
			{
				face.push_back(f_v);
				f_v.clear();
			}
			
		}
		else if (input[0] == L'f' && input[1] == L' ' && std::count(&input[0], &input[256], '/') == 8)
		{
			f = new FACE();
			int gh = std::count(&input[0], &input[256], '/');
			swscanf_s(input, L"%*s %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &f->v1, &f->t1, &f->n1, &f->v2, &f->t2, &f->n2, &f->v3, &f->t3, &f->n3, &f->v4, &f->t4, &f->n4);
			f->quad = true;
			f_v.push_back(f);
		}
		else if (input[0] == L'f' && input[1] == L' ' && std::count(&input[0], &input[256], '/') == 6)
		{
			f = new FACE();
			int gh = std::count(&input[0], &input[256], '/');
			swscanf_s(input, L"%*s %d/%d/%d %d/%d/%d %d/%d/%d", &f->v1, &f->t1, &f->n1, &f->v2, &f->t2, &f->n2, &f->v3, &f->t3, &f->n3);
			f->quad = false;
			f_v.push_back(f);
		}
		for (size_t i = 0; i < 256; i++)
		{
			input[i] = NULL;
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
	
	return v;
}

MeshLoader::MeshLoader()
{
}


MeshLoader::~MeshLoader()
{
}

std::vector<std::vector<VERTEX>> MeshLoader::LoadMesh(const std::string & path)
{
	std::wstring wstr = std::wstring(path.begin(), path.end());

	return _loadMesh(wstr.c_str());
	
}
