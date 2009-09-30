
#include "GMessageBox.h"

void		GMessageBox::Error(const GString &Title, const GString &Texte)
{
#if defined (WIN32) | defined (_WIN32) |  defined (__WIN32) | defined (WIN) | defined (WIN64) | defined (__WIN64)
	char	*txt = Texte.ToChar();
	char	*ttl = Title.ToChar();
	MessageBox(NULL, txt, ttl, NULL);
	delete[] txt;
	delete[] ttl;
#endif
}
