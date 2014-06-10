#pragma once

template<typename T>
class singleton
{
protected :
   singleton(){}
   virtual ~singleton(){}

public :
   static T& GetReference()
   {
      static T instance;
      return instance;
   }
};
