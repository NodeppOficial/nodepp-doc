``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/crypto.h>

using namespace nodepp;

onMain([](){

    auto ppt = crypto::hash::sha256();
         ppt.update("Hello World!");
    auto p = ppt.get();

    console::log( "sha:>", p );

})
```