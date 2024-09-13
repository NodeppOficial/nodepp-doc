# Common HTTP Server Usage In Nodepp

This starts an HTTP server listening on port 3000. It demonstrates basic routing with a number of common responses and also handles POST data from standard forms or as JSON.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>
#include <nodepp/json.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain(){

    auto server = http::server([=]( http_t cli ){ 

        if( cli.path == "/" ){
            cli.write_header( 200, header_t({
                { "content-type", "text/plain" }
            }));
            cli.write("Welcome to Nodepp");
            return;
        }

        elif( cli.path == "/abc" ) {
            cli.write_header( 301, header_t({
                { "content-type", "text/plain" },
                { "Location", "/source" }
            }));
            return;
        }

        elif( cli.path == "/source" ) {
            auto file = fs::readable("LICENSE");
            cli.write_header( 200, header_t({
                { "content-type", "text/plain" }
            }));
            stream::pipe( file, cli );
            return;
        }

        elif( cli.path == "/api" ) {
            cli.write_header( 200, header_t({
                { "content-type", "text/plain" }
            }));
            cli.write( json::stringify( object_t({
                { "variable", "Hello World!" }
            }) ));
            return;
        }

        elif( cli.path == "/data" && cli.method == "POST" ){
            auto len  = string::to_ulong( cli.headers["Content-Length"] );
            auto data = cli.read( len ); console::log( "->", data );
            cli.write_header( 200, header_t({
                { "content-type", "text/plain" }
            }));
            cli.write( "DONE" );
            return;
        }

        cli.write_header( 404, header_t({
            { "content-type", "text/plain" }
        }));

        cli.write( "Oops 404 Error" );

    });

    server.listen( "localhost", 3000, [=]( socket_t server ){
        console::log("-> http://localhost:3000 <-");
    });

}
```