``` cpp
#include <nodepp/nodepp.h>

using namespace nodepp;

//Define an object you want to share
class object { public: uint data = 10;
      object(){ console::log("created"); }
     ~object(){ console::log("deleted"); }
};

onMain([](){

    //Create your first Smart Pointer
    ptr_t<object> ptr = new object();

    //Create a new async process
    process::add([=](){
    coStart

        while( ptr->data --> 0 ){
            console::log( ptr->data );
            coNext;
        }

    coStop
    });

})
```