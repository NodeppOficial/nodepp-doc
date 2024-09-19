#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto file = fs::readable( "LICENSE" );

    file.onData([]( string_t line ){
        console::log( "->", line );
    });

    file.onClose([](){
        console::log("Done");
    });

    stream::line( file );

}