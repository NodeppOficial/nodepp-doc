#pragma once

#include <nodepp/stream.h>
#include <nodepp/json.h>
#include <nodepp/fs.h>
#include "./html.cpp"

namespace controller { namespace blog {

    express_tcp_t add () {
        express_tcp_t app;

        app.ALL( "/:name" ,[]( express_http_t cli ){ try {

            auto finf = fs::readable( regex::format( "./View/Blog/${0}/info.json", cli.params["name"] ) );
            auto info = json::parse( stream::await( finf ) );

            auto host = cli.protocol.to_lower_case() + "://" + cli.headers["Host"] + cli.path;

            auto file = fs::readable( "./View/article.html" );
            auto data = stream::await( file );

            cli.render( html::render( data , header_t({
                { "<!--DESCRIPTION-->", info["desc"].as<string_t>() },
                { "<!--AUTHOR-->",      info["auth"].as<string_t>() },
                { "<!--TITLE-->",       info["name"].as<string_t>() },
                { "<!--IMAGE-->",       info["img"].as<string_t>() },
                { "<!--ORIGIN-->",      host },
            }) ));

        } catch(...) {
            cli.redirect( 301, "/blog" );
        } });

        app.ALL([]( express_http_t cli ){
            
            auto file = fs::readable("./View/blog.html");
            auto data = stream::await( file );

            auto list = fs::read_folder("./View/Blog")

            .sort([=]( string_t a, string_t b ){
                uint pos[2] = { 0, 0 };
                string::parse(a.get(),"%u-",&pos[0]);
                string::parse(b.get(),"%u-",&pos[1]);
                return pos[0] >= pos[1];
            });

            string_t content; forEach( x, list ){
                auto file = fs::readable( regex::format( "./View/Blog/${0}/info.json", x ) );
                auto data = json::parse( stream::await( file ) );
                content  += regex::format( R"(
                    <a class="uk-padding-small uk-text-weak" 
                       href="/blog/${4}"> <h3> ${0} </h3> 
                        <img src="${2}"> </img>
                        <p class="uk-text-normal"> ${1} <br><br> 
                        <strong> Written by: </strong> ${3}
                        </p>
                        
                    </a>
                )", data["name"].as<string_t>(),
                    data["desc"].as<string_t>(),
                    data["img"] .as<string_t>(), 
                    data["auth"].as<string_t>(),x
                );
            }

            cli.render( html::render( data, header_t({
                "<!-- CONTENT -->", content
            }) ));
        });

        return app;
    }

}}