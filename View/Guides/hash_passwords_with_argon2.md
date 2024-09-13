# Hash Passwords With Argon2 <br>

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/encoder.h>
#include <argon/argon2.h>

using namespace nodepp;

void onMain() {

    ptr_t<uchar> hash ( 32, '\0' );
    argon2_t argon; 

    argon.hash( hash, "password" );
    console::log( encoder::hex::get( hash ) );

}
```

[Github Repository](https://github.com/NodeppOficial/nodepp-argon2)