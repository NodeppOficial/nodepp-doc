# Write A Response To A File

This code snippet writes a Response to disk at a particular path.

It uses the fast `stream::pipe()` API to efficiently write data to disk asynchronously. The first argument is a source `file_t`. The second argument is the destination `file_t`.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain(){

    fetch_t args;
            args.method = "GET";
            args.url = "http://www.google.com/";
            args.headers = header_t({
                { "Host", url::host(args.url) }
            });

    http::fetch( args )

    .then([]( http_t cli ){
        auto file = fs::writable("PATH_TO_FILE"); 

        cli.onData([]( string_t chunk ){
            console::log( chunk );
        }); 

        stream::pipe( cli, file );
    })

    .fail([]( except_t err ){
        console::error( err );
    });

}
```

Or you can even use the `stream::await()` API, and the `fs::write_file()` function, to synchronously write data into a file.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain(){

    fetch_t args;
            args.method = "GET";
            args.url = "http://www.google.com/";
            args.headers = header_t({
                { "Host", url::host(args.url) }
            });

    http::fetch( args )

    .then([]( http_t cli ){
        auto data = stream::await( cli );
        fs::write_file( "PATH_TO_FILE", data );
    })

    .fail([]( except_t err ){
        console::error( err );
    });

}
```