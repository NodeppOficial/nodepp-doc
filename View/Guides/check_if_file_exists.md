# Check If A File Exists

The `fs::readable()` function accepts a path and returns a `file_t` instance. Use the `fs::exists_file()` method to check if a file exists at the given path.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    if( !fs::exists_file("PATH_TO_FILE") ){
        process::error("File Does Not Exists");
    } else {
        auto file = fs::readable( "PATH_TO_FILE" );
        auto data = stream::await( file );
        console::log( "->", data );
    }

}
```