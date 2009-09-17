#ifndef __G_H__
# define __G_H__



/*
// Chaines
*/

#include "GChar.h"			// Char
#include "GString.h"		// String
#include "GRegExp.h"		// RegExp

/*
//	CONTENEURS
*/

#include "GVector.hpp"		// Vecteur
#include "GMap.hpp"			// Map
#include "GMultiMap.hpp"	// Multimap

/*
// Temps
*/

#include "GDateTime.h"		// Date et Time
#include "GDate.h"			// Date 
#include "GTime.h"			// Time

/*
// Maths
*/

#include "G2dPoint.h"		// Point 2d
#include "G3dPoint.h"		// Point 3d
#include "GComplexe.h"		// Complexe
#include "GFraction.h"		// Fraction
#include "GIntegerList.h"

/*
// Fichiers et repertoires 
*/

#include "GFile.h"			// Fichier
#include "GFileInfos.h"		// Infos Fichier
#include "GDirectory.h"		// Repertoire

/* 
// Thread, Mutex, Semaphore
*/

#include "GThread.h"		// Thread
#include "GMutex.h"			// Mutex
#include "GSleep.h"			// Sleep

#include "GCryptography.h"



/*
//	Systeme
*/ 

#include "GDesktop.h"		// Bureau
#include "GMouse.h"			// Souris
#include "GProcessus.h"		// Proccessus
#include "GSystem.h"		// Systeme

/*
// Reseau
*/

#include "GSocketTcpClient.h"
#include "GSqlDatabase.h"
#include "GSmtp.h"
#include "GHttp.h"

/*
// Surcharge language
*/

#include "GException.h"		// Exception
#include "GWarning.h"		// Warning
#include "GConnect.h"

#endif
