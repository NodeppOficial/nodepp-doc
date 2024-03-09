``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/ws.h>

using namespace nodepp;

onMain([](){

    //define a ws server instance
    auto server = ws::server();

    //onConnect WS event
    server.onConnect.on([]( ws_t cli ){

        console::log("connected");

        cli.onData([=]( string_t data ){
            console::log( data );
        });

        cli.onClose([=](){
            console::log("closed");
        });

    });

    //Make your server accept new clients
    server.listen( "localhost", 8000, []( ... ){
        console::log("server started at ws://localhost:8000");
    });

})
```