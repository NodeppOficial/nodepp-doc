``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/crypto.h>

using namespace nodepp;

void onMain() {

    auto ppt = crypto::hash::SHA256();
         ppt.update("Hello World!");
    auto p = ppt.get_hex();

    console::log( "sha:>", p );

}
```