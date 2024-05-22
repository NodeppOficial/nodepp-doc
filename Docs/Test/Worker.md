``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/worker.h>

using namespace nodepp;

void onMain() {

    worker::add([=](){ 
        static int x = 10;
    coStart

        while( x-->0 ){
            console::info( "->", x );
            worker::delay( 100 ); 
            coNext;
        }

    coStop
    });

}
```