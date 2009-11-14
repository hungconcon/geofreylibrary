#include "GPlayList.h"

GPlayList::GPlayList(void)
{

}

GPlayList::~GPlayList(void)
{

}

void	GPlayList::AddSong(const GString &Song)
{
	this->_playList.PushBack(Song);
}

void	GPlayList::DeleteSong(const GString &Song)
{
	this->_playList.Delete(Song);
}

