#include "Sprite.h"

IDirect3DVertexBuffer9 *Sprite::buf = 0;
std::list<Sprite*> Sprite::drawObjectList;
IDirect3DVertexDeclaration9 *Sprite::decl;
ID3DXEffect *Sprite::effect;


struct CUSTOM_VERTEX
{
	// ���_���W
	float x;
	float y;
	float z;

	// �e�N�X�`�����W
	float tu;
	float tv;
};


Sprite::Sprite(int screenWidth, int screenHeight) :
	tex(),
	polyW(128), polyH(128),
	pivotX(), pivotY(),
	posX(), posY(), posZ(),
	rad(),
	scaleX(1.0f), scaleY(1.0f),
	uvLeft(), uvTop(),
	uvW(1.0f), uvH(1.0f),
	alpha(1.0f),
	bActivity(true)
{
	setScreenSize(screenWidth, screenHeight);
}


Sprite::Sprite() :
	tex(),
	polyW(128), polyH(128),
	pivotX(), pivotY(),
	posX(), posY(), posZ(),
	rad(),
	scaleX(1.0f), scaleY(1.0f),
	uvLeft(), uvTop(),
	uvW(1.0f), uvH(1.0f),
	alpha(1.0f),
	bActivity(true)
{
	setScreenSize(640, 480);
}


Sprite::Sprite(const Sprite &r) {
	copy(r);
}


Sprite::~Sprite() {
	if (tex)
		tex->Release();
}





// �|���T�C�Y�w��
void Sprite::setSize(int w, int h) {
	polyW = w;
	polyH = h;
}


// �|���T�C�Y�w��
void Sprite::setPivot(float x, float y) {
  pivotX = x;
  pivotY = y;
}

void Sprite::getPivot(float * x, float * y)
{
	*x = pivotX;
	*y = pivotY;
}

void Sprite::setPos(float x, float y)
{
	posX = x;
	posY = y;
}

void Sprite::getPos(float * x, float * y)
{
	*x = posX;
	*y = posY;
}

void Sprite::setRotate(float deg)
{
	rad = deg;
}

float Sprite::getRotate()
{
	return rad;
}

void Sprite::setScale(float sx, float sy)
{
	scaleX = sx;
	scaleY = sy;
}

void Sprite::getScale(float * sx, float *sy)
{
	*sx = scaleX;
	*sy = scaleY;
}

void Sprite::setTexture(IDirect3DTexture9 * tex, bool isResize)
{
	if (tex)
		tex->AddRef();
	if (this->tex)
		this->tex->Release();
	this->tex = tex;

	if (isResize == true) {
		D3DSURFACE_DESC desc;
		tex->GetLevelDesc(0, &desc);
		setSize(desc.Width, desc.Height);
	}
}

IDirect3DTexture9 * Sprite::getTexture()
{
	return tex;
}

void Sprite::setUV(float left, float top, float width, float height)
{
	uvLeft = left;
	uvTop = top;
	uvW = width;
	uvH = height;
}

void Sprite::getUV_LT(float * left, float * top)
{
	*left = uvLeft;
	*top = uvTop;
}

void Sprite::getUV_WH(float * width, float * height)
{
	*width = uvW;
	*height = uvH;
}

