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

template<typename T>
T Select(HDC hdc, T obj)
{
	return (T)::SelectObject(hdc, obj);
}