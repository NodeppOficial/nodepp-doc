``` cpp
#include <nodepp/nodepp.h>
#include <nodepp/zlib.h>
#include <nodepp/fs.h>

using namespace nodepp;

onMain([](){

    auto B = fs::writable("Output_File");
    auto A = fs::readable("Input_File");

    zlib::gzip::pipe( A, B );

})

```