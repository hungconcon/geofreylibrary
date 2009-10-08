
#include "GMusic.h"

GMusic::GMusic(void) : _playing(false)
{
}

GMusic::GMusic(const GMusic &m) : _playing(false)
{
	this->_file = m._file;
#if defined (GWIN)
	char	*tmp = this->_file.ToChar();
    this->OpenParam.lpstrElementName = tmp;
#endif
}

GMusic::GMusic(const GString &Name) : _file(Name), _playing(false)
{
#if defined (GWIN)
	char	*tmp = this->_file.ToChar();
    this->OpenParam.lpstrElementName = tmp;
#endif
}

GMusic::~GMusic(void)
{
	this->Stop();
#if defined (GWIN)
	delete[] this->OpenParam.lpstrElementName;
#endif
}

bool	GMusic::Play(void)
{
#if defined (GWIN)
	if (!this->_playing)
	{
		MCI_STATUS_PARMS	StatusParam;
		MCI_PLAY_PARMS		PlayParam;
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD_PTR)&OpenParam);
		StatusParam.dwItem = MCI_STATUS_LENGTH;
		mciSendCommand(OpenParam.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&StatusParam);
		PlayParam.dwFrom = 0;
		PlayParam.dwTo = (DWORD)StatusParam.dwReturn;
		StatusParam.dwItem = MCI_STATUS_READY;
		mciSendCommand(OpenParam.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&StatusParam);
		if (StatusParam.dwReturn != NULL)
			mciSendCommand(OpenParam.wDeviceID, MCI_PLAY, 0, (DWORD_PTR)&PlayParam);
		else
			return (false);
		this->_playing = true;
		return (true);
	}
#else
#endif
	return (false);
}

bool	GMusic::Pause(void)
{
#if defined (GWIN)
    if (this->_playing == false)
	{
        mciSendCommand(OpenParam.wDeviceID, MCI_CLOSE, 0, 0);
		return (false);
	}
	mciSendCommand(OpenParam.wDeviceID, MCI_PAUSE, 0, 0);
	this->_playing = false;
	return (true);
#else
	return (false);
#endif
	return (true);
}

bool	GMusic::Stop(void)
{
#if defined (GWIN)
	if (this->_playing)
	{
		mciSendCommand(OpenParam.wDeviceID, MCI_CLOSE, 0, 0);
		this->_playing = false;
		return (true);
	}
#else
#endif
	return (false);
}
