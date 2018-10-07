// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
  MaxPower=mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
  MaxPower=s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
  MaxPower=bf.GetLength();
}

TSet::operator TBitField()
{
  TBitField res(BitField);
  return res;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
  try {
    return BitField.GetBit(Elem);
  }
  catch(int a)
  {
    cout<<endl<<"Error!"<<endl;
    exit(1);
  }
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
  try {
    BitField.SetBit(Elem);
  }
  catch(int a)
  {
    cout<<endl<<"Error!"<<endl;
    exit(1);
  }
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
  try {
    BitField.ClrBit(Elem);
  }
  catch(int a)
  {
    cout<<endl<<"Error!"<<endl;
    exit(1);
  }
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
  MaxPower=s.MaxPower;
  BitField=s.BitField;
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  return BitField==s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  return BitField!=s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
  TBitField res(BitField|s.BitField);
  return TSet(res);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  TSet res(*this);
  res.InsElem(Elem);
  return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  TSet res(*this);
  res.DelElem(Elem);
  return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  TBitField res(BitField&s.BitField);
  return TSet(res);
}

TSet TSet::operator~(void) // дополнение
{
  TSet res(*this);
  res.BitField=~res.BitField;
  return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  int n;
  cout<<"Input MaxPower ";
  cin>>n;
  int a,flag=0;
  s=TSet(n);
  cout<<"Input number of elements ";
  cin>>n;
  cout<<"Input numeric set ";
  for(int i=0;i<n;i++)
  {
    cin>>a;
    if((a>s.MaxPower)||(a<flag))
    {
      cout<<"You entered "<<i<<" digits. Thank you!"<<endl;
      break;
    }
    else
    {
      s.InsElem(a);
      flag=a;
    }
  }
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  int flag=1;
  int i,n;
  for (i=0;i<s.MaxPower;i++)
    if(s.IsMember(i))
    {
      flag=0;
      break;
    }
  if (flag)
  {
    cout<<"{ \u2205 }";
  }
  else
  {
    cout<<endl<<"Output Numeric set(1) or Bitfield(2) ";
    while(1)
    {
      cin>>i;
      switch (i)
      {
        case 1:
        {
          char ch = ' ';
          ostr << "{";
          n = s.GetMaxPower();
          for (i = 0; i < n; i++)
            if(s.IsMember(i))
            {
              ostr<<ch<<i;
              ch = ',';
            }
            ostr << " }";
            return ostr;
          }
          case 2:
          {
            cout<<s.BitField;
            return ostr;
          }
          default: cout<<"Invalid input, try again!";
        }
      }
    }
  return ostr;
  //
  // int i,n; char ch = ' ';
  // ostr << "{";
  // n = s.GetMaxPower();
  // for (i = 0; i < n; i++)
  //   if(s.IsMember(i))
  //   {
  //     ostr<<ch<<i;
  //     ch = ',';
  //   }
  // ostr << " }";
  // return ostr;
}
