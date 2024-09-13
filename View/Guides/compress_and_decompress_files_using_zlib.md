# Compress And Decompress Files Using ZLIB

Use `zlib::gzip::pipe` to compress a `file_t` file in Nodepp.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/zlib.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto write= fs::writable("PATH_1");
    auto read = fs::readable("PATH_2");

    read.onClose.once([](){ 
        console::log("Compressed"); 
    });

    zlib::gzip::pipe( read, write );

}
```

Use `zlib::gunzip::pipe` to decompress a `file_t` file in Nodepp.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/zlib.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto write= fs::writable("PATH_1");
    auto read = fs::readable("PATH_2");

    read.onClose.once([](){ 
        console::log("Dempressed"); 
    });

    zlib::gunzip::pipe( read, write );

}
```

`zlib.h` also supports other algorithms like:

- `inflate` & `deflate` :
    ```cpp
        zlib::inflate::pipe( read, write );
        zlib::deflate::pipe( read, write );
    ```

- `rawinflate` & `rawdeflate` :
    ```cpp
        zlib::rawinflate::pipe( read, write );
        zlib::rawdeflate::pipe( read, write );
    ```