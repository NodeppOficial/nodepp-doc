``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>

using namespace nodepp;

onMain([](){

    fetch_t args;
            args.method = "GET";
            args.url = "http://www.google.com/";
            args.headers = {{ 
                { "Host", url::host(args.url) } 
            }};

    http::fetch( args )

    .then([]( http_t cli ){
        console::log( cli.headers["Host"] );
        
        cli.onData([]( string_t chunk ){
            console::log( chunk );
        }); 
        
        stream::pipe( cli );
    })

    .fail([]( except_t err ){
        console::error( err );
    });

})
```