
#include "GComplexe.h"

GComplexe::GComplexe(const GFraction &im, const GFraction &re)
{
  this->_im = im;
  this->_re = re;
}

GComplexe::~GComplexe(void)
{

}

GFraction	&GComplexe::Im(void)
{
  return (this->_im);
}

GFraction	&GComplexe::Re(void)
{
  return (this->_re);
}


