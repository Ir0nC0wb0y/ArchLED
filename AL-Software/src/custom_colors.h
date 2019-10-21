
#ifndef custom_colors_h
#define custom_colors_h
#endif

#include <Arduino.h>

class Color{
    public:
      Color();

      void mapRO(int);
      void mapOY(int);
      void mapYG(int);
      void mapGB(int);
      void mapBP(int);
      void mapPR(int);
      void mapW ();

      int return_R();
      int return_G();
      int return_B();
      int return_W();


    private:
      int _R, _G, _B, _W;
};