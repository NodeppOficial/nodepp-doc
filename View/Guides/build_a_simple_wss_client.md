# Build A Simple WebSocket + TLS Client 

Start a simple WebSocket client using `wss::client()` function from `wss.h`.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/timer.h>
#include <nodepp/wss.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    ssl_t ssl( "./ssl/cert.key", "./ssl/cert.crt" );
    
    auto client = wss::client( "wss://localhost:8000/", &ssl );
    
    client.onConnect([=]( wss_t cli ){ 
        
        console::log("connected"); 

        cli.onData([]( string_t chunk ){ 
            console::log("client:>",chunk); 
        });
        
        cli.onClose([](){ 
            console::log("closed"); 
            process::exit(1);
        });

    });

}
```