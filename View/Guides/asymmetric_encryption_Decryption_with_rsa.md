# Asymmetric Encryption And Decryption With RSA

To Encrypt messages use the `crypto::encrypt::RSA` from `crypto.h` and the `public_encrypt()` function

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/crypto.h>

using namespace nodepp;

void onMain(){

    string_t msg = "Hello World!";

    crypto::encrypt::RSA RSA;
    RSA.generate_keys( 2048 );

    RSA.write_public_key( "PUBLIC.txt" );
    RSA.write_private_key( "PRIVATE.txt" );

    auto data = ppt.public_encrypt( msg );

    console::log( data.size(), data );

}
```

To Dncrypt messages use the `crypto::decrypt::RSA` from `crypto.h` and the `private_decrypt()` function

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/crypto.h>

using namespace nodepp;

void onMain(){

    string_t msg = "Hello World!";

    crypto::encrypt::RSA RSA;

    RSA.read_private_key( "PRIVATE.txt" );

    auto data = ppt.private_decrypt( msg );
     
    console::log( data.size(), data );

}
```