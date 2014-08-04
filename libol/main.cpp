//  Copyright (c) 2014 Andrew Toulouse. All rights reserved.

#include <iostream>
#include <fstream>

#include "File.h"

int main(int argc, const char * argv[])
{

    std::ifstream ifs("/Users/toulouse/code/lol/lmao/rofl/22923174.rofl", std::ios::binary);

    libol::File file = libol::File::decode(ifs);

    //std::cout << file << std::endl;
    return 0;
}

