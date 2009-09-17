//
// Matrice.cpp for Matrice in /home/tincan_g/work/cpp/class/Math
// 
// Made by geoffrey tincani
// Login   <tincan_g@epitech.net>
// 
// Started on  Wed May  6 22:12:39 2009 geoffrey tincani
// Last update Thu May  7 22:58:40 2009 geoffrey tincani
//

#include "Matrice.h"

// -----------------
// | CONSTRUCTEURS |
// -----------------

Matrice::Matrice(unsigned int nbr_lig, unsigned int nbr_col)
{
  _lig = nbr_lig;
  _col = nbr_col;
  _carre = false;
  if (_lig == _col)
    _carre = true;
  matrice = new int*[_lig];
  for (int i = 0; i < _lig; i++)
    {
      matrice[i] = new int[_col];
      for (int j = 0; j < _col; j++)
	matrice[i][j] = 1;
    }
  _name = NULL;
}
 
Matrice::Matrice(unsigned int nbr)
{
  _lig = nbr;
  _col = nbr;
  _carre = true;
  matrice = new int*[_lig];
  for (int i = 0; i < _lig; i++)
    {
      matrice[i] = new int[_col];
      for (int j = 0; j < _col; j++)
	matrice[i][j] = 0;
    }
  _name = NULL;
}

Matrice::Matrice(const Matrice &mat)
{
  this->_lig = mat._lig;
  this->_col = mat._col;
  this->_carre = _carre;
  this->matrice = new int*[_lig];
  this->_name = NULL;
  for (int i = 0; i < _lig; i++)
    {
      matrice[i] = new int[_col];
      for (int j = 0; j < _col; j++)
	matrice[i][j] = mat.matrice[i][j];
    }
}

Matrice::~Matrice(void)
{
  if (_name)
    delete(_name);
}

// --------------------
// | METHODE DIVERSES |
// --------------------

void	Matrice::setValue(int *tab)
{
  int i = 0;
  while (tab[i])
    {
      this->matrice[i / this->_lig][i % this->_col] = tab[i];
      i++;
    }
}

void	Matrice::setName(std::string name)
{
  if (_name)
    delete(_name);
  _name = new std::string(name);
}

unsigned int	Matrice::getNbrLig(void) const
{
  return (_lig);
}

unsigned int	Matrice::getNbrCol(void) const
{
  return (_col);
}

int	Matrice::getValue(unsigned int lig, unsigned int col) const
{
  return (this->matrice[lig][col]);
}



void	Matrice::disp_matrice(void)
{
  if (_name)
    std::cout << "Matrice " << *_name << " " << _lig << "x" << _col << std::endl;
  else
  std::cout << "Matrice " << _lig << "x" << _col << std::endl;
  for (int i = 0; i < _lig; i++)
    {
      for (int j = 0; j < _col; j++)
	std::cout << matrice[i][j] << " ";
      std::cout << std::endl;
    }
}

// -------------------------
// | SURCHARGE OPERATEUR + |
// -------------------------

Matrice	&Matrice::operator+(const Matrice &mat)
{
  Matrice *result = new Matrice(_lig, _col);
  try
    {
      if (this->_lig != mat._lig || this->_col != mat._col)
	throw "Impossible d'additionner 2 matrices de taille differente !";
      for (int i = 0; i < _lig; i++)
	for (int j = 0; j < _col; j++)
	  result->matrice[i][j] = mat.matrice[i][j] + this->matrice[i][j];      
    }
  catch (const char *str)
    {
      std::cout << str << std::endl;
      exit(1);
    }
  return (*result);
}

Matrice	&Matrice::operator+=(const Matrice &mat)
{
  try
    {
      if (this->_lig != mat._lig || this->_col != mat._col)
	throw "Impossible d'additionner 2 matrices de taille differente !";
      for (int i = 0; i < _lig; i++)
	for (int j = 0; j < _col; j++)
	  this->matrice[i][j] += mat.matrice[i][j];
    }
  catch (const char *str)
    {
      std::cout << str << std::endl;
      exit(1);
    }
  return (*this);
}

// -------------------------
// | SURCHARGE OPERATEUR - |
// -------------------------

Matrice	&Matrice::operator-(const Matrice &mat)
{
  Matrice *result = new Matrice(_lig, _col);
  try
    {
      if (this->_lig != mat._lig || this->_col != mat._col)
	throw "Impossible de soustraire 2 matrices de taille differente !";
      for (int i = 0; i < _lig; i++)
	for (int j = 0; j < _col; j++)
	  result->matrice[i][j] = this->matrice[i][j] - mat.matrice[i][j];      
    }
  catch (const char *str)
    {
      std::cout << str << std::endl;
      exit(1);
    }
  return (*result);
}

