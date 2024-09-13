# Write String To A File

This code snippet writes a string to disk at a particular absolute path.

It uses the fast `fs::write_file()` API to efficiently write data to disk. The first argument is a destination; the second is the data to write.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    string_t path = "/path/to/file.txt";
    string_t data = "Hello World!";

    fs::write_file( path, data );

}
```

Or, you can even use the `fs::writable()` function to create a `file_t` object in writable mode, and use the `.write()` function, to write data to disk. 

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto file fs::writable("/path/to/file.txt");
    string_t data = "Hello World!";

    file.write( data );

}
```