#include "MeshLoader.h"


#include <iostream>
std::vector<VERTEX> MeshLoader::_loadMesh(const wchar_t * path)
{
	std::vector <DirectX::XMFLOAT4*> position;
	std::vector <DirectX::XMFLOAT3*> normal;
	std::vector <DirectX::XMFLOAT2*> texPos;

	std::wifstream in(path);

	if (!in.is_open())
	{
		std::cout << "Didn't find file" << std::endl;
		return std::vector<VERTEX>();

	}
	std::vector<std::wstring*> input;
	wchar_t buff[256];
	while (!in.eof())
	{
		in.getline(buff, 256);
		input.push_back(new std::wstring(buff));
	}
	in.close();
	DirectX::XMFLOAT4 tmp;
	for (size_t i = 0; i < input.size(); i++)
	{
		if ((*input[i])[0] == L'#') {}
		else if ((*input[i])[0] == L'v' && (*input[i])[1] == L' ') {
			swscanf_s(input[i]->c_str(), L"%*s %f %f %f", &tmp.x, &tmp.y, &tmp.z);
			position.push_back(new DirectX::XMFLOAT4(tmp.x, tmp.y, tmp.z, 1.0f));
		}
		else if ((*input[i])[0] == L'v' && (*input[i])[1] == L't') {
			swscanf_s(input[i]->c_str(), L"%*s %f %f", &tmp.x, &tmp.y);
			texPos.push_back(new DirectX::XMFLOAT2(tmp.x, tmp.y));
		}
		else if ((*input[i])[0] == L'v' && (*input[i])[1] == L'n') {
			swscanf_s(input[i]->c_str(), L"%*s %f %f %f", &tmp.x, &tmp.y, &tmp.z);
			normal.push_back(new DirectX::XMFLOAT3(tmp.x, tmp.y, tmp.z));
		}
	}

	for (size_t i = 0; i < input.size(); i++)
	{
		delete input[i];
	}

	return std::vector<VERTEX>();
}

MeshLoader::MeshLoader()
{
}


MeshLoader::~MeshLoader()
{
}

std::vector<VERTEX> MeshLoader::LoadMesh(const std::string & path)
{
	std::wstring wstr = std::wstring(path.begin(), path.end());

	return _loadMesh(wstr.c_str());
	
}
