
#include "GRegExp.h"

GStringMap GRegExp::_map = GStringMap();

void	GRegExp::AddDefinition(const GString &, const GString &)
{
	//this->_map[def] = value; 
}

void	GRegExp::DeleteDefinition(const GString &)
{
	//if (this->_map.ExistKey(def))
		//this->_map.EraseKey(def);
}

GRegExp::GRegExp(const GString &re)
{
	this->_regexp = re;
}

GRegExp::~GRegExp(void)
{

}

void	GRegExp::SetRegExp(const GString &re)
{
	this->_regexp = re;
}

void	GRegExp::SetPattern(const GString &re)
{
	this->_regexp = re;
}

GString	GRegExp::ReToPost(const GString &rere)
{
	GString re(rere);
	int nalt, natom;
	GString dst;
	struct 
	{
		int nalt;
		int natom;
	} paren[100], *p;
	p = paren;
	nalt = 0;
	natom = 0;
	for(unsigned int i = 0; i < re.Size(); ++i)
	{
		switch(re[i])
		{
		case '(':
			if(natom > 1)
			{
				--natom;
				dst += '.';
			}
			if(p >= paren+100)
				return NULL;
			p->nalt = nalt;
			p->natom = natom;
			p++;
			nalt = 0;
			natom = 0;
			break;
		case '|':
			if (natom == 0)
				return NULL;
			while(--natom > 0)
			{
				dst += '.';
			}
			nalt++;
			break;
		case ')':
			if(p == paren)
				return ("");
			if(natom == 0)
				return ("");
			while(--natom > 0)
				dst += '.';
			for(; nalt > 0; nalt--)
				dst += '|';
			--p;
			nalt = p->nalt;
			natom = p->natom;
			natom++;
			break;
		case '*':
		case '+':
		case '?':
			if(natom == 0)
				return NULL;
			dst += re[i];
			break;
		default:
			if(natom > 1){
				--natom;
				dst += '.';
			}
			dst += re[i];
			natom++;
			break;
		}
	}
	if(p != paren)
		return NULL;
	while(--natom > 0)
		dst += '.';
	for(; nalt > 0; nalt--)
		dst += '|';
	return (dst);
}




enum
{
	Match = 256,
	Split = 257
};


State matchstate = { Match };	/* matching state */
int nstate;

/* Allocate and initialize State */
State*
state(int c, State *out, State *out1)
{
	State *s;
	
	nstate++;
	s = (State *)malloc(sizeof(*s));
	s->lastlist = 0;
	s->c = c;
	s->out = out;
	s->out1 = out1;
	return s;
}

/*
 * A partially built NFA without the matching state filled in.
 * Frag.start points at the start state.
 * Frag.out is a list of places that need to be set to the
 * next state for this fragment.
 */
typedef struct Frag Frag;
typedef union Ptrlist Ptrlist;
struct Frag
{
	State *start;
	Ptrlist *out;
};

/* Initialize Frag struct. */
Frag
frag(State *start, Ptrlist *out)
{
	Frag n = { start, out };
	return n;
}

/*
 * Since the out pointers in the list are always 
 * uninitialized, we use the pointers themselves
 * as storage for the Ptrlists.
 */
union Ptrlist
{
	Ptrlist *next;
	State *s;
};

/* Create singleton list containing just outp. */
Ptrlist*
list1(State **outp)
{
	Ptrlist *l;
	
	l = (Ptrlist*)outp;
	l->next = NULL;
	return l;
}

/* Patch the list of states at out to point to start. */
void
patch(Ptrlist *l, State *s)
{
	Ptrlist *next;
	
	for(; l; l=next){
		next = l->next;
		l->s = s;
	}
}

/* Join the two lists l1 and l2, returning the combination. */
Ptrlist*
append(Ptrlist *l1, Ptrlist *l2)
{
	Ptrlist *oldl1;
	
	oldl1 = l1;
	while(l1->next)
		l1 = l1->next;
	l1->next = l2;
	return oldl1;
}


