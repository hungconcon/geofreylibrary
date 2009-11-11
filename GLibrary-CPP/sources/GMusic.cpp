
#include "GMusic.h"

GMusic::GMusic(void) : _playing(false)
{
#if defined (GWIN)
    this->_openParam.lpstrElementName = NULL;
#endif
}

GMusic::GMusic(const GMusic &m) : _playing(false)
{
	this->_file = m._file;
#if defined (GWIN)
#if defined (UNICODE)
	this->_openParam.lpstrElementName = this->_file.ToWChar_t();
#else
	char	*tmp = this->_file.ToChar();
    this->_openParam.lpstrElementName = tmp;
#endif
#endif
}

GMusic::GMusic(const GString &Name) : _file(Name), _playing(false)
{
#if defined (GWIN)
#if defined (UNICODE)
	this->_openParam.lpstrElementName = this->_file.ToWChar_t();
#else
	char	*tmp = this->_file.ToChar();
    this->_openParam.lpstrElementName = tmp;
#endif
#endif
}

GMusic::~GMusic(void)
{
	this->Stop();
#if defined (GWIN)
	if (this->_openParam.lpstrElementName)
		delete[] this->_openParam.lpstrElementName;
#endif
}

bool	GMusic::Play(void)
{
#if defined (GWIN)
	if (!this->_playing && this->_openParam.lpstrElementName)
	{
		MCI_STATUS_PARMS	StatusParam;
		MCI_PLAY_PARMS		PlayParam;
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD_PTR)&this->_openParam);
		StatusParam.dwItem = MCI_STATUS_LENGTH;
		mciSendCommand(this->_openParam.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&StatusParam);
		PlayParam.dwFrom = 0;
		PlayParam.dwTo = (DWORD)StatusParam.dwReturn;
		StatusParam.dwItem = MCI_STATUS_READY;
		mciSendCommand(this->_openParam.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&StatusParam);
		if (StatusParam.dwReturn != NULL)
			mciSendCommand(this->_openParam.wDeviceID, MCI_PLAY, 0, (DWORD_PTR)&PlayParam);
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
	if (this->_openParam.lpstrElementName)
	{
		if (this->_playing == false)
		{
			mciSendCommand(this->_openParam.wDeviceID, MCI_CLOSE, 0, 0);
			return (false);
		}
		mciSendCommand(this->_openParam.wDeviceID, MCI_PAUSE, 0, 0);
		this->_playing = false;
		return (true);
	}
	return (false);
#else
	return (false);
#endif
	return (true);
}

bool	GMusic::Stop(void)
{
#if defined (GWIN)
	if (this->_playing && this->_openParam.lpstrElementName)
	{
		mciSendCommand(this->_openParam.wDeviceID, MCI_CLOSE, 0, 0);
		this->_playing = false;
		return (true);
	}
#else
#endif
	return (false);
}

void	GMusic::SetMusic(const GString &MusicPath)
{
	if (!this->_playing)
	{
		this->_file = MusicPath;
		#if defined (GWIN)
		#if defined (UNICODE)
			this->_openParam.lpstrElementName = this->_file.ToWChar_t();
		#else
			char	*tmp = this->_file.ToChar();
			this->_openParam.lpstrElementName = tmp;
		#endif
		#endif
	}
}

bool	GMusic::IsPlayed(void) const
{
	return (this->_playing);
}