#include <iostream>
#include <bitset>

int main()
{
    union
    {
         float input;   // assumes sizeof(float) == sizeof(int)
         int   output;
    }    data;

    data.input = 2.25125;

    std::bitset<sizeof(float) * 8>   bits(data.output);


    std::cout << bits << std::endl;

    
}
