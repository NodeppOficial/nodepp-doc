``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/event.h>

using namespace nodepp;

event_t<> event; 

onMain([](){

    event.on([](){ 
        console::done("execute too many times"); 
    });

    event.once([](){ 
        console::done("execute only once"); 
    });
    
    event.emit();

})
```