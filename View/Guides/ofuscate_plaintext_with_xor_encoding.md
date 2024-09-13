# Ofuscate Plaintext With XOR Encoding

The `crypto.h` header includes the `crypto::encoder::XOR()` function, which can be used to obfuscate plaintext content using the XOR encoding technique. This function takes the original plaintext as input and applies the XOR encoding to it, generating an obfuscated version of the content. This can be a useful technique for protecting sensitive information or hiding the true nature of the data.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/encoder.h>

using namespace nodepp;

void onMain() {

    auto data = "Hello World!";
    auto pass = "SECRET_PASSWORD";
    
    auto XOR  = encoder::XOR::get( data, pass );
    console::log( XOR ); // data ^= PASS

    auto ROX  = encoder::XOR::get( XOR, pass );
    console::log( ROX ); // Hello World!
    
}
```