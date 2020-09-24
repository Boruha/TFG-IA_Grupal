#include <main.hpp>

extern "C"
{
  #include "tinyPTC/tinyptc.h"  
} 

int main()
{

    ptc_open("window", 640, 360);

    for(;;);

    ptc_close();

    return 0;
}