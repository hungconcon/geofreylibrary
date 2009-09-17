
#include "GCryptography.h"



namespace GCryptography
{
	inline char GBase64::Encode64(unsigned char uc)
	{
		if (uc < 26)
			return ('A' + uc);
		if (uc < 52)
			return ('a' + (uc - 26));
		if (uc < 62)
			return ('0' + (uc - 52));
		if (uc == 62)
			return ('+');
		return ('/');
	}

	inline unsigned char GBase64::Decode64(char c)
	{
		 if (c >= 'A' && c <= 'Z')
			return (c - 'A');
		if (c >= 'a' && c <= 'z')
			return (c - 'a' + 26);
		if (c >= '0' && c <= '9')
			return (c - '0' + 52);
		if (c == '+')
			return (62);
		return (63);
	}

	inline bool GBase64::IsBase64(char c)
	{
		if (c >= 'A' && c <= 'Z')
			return (true);
		if (c >= 'a' && c <= 'z')
			return (true);
		if (c >= '0' && c <= '9')
			return (true);
		if (c == '+')
			return (true);
		if (c == '/')
			return (true);
		if (c == '=')
			return (true);
		return false;
	};

	inline GString	GBase64::Encode(const GString &vb)
	{
		GString vby(vb);
		GString retval;
		if (vby.Size() == 0)
		{
			return (retval);
		}
		for (unsigned int i = 0; i < vby.Size(); i += 3)
		{
			unsigned char by1 = 0, by2 = 0, by3 = 0;
			by1 = vby[i];
			if (i + 1 < vby.Size())
			{
				by2 = vby[i + 1];
			}
			if (i + 2 < vby.Size())
				by3 = vby[i + 2];
			unsigned char by4 = 0, by5 = 0, by6 = 0, by7 = 0;
			by4 = by1 >> 2;
			by5 = ((by1 & 0x3) << 4)|(by2 >> 4);
			by6 = ((by2 & 0xf) << 2)|(by3 >> 6);
			by7 = by3 & 0x3f;
			retval += GBase64::Encode64(by4);
			retval += GBase64::Encode64(by5);
			if (i + 1 < vby.Size())
				retval += GBase64::Encode64(by6);
			else
			{
				retval += "=";
			}
			if (i + 2 < vby.Size())
				retval += GBase64::Encode64(by7);
			else
			{
				retval += "=";
			}
			//if (i % (76 / 4 * 3) == 0)
			//	retval += "\r\n";
		}
		return (retval);
	}

	inline GString	GBase64::Decode(const GString &_s)
	{
		GString _str(_s);
		GString	str;
		for (unsigned int j = 0; j < _str.Size(); j++)
		{
			if (GBase64::IsBase64(_str[j]))
				str += _str[j];
		}
		GString retval;
		if (str.Size() == 0)
			return (retval);
		for (unsigned int i = 0; i < str.Size(); i += 4)
		{
			char c1 = 'A', c2 = 'A', c3 = 'A', c4 = 'A';
			c1 = str[i];
			if (i + 1 < str.Size())
				c2 = str[i + 1];
			if (i + 2 < str.Size())
				c3 = str[i + 2];
			if (i + 3 < str.Size())
				c4 = str[i + 3];
			unsigned char by1 = 0, by2 = 0, by3 = 0, by4 = 0;
			by1 = GBase64::Decode64(c1);
			by2 = GBase64::Decode64(c2);
			by3 = GBase64::Decode64(c3);
			by4 = GBase64::Decode64(c4);
			retval += (unsigned char)((by1 << 2) | (by2 >> 4));
			if (c3 != '=')
				retval += (unsigned char)(((by2 & 0xf)<< 4)|(by3 >> 2));
			if (c4 != '=')
				retval += (unsigned char)(((by3 & 0x3) << 6) | by4);
		}
		return (retval);
	}
}


