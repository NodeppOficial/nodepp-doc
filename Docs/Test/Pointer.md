``` cpp
#include <nodepp/nodepp.h>

using namespace nodepp;

class object { public: uint data = 10;
      object(){ console::log("created"); }
     ~object(){ console::log("deleted"); }
};

void onMain() {

    ptr_t<object> ptr = new object();

    process::add([=](){
    coStart

        while( ptr->data --> 0 ){
            console::log( ptr->data );
            coNext;
        }

    coStop
    });

}
```