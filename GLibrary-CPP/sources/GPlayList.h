
#ifndef __GPLAYLIST_H__
# define __GPLAYLIST_H__

#include "GExport.h"
#include "GVector.hpp"
#include "GString.h"
#include "GMusic.h"
#include "GFileInfos.h"

class GEXPORTED GPlayList
{
	public:
		GPlayList(void);
		~GPlayList(void);

		void	Play(void);
		void	Pause(void);
		void	Stop(void);
		void	Next(void);
		void	Previous(void);
		void	AddSong(const GString &);
		void	AddSong(const GFileInfos &);
		void	Shuffle(void);
		void	DeleteSong(const GString &);
		void	DeleteSong(const GFileInfos &);
		void	SaveToM3U(void);

	private:
		GStringList	_playList;



};

#endif