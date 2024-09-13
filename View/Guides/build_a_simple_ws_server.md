# Build A Simple WebSocket Server 

Start a simple WebSocket server using `ws::server()` function from `ws.h`.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>
#include <nodepp/ws.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain(){

    auto server = http::server([=]( http_t cli ){ 
        /* Server logic here */
    }); ws::server( server );

    server.onConnect([=]( ws_t cli ){

        console::log("connected");

        cli.onData([=]( string_t data ){
            console::log( data );
        });

        cli.onClose([=](){
            console::log("closed");
        });

    });

    server.listen( "localhost", 8000, [=]( socket_t server ){
        console::log("-> http://localhost:8000 <-");
    });

}
```