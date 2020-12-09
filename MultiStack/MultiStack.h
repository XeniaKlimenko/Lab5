#ifndef _MULTISTACK_H_
#define _MULTISTACK_H_

#include <iostream>
#include <math.h>
#include "Stack.h"

using namespace std;

template <class T>
class TMultiStack
{
protected:
  int length;
  T* data;
  int StackCount;

  TStack<T>* stacks;
  T** oldData;

  void StackRelocation(int i);

public:
  TMultiStack(int size = 1, int _StackCount = 1);
  TMultiStack(TMultiStack<T>& _v);
  ~TMultiStack();

  TMultiStack<T>& operator =(TMultiStack<T>& _v);
  int IsEmpty(int i) const;
  int IsFull(int i) const;
  void Push(T d, int i);
  T Get(int i);

  template <class T1>
  friend ostream& operator<< (ostream& ostr, const TMultiStack<T1> &A);
  template <class T1>
  friend istream& operator >> (istream& istr, TMultiStack<T1> &A);

  int GetSize() const;
  void Resize(int size = 1, int StackCount = 1);
};


template <class T1>
ostream& operator<< (ostream& ostr, const TMultiStack<T1> &A) {
  for (int i = 0; i < A.StackCount; i++) {
    ostr << A.stacks[i] << endl;
  }
  return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TMultiStack<T1> &A) {
  int stCount = 0;
  istr >> stCount;
  int size = 0;
  istr >> size;
  A.Resize(size, stCount);
  for (int i = 0; i < A.stCount; i++) 
    istr >> A.stacks[i] ;
    
  return istr;
}

template<class T>
inline TMultiStack<T>::TMultiStack(int size, int _StackCount)
{
  if ((size > 0) && (_StackCount > 0))
  {
    this->length = size;
    this->StackCount = _StackCount;

    data = new T[length];
    for (int i = 0; i < length; i++)
      data[i] = 0;

    int count = int(floor(double(size) / StackCount));
    int* sizes = new int[this->StackCount];

    for (int i = 0; i < (StackCount - 1); i++)
      sizes[i] = count;

    sizes[StackCount - 1] = size - (count * (StackCount - 1));
    oldData = new T * [StackCount];
    this->stacks = new TStack<T>[StackCount];

    int k = 0;
    for (int i = 0; i < StackCount; i++)
    {
      this->stacks[i].SetData(&(data[k]), sizes[i], 0);
      this->oldData[i] = &(data[k]);
      k = k + sizes[i];
    }
  }
  else throw "wrong index";
}

template <class T>
TMultiStack<T>::TMultiStack(TMultiStack<T>& _v)
{
  length = _v.length;
  StackCount = _v.StackCount;
  data = new T [length];
  for (int i = 0; i < length; i++)
    data[i] = _v.data[i];

  stacks = new TStack<T>[StackCount];
  for (int i = 0; i < StackCount; i++)
    stacks[i] = _v.stacks[i];

  oldData = _v.oldData;
}

template <class T>
TMultiStack<T>::~TMultiStack()
{
  length = 0;
  StackCount = 0;

  if (data == NULL)
  {
    delete[] data;
    data = 0;
  }
  if (stacks == NULL)
  {
    delete[] stacks;
    stacks = 0;
  }
}

template<class T>
inline void TMultiStack<T>::StackRelocation(int index)
{
  int freeSize = 0;
  for (int i = 0; i < StackCount; i++)
    freeSize += stacks[i].GetSize() - stacks[i].GetCount();

  if (freeSize == 0)
    throw logic_error("Error");

  int count = int(floor(double(freeSize) / StackCount));
  int* sizes = new int[this->StackCount];

  for (int i = 0; i < (StackCount - 1); i++)
    sizes[i] = stacks[i].GetCount() + count;
  
  int c = stacks[StackCount - 1].GetCount();
  sizes[this->StackCount - 1] = c + (freeSize - (count * (this->StackCount - 1)));

  T** newData = new T * [StackCount];
  int k = 0;

  for (int i = 0; i < StackCount; i++)
  {
    newData[i] = &(data[k]);
    k = k + sizes[i];
  }

  for (int i = 0; i < StackCount; i++)
  {
    if (newData[i] == oldData[i])
    {
      stacks[i].SetData(newData[i], sizes[i], stacks[i].GetCount());
    }
    else if (newData[i] < oldData[i])
    {
      for (int j = 0; j < stacks[i].GetCount(); j++)
      {
        newData[i][j] = oldData[i][j];
      }
      stacks[i].SetData(newData[i], sizes[i], stacks[i].GetCount());
    }
    else if (newData[i] > oldData[i])
    {
      int k = i;
      for (; k < StackCount; k++)
      {
        if (newData[k] > oldData[k])
          continue;
        else
          break;
      }
      k--;

      for (int s = k; s <= i; s--)
      {
        for (int j = stacks[s].GetCount() - 1; j >= 0; j--)
        {
          newData[s][j] = oldData[s][j];
        }
        stacks[s].SetData(newData[s], sizes[s], stacks[s].GetCount());
      }

    }
  }

  T** buf = oldData;
  oldData = newData;
  delete[] buf;
  delete[] sizes;
}

template <typename T>
TMultiStack<T>& TMultiStack<T>::operator =(TMultiStack<T>& _v)
{
  if (this == &_v)
    return *this;

  length = _v.length;
  
  if (data != NULL)
    delete[] data;
  if (stacks != NULL)
    delete[] stacks;

  data = new T[length];
  for (int i = 0; i < length; i++)
    data[i] = _v.data[i];
  
  stacks = new TStack<T>[StackCount];
  for (int i = 0; i < StackCount; i++)
    stacks[i] = _v.stacks[i];

  return *this;
}

template<class T>
inline int TMultiStack<T>::IsEmpty(int i) const
{
  if (i < 0 || i > StackCount)
    throw "wrong index";

  return stacks[i].IsEmpty();
}

template<class T>
inline int TMultiStack<T>::IsFull(int i) const
{
  if (i < 0 || i > StackCount)
    throw "wrong index";

  return stacks[i].IsFull();
}

template<class T>
inline void TMultiStack<T>::Push(T d, int i)
{
  if (i < 0 || i >= StackCount)
    throw "wrong index";

  if (stacks[i].IsFull())
    StackRelocation(i);

    stacks[i].Push(d);
}

template<class T>
inline T TMultiStack<T>::Get(int i)
{
  if (i < 0 || i > StackCount)
    throw "wrong index";

  if (stacks[i].IsEmpty())
    throw "stack is empty";

  T d = stacks[i].Get();
  return d;
}

template <typename T>
inline int TMultiStack<T>::GetSize() const
{
  return length;
}

template<class T>
inline void TMultiStack<T>::Resize(int size, int StackCount)
{
  stacks[StackCount].Resize(size);
}

#endif