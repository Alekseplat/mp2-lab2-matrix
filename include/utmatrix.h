// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {

	  for (int i = 0; i < (v.Size-v.StartIndex); i++)

		  in >> v.pVector[i];

	  return in;

  }

  friend ostream& operator<<(ostream &out, const TVector &v)

  {

	  for (int i = 0; i < (v.Size-v.StartIndex); i++)

		  out << v.pVector[i] << ' ';

	  return out;

  }

  


};

template <class ValType>
TVector<ValType>::TVector(int s, int si)

{

	if ((s < 0) || (s>MAX_VECTOR_SIZE))

	{

		throw - 1;

	}

	if ((si<0) || (si>s))

	{

		throw - 3;

	}

	Size = s;

	StartIndex = si;

	pVector = new ValType[Size - StartIndex];

	for (int i = 0; i < Size - StartIndex; i++)

	{

		pVector[i] = 1;

	}

}

template <class ValType> //конструктор копирования

TVector<ValType>::TVector(const TVector<ValType> &v)

{

	Size = v.Size;

	StartIndex = v.StartIndex;

	pVector = new ValType[Size - StartIndex];

	for (int i = 0; i< Size - StartIndex; i++)

	{

		pVector[i] = v.pVector[i];

	}

} /*-------------------------------------------------------------------------*/

template <class ValType>

TVector<ValType>::~TVector()

{

	delete[]pVector;

}

template <class ValType> // доступ

ValType& TVector<ValType>::operator[](int pos) {

	if ((pos < StartIndex) || (pos > Size))

	{

		throw - 9000;

	}

	return pVector[pos];

} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение

bool TVector<ValType>::operator==(const TVector &v) const

{

	if ((Size != v.Size) || (StartIndex != v.StartIndex))

	{

		return false;

	}

	for (int i = 0; i < Size - StartIndex; i++)

	{

		if (pVector[i] != v.pVector[i]) return false;
	}

	return true;

} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение

bool TVector<ValType>::operator!=(const TVector &v) const

{

	if (*this == v) return false;

	return true;

} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание

TVector<ValType>& TVector<ValType>::operator=(const TVector &v)

{

	if (this == &v) return *this;

	Size = v.Size;

	StartIndex = v.StartIndex;

	delete[]pVector;

	pVector = new ValType[Size - StartIndex];

	for (int i = 0; i < Size - StartIndex; i++)

	{

		pVector[i] = v.pVector[i];

	}

	return *this;

} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр

TVector<ValType> TVector<ValType>::operator+(const ValType &val)

{

	TVector<ValType> res(Size - StartIndex);

	for (int i = 0; i < Size - StartIndex; i++)

	{

		res.pVector[i] = pVector[i] + val;

	}

	return res;

} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр

TVector<ValType> TVector<ValType>::operator-(const ValType &val)

{

	TVector<ValType> res(Size - StartIndex);

	for (int i = 0; i < Size - StartIndex; i++)

	{

		res.pVector[i] = pVector[i] - val;

	}

	return res;

} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр

TVector<ValType> TVector<ValType>::operator*(const ValType &val)

{

	TVector<ValType> res(Size - StartIndex);

	for (int i = 0; i < Size - StartIndex; i++)

	{

		res.pVector[i] = pVector[i] * val;

	}

	return res;

} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение

TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)

{

	if (Size != v.Size)

	{

		throw - 42;

	}

	TVector<ValType> res(Size - StartIndex);

	for (int i = 0; i < Size - StartIndex; i++)

	{

		res.pVector[i] = pVector[i] + v.pVector[i];

	}

	return res;

} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание

TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)

{

	if (Size == v.Size)

	{

		TVector<ValType> res(Size - StartIndex);

		for (int i = 0; i < Size - StartIndex; i++)

		{

			res.pVector[i] = pVector[i] - v.pVector[i];

		}

		return res;

	}

	else

	{

		throw - 24;

	}

} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение

ValType TVector<ValType>::operator*(const TVector<ValType> &v)

{

	if (Size != v.Size)

	{

		throw - 4223;

	}

	ValType res;

	res = 0;

	for (int i = 0; i < Size - StartIndex; i++)

	{

		res = res + (pVector[i] * v.pVector[i]);

	}

	return res;

} /*-------------------------------------------------------------------------*/

  // Верхнетреугольная матрица
template <class ValType>

class TMatrix : public TVector<TVector<ValType> >

{

public:

	TMatrix(int s = 10);

	TMatrix(const TMatrix &mt); // копирование

	TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа

	bool operator==(const TMatrix &mt) const; // сравнение

	bool operator!=(const TMatrix &mt) const; // сравнение

	TMatrix& operator= (const TMatrix &mt); // присваивание

	TMatrix operator+ (const TMatrix &mt); // сложение

	TMatrix operator- (const TMatrix &mt); // вычитание

										   // ввод / вывод

	friend istream& operator>>(istream &in, TMatrix &mt)

	{

		for (int i = 0; i < mt.Size; i++)

			in >> mt.pVector[i];

		return in;

	}

	friend ostream & operator<<(ostream &out, const TMatrix &mt)

	{

		for (int i = 0; i < mt.Size; i++)

			out << mt.pVector[i] << endl;

		return out;

	}

};

template <class ValType>

TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)

{


	if ((s < 0) || (s > MAX_MATRIX_SIZE))

	{

		throw - 4;

	}
	s = Size;

	pVector = new TVector<ValType>[Size - StartIndex];

	for (int i = 0; i < Size - StartIndex; i++)

	{

		pVector[i] = TVector<ValType>(Size, i);

	}

}

/*

if ((s < 0) || (s > MAX_MATRIX_SIZE))

{

throw - 9;

}

s = Size;

for (int i = 0; i < Size-StartIndex; i++)

{

int k=0;

for (int j=k; j < Size - StartIndex; j++)

{

pVector[j] = new TVector<ValType>[Size-StartIndex];

}

k++;

}

} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования

TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) :

	TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа

TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt) :

	TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение

bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const

{



	if (Size != mt.Size) return false;

	for (int i = 0; i < Size - StartIndex; i++)

	{

	if (pVector[i] != mt.pVector[i]) return false;

	}

	return true;


//	return TVector<TVector<ValType> >::operator==(mt);

} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение

bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const

{

	if (*this == mt) return false;

	return true;

} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание

TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)

{

	if (this != &mt)

	{

		if (Size != mt.Size)

		{

			delete[] pVector;

			pVector = new TVector<ValType>[mt.Size];

		}

		for (int i = 0; i < Size - StartIndex; i++)

			pVector[i] = mt.pVector[i];

	}

	return *this;

} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение

TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)

{

	/* TMatrix<ValType> res(Size - StartIndex);

 for (int i = 0; i < Size - StartIndex; i++)

 res.pVector[i] = pVector[i] + mt.pVector[i];

 return res;
 */
 return TVector<TVector<ValType> >::operator+(mt);

 

	

} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание

TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)

{
/*
 TMatrix<ValType> res(Size - StartIndex);

 for (int i = 0; i < Size - StartIndex; i++)

 res.pVector[i] = pVector[i] - mt.pVector[i];

 return res;
 */
 return TVector<TVector<ValType> >::operator-(mt);
 

	

} /*-------------------------------------------------------------------------*/

  // TVector О3 Л2 П4 С6

  // TMatrix О2 Л2 П3 С3

#endif