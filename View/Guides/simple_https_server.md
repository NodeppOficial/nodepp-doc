# Simple HTTP + TLS Server

This starts an HTTPS server listening on port `3000`. It responds to all requests with a `Response` with status `200` and body `"Welcome to Nodepp!"`.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/https.h>

using namespace nodepp;

void onMain(){

    ssl_t ssl( "./ssl/cert.key", "./ssl/cert.crt" );

    auto server = https::server([=]( https_t cli ){

        console::log( cli.path, cli.get_fd() );
        
        cli.write_header( 200, header_t({
            { "content-type", "text/html" }
        }));
        
        cli.write( "Welcome to Nodepp!" );
        cli.close();

    }, &ssl );

    server.listen( "localhost", 3000, [=]( ssocket_t server ){
        console::log("-> https://localhost:3000 <-");
    });

}
```