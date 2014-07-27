Blowfish
========

Blowfish C++ implementation

[![image](http://i.creativecommons.org/p/zero/1.0/88x31.png)](http://creativecommons.org/publicdomain/zero/1.0/)

 * Tested on OSX (32bit/64bit)
 * ECB mode only
 * The key length must be a multiple of 8bit
 * PKCS #5 Padding

## Usage

```cpp
#include <iostream>
#include <string>

#include "blowfish.h"

int main(int argc, const char * argv[])
{
    char key[] = "The quick brown fox jumps over the lazy dog.";
    
    Blowfish blowfish;
    blowfish.SetKey(key);
    
    std::string text = "This is not a pipe.";
    std::string encrypted, decrypted;
    
    blowfish.Encrypt(&encrypted, text);
    std::cout << encrypted << std::endl;
    
    blowfish.Decrypt(&decrypted, encrypted);
    std::cout << decrypted << std::endl;
    
    return 0;
}
```