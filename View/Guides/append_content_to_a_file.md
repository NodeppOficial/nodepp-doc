# Append Content To A File

Nodepp implements a `fs.h` header, which includes the `fs::append_file()` and also `file_t` class allows you write a file in append Mode.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {
    fs::append_file( "PATH_TO_FILE", "Hello World!" );
}
```

Or

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {
    auto file = file_t( "PATH_TO_FILE", "a" );
    file.write( "Hello World !" );
}
```