# Cluster

Clusters in Nodepp are a way to create child processes that all share server port, allowing a Nodepp application to take advantage of multi-core systems.

```cpp
#include <nodepp/nodepp.h>

#include <nodepp/cluster.h>
#include <nodepp/http.h>
#include <nodepp/fs.h>

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