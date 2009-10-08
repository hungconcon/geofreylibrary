#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN64) | defined (_WIN64) | defined (__WIN64)


#include "GRegistry.h"
    
GRegistry::GRegistry(void)
{
     this->_key = NULL;
}

GRegistry::GRegistry(const GString &strClef, int ModeOuverture, HKEY hRacine)
{
	this->_key = NULL;
    LONG lResult;
	char	*tmp(strClef.ToChar());
	lResult = RegCreateKeyEx(hRacine, tmp, 0, NULL, REG_OPTION_NON_VOLATILE, ModeOuverture, NULL, &this->_key, NULL);
	delete[] tmp;
}
    
GRegistry::~GRegistry(void)
{
	if (this->_key)
		RegCloseKey(this->_key);
}
    
bool	GRegistry::OpenKey(const GString &strClef, int ModeOuverture, HKEY hRacine)
{
     if (this->_key)
		RegCloseKey(this->_key);
	 char	*tmp(strClef.ToChar());
     RegOpenKeyEx(hRacine, tmp, NULL, ModeOuverture, &this->_key);
	 delete[] tmp;
     return (this->_key != NULL);
}
    
bool	GRegistry::CloseKey(void)
{
     if (this->_key)
		RegCloseKey(this->_key);
     this->_key = NULL;
     return (true);
}
    
bool	GRegistry::IsKeyOpen(void) const
{
     return (this->_key != NULL);
}
    
bool	GRegistry::CreateKey(const GString &strClef, int ModeOuverture, HKEY hRacine)
{
     LONG lResult = -1;
     if(this->_key)
		RegCloseKey(this->_key);
	 char	*tmp(strClef.ToChar());
     RegCreateKeyEx(hRacine, tmp, 0, NULL, REG_OPTION_NON_VOLATILE, ModeOuverture, NULL, &this->_key, NULL);
	 delete[] tmp;
     return (this->_key != NULL);
}
    
bool	GRegistry::DeleteKey(void)
{
     LONG lResult = -1;
     if(this->_key)
		lResult = RegDeleteKey(this->_key,NULL);
     return (lResult == ERROR_SUCCESS);
}
    
bool	GRegistry::SaveKey(const GString& strNomFichier)
{
     LONG lResult = -1;
     if	(this->_key)
	 {
		char	*tmp = strNomFichier.ToChar();
		lResult = RegSaveKey(this->_key, tmp, NULL);
		delete[] tmp;
	 }
     return (lResult == ERROR_SUCCESS);
}

bool	GRegistry::WriteStringValue(const GString &strNomValeur, const GString& strValeur)
{
    LONG lResult = -1;
	if (this->_key)
	{
		char	*tmp = strNomValeur.ToChar();
		char	*str = strValeur.ToChar();
		lResult = RegSetValueEx(this->_key, tmp, 0,REG_SZ,(LPBYTE)str, strValeur.Size() + 1);
		delete[] str;
		delete[] tmp;
	}
     return (lResult == ERROR_SUCCESS);
}
    
bool	GRegistry::WriteIntValue(const GString& strNomValeur, int iValeur)
{
	LONG lResult = -1;
    GString strValeur = iValeur;
    if (this->_key)
	{
		char	*name = strNomValeur.ToChar();
		char	*val = strValeur.ToChar();
		lResult = RegSetValueEx(this->_key, name, 0, REG_SZ, (LPBYTE)val, strValeur.Size() + 1);
		delete[] name;
		delete[] val;
	}
     return (lResult==ERROR_SUCCESS);
}
    
bool	GRegistry::WriteDoubleValue(const GString& strNomValeur, double dValeur)
{
	LONG lResult = -1;
    GString strValeur = dValeur;
    if (this->_key)
	{
		char	*name = strNomValeur.ToChar();
		char	*val = strValeur.ToChar();
		lResult = RegSetValueEx(this->_key, name, 0, REG_SZ, (LPBYTE)val, strValeur.Size() + 1);
		delete[] name;
		delete[] val;
	}
     return (lResult == ERROR_SUCCESS);
}
    
bool	GRegistry::WriteBoolValue(const GString& strNomValeur, BOOL bValeur)
{
	LONG lResult = -1;
    GString strValeur;
    if (bValeur)
	    strValeur = "TRUE";
    else
	    strValeur = "FALSE";
    if (this->_key)
	{
		char	*tmp = strNomValeur.ToChar();
		char	*tmp1 = strValeur.ToChar();
		lResult = RegSetValueEx(this->_key, tmp, 0, REG_SZ,(LPBYTE)tmp1, strValeur.Size() + 1);
		delete[] tmp;
		delete[] tmp1;
	}
    return (lResult == ERROR_SUCCESS);
}
    
