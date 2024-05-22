``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/promise.h>
#include <nodepp/timer.h>

using namespace nodepp;

void onMain() {

    promise_t<int,int>([=]( function_t<void,int> res, function_t<void,int> rej ){
        timer::timeout([=](){ res(10); },1000);
    })
    
    .then([=]( int res ){
        console::done(":>",res);
    })
    
    .fail([=]( int rej ){
        console::error(":>",rej);
    });

}
```