void Sprite::setRGB(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

void Sprite::getRGB(float * r, float * g, float * b)
{
	*r = this->r;
	*g = this->g;
	*b = this->b;
}

void Sprite::setAlpha(float a)
{
	alpha = a;
}

float Sprite::getAlpha()
{
	return alpha;
}

void Sprite::setPriority(float z)
{
	priority = z;
}

float Sprite::getPriority()
{
	return priority;
}

void Sprite::setActivity(bool isActive)
{
	bActivity = isActive;
}

bool Sprite::getActivity()
{
	return bActivity;
}


// ���ʒ��_�o�b�t�@�쐬
void Sprite::begin_first()
{
	IDirect3DDevice9 *dev = DXDevice::GetDevice()->pDevice;
	if (buf == 0) {
		CUSTOM_VERTEX commonVtx[] = {
			{0.0f, 0.0f, 0.0f,   0.0f, 0.0f},  // 0
			{1.0f, 0.0f, 0.0f,   1.0f, 0.0f},  // 1
			{0.0f, 1.0f, 0.0f,   0.0f, 1.0f},  // 2
			{1.0f, 1.0f, 0.0f,   1.0f, 1.0f},  // 3
		};
		dev->CreateVertexBuffer(sizeof(commonVtx), 0, 0, D3DPOOL_MANAGED, &buf, 0);
		float *p = 0;
		if (buf) {
			buf->Lock(0, 0, (void**)&p, 0);
			memcpy(p, commonVtx, sizeof(commonVtx));
			buf->Unlock();
		}
	}

	// �V�F�[�_�쐬
	if (effect == 0) {
		DXShader Shader;
		effect = Shader.CreateShader("res/Shaders/Sprite.fx");
		if (effect == 0) {
			return;
		}
	}

	// ���_�錾�쐬
	if (decl == 0) {
		D3DVERTEXELEMENT9 elems[] = {
			{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
			{0, sizeof(float) * 3, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
			D3DDECL_END()
		};
		dev->CreateVertexDeclaration(elems, &decl);
	}
}


// ��Еt��
void Sprite::end_last() {
	if (buf)
		buf->Release();
}

void Sprite::setScreenSize(int w, int h)
{
	scW = w;
	scH = h;
}


// �`�惊�X�g�ɐς�
void Sprite::draw() {
	drawObjectList.push_back(this);
}


// �`�惊�X�g����C�ɕ`��
void Sprite::drawAll() {
	IDirect3DDevice9 *dev = DXDevice::GetDevice()->pDevice;
	if (buf == 0 || effect == 0 || decl == 0)
		return; // �`��s��

	// ���_�o�b�t�@�E���_�錾�ݒ�
	dev->SetStreamSource(0, buf, 0, sizeof(float) * 5);
	dev->SetVertexDeclaration(decl);

	// 2D�`��p�ˉe�ϊ��s��
	D3DXMATRIX proj;
	D3DXMatrixIdentity(&proj);
	proj._41 = -1.0f;
	proj._42 = 1.0f;

	// �V�F�[�_�J�n
	UINT numPass = 0;
	effect->SetTechnique("Tech");
	effect->Begin(&numPass, 0);
	effect->BeginPass(0);

	// �`�惊�X�g�ɓo�^����Ă���X�v���C�g����C�ɕ`�悷��
	std::list<Sprite*>::iterator it = drawObjectList.begin();
	for (; it != drawObjectList.end(); it++) {
		Sprite* sp = (*it);
		if (sp->bActivity == false)
			continue;

		// �ˉe�ϊ��s��쐬
		proj._11 = 2.0f / sp->scW;
		proj._22 = -2.0f / sp->scH;

		// ���[���h�ϊ��s��쐬
		D3DXMATRIX world, scale, rot;
		D3DXMatrixScaling(&world, (float)sp->polyW, (float)sp->polyH, 1.0f); // �|���S���T�C�Y��
		D3DXMatrixScaling(&scale, sp->scaleX, sp->scaleY, 1.0f);             // ���[�J���X�P�[��
		D3DXMatrixRotationZ(&rot, sp->rad);     // ��]
		world._41 = -sp->pivotX;                  // �s�{�b�g���I�t�Z�b�g
		world._42 = -sp->pivotY;
		world = world * scale * rot;
		world._41 += sp->posX + sp->pivotX;       // �s�{�b�g���I�t�Z�b�g
		world._42 += sp->posY + sp->pivotY;

		// �G�t�F�N�g��
		effect->SetMatrix("world", &world);
		effect->SetMatrix("proj", &proj);
		effect->SetTexture("tex", sp->tex);
		effect->SetFloat("uv_left", sp->uvLeft);
		effect->SetFloat("uv_top", sp->uvTop);
		effect->SetFloat("uv_width", sp->uvW);
		effect->SetFloat("uv_height", sp->uvH);
		effect->SetFloat("alpha", sp->alpha);
		effect->CommitChanges();
		dev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	effect->EndPass();
	effect->End();
}

void Sprite::copy(const Sprite & r)
{
	r.tex->AddRef();
	tex = r.tex;
	polyW = r.polyW;
	polyH = r.polyH;
	pivotX = r.pivotX;
	pivotY = r.pivotY;
	posX = r.posX;
	posY = r.posY;
	posZ = r.posZ;
	rad = r.rad;
	scaleX = r.scaleX;
	scaleY = r.scaleY;
	uvLeft = r.uvLeft;
	uvTop = r.uvTop;
	uvW = r.uvW;
	uvH = r.uvH;
	alpha = r.alpha;
	scW = r.scW;
	scH = r.scH;
	bActivity = r.bActivity;
}


// �`�惊�X�g�N���A
void Sprite::clearDrawList() {
	drawObjectList.clear();
}