#pragma once
class ApplicationBase
{
public:
  ApplicationBase();
  virtual ~ApplicationBase();

  virtual bool CallInitialize();
  virtual bool CallTerminate();
  virtual bool CallInput();
  virtual bool CallProcess();
  virtual bool CallRender();

protected:
  virtual bool Initialize() = 0;
  virtual bool Terminate() = 0;
  virtual bool Input() = 0;
  virtual bool Process() = 0;
  virtual bool Render() = 0;

  static ApplicationBase* GetInstance() { return _lpInstance; }
  static	ApplicationBase	*_lpInstance;
};

