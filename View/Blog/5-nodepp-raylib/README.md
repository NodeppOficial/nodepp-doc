# Create your own online multiplayer: Small, fast, and fun with Raylib, Nodepp, and Websockets!

![Image1](https://miro.medium.com/v2/resize:fit:720/format:webp/1*2EkftZukONO2_VouR6xXUQ.jpeg)

Do you dream of creating your own online multiplayer game? Now is your chance! In this tutorial, I will guide you step by step in developing a small multiplayer using Raylib, Nodepp, and Websockets.

Here you will learn:

- **The Basics of Raylib:** A Graphics and Gaming Library for C/C++.
- **The power of Nodepp:** A lightweight and efficient framework for C++.
- **The magic of WebSockets:** A technology that allows bidirectional communication in real time between the client and the server.

It doesn’t matter if you are a beginner or an experienced developer, this tutorial will provide you with the tools and knowledge necessary to create your own online multiplayer game.

Are you ready to start? Read on and get ready for an exciting adventure!

## What is this Websocket?

WebSocket is a communication protocol that enables real-time, bidirectional data exchange between a client (such as a web browser) and a server. Unlike HTTP, which establishes a connection for each request and response, WebSocket maintains an open connection, allowing the constant flow of information.

![Image2](https://miro.medium.com/v2/resize:fit:720/format:webp/0*iiqcczeby7lAY7eA.png)

## Implementation

Ok, before continuing, I recommend reading this other article called [Creating the Snake Game: A Journey Through Event-Driven Programming in C++ with Nodepp and Raylib](./4-nodepp-snake), since part of the code that we will use next comes from that article.

So if you already read it, let’s continue.

Ok, we must remember that Nodepp allows us to program in C++ 100% asynchronously and also event-driven, so to create our first WebSocket server, we must use the next code.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/ws.h>

using namespace nodepp;

void onMain() {

     // WebSocket server inicialization
    auto server = ws::server();

    server.onConnect([]( ws_t cli ){

        // to know when there is a new client
        console::log("connected");

        cli.onData([=]( string_t data ){
            // to read client's messages
        });

        cli.onClose([=](){
            // to know when client is disconnected
        });

    });

    server.listen( "localhost", 8000, []( ... ){
        console::log("server started at ws://localhost:8000");
    });

}
```

And also, if we want to create a WebSocket client we must use this other code.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/ws.h>

using namespace nodepp;

void onMain() {

    // Websocket client Inicialization
    auto client = ws::client( "ws://localhost:8000/" );
    
    // Websocket events
    client.onOpen([=](){ });
    client.onClose([=](){ });
    client.onError([=]( except_t err ){ });
    client.onMessage([=]( string_t data ){ });

}
```

Everything is great at this point, right? it looks simple and easy to use. Ok, to avoid having to rewrite the code twice, once for the client and other for the server, Nodepp allows us to write environment variables at runtime:

```cpp
#include <nodepp/nodepp.h>

using namespace nodepp;

void onMain() {

    if( process::env::get("mode") == "server" ){
        // Websocket Server logic goes here
    } else {
        // WebSocket Client logic goes here  
    }

}
```

```bash
g++ -o main main.cpp -I ./include ; ./main ?mode=client #client mode
g++ -o main main.cpp -I ./include ; ./main ?mode=server #server mode
```

Once we understand how to create WebSocket clients and servers, now we can get our hands on the code.

First, we must create a header object, which contains all the necessary information about the status of the players.

```cpp
struct item_header {
  rl::Vector2 siz;
  rl::Vector2 pos;
  rl::Color   col;
};

map_t<string_t,optional_t<item_header>> players;
```

Now, we must create our player, that will respond to our events.

```cpp
objects["player"] = optional_t<item_t>([=]( item_t& self ){
      
   // Some Attributes
   self.attr = {{ { "pos", rl::Vector2({ 0, 0 }) } }};

   // onLoop Event
   auto idl = onLoop([=]( float delta ){
        auto pos = self.attr["pos"].as<rl::Vector2>();

          if( rl::IsKeyDown( rl::KEY_W ) ){ pos.y -= delta * 100; }
        elif( rl::IsKeyDown( rl::KEY_S ) ){ pos.y += delta * 100; }
          if( rl::IsKeyDown( rl::KEY_A ) ){ pos.x -= delta * 100; }
        elif( rl::IsKeyDown( rl::KEY_D ) ){ pos.x += delta * 100; }
        
        self.attr["pos"] = pos;
   });

   // A timer to send our attributes over WS
   auto tmr = timer::interval([=](){
       auto pos = self.attr["pos"].as<rl::Vector2>();

       item_header info({
          .siz = rl::Vector2({ 10, 10 }),
          .pos = pos, .col = BLUE,
       });

       string_t message ( sizeof(info) );
       memcpy( message.get(), &info, sizeof(info) );
       onSend.emit( message ); 
   
    },100);

    // An onDraw Event to draw our player
    auto idd = onDraw([=](){
        auto pos = self.attr["pos"].as<rl::Vector2>();
        rl::DrawRectangle( pos.x, pos.y, 10, 10, RED );
    });
    
    // And onRemove Event to clear all evnts once item is removed
    self.onRemove([=](){
        console::log( "removed" );
        timer::clear( tmr );
        onDraw.off( idd );
        onLoop.off( idl );
    });
    
});
```

As you can see, I am emitting an onSend event inside the main player, right? Well, this event is the one that will be responsible for sharing our player’s state with the other player. So Now, we must declare the event onSend, right?

```cpp
event_t<string_t> onSend; // onSend Event
```

Now, we must add a WebSocket client/server to our code.

```cpp
if( process::env::get("mode") == "server" ){
    auto server = ws::server();
    server.onConnect( server_handler );
    server.listen( "0.0.0.0", 8000 );
} else {
    auto client = ws::client("ws://localhost:8000");
    client.onOpen ([=](){
        server_handler( client );
    });
}
```

Now, we have to define the function server_handler, right?

```cpp
void server_handler( ws_t cli ){
  
  // define player's name
  string_t name = string::format("player%d",cli.get_fd());

  // onData event
  cli.onData([=]( string_t data ){ });

  // onSend event
  auto ids = onSend([=]( string_t msg ){});

  // onClose event
  cli.onClose([=](){});

}
```

And we have to define the logic of each event within the server.

```cpp
cli.onData([=]( string_t data ){
    item_header info;
    memcpy( &info, data.get(), sizeof(info) );
    players[name] = optional_t<item_header>( info );
});
```

```cpp
auto ids = onSend([=]( string_t msg ){
     cli.write( msg );
});
```

```cpp
cli.onDrain([=](){
    onSend.off( ids );
    players.erase( name );
    console::log("disconnected");
});
```

Now we just need to compile, and we will see the following result

![Image4](https://miro.medium.com/v2/resize:fit:640/format:webp/1*nmtbmDRgw52RO8EvDLdxjA.gif)

## Source-Code

```cpp
#include <nodepp/nodepp.h>

#include <nodepp/optional.h>
#include <nodepp/object.h>
#include <nodepp/timer.h>
#include <nodepp/event.h>
#include <nodepp/map.h>
#include <nodepp/ws.h>

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl {
#include <raylib/raylib.h>
#include <raylib/raymath.h>
}

/*────────────────────────────────────────────────────────────────────────────*/

using namespace nodepp;

/*────────────────────────────────────────────────────────────────────────────*/

event_t<>         onClose;
event_t<float>    onLoop;
event_t<>         onDraw;
event_t<string_t> onSend;

/*────────────────────────────────────────────────────────────────────────────*/

struct item_header {
  rl::Vector2 siz;
  rl::Vector2 pos;
  rl::Color   col;
};
map_t<string_t,optional_t<item_header>> players;

/*────────────────────────────────────────────────────────────────────────────*/

class item_t { public:

    ptr_t<int> state = new int(1);
    event_t<>  onRemove;
    object_t   attr;

    template< class T >
    item_t ( T cb ){ cb(*this); }
    item_t () noexcept = default;

    void remove() const noexcept {
      if(*state == 0 ) { return; } 
         *state =  0; onRemove.emit(); 
    }

   ~item_t(){ 
      if( state.count() > 1 )
        { return; } remove();
    } 

}; 
map_t<string_t,optional_t<item_t>> objects;

/*────────────────────────────────────────────────────────────────────────────*/

void server_handler( ws_t cli ){
  string_t name = string::format("player%d",cli.get_fd());
  console::log("connected");

  cli.onData([=]( string_t data ){
    item_header info;
    memcpy( &info, data.get(), sizeof(info) );
    players[name] = optional_t<item_header>( info );
  });

  auto ids = onSend([=]( string_t msg ){
       cli.write( msg );
  });

  cli.onDrain([=](){
    onSend.off( ids );
    players.erase( name );
    console::log("disconnected");
  });

}

/*────────────────────────────────────────────────────────────────────────────*/

void onMain() {

    rl::InitWindow( 300, 400, "Snake Game" );
    rl::SetTargetFPS( 60 );
    
    /*─······································································─*/

    onDraw ([](){ rl::ClearBackground(BLACK); });
    onClose([](){ process::exit(1); });
    
    /*─······································································─*/

    process::add([](){
        if( rl::WindowShouldClose() )
          { onClose.emit(); }
    coStart

        onLoop.emit( rl::GetFrameTime() ); coNext;

        rl::BeginDrawing();
        onDraw.emit(); coNext;
        rl::EndDrawing();

        coGoto(0);

    coStop
    });
    
    /*─······································································─*/

    if( process::env::get("mode") == "server" ){
        auto server = ws::server();
        server.onConnect( server_handler );
        server.listen( "0.0.0.0", 8000 );
    } else {
        auto client = ws::client("ws://localhost:8000");
        client.onOpen ([=](){
          server_handler( client );
        });
    }

    /*─······································································─*/

    onDraw([](){
      for( auto &ply: players.get() ){
        if( !ply.second.has_value() ){ continue; }
        auto x = ply.second.value();
        rl::DrawRectangleV( x.pos, { 10, 10 }, BLUE );
      }
    });

    /*─······································································─*/
  
    objects["player"] = optional_t<item_t>([=]( item_t& self ){
      
      self.attr = {{ { "pos", rl::Vector2({ 0, 0 }) } }};

      auto idl = onLoop([=]( float delta ){
        auto pos = self.attr["pos"].as<rl::Vector2>();

          if( rl::IsKeyDown( rl::KEY_W ) ){ pos.y -= delta * 100; }
        elif( rl::IsKeyDown( rl::KEY_S ) ){ pos.y += delta * 100; }
          if( rl::IsKeyDown( rl::KEY_A ) ){ pos.x -= delta * 100; }
        elif( rl::IsKeyDown( rl::KEY_D ) ){ pos.x += delta * 100; }
        
        self.attr["pos"] = pos;
      });

      auto tmr = timer::interval([=](){
        auto pos = self.attr["pos"].as<rl::Vector2>();

        item_header info({
          .siz = rl::Vector2({ 10, 10 }),
          .pos = pos, .col = BLUE,
        });

        string_t message ( sizeof(info) );
        memcpy( message.get(), &info, sizeof(info) );
        onSend.emit( message ); 
      },100);

      auto idd = onDraw([=](){
        auto pos = self.attr["pos"].as<rl::Vector2>();
        rl::DrawRectangle( pos.x, pos.y, 10, 10, RED );
      });

      self.onRemove([=](){
        console::log( "removed" );
        timer::clear( tmr );
        onDraw.off( idd );
        onLoop.off( idl );
      });
    
    });

}
```

Congratulations! You have reached the end of this tutorial and now you have the foundations to build your own online multiplayer game. With what you’ve learned about Raylib, Nodepp, and Websockets, you have a set of powerful tools to create interactive experiences in real-time.

Remember that this is just the beginning. You can expand your game by adding new mechanics, power-ups, levels, and even chat systems to make interaction even more fun. Don’t be afraid to experiment and explore the possibilities these technologies offer.

Keep creating and having fun! The world of online game development awaits you.