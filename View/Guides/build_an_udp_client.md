# Build An UDP Client

This starts an UDP client to `localhost:8000`.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/udp.h>

using namespace nodepp;

void onMain(){

    auto client = udp::client();

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