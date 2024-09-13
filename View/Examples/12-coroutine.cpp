#include <nodepp/nodepp.h>

using namespace nodepp;

void onMain() {

    process::add([=](){
        static int x = 10;
    coStart

        while( x-->0 ){
            console::info( "->", x );
            coDelay( 1000 );
            coNext;
        }

    coStop
    });

}