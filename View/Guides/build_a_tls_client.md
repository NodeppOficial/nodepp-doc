# Build A TLS Client

This starts a TLS client to `localhost:8000`.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/tls.h>

using namespace nodepp;

ssl_t ssl( "./ssl/cert.key", "./ssl/cert.crt" );

void onMain(){

    auto client = tls::client( &ssl );

    client.onOpen([=]( socket_t cli ){
    
        cli.onData([=]( string_t data ){
            console::log( data );
        });

        cli.onClose.once([=](){
            console::log("closed");
        });

        cli.write("Hello World!");

    });

    client.connect( "localhost", 8000 );

}
```