Matrice	&Matrice::operator-=(const Matrice &mat)
{
  try
    {
      if (this->_lig != mat._lig || this->_col != mat._col)
	throw "Impossible de soustraire 2 matrices de taille differente !";
      for (int i = 0; i < _lig; i++)
	for (int j = 0; j < _col; j++)
	  this->matrice[i][j] = this->matrice[i][j] - mat.matrice[i][j];      
    }
  catch (const char *str)
    {
      std::cout << str << std::endl;
      exit(1);
    }
  return (*this);
}

// -------------------------
// | SURCHARGE OPERATEUR / |
// -------------------------

Matrice	&Matrice::operator/(int num)
{
  Matrice *result = new Matrice(_lig, _col);
  for (int i = 0; i < _lig; i++)
    {
      for (int j = 0; j < _col; j++)
	result->matrice[i][j] = (this->matrice[i][j]) / num;
    }
  return (*result);  
}

Matrice	&Matrice::operator/=(int num)
{
  Matrice *result = new Matrice(_lig, _col);
  for (int i = 0; i < _lig; i++)
    {
      for (int j = 0; j < _col; j++)
	result->matrice[i][j] = (this->matrice[i][j]) / num;
    }
  return (*result);  
}

// -------------------------
// | SURCHARGE OPERATEUR * |
// -------------------------

Matrice	&Matrice::operator*(int num)
{
  Matrice *result = new Matrice(_lig, _col);
  for (int i = 0; i < _lig; i++)
    {
      for (int j = 0; j < _col; j++)
	result->matrice[i][j] = (this->matrice[i][j]) * num;
    }
  return (*result);  
}

Matrice	&Matrice::operator*=(int num)
{
  for (int i = 0; i < _lig; i++)
    {
      for (int j = 0; j < _col; j++)
	this->matrice[i][j] = (this->matrice[i][j]) * num;
    }
  return (*this);  
}

Matrice	&operator*(int num, const Matrice &m)
{
  Matrice *result = new Matrice(m.getNbrLig(), m.getNbrCol());
  for (int i = 0; i < result->_lig; i++)
    {
      for (int j = 0; j < result->_col; j++)
	result->matrice[i][j] = m.getValue(i, j) * num;
    }
  return (*result);  
}

int	Matrice::multiplie_cases(const Matrice &mat, unsigned x, unsigned y)
{
  int	resultat;

  resultat = 0;
  for (int i = 0; i < this->_lig; i++)
    resultat += this->matrice[x][i] * mat.matrice[i][y];
  return (resultat);
}

Matrice	&Matrice::operator*(const Matrice &mat)
{
  Matrice *result = new Matrice(this->getNbrLig(), this->getNbrCol());
  if (this->_lig != mat._col || this->_col != mat._lig)
    throw "Impossible de multiplier ces 2 matrices !";
  for (int i = 0; i < result->_lig; i++)
    {
      for (int j = 0; j < result->_col; j++)
	result->matrice[i][j] = multiplie_cases(mat, i, j);
    }
  return (*result);  
}

Matrice	&Matrice::operator*=(const Matrice &mat)
{
  if (this->_lig != mat._col || this->_col != mat._lig)
    throw "Impossible de multiplier ces 2 matrices !";
  for (int i = 0; i < this->_lig; i++)
    {
      for (int j = 0; j < this->_col; j++)
	this->matrice[i][j] = this->multiplie_cases(mat, i, j);
    }
  return (*this);
}

// ----------------------------
// | SURCHARGE OPERATEUR [][] |
// ----------------------------

int	*Matrice::operator[](const int i)
{
  return (this->matrice[i]);
}

// -------------------------
// | METHODE MATRICE CARRE |
// -------------------------

int	Matrice::Calcul_Trace(void)
{
  if (!_carre)
    throw "Uniquement pour les matrice carre";
  int	result = 0;
  for (int i = 0; i < _col; i++)
    result += this->matrice[i][i];
  return (result);
}

int	Matrice::Calcul_Determinant(void)
{
  if (!_carre)
    throw "Uniquement pour les matrice carre";
  int	result = 0;
  int	test;
  for (int i = 0; i < _col; i++)
    {
      test = 1;
      for (int j = 0; j < _col; j++)
	{
	  test *= this->matrice[j % _col][j % _col];
	}
      result += test;
    }
  for (int i = 0; i < _col; i++)
    {
      test = 1;
      for (int j = _col; j >= 0; j--)
	{
	  test *= this->matrice[j % _col][j % _col];
	}
      result -= test;
    }
  return (result);
}
