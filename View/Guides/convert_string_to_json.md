# Convert String To JSON

To convert an `string_t` to an `object_t`, Nodepp implements `json::parse()` function inside `json.h`, this function will return a new `object_t` on success or `nullptr` otherwise;

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/json.h>

using namespace nodepp;

void onMain() {

    string_t data = R"({
        "var1": 1000,
        "var2": true,
        "var3": { 
            "var1": "Hello World"
        },
        "var4": [ 10, 20, 30, 40, 50 ]
    })";

    object_t obj = json::parse( data );

    console::log( "->", obj["var1"].as<int>() );
    console::log( "->", obj["var4"][2].as<int>() );
    console::log( "->", obj["var3"]["var1"].as<string_t>() );
    console::log( "->", obj["var2"].as<bool>() ? "🟢":"🔴" );

}
```