#pragma once

/*────────────────────────────────────────────────────────────────────────────*/

#include <nodepp/map.h>
#include <nodepp/fs.h>

/*────────────────────────────────────────────────────────────────────────────*/

namespace controller { namespace html {

    string_t& render( string_t& data ){
        while( regex::test( data, "<°[^°]+°>" ) ){

            process::next();
            auto pttr = regex::match( data, "<°[^°]+°>" );
            auto name = regex::match( pttr, "[^<°> \n\t]+" );

            if( fs::exists_file( name ) ){ 
                auto str = stream::await( fs::readable( name ) );
                data = regex::replace_all( data, pttr, str );
            } else {
                data = regex::replace_all( data, pttr, "file does not exists" );
            }
            
        }   return regex::test(data,"<°[^°]+°>") ? render(data) : data;
    }

    /*.........................................................................*/

    string_t& render( string_t& data, map_t<string_t,string_t> list ){
        data = render( data ); forEach( x, list.data() ){
        data = regex::replace_all( data,x.first,x.second );
        }      return data;
    }

}}