State	*GRegExp::PostToNFA(const GString &post)
{
	GString postfix(post);
	Frag stack[1000], *stackp, e1, e2, e;
	State *s;
	#define push(s) *stackp++ = s
	#define pop() *--stackp
	stackp = stack;
	for (unsigned int i = 0; i < postfix.Size(); ++i)
	{
		switch(postfix[i])
		{
		default:
			s = state(postfix[i], NULL, NULL);
			push(frag(s, list1(&s->out)));
			break;
		case '.':
			e2 = pop();
			e1 = pop();
			patch(e1.out, e2.start);
			push(frag(e1.start, e2.out));
			break;
		case '|':
			e2 = pop();
			e1 = pop();
			s = state(Split, e1.start, e2.start);
			push(frag(s, append(e1.out, e2.out)));
			break;
		case '?':	/* zero or one */
			e = pop();
			s = state(Split, e.start, NULL);
			push(frag(s, append(e.out, list1(&s->out1))));
			break;
		case '*':
			e = pop();
			s = state(Split, e.start, NULL);
			patch(e.out, s);
			push(frag(s, list1(&s->out1)));
			break;
		case '+':
			e = pop();
			s = state(Split, e.start, NULL);
			patch(e.out, s);
			push(frag(e.start, list1(&s->out1)));
			break;
		}
	}
	e = pop();
	if(stackp != stack)
		return NULL;

	patch(e.out, &matchstate);
	return e.start;
#undef pop
#undef push
}

typedef struct List List;

List l1, l2;
static int listid;

void addstate(List*, State*);
void step(List*, int, List*);


List*
startlist(State *start, List *l)
{
	l->n = 0;
	listid++;
	addstate(l, start);
	return l;
}

/* Check whether state list contains a match. */
int
ismatch(List *l)
{
	int i;

	for(i=0; i<l->n; i++)
		if(l->s[i] == &matchstate)
			return 1;
	return 0;
}

/* Add s to l, following unlabeled arrows. */
void
addstate(List *l, State *s)
{
	if(s == NULL || s->lastlist == listid)
		return;
	s->lastlist = listid;
	if(s->c == Split){
		/* follow unlabeled arrows */
		addstate(l, s->out);
		addstate(l, s->out1);
		return;
	}
	l->s[l->n++] = s;
}

/*
 * Step the NFA from the states in clist
 * past the character c,
 * to create next NFA state set nlist.
 */
void
step(List *clist, int c, List *nlist)
{
	int i;
	State *s;

	listid++;
	nlist->n = 0;
	for(i=0; i<clist->n; i++){
		s = clist->s[i];
		if(s->c == c)
			addstate(nlist, s->out);
	}
}

/* Run NFA to determine whether it matches s. */
int GEXPORTED
match(State *start, char *s)
{
	int c;
	List *clist, *nlist, *t;

	clist = startlist(start, &l1);
	nlist = &l2;
	for(; *s; s++){
		c = *s & 0xFF;
		step(clist, c, nlist);
		t = clist; clist = nlist; nlist = t;	/* swap clist, nlist */
	}
	return ismatch(clist);
}


GString	GRegExp::GStringToRe(const GString &t)
{
	return (t);
}

bool	GRegExp::Match(const GString &str)
{
	GString post = this->ReToPost(this->GStringToRe(str));
	State *start = this->PostToNFA(post.ToChar());
	l1.s = (State **)malloc(nstate*sizeof l1.s[0]);
	l2.s = (State **)malloc(nstate*sizeof l2.s[0]);
	if(match(start, str.ToChar()))
		return (true);
	return (false);
}

GVector<GStringList>	GRegExp::PregMatchAll(const GString &req)
{
	GVector<GStringList> res;
	GString str(req);
	while (true)
	{
		GStringList r = this->PregMatch(str);
		if (r.Size())
		{
			res.PushBack(r);
			int pos = str.Find(r[r.Size() - 1]);
			str = str.Substr(pos);
			continue;
		}
		break;
	}
	return (res);
}


