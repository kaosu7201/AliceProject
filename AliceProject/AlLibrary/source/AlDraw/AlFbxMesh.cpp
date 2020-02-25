// --------------------------------------------------------------------------
/// @file 
/// @brief 
// 
// --------------------------------------------------------------------------
#include <iostream>
#include "AlLibrary.h"
#include "AlFbxMesh.h"

#include "mcfallib.h"

#ifdef _DEBUG
#pragma comment( lib, "debug/libfbxsdk-md.lib")
#else
#pragma comment( lib, "release/libfbxsdk.lib")
#endif

map<string,AlFbxMesh*> gFbxModel;

int LoadFbxMesh(const string szFileName, const string szName)
{
  gFbxModel[szName] = new AlFbxMesh();
  gFbxModel[szName]->Create(szFileName);
  
  return 0;
}

AlFbxMesh::AlFbxMesh()
{
}

AlFbxMesh::~AlFbxMesh()
{
}

void AlFbxMesh::Update()
{
}

void AlFbxMesh::Render()
{
	Platform *lpPlatform = Platform::GetInstance();

	//	���[�V���������݂���ꍇ��Skinning
	//if (motion[MotionName].NumFrame > 0) {
	//	Skinning();
	//}

	int start = 0;
	for (int m = 0; m < NumMesh; m++) {
		int iTexture = -1;
		int material_no = MeshMaterial[m];
		
		if (Textures[material_no] != -1) {
			iTexture = Textures[material_no];
		}
		//	�`��
		lpPlatform->DrawIndexed(start, MaterialFaces[m], Indices, Vertices, iTexture);
		start += MaterialFaces[m] * 3;
	}
}

void AlFbxMesh::Create(const string szFileName)
{
	FbxManager* manager = FbxManager::Create();

	FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(ios);
	FbxScene* scene = FbxScene::Create(manager, "");

	FbxImporter* importer = FbxImporter::Create(manager, "");
	importer->Initialize(szFileName.c_str(), -1, manager->GetIOSettings());
	importer->Import(scene);
	importer->Destroy();

	FbxGeometryConverter geometryConverter(manager);
	geometryConverter.Triangulate(scene, true);
	geometryConverter.RemoveBadPolygonsFromMeshes(scene);

	// TIPS:�}�e���A�����ƂɃ��b�V���𕪗�
	geometryConverter.SplitMeshesPerMaterial(scene, true);

	NumBone = 0;

	// �V�[���Ɋ܂܂�郁�b�V����
	NumMesh = scene->GetSrcObjectCount<FbxMesh>();

	//	���_���v�Z
	int work = 0;
	for (int m = 0; m < NumMesh; m++)
	{
		FbxMesh* mesh = scene->GetSrcObject<FbxMesh>(m);
		int num = mesh->GetPolygonVertexCount();
		work += num; // ���v���_��
	}

	//	���_�m��
	Vertices.reserve(work);
	Indices.reserve(work);
	Weights.reserve(work);

	NumVertices = 0;
	//	������
	for (int v = 0; v < work; v++)
	{
		Weights.push_back(WEIGHT());
		Weights[v].count = 0;
	}

	//�ގ����Ƃ̃|���S�����_��
	MaterialFaces = new int[NumMesh];
	MeshMaterial = new int[NumMesh];
	Textures = new int[NumMesh];
	NTextures = new int[NumMesh];
	for (int m = 0; m < NumMesh; m++)
	{
		Textures[m] = NULL;
		NTextures[m] = NULL;
	}

	//	���_�ǂݍ���
	for (int m = 0; m < NumMesh; m++)
	{
		FbxMesh* mesh = scene->GetSrcObject<FbxMesh>(m);
		int num = mesh->GetPolygonVertexCount();

		//	���_���ǂݍ���
		LoadPosition(mesh);		//	���W�ǂݍ���
		LoadNormal(mesh);		//	�@���ǂݍ���
		LoadUV(mesh);			//	�e�N�X�`��UV
		LoadVertexColor(mesh);	//	���_�J���[�ǂݍ���

		//	�C���f�b�N�X�ݒ�(�O�p�`����)
		for (int i = 0; i < num; i += 3)
		{
			Indices.push_back(i + 2 + NumVertices);
			Indices.push_back(i + 1 + NumVertices);
			Indices.push_back(i + 0 + NumVertices);
		}

		//	�{�[���ǂݍ���
		//LoadBone(mesh);

		//	���b�V���̎g�p�ގ��擾
		FbxLayerElementMaterial* LEM = mesh->GetElementMaterial();
		if (LEM != NULL)
		{
			//	�|���S���ɓ\���Ă���ގ��ԍ�
			int material_index = LEM->GetIndexArray().GetAt(0);
			//	���b�V���ގ���material_index�Ԗڂ��擾
			FbxSurfaceMaterial* material = mesh->GetNode()->GetSrcObject<FbxSurfaceMaterial>(material_index);
			LoadMaterial(m, material);
		}
		//	�g�p�ގ��ݒ�
		MeshMaterial[m] = m;
		MaterialFaces[m] = num / 3;

		NumVertices += num;
	}

	manager->Destroy();	//������Ă�ł�����FBX SDK�̃���������Y��͂Ȃ��͂��ł��B
}

