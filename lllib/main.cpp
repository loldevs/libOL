//  Copyright (c) 2014 Andrew Toulouse. All rights reserved.

#include <iostream>
#include <fstream>

#include "File.h"

int main(int argc, const char * argv[])
{

    std::ifstream ifs("/Users/toulouse/code/lmao/rofl/22923174.rofl", std::ios::binary);

    lllib::File file = lllib::File::decode(ifs);

    //std::cout << file << endl;
    return 0;
}

