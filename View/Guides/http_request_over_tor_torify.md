# HTTP Request Over TOR With Nodepp And Torify 

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/url.h> 
#include <tor/http.h>

using namespace nodepp;

void onMain() {

    tor_fetch_t args;
    args.timeout = 0; // Disable Fetch timeout
    args.method  = "GET";
    args.tor     = "tcp://localhost:9050";
    args.url     = "http://check.torproject.org/";
    args.headers = header_t({
        { "Host", url::hostname( args.url ) }
    });

    tor::http::fetch( args )

    .then([]( http_t cli ){
        console::log( cli.read() );
    })

    .fail([]( except_t err ){
        console::log(err);
    });

}
```

[Github Repository](https://github.com/NodeppOficial/nodepp-torify)