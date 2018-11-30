#ifndef TEMPLATECLASS_H
#define TEMPLATECLASS_H

#include "supertimer.h"

#include <iostream>
#include <string>
using namespace std;

template <class numtype>
//定义类模板
class Compare
{
public :
   Compare(numtype a,numtype b)
   {x=a;y=b;}
   numtype max( )
   {return (x>y)?x:y;}
   numtype min( ){            //某论坛说模板类的函数声明与定义都要放在函数内部，要不会出问题
    return (x<y)?x:y;
   }
private :
   numtype x,y;
};

#endif // TEMPLATECLASS_H
