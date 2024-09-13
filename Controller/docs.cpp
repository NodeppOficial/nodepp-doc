#pragma once

#include "./html.cpp"

namespace controller { namespace docs {

    express_tcp_t add () {
        express_tcp_t app;

        app.ALL([]( express_http_t cli ){
            cli.render( "DONE" );
        });

        return app;
    }

}}