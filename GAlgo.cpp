
#include "GAlgo.h"

int		GAlgo::PGCD(int a, int b)
{
	if (a < b)
	{
		int c = a;
		a = b;
		b = c;
	}
	while (true)
	{
		int reste = (int)(a / b);
		reste = a - b * reste;
		if (reste == 0)
			return (b);
		a = b;
		b = reste;		
	}
	return (1);
}

GStringList		GAlgo::GStringToArray(const GString &s)
{
	GString str(s);
	GStringList result;
	int save = -1;
	for (unsigned int i = 0; i < str.Size(); ++i)
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' || str[i] == '%' || str[i] == '(' || str[i] == ')' || str[i] == ']' || str[i] == '[')
		{
			if (save != -1)
			{
				result.PushBack(str.Substr(save, i));
				save = -1;
			}
			result.PushBack(GString(str[i]));
		}
		else if (str[i] != ' ')
		{
			if (save == -1)
				save = i;
		}
	}
	if (save != -1)
		result.PushBack(str.Substr(save, str.Size()));
	return (result);
}

GStringList		GAlgo::GStringToNPI(const GString &s)
{
	GStringList l = GAlgo::GStringToArray(s);
	GStringList sortie;
	GStringList pile;
	GMap<GString, int> priority;
	priority["+"] = 0;
	priority["-"] = 0;
	priority["%"] = 1;
	priority["*"] = 1;
	priority["/"] = 1;
	for (unsigned int i = 0; i < l.Size(); ++i)
	{
		if (l[i] == "(" || l[i] == "[")
			pile.PushBack(l[i]);
		else if (l[i].IsNumeric() || l[i].IsAlpha())
			sortie.PushBack(l[i]);
		else if (l[i] == ")")
		{
			while (pile.Back() != "(")
			{
				sortie.PushBack(pile.PopBack());
				if (pile.Size() == 0)
					throw GException("GAlgo", "Bad Expression");
			}
			pile.PopBack();
		}
		else if (l[i] == "]")
		{
			while (pile.Back() != "[")
			{
				sortie.PushBack(pile.PopBack());
				if (pile.Size() == 0)
					throw GException("GAlgo", "Bad Expression");
			}
			pile.PopBack();
		}
		else
		{
			if (pile.Size())
			{
				while (pile.Back() != "[" && pile.Back() != "]" && pile.Back() != "(" && pile.Back() != ")")
				{
					if (priority[pile.Back()] < priority[l[i]])
						sortie.PushBack(pile.PopBack());
				}
			}
			pile.PushBack(l[i]);
		}
	}
	while (pile.Size() > 0)
		sortie.PushBack(pile.PopBack());
	return (sortie);	
}

int		GAlgo::GStringToInt(const GString &s)
{
	GStringList	l = GAlgo::GStringToNPI(s);
	int n1, n2;
	while (l.Size() != 1)
	{
		n1 = l.PopBack().ToInt();
		n2 = l.PopBack().ToInt();
		if (l.Back() == "+")
		{
			l.PopBack();
			l.PushBack(GString(n1 + n2));
		}
		else if (l.Back() == "-")
		{
			l.PopBack();
			l.PushBack(GString(n1 - n2));
		}
		else if (l.Back() == "*")
		{
			l.PopBack();
			l.PushBack(GString(n1 * n2));
		}
	}
	return (l.PopBack().ToInt());
}
