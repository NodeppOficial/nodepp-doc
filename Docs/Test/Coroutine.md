``` cpp
#include <nodepp/nodepp.h>

using namespace nodepp;

onMain([](){

    process::add([=](){
        static int x = 10;
    coStart

        while( x-->0 ){
            console::log( ":>", x );
            coNext;
        }

    coStop
    });

})
```