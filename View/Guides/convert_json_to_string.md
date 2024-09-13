# Convert JSON To String

To Conver an `object_t` to a `string_t` again, Nodepp implements `json::stringify()` function inside `json.h`, this function will return a new `string_t` on success or `nullptr` otherwise;

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/json.h>

using namespace nodepp;

void onMain() {

    object_t obj ({
        { "var1", "Hello World" },
        { "var2", objec_t({
            "var1", 10
        })},
        { "var3", true }
    });

    console::log( json::stringify( obj ) );

}
```