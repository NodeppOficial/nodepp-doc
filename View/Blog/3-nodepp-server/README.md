# How to create an Asynchronous Web Server in C++ Under 40 Lines Of Code

![Image](https://miro.medium.com/v2/resize:fit:720/format:webp/1*hXHAdcN0BaXEQfsZtdHRaQ.png)

In this article, you will learn how to make your web server using C++ and Nodepp, allowing you to understand the fundamentals of server-side programming simply and efficiently. Get ready to immerse yourself in the exciting world of creating web servers with Nodepp!

Let’s get started.

## What is this HTTP server?

Hypertext Transfer Protocol — HTTP, is a standard for sending and receiving data, whether in HTML, JSON, or plain text format over the Internet. It was designed mainly to establish communication between browsers and web servers, and it is one of the most used protocols today.

if you want to know more about it, I’ll recommend you read this [page](https://developer.mozilla.org/en-US/docs/Learn/Common_questions/Web_mechanics/What_is_a_web_server).

![Image1](https://study-ccna.com/wp-content/images/http_process_explained.jpg)

## What is Nodepp?

Now, Nodepp is an open-source project written in C++, whose main objective is to facilitate the creation of software in C++ using a friendly syntax in the process. With Nodepp, we will be able to create HTTP, HTTPS, TLS, TCP, Websocket, and more. Not only that, the great thing about Nodepp is that it is 100% asynchronous, thanks to an internal Event Loop which is responsible for managing Nodepp’s internal tasks, allowing us to create scalable and concurrent applications in just a few lines of code.

![Image2](https://miro.medium.com/v2/resize:fit:720/format:webp/1*5OQcgZl8T5ZRhkQTVz_UdA.png)

Now, to install Nodepp on our PC, we must first go to [the official Nodepp repository on Github](https://github.com/NodeppOficial/nodepp/), copy the repository link, and clone the project to our PC with a git client.

![Image4](https://miro.medium.com/v2/resize:fit:720/format:webp/1*ZTWBWXaUinDMzHaJe_CzNg.png)

Once downloaded, we must open the project from any IDE. I will open it from Visual Studio Code.

![Image5](https://miro.medium.com/v2/resize:fit:720/format:webp/1*m-bCrZ_bckaT0GaQG9GW9A.png)

Now we have to create a main.cpp file inside the Nodepp project, and include the following libraries:

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>
#include <nodepp/path.h>
#include <nodepp/fs.h>
```

These are all the libraries that we are gonna use to create a 100% functional web server. We are also going to include the using namespace nodepp, which will allow us to access the Nodepp content from the main.cpp.

```cpp
using namespace nodepp;
```

Now we have to include our main function, right? to do so, we have to invoke an event called onMain with which we will be able to initialize our code without having to do strange things to initialize Nodepp. The code in question would look like this.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>
#include <nodepp/path.h>
#include <nodepp/fs.h>

using namespace nodepp;

onMain([](){ /* Our code goes here */ })
```

But if you’re not comfortable using onMain event, you can also use this other way.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>
#include <nodepp/path.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

  //Our code goes here

}
```

Now to create our first web server in C++, we must first include an HTTP server instance in our code.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>
#include <nodepp/path.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto server = http::server([=]( http_t cli ){
        //place the HTTP request's logic here.
    });

}
```

Now we need to make this server listen for new incoming messages.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>
#include <nodepp/path.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    // first, create an http server instance
    auto server = http::server([=]( http_t cli ){});

    // second, make it listen for incomming messages
    server.listen( "localhost", 8000 );

}
```

But, we can also include a callback that will be executed when the Web server is successfully initialized, inside the listen function.

```cpp
    server.listen( "localhost", 8000, [=]( socket_t /*unused*/ ){
        console::log("server started at http://localhost:8000");
    });
```

And last, we must define the logic that our server must follow to handle incoming messages. So, inside the server callback, we must add the next code.

```cpp
    auto server = http::server([=]( http_t cli ){ 

    // first, we need to normalize the client's path we want to get in.
    string_t dir = "www/index.html";
    if( cli.path != "/" )
        dir = path::join( "www", cli.path );

    // then, we need to filter or skip non available files.
    if( !fs::exists_file(dir) ){
        cli.write_header( 404, {{ { "content-type", "text/plain" } }} );
        cli.write( "Oops 404 time" ); 
        cli.close(); return;
    }

    // now, we must have to create a file as a readable stream.
    auto str = fs::readable( dir );
    
    // we also need to send back the header response
    cli.write_header( 200, {{
        { "Content-Length", string::to_string(str.size()) },
        { "Content-Type",   path::mimetype(dir) }
    }});

    // finally, we can pipe back the file's response 
    stream::pipe( str, cli );

    });
```

And that’s it, All you need to do is compile the code. However, before we proceed with that, we need to define the page that our server will serve. To accomplish this, I have created a basic web page and saved it in the ./www folder.

![Image6](https://miro.medium.com/v2/resize:fit:640/format:webp/1*KuqaQmghqnzs9N8fg6KdyA.png)

With this in place, we can now proceed with compilation.

![Image7](https://miro.medium.com/v2/resize:fit:640/format:webp/0*KZnEfJb4K40XM0sE.gif)

## Source Code

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>
#include <nodepp/path.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto server = http::server([=]( http_t cli ){

        string_t dir = "www/index.html";
        if( cli.path != "/" )
            dir = path::join( "www", cli.path );

        console::log( cli.path, cli.get_fd() );

        if( !fs::exists_file(dir) ){
            cli.write_header( 404, {{ { "content-type", "text/plain" } }} );
            cli.write("Opps 404 error"); 
            cli.close(); return;
        }

        auto str = fs::readable( dir );

        cli.write_header( 200, {{
            { "Content-Length", string::to_string(str.size()) },
            { "Content-Type",   path::mimetype(dir) }
        }});

        stream::pipe( str, cli );
    });

    server.listen( "localhost", 8000, [=]( socket_t /*unused*/ ){
        console::log("server started at http://localhost:8000");
    });

}
```

## Conclusion

As you can see, making an HTTP server in C++ is not too complicated, with Noddpp we can significantly simplify the development of complex applications in C++, such as web servers. In essence, Nodepp stands as a robust framework that makes it faster to create asynchronous applications (not just web servers) in C++. By aligning with the NodeJS syntax, we can leverage the strengths of the C++ language while embracing the easy-to-use nature and adaptability of NodeJS.

thanks for read this article 👍