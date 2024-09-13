#define MAX_FILENO 1048576

/*────────────────────────────────────────────────────────────────────────────*/

#include <nodepp/nodepp.h>
#include <express/http.h>

using namespace nodepp;

/*────────────────────────────────────────────────────────────────────────────*/

void onMain() {
    
    auto app = express::http::add();

    app.USE( express::http::ssr( "View" ) );

    app.listen( "localhost", 8000, []( ... ){
        console::log( "-> http://localhost:8000 <-" );
    });

}

/*────────────────────────────────────────────────────────────────────────────*/