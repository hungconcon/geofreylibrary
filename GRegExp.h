
#ifndef __GREGEXP_H__
# define __GREGEXP_H__

#include "GString.h"
#include "GVector.hpp"
#include "GExport.h"
#include "GMap.hpp"

struct State
{
	int c;
	State *out;
	State *out1;
	int lastlist;
};

struct List
{
	State **s;
	int n;
};

class GEXPORTED GRegExp
{
	public:
		GRegExp(const GString &);
		~GRegExp(void);

		void					AddDefinition(const GString &, const GString &);
		void					DeleteDefinition(const GString &);
		void					SetRegExp(const GString &);
		void					SetPattern(const GString &);
		bool					Match(const GString &);
		GVector<GStringList>	PregMatchAll(const GString &);
		GStringList				PregMatch(const GString &);
	private:
		static GStringMap	_map;		
		GString				_regexp;

		GString				GStringToRe(const GString &);
		GString				ReToPost(const GString &);
		State				*PostToNFA(const GString &);

};


#endif


