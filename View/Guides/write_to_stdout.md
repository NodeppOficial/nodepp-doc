# Write To Stdout

The `console.log()` function writes to stdout. It will automatically append a line break at the end of the printed data.

```cpp
#include <nodepp/nodepp.h>

using namespace nodepp;

void onMain() {

    console::log("Hello World !");

}
```

For more advanced use cases, Nodepp exposes stdout as a `file_t` via the `fs::std_output` property. This can be used as a destination for `file.write()`.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto file = fs::std_output();

    file.write( "Hello World! \n" );

}
```

Or read a file in real-time and show every single chunk

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto fint = fs::readable( "PATH_TO_FILE" );
    auto file = fs::std_output();

    stream::pipe( fint, file );

}
```