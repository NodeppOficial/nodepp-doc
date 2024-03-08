``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/file.h>

using namespace nodepp;

onMain([](){
    
    file_t fileA ( "fileB.txt", "r" );
    file_t fileB ( "fileA.txt", "w" );

    fileA.onData([]( string_t chunk ){
        console::log( chunk );
    });

    fileA.onClose([](){
        console::log("done");
    });

    stream::pipe( fileA, fileB );

})
```