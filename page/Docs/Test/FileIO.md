``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/file.h>

using namespace nodepp;

onMain([](){
    
    //Write File
    file_t fileA ( "file.txt", "w" );
    fileA.write( "Hello Worl!" );
    fileA.close();

    /*-----------------------------------------*/

    //Read File
    file_t fileB ( "file.txt", "r" );
    console::log( fileB.read() );
    fileB.close();

})
```