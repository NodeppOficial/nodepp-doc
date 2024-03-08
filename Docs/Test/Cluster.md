``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/cluster.h>

using namespace nodepp;

onMain([](){

    auto p = cluster::add();

    if( process::is_parent() ){
        console::log("is parent process");
    } else {
        console::log("is child process");
    }

})
```