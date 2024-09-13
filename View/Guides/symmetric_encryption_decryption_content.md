# Symmetric Encryption & Decryption Content In Nodepp

To Encrypt Files use the `crypto::encrypt` namespace from `crypto.h`

```cpp
#define SECRET "MY_SECRET_KEY"

#include <nodepp/nodepp.h>
#include <nodepp/crypto.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto fout = fs::writable( "PATH_TO_FILE1" ); 
    auto file = fs::readable( "PATH_TO_FILE2" ); 

    auto fd   = crypto::encrypt::AES_128_CBC( SECRET );

    file.onClose([=](){ console::log("Encrypted"); });

    file.onData([=]( string_t data ){
        fd.update( data );
    });

    fd.onData([=]( string_t data ){
        fout.write( data );
    });

    stream::pipe( file );
    
}
```

Algorithms Supported by `crypto::encrypt`

- `crypto::encrypt::TRIPLE_DES_CFB()`
- `crypto::encrypt::TRIPLE_DES_CBC()`
- `crypto::encrypt::TRIPLE_DES_ECB()`
- `crypto::encrypt::AES_128_CBC()`
- `crypto::encrypt::AES_192_CBC()`
- `crypto::encrypt::AES_256_CBC()`
- `crypto::encrypt::AES_128_ECB()`
- `crypto::encrypt::AES_192_ECB()`
- `crypto::encrypt::AES_256_ECB()`
- `crypto::encrypt::DES_CFB()`
- `crypto::encrypt::DES_CBC()`
- `crypto::encrypt::DES_ECB()`
- `crypto::encrypt::XOR()`

To Decrypt Files use the `crypto::decrypt` namespace from `crypto.h`

```cpp
#define SECRET "MY_SECRET_KEY"

#include <nodepp/nodepp.h>
#include <nodepp/crypto.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto fout = fs::writable( "PATH_TO_FILE1" ); 
    auto file = fs::readable( "PATH_TO_FILE2" ); 

    auto fd   = crypto::decrypt::AES_128_CBC( SECRET );

    file.onClose([=](){ console::log("Decrypted"); });

    file.onData([=]( string_t data ){
        fd.update( data );
    });

    fd.onData([=]( string_t data ){
        fout.write( data );
    });

    stream::pipe( file );
    
}
```

Algorithms Supported by `crypto::decrypt`

- `crypto::decrypt::TRIPLE_DES_CFB()`
- `crypto::decrypt::TRIPLE_DES_CBC()`
- `crypto::decrypt::TRIPLE_DES_ECB()`
- `crypto::decrypt::AES_128_CBC()`
- `crypto::decrypt::AES_192_CBC()`
- `crypto::decrypt::AES_256_CBC()`
- `crypto::decrypt::AES_128_ECB()`
- `crypto::decrypt::AES_192_ECB()`
- `crypto::decrypt::AES_256_ECB()`
- `crypto::decrypt::DES_CFB()`
- `crypto::decrypt::DES_CBC()`
- `crypto::decrypt::DES_ECB()`
- `crypto::decrypt::XOR()`