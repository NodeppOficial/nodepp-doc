``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>

using namespace nodepp;

onMain([](){

    //Create a new HTTP Server Instance
    auto server = http::server([=]( http_t cli ){

        console::log( cli.path, cli.get_fd() );
        
        cli.write_header( 200, {{
            { "content-type", "text/html" }
        }});
        
        cli.write("Hello World!");
        cli.close();

    });

    //Make your server accept new clients
    server.listen( "localhost", 8000, [=]( socket_t server ){
        console::log("server started at http://localhost:8000");
    });

})
```