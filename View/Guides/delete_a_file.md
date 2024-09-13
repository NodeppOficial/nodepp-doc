# Delete A File

To synchronously delete a file with Nodepp, use the `remove_file()` or `remove_folder()` function from the `fs.h`.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    fs::remove_file( "PATH_TO_FILE" );

    // or

    fs::remove_folder( "PATH_TO_FOLDER" );

}
```