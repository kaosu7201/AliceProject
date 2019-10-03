#include "../DirectX11Manager.h"


DXInput *DXInput::lpInput = NULL;

DXInput::DXInput()
{
	lpInput = this;
}


DXInput::~DXInput()
{
}


BOOL WINAPI DIEnumDevCallback(
	LPCDIDEVICEINSTANCE lpddi,
	LPVOID pvRef
)
{
	// ��2������DIDEVICEINSTANCE�\���̂�vecor STL���Ƃ��܂�
	vector<DIDEVICEINSTANCE>* ptr = (vector<DIDEVICEINSTANCE>*)pvRef;
	DIDEVICEINSTANCE tmp = *lpddi;

	// �z��Ɋi�[
	ptr->push_back(tmp);

	// �񋓂𑱂���ꍇ��DIENUM_CONTINUE�A�~�߂�ꍇ��DIENUM_STOP���w��
	// �S�Ă̗񋓂��I������Ǝ����I�ɃR�[���o�b�N���I������̂ŁA
	// �~�߂闝�R���������DIENUM_CONTINUE�ɂ���B
	return DIENUM_CONTINUE;
}



// �f�o�C�X�̃I�u�W�F�N�g��񋓂���R�[���o�b�N�֐��istatic�錾�j
BOOL WINAPI DIEnumDevObjCallback(
	LPCDIDEVICEOBJECTINSTANCE lpddoi,
	LPVOID pvRef
)
{
	// ��2������vector<DIDEVICEOBJECTINSTANCE>�ւ̃|�C���^�Ɍ^�ϊ�
	vector<DIDEVICEOBJECTINSTANCE> *tmp = (vector<DIDEVICEOBJECTINSTANCE>*)pvRef;

	// �z��ɃI�u�W�F�N�g�̏����i�[
	tmp->push_back(*lpddoi);

	// �񋓂͑S�ďI���Ύ����I�ɏI������̂ŁA
	// �񋓂�������
	return DIENUM_CONTINUE;
}


bool DXInput::CreateInput()
{
  HWND hWnd = g_DX11Manager.gethWd();
	HINSTANCE hInst = GetModuleHandle(0);
	HRESULT hr;
	hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pDInput, NULL);
	if (FAILED(hr)) {
		return false;
	}
	//--------------------------------------------------------------------------------------
	//�L�[�{�[�h�擾
	//--------------------------------------------------------------------------------------
	//�L�[�{�[�h
	pDInput->CreateDevice(GUID_SysKeyboard, &m_KeyDevice, NULL);
	//�f�o�C�X�̃t�H�[�}�b�g�E�������x����ݒ�
	m_KeyDevice->SetDataFormat(&c_dfDIKeyboard);
	m_KeyDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_KeyDevice->Acquire();

	//--------------------------------------------------------------------------------------
	//�}�E�X�擾
	//--------------------------------------------------------------------------------------
	//�}�E�X
	pDInput->CreateDevice(GUID_SysMouse, &m_MouseDevice, NULL);
	//�f�o�C�X�̃t�H�[�}�b�g�E�������x����ݒ�
	m_MouseDevice->SetDataFormat(&c_dfDIMouse);
	m_MouseDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_MouseDevice->Acquire();
  //--------------------------------------------------------------------------------------
  //�p�b�h�擾
  //--------------------------------------------------------------------------------------
  //�p�b�h
	return true;
}
