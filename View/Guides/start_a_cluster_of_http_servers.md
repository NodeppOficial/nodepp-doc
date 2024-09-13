# Start A Cluster Of HTTP Servers

To run multiple HTTP servers concurrently, use the `cluster::add()` function in `cluster.h` which shares the same server across multiple forks.

This automatically load balances incoming requests across multiple instances of Nodepp.

```cpp
#include <nodepp/nodepp.h>

#include <nodepp/cluster.h>
#include <nodepp/http.h>

using namespace nodepp;

void server( int process ){

    auto server = http::server([=]( http_t cli ){ 
        //HTTP Logic Inside
    });

    server.listen( "localhost", 8000, [=]( socket_t server ){
        //Optional Callbac
    });

}

void onMain(){

    if( process::is_child() ){ server( os::pid() ); } else {
        for( auto x = os::cpus(); x--; ){
             auto y = cluster::add();
        }
    }

}
```