//****************************************************************
//
//	���_���ǂݍ���
//
//****************************************************************
//------------------------------------------------
//	���W�ǂݍ���
//------------------------------------------------
void AlFbxMesh::LoadPosition(FbxMesh* mesh)
{
  int* index = mesh->GetPolygonVertices();
  FbxVector4* source = mesh->GetControlPoints();
  // ���b�V���̃g�����X�t�H�[��
  FbxVector4 T = mesh->GetNode()->GetGeometricTranslation(FbxNode::eSourcePivot);
  FbxVector4 R = mesh->GetNode()->GetGeometricRotation(FbxNode::eSourcePivot);
  FbxVector4 S = mesh->GetNode()->GetGeometricScaling(FbxNode::eSourcePivot);
  FbxAMatrix TRS = FbxAMatrix(T, R, S);
  //	�S���_�ϊ�
  for (int v = 0; v < mesh->GetControlPointsCount(); v++)
  {
    source[v] = TRS.MultT(source[v]);
  }

  // ���_���W�ǂݍ���
  int num = mesh->GetPolygonVertexCount();
  for (int v = 0; v < num; v++)
  {
    int vindex = index[v];

	Vertices.push_back(PolygonVertex());

    Vertices[v + NumVertices].Pos.x = (float)-source[vindex][0];
    Vertices[v + NumVertices].Pos.y = (float)-source[vindex][1];
    Vertices[v + NumVertices].Pos.z = (float)-source[vindex][2];

    Vertices[v + NumVertices].uv.x = 0;
    Vertices[v + NumVertices].uv.y = 0;
	//Vertices[v + NumVertices].color.Set(1.0f, 1.0f, 1.0f, 1.0f);
  }
}

//------------------------------------------------
//	�@���ǂݍ���
//------------------------------------------------
void AlFbxMesh::LoadNormal(FbxMesh* mesh)
{
  FbxArray<FbxVector4> normal;
  mesh->GetPolygonVertexNormals(normal);
  for (int v = 0; v < normal.Size(); v++)
  {
    Vertices[v + NumVertices].Normal.x = -(float)normal[v][0];
    Vertices[v + NumVertices].Normal.y = (float)normal[v][1];
    Vertices[v + NumVertices].Normal.z = (float)normal[v][2];
  }
}

