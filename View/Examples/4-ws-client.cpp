#include <nodepp/nodepp.h>
#include <nodepp/ws.h>

using namespace nodepp;

void onMain() {

    auto cli = ws::client( "ws://localhost:8000/" );
    
    cli.onOpen([=](){ 
        
        console::log("connected"); 
        cli.write( "Hello World" );

        cli.onClose([](){ 
            console::log("closed"); 
        });

        cli.onData([]( string_t data ){ 
            console::log(data);
        });

    });

    cli.onError([=]( except_t err ){
        console::log(err);
    });

}