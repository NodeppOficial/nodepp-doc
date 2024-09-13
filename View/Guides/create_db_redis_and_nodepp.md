# Create A DB With Redis And Nodepp

```cpp
#include <nodepp/nodepp.h>
#include <redis/http.h>

using namespace nodepp;

void onMain() {

    redis_t db ("db://auth@localhost:8000");

    db.exec(" SET FOO BAT ");

    db.exec("GET FOO",[]( string_t data ){
        console::log( "->", data )
    });

}
```

[Github Repository](https://github.com/NodeppOficial/nodepp-redis)