# Convert A Base64 To A Plaintext Format

To Conver a `Base64` string to a `Plaintext` string, Nodepp implements `encoder::base64::set()` function inside `encoder.h`, this function will return a new `string_t` in Plaintext format on success or `nullptr` otherwise;

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/encoder.h>

using namespace nodepp;

void onMain() {

    auto b64  = "SGVsbG8gV29ybGQh";
    auto data = encoder::base64::set( b64 );

    console::log( data ); // Hello World!

}
```