#pragma once
// --------------------------------------------------------------------------
/// @file 
/// @brief FbxMesh �p Include 
// 
// --------------------------------------------------------------------------
#include <stdint.h>
#include <string>
#include <vector>
#include <map>

#include <fbxsdk.h>
#include "AlMath.h"
#include "AlColor.h"

using namespace std;

struct PolygonVertex
{
  AlVector3 Pos;
  AlVector3 Normal;
  AlVector2 uv;
  //AlColor4 color;
};

typedef PolygonVertex VERTEX;

class AlFbxMesh
{
protected:
	int NumMesh;
	int NumVertices;	//�S���_��
	int NumFaces;		//�S�|���S����
	vector<PolygonVertex> Vertices;
	vector<PolygonVertex> VerticesSrc;
	vector<AlU32> Indices;

	std::string FBXDir;
	int* MeshMaterial;
	int* MaterialFaces;
	int* Textures;
	int* NTextures;

	//	�{�[���֘A
	struct BONE
	{
		char	Name[128];
		//D3DXMATRIX	OffsetMatrix;
		//D3DXMATRIX	transform;
	};
	int NumBone;
	BONE Bone[256];

	void LoadBone(FbxMesh* mesh);

	//	�E�F�C�g�֘A
	struct WEIGHT
	{
		int count;
		int bone[4];
		float weight[4];
	};
	vector<WEIGHT> Weights;

	void LoadMaterial(int index, FbxSurfaceMaterial* material);

	void LoadPosition(FbxMesh* mesh);
	void LoadNormal(FbxMesh* mesh);
	void LoadUV(FbxMesh* mesh);
	void LoadVertexColor(FbxMesh* mesh);

	void OptimizeVertices();
public:
	AlFbxMesh();
	virtual ~AlFbxMesh();

	void Update();
	virtual void Render();

	void Create(const string szFileName);
};

int LoadFbxMesh(const string szFileName, const string szName);

extern map<string, AlFbxMesh*> gFbxModel;