GString	GRegistry::ReadStringValue(const GString& strNomValeur)
{
	GString strResult;
    char strValeur[MAX_REGVALEUR];
    DWORD dwTailleValeur = MAX_REGVALEUR;
    if (this->_key)
    {
		char	*tmp(strNomValeur.ToChar());
		RegQueryValueEx(this->_key, tmp, NULL, NULL, (LPBYTE)strValeur,&dwTailleValeur);
		delete[] tmp;
		strResult = strValeur;
    }
    return (strResult);
}
    
int	GRegistry::ReadIntValue(const GString& strNomValeur)
{
     GString strResult;
     char strValeur[MAX_REGVALEUR];
     DWORD dwTailleValeur = MAX_REGVALEUR;
     if (this->_key)
     {
		char	*tmp(strNomValeur.ToChar());
		RegQueryValueEx(this->_key, tmp, NULL, NULL, (LPBYTE)strValeur,&dwTailleValeur);
		delete[] tmp;
		strResult = strValeur;
     }
     return (strResult.ToInt());
}
    
double	GRegistry::ReadDoubleValue(const GString& strNomValeur)
{
	GString strResult;
    char strValeur[MAX_REGVALEUR];
    DWORD dwTailleValeur = MAX_REGVALEUR;
    if (this->_key)
    {
		char	*tmp(strNomValeur.ToChar());
		RegQueryValueEx(this->_key, tmp, NULL, NULL, (LPBYTE)strValeur,&dwTailleValeur);
		delete[] tmp;
		strResult = strValeur;
    }
    return (strResult.ToDouble());
}
    
bool GRegistry::ReadBoolValue(const GString& strNomValeur)
{
	bool bResult = FALSE;
    GString strResult;
    char strValeur[6];
    DWORD dwTailleValeur = 6;
    if(this->_key)
    {
		char	*tmp(strNomValeur.ToChar());
		RegQueryValueEx(this->_key, tmp, NULL, NULL, (LPBYTE)strValeur,&dwTailleValeur);
		delete[] tmp;
		strResult = strValeur;
		bResult = (strResult==GString("TRUE"));
    }
    return bResult;
}
    
bool GRegistry::DeleteValue(const GString& strNomValeur)
{
     LONG lResult = -1;
     if (this->_key)
	 {
		char	*tmp(strNomValeur.ToChar());
		lResult = RegDeleteValue(this->_key, tmp);
		delete[] tmp;
	 }
     return (lResult==ERROR_SUCCESS);
}
    
int	GRegistry::GetNbValue(void)
{
    int iNbValeurs;
    DWORD dwNbValeur = -1;
    if(this->_key)
		RegQueryInfoKey(this->_key,NULL,NULL,NULL,NULL,NULL,NULL,&dwNbValeur,NULL,NULL,NULL,NULL);
    iNbValeurs = (int)dwNbValeur;
    return iNbValeurs;
}
    
int GRegistry::GetNbSubKey(void)
{
    int iNbSousClefs = -1;
    DWORD dwNbSousClefs = -1;
    if(this->_key)
		RegQueryInfoKey(this->_key,NULL,NULL,NULL,&dwNbSousClefs,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
    iNbSousClefs = (int)dwNbSousClefs;
    return iNbSousClefs;
}
    
GString GRegistry::GetSubKeyName(int iIndex)
{
    GString strSousClef;
    char sSousClef[MAX_REGCLEF];
    DWORD dwTaille = MAX_REGCLEF;
    if (this->_key)
    {
		if (iIndex<this->GetNbSubKey())
		{
			RegEnumKeyEx(this->_key,(DWORD)iIndex,sSousClef,&dwTaille,NULL,NULL,NULL,NULL);
			strSousClef = sSousClef;
		}
	}
    return (strSousClef);
}
    
GString GRegistry::GetValueName(int iIndex)
{
	GString strValeur;
    char sValeur[MAX_REGVALEUR];
    DWORD dwTaille = MAX_REGVALEUR;
    if(this->_key)
    {
		if(iIndex < this->GetNbValue())
		{
			RegEnumValue(this->_key,(DWORD)iIndex,sValeur,&dwTaille,0,NULL,NULL,NULL);
			strValeur = sValeur;
		}
    }
    return (strValeur);
}
#endif
