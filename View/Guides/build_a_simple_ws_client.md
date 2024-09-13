# Build A Simple WebSocket Client 

Start a simple WebSocket client using `ws::client()` function from `ws.h`.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/fs.h>
#include <nodepp/ws.h>

using namespace nodepp;

void onMain() {

    auto cli = ws::client( "ws://localhost:8000/" );
    
    cli.onOpen([=](){ 
        
        console::log("connected"); 

        cli.onData([]( string_t chunk ){ 
            console::log("client:>",chunk); 
        });

        cli.onClose([](){ 
            console::log("closed"); 
            process::exit(1);
        });

    });

    cli.onError([=]( except_t err ){
        console::log(err);
    });

}
```