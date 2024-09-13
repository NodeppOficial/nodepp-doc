# Stream A File As An HTTP Response

This snippet reads a file from disk using `fs::readable()`. This returns a `file_t` instance, which can be passed directly into the new Response constructor.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>
#include <nodepp/path.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain(){

    auto server = http::server([=]( http_t cli ){ 

        auto file = fs::readable( "LICENSE" );
        
        cli.write_header( 200, header_t({
            { "content-length", string::to_string( file.size() ) },
            { "content-type", path::mimetype( "LICENSE.txt" ) }
        }));
        
        stream::pipe( file, cli );

    });

    server.listen( "localhost", 3000, [=]( socket_t server ){
        console::log("-> http://localhost:3000 <-");
    });

}
```