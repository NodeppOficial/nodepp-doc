#include <nodepp/nodepp.h>
#include <nodepp/timer.h>
#include <nodepp/http.h>
#include <nodepp/path.h>
#include <nodepp/date.h>
#include <nodepp/fs.h>

/*────────────────────────────────────────────────────────────────────────────*/

using namespace nodepp;

void HTTPHandler( http_t cli ) {

    string_t dir = "../index.html";
    if( cli.path.size() > 1 )
        dir = path::join( "..", cli.path );

    console::log( cli.path, cli.get_fd() );

    if( !fs::exists_file(dir) ){
        cli.write_header( 404, header_t({ { "content-type", "text/plain" } }) );
        cli.write( string::format("404: Oops time: %s",date::fulltime().data()) ); 
        cli.close(); return;
    }

    auto str = fs::readable( dir );

    if( cli.headers["Range"].empty() ){

        cli.write_header( 200, header_t({
            { "Content-Length", string::to_string(str.size()) },
        //  { "Cache-Control", "public, max-age=3600" },
            { "Content-Type",   path::mimetype(dir) }
        }));

        if(!regex::test(path::mimetype(dir),"audio|video") ) 
            stream::pipe( str, cli );

    } elif ( !cli.headers["Range"].empty() ) {

        array_t<string_t> range = regex::match_all(cli.headers["Range"],"\\d+","i");
        ulong rang[2]; rang[0] = string::to_ulong( range[0] );
              rang[1] = min( rang[0]+CHUNK_MB(10), str.size()-1 );

        cli.write_header( 206, header_t({
            { "Content-Range", string::format("bytes %lu-%lu/%lu",rang[0],rang[1],str.size()) },
            { "Content-Type",  path::mimetype(dir) }, 
            { "Accept-Range", "bytes" }
        }));

        str.set_range( rang[0], rang[1] ); stream::pipe( str, cli );

    }

}

void onMain() {

    auto server = http::server( HTTPHandler );

    server.listen( "localhost", 8000, [=]( socket_t /*unused*/ ){
        console::log("server started at http://localhost:8000");
    });

}

/*────────────────────────────────────────────────────────────────────────────*/