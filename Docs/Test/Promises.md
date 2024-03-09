``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/promise.h>
#include <nodepp/timer.h>

using namespace nodepp;

onMain([](){

    //Define a Promise
    promise_t<int,int>([=]( function_t<void,int> res, function_t<void,int> rej ){
        timer::timeout([=](){ res(10); },1000);
    })
    
    //If it's OK
    .then([=]( int res ){
        console::done(":>",res);
    })
    
    //If it Fails
    .fail([=]( int rej ){
        console::error(":>",rej);
    });

})
```