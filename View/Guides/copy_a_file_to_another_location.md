# Copy a file to another location

This code snippet copies a file to another location on disk.

It uses the fast `stream::pipe()` API to efficiently write data from one `file_t` to another `file_t` asynchronously. The first argument is a source `file_t` instance. The second argument is the destination `file_t` instance.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto fint = fs::readable( "Input.txt" );
    auto fout = fs::writable( "Output.txt" );

    fint.onClose([](){
        console::log("DONE");
    });

    stream::pipe( fint, fout );

}
```
