#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>

using namespace std;

template <class T>
class TStack
{
protected:
  int length;
  T* data;
  int top;
  bool isHaveData;
public:
  TStack(int size = 1, bool _f = true);
  TStack(TStack<T>& _v);
  ~TStack();

  TStack<T>& operator =(TStack& _v);
  int GetSize() const;
  int GetCount() const;
  int IsEmpty(void) const;
  int IsFull(void) const;
  void Push(T d);
  T Get();
  void SetData(T* _data, int size, int top_);
  void Resize(int size);

  template <class T1>
  friend ostream& operator<< (ostream& ostr, const TStack<T1> &A);
  template <class T1>
  friend istream& operator >> (istream& istr, TStack<T1> &A);

};

template <class T1>
ostream& operator<< (ostream& ostr, const TStack<T1> &A) {
  for (int i = 0; i < A.top; i++) {
    ostr << A.data[i] << endl;
  }
  return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TStack<T1> &A) {
  int count;
  istr >> count;
  for (int i = 0; i < count; i++) {
    T1 d;
    istr >> d;
    A.Push(d);
  }
  return istr;
}


template<class T>
inline TStack<T>::TStack(int size, bool _f)
{
  if (size > 0)
  {
    this->length = size;
    this->isHaveData = _f;
    if (isHaveData)
    {
      data = new T[length];
      for (int i = 0; i < length; i++)
        data[i] = 0;
    }
    this->top = 0;
  }
  else 
    throw logic_error("Error");
}

template <class T>
TStack<T>::TStack(TStack<T>& _v)
{
  length = _v.length;
  top = _v.top;
  isHaveData = _v.isHaveData;
  if (isHaveData)
  {
    data = new T[length];
    for (int i = 0; i < length; i++)
      data[i] = _v.data[i];
  }
  else data = _v.data;
}

template <class T>
TStack<T>::~TStack()
{
  length = 0;
  if (isHaveData)
    if (data != NULL)
    {
      delete[] data;
      data = 0;
    }
}

template <class T>
TStack<T>& TStack<T>::operator =(TStack<T>& _v)
{
  if (this == &_v)
    return *this;

  length = _v.length;
  isHaveData = _v.isHaveData;
  if (isHaveData)
  {
    if (data != NULL)
      delete[] data;
    data = new T[length];
    for (int i = 0; i < length; i++)
      data[i] = _v.data[i];
  }
  else data = _v.data;

  top = _v.top;
  return *this;
}


template <typename T>
inline int TStack<T>::GetSize() const
{
  return length;
}

template <typename T>
inline int TStack<T>::GetCount() const
{
  return top;
}

template<class T>
inline int TStack<T>::IsEmpty(void) const
{
  return (top == 0);
}

template<class T>
inline int TStack<T>::IsFull(void) const
{
  return (top - 1 > length);
}

template<class T>
inline void TStack<T>::Push(T d)
{
  if (top >= length)
    throw logic_error("Error");
  data[top] = d;
  top++; 
}

template<class T>
inline T TStack<T>::Get()
{
  if (top <= 0)
    throw logic_error("Error");
  T d = data[top - 1];
  top--;
  return d;
}

template<class T>
inline void TStack<T>::SetData(T* _data, int size, int top_)
{
  if (isHaveData)
    if (data != NULL)
      delete[] data;
 
  this->length = size;
  isHaveData = false;
  data = _data;
  top = top_;
}

template<class T>
inline void TStack<T>::Resize(int size)
{
  if (size <= 0)
    throw "negative size";

  if (data == 0)
  {
    delete[] data;
    data = new T[size];
  }
  else
  {
    T* tmp = new T[size];

    for (int i = 0; i < this->GetCount(); i++)
      tmp[i] = Get();

    delete[] data;
    data = new T[size];

    for (int i = 0; i < 1; i++)
      data[i] = tmp[i];
  }
}


#endif