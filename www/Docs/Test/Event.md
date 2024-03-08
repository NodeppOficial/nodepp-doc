``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/event.h>

using namespace nodepp;

event_t<> event; 

onMain([](){

    event.on([](){ 
        console::done(" Hello World! "); 
    });

    event.once([](){ 
        console::done(" Hello World! "); 
    });
    
    event.emit();

})
```