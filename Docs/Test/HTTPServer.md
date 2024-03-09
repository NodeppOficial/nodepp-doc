``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>

using namespace nodepp;

onMain([](){

    auto server = http::server([=]( http_t cli ){

        console::log( cli.path, cli.get_fd() );
        
        cli.write_header( 200, {{
            { "content-type", "text/html" }
        }});
        
        cli.write("Hello World!");
        cli.close();

    });

    server.listen( "localhost", 8000, [=]( socket_t server ){
        console::log("server started at http://localhost:8000");
    });

})
```