//------------------------------------------------
//	�t�u�ǂݍ���
//------------------------------------------------
void AlFbxMesh::LoadUV(FbxMesh* mesh)
{
  FbxStringList names;
  mesh->GetUVSetNames(names);
  FbxArray<FbxVector2> uv;
  mesh->GetPolygonVertexUVs(names.GetStringAt(0), uv);
  for (int v = 0; v < uv.Size(); v++)
  {
    Vertices[v + NumVertices].uv.x = (float)(uv[v][0]);
    Vertices[v + NumVertices].uv.y = (float)(1.0 - uv[v][1]);
  }
}

//------------------------------------------------
//	���_�J���[�ǂݍ���
//------------------------------------------------
void AlFbxMesh::LoadVertexColor(FbxMesh* mesh)
{

  int vColorLayerCount = mesh->GetElementVertexColorCount();
  if (mesh->GetElementVertexColorCount() <= 0) return;
  //    ���_�J���[���C���[�擾
  FbxGeometryElementVertexColor* element = mesh->GetElementVertexColor(0);

  //  �ۑ��`���̎擾
  FbxGeometryElement::EMappingMode mapmode = element->GetMappingMode();
  FbxGeometryElement::EReferenceMode refmode = element->GetReferenceMode();

  //    �|���S�����_�ɑ΂���C���f�b�N�X�Q�ƌ`���̂ݑΉ�
  if (mapmode == FbxGeometryElement::eByPolygonVertex)
  {
    if (refmode == FbxGeometryElement::eIndexToDirect)
    {
      FbxLayerElementArrayTemplate<int>* index = &element->GetIndexArray();
      int indexCount = index->GetCount();
      for (int j = 0; j < indexCount; j++)
      {
        // FbxColor�擾
        FbxColor c = element->GetDirectArray().GetAt(index->GetAt(j));
        // DWORD�^�̃J���[�쐬        
        AlU32 color = ((AlU32)(c.mAlpha * 255) << 24) + ((AlU32)(c.mRed * 255) << 16) + ((AlU32)(c.mGreen * 255) << 8) + ((AlU32)(c.mBlue * 255));
		//Vertices[j + NumVertices].color.Set(c.mAlpha,c.mRed, c.mGreen, c.mBlue);
      }
    }
  }
}

//****************************************************************
//	�ގ��ǂݍ���
//****************************************************************
void AlFbxMesh::LoadMaterial(int index, FbxSurfaceMaterial * material)
{
  FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);

  //	�e�N�X�`���ǂݍ���
  const char* path = NULL;
  int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();
  if (fileTextureCount > 0)
  {
    FbxFileTexture* FileTex = prop.GetSrcObject<FbxFileTexture>(0);
    path = FileTex->GetFileName();
  }
  else
  {
    int numLayer = prop.GetSrcObjectCount<FbxLayeredTexture>();
    if (numLayer > 0)
    {
      FbxLayeredTexture* LayerTex = prop.GetSrcObject<FbxLayeredTexture>(0);
      FbxFileTexture* FileTex = LayerTex->GetSrcObject<FbxFileTexture>(0);
      path = FileTex->GetFileName();
    }
  }
  if (path == NULL) path = "Untitled.png";

  //  C:\\AAA\\BBB\\a.fbx  C:/AAA/BBB/a.fbx
  const char* name = &path[strlen(path)];
  for (int i = 0; i < (int)strlen(path); i++)
  {
    name--;
    if (name[0] == '/') { name++; break; }
    if (name[0] == '\\') { name++; break; }
  }
  char work[128];
  strcpy(work, FBXDir.c_str());		//"AAA/BBB/";
  strcat(work, "texture/");	//"AAA/BBB/texture/"
  strcat(work, name);			//"AAA/BBB/texture/a.png

  char filename[128];
  strcpy(filename, work);
  Textures[index] = TextureLoad(filename);

  //	�@���}�b�v�ǂݍ���
  strcpy(work, FBXDir.c_str());		//"AAA/BBB/";
  strcat(work, "texture/N");	//"AAA/BBB/texture/N"
  strcat(work, name);			//"AAA/BBB/texture/Na.png
  strcpy(filename, work);
  NTextures[index] = TextureLoad(filename);

}