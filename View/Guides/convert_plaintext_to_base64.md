# Convert A Plaintext To A Base64 Format

To Conver a `Plaintext` string to a `Base64` string, Nodepp implements `encoder::base64::get()` function inside `encoder.h`, this function will return a new `string_t` in Base64 format on success or `nullptr` otherwise;

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/encoder.h>

using namespace nodepp;

void onMain() {

    auto data = "Hello World!";
    auto b64  = encoder::base64::get( data );

    console::log( b64 ); // SGVsbG8gV29ybGQh

}
```