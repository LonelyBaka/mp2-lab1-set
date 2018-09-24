// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
  if(len<0)
      throw 1;
  BitLen=len;
  MemLen=(BitLen+31)>>5;
  pMem=new TELEM[MemLen];
  if (pMem)
  {
    for(int i=0;i<MemLen;i++)
      pMem[i]=0;
  }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  BitLen=bf.BitLen;
  MemLen=bf.MemLen;
  pMem=new TELEM[MemLen];
  if (pMem)
  {
    for(int i=0;i<MemLen;i++)
      pMem[i]=bf.pMem[i];
  }
}

TBitField::~TBitField()
{
  delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  return n>>5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  TELEM tmp=0;
  tmp=1<<(n%32);
  return tmp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if((n<0)||(n>BitLen))
        throw 1;
    pMem[GetMemIndex(n)]=pMem[GetMemIndex(n)]|GetMemMask(n);

}

void TBitField::ClrBit(const int n) // очистить бит
{
    if((n<0)||(n>BitLen))
        throw 1;
    pMem[GetMemIndex(n)]=pMem[GetMemIndex(n)]&(~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if((n<0)||(n>BitLen))
        throw 1;
  return (pMem[GetMemIndex(n)]&GetMemMask(n))>>(n%32);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    delete[] pMem;
    BitLen=bf.BitLen;
    MemLen=bf.MemLen;
    pMem=new TELEM[MemLen];
    for (int i=0;i<MemLen;i++)
        pMem[i]=bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    int flag=0; int flag1=MemLen;
    if ((MemLen==bf.MemLen)&&(BitLen==bf.BitLen))
    {
        for(int i=0;i<MemLen;i++)
            if(pMem[i]==bf.pMem[i])
                flag+=1;
        if(flag==flag1)
            return 1;
        else return 0;
    }
    else return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    int flag=0; int flag1=MemLen;
    if ((MemLen==bf.MemLen)&&(BitLen==bf.BitLen))
    {
        for(int i=0;i<MemLen;i++)
            if(pMem[i]==bf.pMem[i])
                flag+=1;
        if(flag==flag1)
            return 0;
        else return 1;
    }
    else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int i, len = BitLen;
    if (bf.BitLen > len)
    len = bf.BitLen;
    TBitField temp(len);
    for (i = 0; i < MemLen; i++)
    temp.pMem[i] = pMem[i];
    for (i = 0; i < bf.MemLen; i++)
    temp.pMem[i] |= bf.pMem[i];
    return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int i, len = BitLen;
    if (bf.BitLen > len)
    len = bf.BitLen;
    TBitField temp(len);
    for (i = 0; i < MemLen; i++)
    temp.pMem[i] = pMem[i];
    for (i = 0; i < bf.MemLen; i++)
    temp.pMem[i] &= bf.pMem[i];
    return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField temp(*this);
    int i;
    if (MemLen>1)
      for (i = 0; i < MemLen-1; i++)
          for(int j=0;j<32;j++)
          {
              if(temp.GetBit(i*32+j))
                  temp.ClrBit((i*32+j));
              else
                  temp.SetBit((i*32+j));
          }
    for(i=0;i<BitLen%32;i++)
        if(temp.GetBit((MemLen-1)*32+i))
            temp.ClrBit((MemLen-1)*32+i);
        else
            temp.SetBit((MemLen-1)*32+i);
    return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int flag=0,flag1=1;
    cout<<"Input n: ";
    cin>>bf.BitLen;
    bf.MemLen=(bf.BitLen+31)>>5;
    bf.pMem=new TELEM[bf.MemLen];
    char ch;
    while(flag1)
    {
        cout<<"Enter the number: ";
        for(int i=bf.BitLen-1;i>-1;i--)
        {
            cin>>ch;
            switch (ch)
            {
            case '1':
                bf.SetBit(i);
                break;
            case '0':
                bf.ClrBit(i);
                break;
            default: flag=1;
            }
            if(i==0)
                flag1=0;
            if (flag==1)
            {
                cout<<"Invalid input, try again! "<<endl;
                flag=0;
                break;
            }
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for(int i=bf.BitLen-1;i>-1;i--)
        cout<<bf.GetBit(i);
    cout<<endl;
    return ostr;
}
