# Read A File As FileStream

The `fs::readable()` function accepts a path and returns a `file_t` instance. The `file_t` class allows you to lazily read the file in a variety of formats. Use `stream::pipe()` to consume the file incrementally as a ReadableStream.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto file = fs::readable( "PATH_TO_FILE" );

    file.onData([]( string_t data ){
        console::log( data );
    });

    file.onClose([](){
        console::success( "DONE" );
    });

    stream::pipe( file );

}
```

The chunks of the stream can be consumed as an async iterable using await.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto file = fs::readable( "PATH_TO_FILE" );
    auto data = stream::await( file );

}
```