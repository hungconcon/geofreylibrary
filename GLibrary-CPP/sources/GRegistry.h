
#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN64) | defined (_WIN64) | defined (__WIN64)

#ifndef __GREGISTRY_H__
# define __GREGISTRY_H__

#include "windows.h"

#define MAX_REGCLEF 255
#define MAX_REGVALEUR 16383

#include <windows.h>
#include "GString.h"

class GRegistry
{
	public:
		enum Mode
		{
		Lecture = KEY_READ,
		Ecriture = KEY_WRITE,
		Total = KEY_ALL_ACCESS
		};

	GRegistry(void);
	GRegistry(const GString& , int ModeOuverture = GRegistry::Lecture, HKEY hRacine = HKEY_CURRENT_USER);
	~GRegistry(void);

	bool	OpenKey(const GString& strClef, int ModeOuverture = GRegistry::Lecture, HKEY hRacine = HKEY_CURRENT_USER);
	bool	CreateKey(const GString& strClef, int ModeOuverture = GRegistry::Ecriture, HKEY hRacine = HKEY_CURRENT_USER);
	bool	CloseKey(void);
	bool	IsKeyOpen(void) const;
	bool	DeleteKey(void);
	bool	SaveKey(const GString& strNomFichier);
	int		GetNbSubKey(void);
	GString GetSubKeyName(int iIndex);
	int		GetNbValue(void);
	GString GetValueName(int iIndex);
	GString ReadStringValue(const GString& strNomValeur);
	int		ReadIntValue(const GString& strNomValeur);
	double	ReadDoubleValue(const GString& strNomValeur);
	bool	ReadBoolValue(const GString& strNomValeur);
	bool	WriteStringValue(const GString& strNomValeur, const GString& strValeur);
	bool	WriteIntValue(const GString& strNomValeur, int iValeur);
	bool	WriteDoubleValue(const GString& strNomValeur, double dValeur);
	bool	WriteBoolValue(const GString& strNomValeur, BOOL bValeur);
	bool	DeleteValue(const GString& strNomValeur);

	private:
		HKEY	_key;
}; 

#endif

#endif