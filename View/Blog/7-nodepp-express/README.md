# Building Web Applications in C++ with ExpressPP: A Comprehensive Guide

![Image](https://miro.medium.com/v2/resize:fit:720/format:webp/1*JeyuP5rL8kMxETDgelcF0g.png)

[ExpressPP](https://github.com/NodeppOficial/nodepp-express) is a library for building web applications on top of C++. It provides a robust set of features and tools that make it easy to develop scalable and maintainable web applications. In this post, we will explore the various components of ExpressPP and learn how to build a basic web application using it. To summaries, you will learn:

- Setting up a basic **ExpressPP** application
- Routing & Middleware
- Serving static files
- Handling forms and input data
- Cookies & User authentication

## What is ExpressPP?

**ExpressPP** is a web application library for **C++**. It provides a set of tools and features for building web applications and APIs quickly and easily. It simplifies the process of building web applications by providing a robust set of features for handling HTTP/s requests and responses, routing, middleware, templates and views, serving static files, and more.

## Setting up a basic ExpressPP application

To set up a basic ExpressPP application, follow these steps:

- Create a new folder for your project and navigate to it in your terminal.
- Clone and initialize a new  [Nodepp project](https://github.com/NodeppOficial/nodepp).
- Clone and install the [ExpressPP project](https://github.com/NodeppOficial/nodepp-express).
- Create a new `.cpp` file in the project directory and name it `main.cpp` or any name you prefer.
- Open `main.cpp` file in your code editor and add the following code:

```cpp
#include <nodepp/nodepp.h>
#include <express/http.h>

using namespace nodepp;

void onMain() {

    auto app = express::http::add();

    app.GET( "/", []( express_http_t cli ){
        cli.send( "Hello, World!" );
    });

    app.listen( "0.0.0.0", 3000, []( ... ){
        console::log("Server listening on port 3000");
    });

}
```

In the above code, we have included the express library and created a new Express application by calling the, `express::http::add()` function, which returns an instance of the application.

We have then defined a route for the root URL `/` using the `app.GET()` method. When the root URL is requested, the server will send the response `Hello, World!`.

Finally, we have started the server by calling the `app.listen()` method and passing in the address, the port number that the server should listen on. In this case, the server will listen on port `3000`.

- Save the changes and compile the code.
```bash
🪟: g++ -o main main.cpp -I ./include -lssl -lcrypto -lws2_32 ; ./main
🐧: g++ -o main main.cpp -I ./include -lssl -lcrypto ; ./main
```

- Open your web browser and navigate to `http://localhost:3000` to see the `Hello, World!` message displayed in your browser.

Congratulations, you have now set up a basic ExpressPP application!

![Image2](https://miro.medium.com/v2/resize:fit:720/format:webp/1*DmwdfBSE7Q2CFl1bhjQKIA.png)

## Routing in ExpressPP

Routing in **ExpressPP** refers to the process of defining application end points and how requests and responses should be handled at each endpoint. Routing in **ExpressPP** can be done using the `app.GET()`, `app.POST()`, `app.DELETE()` or `app.ALL()` method, which creates a new router object.

Here is an example of how to define a basic route in an ExpressPP application:

```cpp
#include <nodepp/nodepp.h>
#include <express/http.h>

using namespace nodepp;

void onMain() {

    auto app = express::http::add();

    // Define a route
    app.GET( "/hello", []( express_http_t cli ){
        cli.send( "Hello, World!" );
    });

    // Start the server
    app.listen( "0.0.0.0", 3000, []( ... ){
        console::log("Server listening on port 3000");
    });

}
```

In the above example, we have defined a route that listens for GET requests to the `/hello` endpoint. When a request is made to this endpoint, the server will respond with the message `Hello, world!`.

Routing in `ExpressPP` can be more complex than this, however. You can define routes that accept parameters, use middleware, and more. Here is an example of a more complex route definition:

```cpp
#include <nodepp/nodepp.h>
#include <express/http.h>

using namespace nodepp;

void onMain() {

    auto app = express::http::add();

    app.USE("/users/:id", []( express_http_t cli, function_t<void> next ){

        // Retrieve the user from the database
        auto user = db::getUserById( cli.params["id"] );
        
        // If the user is not found, pass control to the error handler
        if ( !user ) {
            console::error( "User not found" );
            next();
        }
        
        // Render the user"s profile page
        res.sendJSON( json::stringify( object_t({
            { "user", user }
        }) ));

    });

    app.listen( "0.0.0.0", 3000, []( ... ){
        console::log("Server listening on port 3000");
    });

}
```

In this example, we are defining a route that accepts a parameter `id` in the URL. We then retrieve the user with that `ID` from the database, and render a template with the user"s information. If the user is not found, we pass control to the error handler middleware by calling next().

Routing is a fundamental concept in building web applications with `ExpressPP`, and is used extensively throughout the framework.

## Using Middleware in ExpressPP

Middleware in Express is a function that acts as a bridge between an incoming request and the route handler. It allows you to execute some logic before the request is sent to the route handler. For example, you can use middleware to authenticate users, parse data, or add headers to the response.

Here’s an example of how to use middleware in Express:

```cpp
#include <nodepp/nodepp.h>
#include <express/http.h>

using namespace nodepp;

void onMain() {

    auto app = express::http::add();

    // Define a middleware
    app.USE( []( express_http_t cli, function_t<void> next ){
        console::log( regex::format( 
            "Received a ${0} request from ${1}",
            cli.method, cli.get_peername()
        )); next();
    });

    // Route handler
    app.GET( "/", []( express_http_t cli ){
        cli.send("Hello, World!");
    });

    app.listen( "0.0.0.0", 3000, []( ... ){
        console::log("Server listening on port 3000");
    });

}
```

In this example, we define a middleware function with `app.USE` that logs a message to the console every time a request is made. When a request is received, the middleware function is executed first, then the route handler is executed.

There are several other ways to use middleware in Express, such as attaching it to a specific route, or a group of routes. You can also apply middleware globally to all requests by using `app.USE()` without a specific path.

### Is it essential to use middleware? and what are more use cases of them?

Using middleware is not essential, but it’s a very useful feature that can greatly enhance the functionality of your Express application. Here are some common use cases for middleware:

- **Authentication:** You can use middleware to authenticate users before allowing them to access certain routes.
- **Data parsing:** You can use middleware to parse incoming data, such as JSON or form data, so that it can be easily accessed in your route handlers.
- **Error handling:** You can use middleware to handle errors that occur during the processing of requests.
- **Logging:** You can use middleware to log information about requests, such as the request method, IP address, and request/response time.
- **CORS:** You can use middleware to handle Cross-Origin Resource Sharing (CORS) and set appropriate headers to control who can access your API.
- **Static file serving:** You can use middleware to serve static files, such as images, CSS, and JavaScript files, from your Express application.

In general, middleware can be used for any logic that needs to be executed before the route handler is called. It’s a powerful feature that makes it easy to modularize and reuse your code, making it easier to maintain and scale your application.

## Serving static files in ExpressPP

In ExpressPP, serving static files such as images, CSS, and JavaScript files is a common task. ExpressPP makes it easy to serve static files using the `express::http::file()` or `express::https::file()` middleware function.

The `express::http::file()` function takes one argument, which is the directory from where the static files should be served. Once the middleware function is set up, any file in the specified directory can be accessed from the browser with the URL path.

Here’s an example of how to set up the `express::http::file()` middleware function in an `ExpressPP` app:

```cpp
#include <nodepp/nodepp.h>
#include <express/http.h>

using namespace nodepp;

void onMain() {

    auto app = express::http::add();
    
    // serve static files from the public directory
    app.USE( "/", express::http::file( "public" ) );

    app.listen( "0.0.0.0", 3000, []( ... ){
        console::log("Server listening on port 3000");
    });

}
```

In the example above, the `express::http::file()` function is used to serve files from the public directory. This means that any file in the public directory can be accessed from the browser with the URL path, for example: `http://localhost:3000/images/logo.png`.

It’s also possible to serve static files from multiple directories by calling the `express::http::file()` middleware function multiple times, passing a different directory each time.

```cpp
#include <nodepp/nodepp.h>
#include <express/http.h>

using namespace nodepp;

void onMain() {

    auto app = express::http::add();

    // serve static files from the public directory
    app.USE( "/public", express::http::file( "public" ) );

    // serve static files from the asset directory
    app.USE( "/assets", express::http::file( "assets" ) );

    app.listen( "0.0.0.0", 3000, []( ... ){
        console::log("Server listening on port 3000");
    });

}
```

In the example above, files from both the `public` and `assets` directories can be accessed from the browser.

Serving static files with `ExpressPP` is a simple and efficient way to serve static assets for your web application.

## Handling forms and input data in ExpressPP

In a web application, forms are commonly used to collect input data from users. ExpressPP provides built-in functionality to handle forms and input data through `middlewares` or `routers` using `query::parse()` function.

Now let’s see an example:

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/query.h>

#include <express/http.h>

using namespace nodepp;

void onMain() {

    auto app = express::http::add();

    app.POST("/read_body", []( express_http_t cli ){

        auto len  = string::to_ulong( cli.headers["Content-Length"] );
        auto data = query::parse( "?" + cli.read( len ) );

        console::log( data["arg"] );

        cli.send( data["arg"] );

    });

    app.listen( "0.0.0.0", 3000, []( ... ){
        console::log("Server listening on port 3000");
    });

}
```

In this example, a `route handler` is set up to handle the POST request made when a form is submitted. The data submitted in the form is available in the `cli.read()` function. In this case, the data is logged to the console and a response is sent to the client.

Other types of input data, such as json, can also be handled using `cli.read()`.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/json.h>

#include <express/http.h>

using namespace nodepp;

void onMain() {

    auto app = express::http::add();

    app.POST("/read_json", []( express_http_t cli ){

        auto len  = string::to_ulong( cli.headers["Content-Length"] );
        auto data = json::parse( cli.read( len ) );
        console::log( data["arg"].as<string_t>() );
        cli.send( data["arg"].as<string_t>() );

    });

    app.listen( "0.0.0.0", 3000, []( ... ){
        console::log("Server listening on port 3000");
    });

}
```

## Cookies and JWT Authentication in ExpressPP

Cookies are used for maintaining state between HTTP requests. They are used to store data on the client’s side. In ExpressPP, cookies are set by using `app.cookie()` function. In other hands cookies are parsed by using `cookie::parse()` function from `cookie.h`.

Let’s see an example:

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/cookie.h>
#include <express/http.h>

using namespace nodepp;

void onMain() {

    auto app = express::http::add();

    app.GET("/write_cookie", []( express_http_t cli ){
        cli.cookie( "name", "value" );
        cli.send( "DONE" );
    });

    app.GET("/read_cookie", []( express_http_t cli ){
        auto data = cookie::parse( cli.headers["Cookie"] );
        console::log( "->", data["arg"] );
        cli.send( data["arg"] );
    });

    app.listen( "0.0.0.0", 3000, []( ... ){
        console::log("Server listening on port 3000");
    });

}
```

User authentication is a crucial aspect of any web application that requires secure access control. It involves validating user identity and authorizing access to resources or functionalities based on user credentials.

For this post, we will be using JWT-based authentication. Make sure you have installed [ExpressPP](https://github.com/NodeppOficial/nodepp-express) and also [JWT](https://github.com/NodeppOficial/nodepp-jwt). 

Let’s start with the example:

```cpp
#define SECRET "SECRET_JWT_PASSWORD"

#include <nodepp/nodepp.h>
#include <nodepp/crypto.h>
#include <nodepp/cookie.h>

#include <express/http.h>
#include <jwt/jwt.h>

using namespace nodepp;

void onMain() {

    auto app = express::http::add();

    app.POST( "/login", []( express_http_t cli ){

        auto len  = string::to_ulong( cli.headers["Content-Length"] );
        auto data = query::parse( "?" + cli.read( len ) );

        if( data["user"].empty() || data["pass"].empty() ) {
            cli.status( 404 ).send( "Something Went Wrong" );
        }

        auto user = data["user"];
        auto pass = data["pass"];

        auto hash = crypto::hash::SHA256();
             hash.update( user + pass );

        if( user == "admin" && pass == "password" ){
            cli.cookie( "auth", jwt::HS256::encode( 
                json::stringify( object_t({
                    { "hash", hash.get() },
                    { "user", "admin" }
                })), SECRET
            ));
            cli.send( "Logged Successfuly" );
            return;
        } else {
            cli.status( 401 )
               .send( "Invalid User or Password" );
            return;
        }

    });

    app.GET("/protected", []( express_http_t cli ){
        if( cli.headers["Cookie"].empty() ){ goto ERROR; }

        do {

        auto data = cookie::parse( cli.headers["Cookie"] );

        if( !jwt::HS256::verify( data["auth"], SECRET ) )
          { goto ERROR; }

        auto info = json::parse( 
            jwt::HS256::decode( data["auth"] )
        );

        cli.send( regex::format(
            "Hello World ${0}",
            info["user"].as<string_t>()
        )); 

        } while(0);
        
        return; ERROR:;
        cli.send( "You are not autorized" ); 
    });

    app.GET("/logout", []( express_http_t cli ){
        if( cli.headers["Cookie"].empty() ){ goto ERROR; }
        cli.clear_cookies(); cli.send("Logout Successfuly"); 
        return; ERROR:;
        cli.send( "Something Went Wrong" ); 
    });

    app.GET( []( express_http_t cli ){
        cli.send("<h1> Hello World </h1>");
    });

    app.listen( "0.0.0.0", 3000, []( ... ){
        console::log("Server listening on port 3000");
    });

}
```

![Image](https://miro.medium.com/v2/resize:fit:720/format:webp/1*Tzrk5jgEPFjR4CMdEATfpg.png)

In this example, we have used JWT create and manage user authentication. Then We have defined three routes:

- `/login`: Authenticates the user by checking the credentials and creating a new **JWT** for the user.
- `/protected`: A protected route that can only be accessed by authenticated users.
- `/logout`: Destroys the user cookies.

When the user logs in successfully, we set a new **JWT token** in the cookie that contains the user's username and hash. When the user logs out, we destroy the cookie, which removes all user's data.

In the protected route, we check if the user is authenticated by checking if the user was signed with the `SECRET` key. If the user is not authenticated, we return a `401 Unauthorized response`.

Overall, user authentication is a critical aspect of web development, and using the right authentication mechanism can help ensure the security of your application.

Thanks for reading! If you enjoy reading this post, got help, knowledge, inspiration, and motivation through it. And if you want to support me — you can [“buy me a coffee.”](https://ko-fi.com/D1D8VFJZC) Your support really makes a difference ❤️