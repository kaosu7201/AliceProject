#pragma once

// --------------------------------------------------------------------------
/// @brief ボタンの定義
// --------------------------------------------------------------------------
enum AlControllerButton
{
  GCBTN_SELECT,   ///<  セレクトボタン
  GCBTN_START,    ///<  スタートボタン
  GCBTN_L_UP,     ///<  方向キー ↑ボタン
  GCBTN_L_LEFT,   ///<  方向キー ←ボタン
  GCBTN_L_DOWN,   ///<  方向キー ↓ボタン
  GCBTN_L_RIGHT,  ///<  方向キー →ボタン
  GCBTN_L1,       ///<  Ⅼボタン
  GCBTN_L2,       ///<  Lボタン
  GCBTN_R1,       ///<  Rボタン
  GCBTN_R2,       ///<  Rボタン
  GCBTN_R_UP,     ///<  △ボタン
  GCBTN_R_LEFT,   ///<  ○ボタン
  GCBTN_R_DOWN,   ///<  ×ボタン
  GCBTN_R_RIGHT,  ///<  □ボタン

  GCBTN_UP = GCBTN_L_UP,			///< 十字キー設定  
  GCBTN_LEFT = GCBTN_L_LEFT,		///< 十字キー設定  
  GCBTN_DOWN = GCBTN_L_DOWN,		///< 十字キー設定  
  GCBTN_RIGHT = GCBTN_L_RIGHT,		///< 十字キー設定  

  GCBTN_OK = GCBTN_R_DOWN,		///< 決定ボタン 
  GCBTN_CANCEL = GCBTN_R_RIGHT,		///< キャンセルボタン

  GCBTN_NUM,
  GCBTN_NONE,
};
typedef AlControllerButton GAMEPAD_BUTTON;

// --------------------------------------------------------------------------
/// @brief 取得タイプ
// --------------------------------------------------------------------------
enum STATE_TYPE
{
  PRESENT,    //!<現在の状態を取得する
  JUST_DOWN,    //!<押された直後かを取得する
  JUST_UP,        //!<離された直後かを取得する
};


class _IController
{
public:
  virtual ~_IController() {}
  virtual void UpDate() = 0;

  //入力処理
  virtual bool GetButtonState(AlControllerButton ctrl, STATE_TYPE get_type = PRESENT) = 0;
  virtual void GetRelativePos(double &x, double &y) = 0;
  virtual void GetAbsScreenPos(double &x, double &y) = 0;
  virtual void GetWheelMove(double &z) = 0;
  //キーコンフィグ
  virtual void SetDefault() = 0;
};

typedef _IController *IController;