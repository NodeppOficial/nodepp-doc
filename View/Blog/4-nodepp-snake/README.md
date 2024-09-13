# Creating the Snake Game: A Journey Through Event-Driven Programming in C++ with Nodepp and Raylib

![Image1](https://miro.medium.com/v2/resize:fit:720/format:webp/1*rQCz9i25SSnwQTxlZzF-XA.png)

Video game programming is an exciting challenge that may seem intimidating at first, but with the right tools and a step-by-step approach, it is achievable. This time you will learn, through event-driven programming, to recreate the iconic game of the snake.

With this knowledge, you will be ready to immerse yourself in the exciting world of video game programming and bring your most creative ideas to life. Get ready to embark on an exciting journey towards creating your own snake game!

Without further ado, let’s get started.

## What is Nodepp?

[Nodepp](/) is a framework for C++ that allows you to write 100% asynchronous applications, using a friendly and easy-to-understand syntax. With Nodepp, it is possible to create everything from multitasking, multithreading, and event-driven programming, to more complex programs, such as 100% asynchronous web servers, HTTP servers, HTTPS, and Websocket, among others. This framework offers a wide range of functionalities for the efficient development of asynchronous applications in C++.

![Image2](https://miro.medium.com/v2/resize:fit:720/format:webp/1*Eo8t9U7kGz6dG90hyYJ23Q.png)

## What is Raylib?

[Raylib](https://www.raylib.com/) is a library inspired by the Borland BGI graphics library and the XNA framework. It is a simple and easy-to-use library to enjoy video game programming. This library can be combined with several additional libraries for additional functionality, some of which are already used internally, while others are provided for user integration. The Raylib community has contributed several plugins to extend Raylib’s features and connection to other libraries, such as immediate mode GUI modules, physics modules, particle systems, Spine animation integration, and more.

![Image3](https://miro.medium.com/v2/resize:fit:720/format:webp/1*yEkm7xzgwPr_JbS7bPu5ow.png)

## Implementation

Now, once Nodepp and Raylib are installed on our PC, we must create a main.cpp file, where we are going to write the code for our video game.

![Image4](https://miro.medium.com/v2/resize:fit:720/format:webp/1*fa1t_NyLjiLKot0j7creBg.png)

Then must import the following Nodepp libraries:

```cpp
#include <nodepp/nodepp.h>   // nodepp library

#include <nodepp/optional.h> // optional contained value
#include <nodepp/object.h>   // dynamic objects 
#include <nodepp/timer.h>    // async timers
#include <nodepp/event.h>    // async events
#include <nodepp/map.h>      // map objects
```

Also, we must import the Raylib libraries:

```cpp
// declare inside a namespace is optional but
// I'll recomend you do this
// if you're working on a windows machine
// because nodepp use windows.h internally

namespace rl {
  #include <raylib/raylib.h>
  #include <raylib/raymath.h>
}
```

Now, we have to add the using namespace nodepp to get access the nodepp’s content, and also declare our main function.

```cpp
using namespace nodepp;

void onMain() {
  // our code goes here
}

// process::start and process::stop 
// are used by nodepp to start the event loop
```

Now, inside out main function, we must initialize our game screen:

```cpp
rl::InitWindow( 300, 400, "Snake Game" );
rl::SetTargetFPS( 60 );
```

Now, we have to create an infinite loop, which is responsible for directing or updating our game, right? This is where Nodepp comes into action. By allowing us create async tasks, we are going to replace the infinite loop with a microtask. So.

```cpp
// process::add declares a new microtask inside the event loop
process::add([](){

  // rl::WindowShouldClose is used to detect when to close the program
  if( rl::WindowShouldClose() ){ onClose.emit(); }

coStart // Start a new coroutine in Nodepp

  // onLoop is an undeclared event
  // used to update the game states
  onLoop.emit( rl::GetFrameTime() ); coNext;

  rl::BeginDrawing();
  // onDraw is an undeclared event
  // used to draw the objects in the game
  onDraw.emit(); 
  coNext; // yield the coroutine
  rl::EndDrawing();
  
  coGoto(0); // reset the coroutine

coStop // stop the coroutine
});
```

We must also declare the following events outside of the main function:


```cpp
event_t<>      onClose; // to detect when should close
event_t<float> onLoop;  // to detect when update the game
event_t<>      onDraw;  // to detect when to draw objects

void onMain() {
  // rest of the code 
}
```

Once the loop is defined and the events are declared, we can define the following event callbacks inside the main function:

```cpp
onDraw ([](){ rl::ClearBackground(BLACK); });
onClose([](){ process::exit(1); });
```

Now, if we compile the game, we’re going to see the next result.

![Image](https://miro.medium.com/v2/resize:fit:720/format:webp/1*jt88l3yOFdv0WICP0qx9IQ.png)

It works great, but now we have to create our character, right? To do this, we must first create an object, which allows us to manage the states and attributes of each new item that we create within the game:

```cpp
class item_t { public:

    ptr_t<int> state = new int(1); // to detect how many times is shared
    event_t<> onRemove;            // and event to detect when is removed
    object_t  attr;                // used to define dynamic attributes

    // item_t constructor
    template< class T >
    item_t ( T cb ){ cb(*this); }
    item_t () noexcept = default;

    // used to emit onRemove event
    void remove() const noexcept {
        if(*state == 0 ) { return; } 
           *state =  0; onRemove.emit(); 
    }
    
    // item_t destructor
   ~item_t(){ 
        if( state.count() > 1 )
          { return; } remove();
    } 

};
```

Also, we have to create a map-type object, to be able to add objects within the game and access them by name.

```cpp
// optional_t is used to detect if the object is empty or not  
map_t<string_t,optional_t<item_t>> objects;
```

Now, we are able to create new objects. Let’s start with the player:

```cpp
objects["player"] = optional_t<item_t>([]( item_t& self ){

  // player's logic goes here

});
```

We are going to assign the following attributes:


```cpp
self.attr = {{
  { "tail", array_t<rl::Vector2>() }, //used to define tail list position
  { "pos" , rl::Vector2({ 0, 0 }) },  //used to define head position
  { "dir" , rl::Vector2({ 0, 0 }) },  //used to define head direction
  { "size", 0 },                      //used to define tail max size
}};
```

now we have assign an onLoop event for our player

```cpp
auto idl = onLoop([=]( float delta ){
  auto pos = self.attr["pos"].as<rl::Vector2>();
  auto dir = self.attr["dir"].as<rl::Vector2>();

  auto sh = rl::GetScreenHeight();
  auto sx = rl::GetScreenWidth();

    if( pos.x > sx ){ pos.x =  0; }
  elif( pos.x <  0 ){ pos.x = sx; }
    if( pos.y > sh ){ pos.y =  0; }
  elif( pos.y <  0 ){ pos.y = sh; }

  pos = rl::Vector2Add( pos, rl::Vector2Scale( dir, 2 ) ); 
  self.attr["pos"] = pos; 
});

// Note: nodepp supports elif 
```

We have assign an onDraw event to the player

```cpp
auto idd = onDraw([=](){

  rl::Color color = { 255, 255, 255, 255 };

  for( auto &x: self.attr["tail"].as<array_t<rl::Vector2>>() ){
    rl::DrawRectangle( x.x, x.y, 10, 10, color );
    if( color.a > 50 ) color.a -= 10;
  }

});
```

And now we have to create a timer::interval for the player

```cpp
// timer interval are similar to setInterval() in js
auto idt = timer::interval([=](){

  // define attributes we're gonna use
  auto tail = self.attr["tail"].as<array_t<rl::Vector2>>();
  auto pos  = self.attr["pos"].as<rl::Vector2>();
  auto dir  = self.attr["dir"].as<rl::Vector2>();

  // define the direction that header must follow
    if( rl::IsKeyDown( rl::KEY_W ) && dir.y==0 ){ dir.y = -1; dir.x = 0; }
  elif( rl::IsKeyDown( rl::KEY_S ) && dir.y==0 ){ dir.y =  1; dir.x = 0; }
  elif( rl::IsKeyDown( rl::KEY_A ) && dir.x==0 ){ dir.x = -1; dir.y = 0; }
  elif( rl::IsKeyDown( rl::KEY_D ) && dir.x==0 ){ dir.x =  1; dir.y = 0; }

  // detect player's self collision
  for( auto &x: tail.slice( 1 ) ){
  if ( rl::CheckCollisionRecs(
     { pos.x, pos.y, 10, 10 },
     { x.x, x.y, 10, 10 }
   )){ onCollision.emit(); }
  }

  // limit the tail max size
  while( tail.size() > self.attr["size"].as<uint>() )
       { tail.pop(); } tail.unshift( pos );

  // update the attribute with new values
  self.attr["tail"] = tail; 
  self.attr["pos"]  = pos; 
  self.attr["dir"]  = dir;

}, 80 );
```

Notice that within the player, I am emitting an onCollision event, right? So we must create a new event and assign a new function to it.

```cpp
event_t<> onCollision; onCollision.on([=](){
   console::log("self collision");
   self.attr["size"] = 0;
});
```

And finally, every time onRemove is executed, we must clean things up, when player’s onRemove is executed:

```cpp
self.onRemove([=](){
  console::log( "removed" );
  timer::clear( idt );
  onLoop.off( idl );
  onDraw.off( idd );
});
```

Now, if we compile, and we are see the next result:

![Image](https://miro.medium.com/v2/resize:fit:640/format:webp/1*Qg5lWLAYuofoER6OrhtooA.gif)

Now, we must create the items that the snake is going to eat.

```cpp
objects["items"] = optional_t<item_t>([]( item_t& self ){

  //item's logic goes here

});
```

We must define item’s attribute

```cpp
self.attr = {{ { "pos", rl::Vector2({ 50, 50 }) } }};
```

We have to assign an onDraw event

```cpp
auto idd = onDraw([=](){
  auto pos = self.attr["pos"].as<rl::Vector2>();
  rl::DrawRectangleV( pos, { 10, 10 }, RED );
});
```

We have to assign an onLoop event

```cpp
auto idl = onLoop([=]( float delta ){

  // detect if player exists
  if( !objects["player"].has_value() ){ return; }

  // get player's attributes
  item_t player = objects["player"].value();
  auto   pos    = self.attr["pos"].as<rl::Vector2>();

  // get player's collision
  for( auto &x: player.attr["tail"].as<array_t<rl::Vector2>>() )
  if ( rl::CheckCollisionRecs(
     { pos.x, pos.y, 10, 10 },
     { x.x, x.y, 10, 10 }
   )){ onCollision.emit(); }

});
```

And now we have to define onCollision Event

```cpp
event_t<> onCollision; onCollision.on([=](){

  // print something
  console::log("onCollision");

  // get screen size
  uint sy = rl::GetScreenHeight(), 
       sx = rl::GetScreenWidth();
       
  // get player's tail size
  auto sz = objects["player"].value().attr["size"].as<int>();

  // update item's position
  rl::Vector2 pos ({ (float)(rand()%sx), (float)(rand()%sy) });

  // update player's tail size attribute
  objects["player"].value().attr["size"] = ++sz;

  // update item's position attribute
  self.attr["pos"] = pos;

});
```

And finally, we have to clean things up when item’s onRemove is executed

```cpp
self.onRemove([=](){
   console::log( "removed" );
   onLoop.off( idl );
   onDraw.off( idd );
});
```

And that’s it, we have finished the snake game, and now if we compile, we will see the following result.

![Image](https://miro.medium.com/v2/resize:fit:640/format:webp/1*hTm-8MoUsQH8GHegYxTaWw.gif)

```cpp
#include <nodepp/nodepp.h>

/*────────────────────────────────────────────────────────────────────────────*/

#include <nodepp/optional.h>
#include <nodepp/object.h>
#include <nodepp/timer.h>
#include <nodepp/event.h>
#include <nodepp/map.h>

/*──────────────────────────────────────────────────────────────────────────*/

namespace rl {
#include <raylib/raylib.h>
#include <raylib/raymath.h>
}

/*──────────────────────────────────────────────────────────────────────────*/

using namespace nodepp;

/*──────────────────────────────────────────────────────────────────────────*/

event_t<>      onClose;
event_t<float> onLoop;
event_t<>      onDraw;
uint           uRand;

class item_t { public:

    ptr_t<int> state = new int(1);
    event_t<> onRemove;
    object_t  attr;

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

};  map_t<string_t,optional_t<item_t>> objects;


/*──────────────────────────────────────────────────────────────────────────*/

void onMain() {

    rl::InitWindow( 300, 400, "Snake Game" );
    rl::SetTargetFPS( 60 );
    
    /*─····································································─*/

    onLoop ([]( float /*unused*/ ){ uRand = rand() % 1000; });
    onDraw ([](){ rl::ClearBackground(BLACK); });
    onClose([](){ process::exit(1); });
    
    /*─····································································─*/

    objects["player"] = optional_t<item_t>([]( item_t& self ){

        self.attr = {{
            { "tail", array_t<rl::Vector2>() },
            { "pos" , rl::Vector2({ 0, 0 }) },
            { "dir" , rl::Vector2({ 0, 0 }) },
            { "size", 0 },
        }};

        event_t<> onCollision; onCollision.on([=](){
          console::log("self collided");
          self.attr["size"] = 0;
        });

        auto idt = timer::interval([=](){
            auto tail = self.attr["tail"].as<array_t<rl::Vector2>>();
            auto pos  = self.attr["pos"].as<rl::Vector2>();
            auto dir  = self.attr["dir"].as<rl::Vector2>();

            if( rl::IsKeyDown( rl::KEY_W ) && dir.y==0 ){ dir.y = -1; dir.x = 0; }
          elif( rl::IsKeyDown( rl::KEY_S ) && dir.y==0 ){ dir.y =  1; dir.x = 0; }
          elif( rl::IsKeyDown( rl::KEY_A ) && dir.x==0 ){ dir.x = -1; dir.y = 0; }
          elif( rl::IsKeyDown( rl::KEY_D ) && dir.x==0 ){ dir.x =  1; dir.y = 0; }

            for( auto &x: tail.slice( 1 ) ){
            if ( rl::CheckCollisionRecs(
                 { pos.x, pos.y, 10, 10 },
                 { x.x, x.y, 10, 10 }
               )){ onCollision.emit(); }
            }

            while( tail.size() > self.attr["size"].as<uint>() )
                 { tail.pop(); } tail.unshift( pos );

            self.attr["tail"] = tail; 
            self.attr["pos"]  = pos; 
            self.attr["dir"]  = dir;
        }, 80 );

        auto idl = onLoop([=]( float delta ){
            auto pos = self.attr["pos"].as<rl::Vector2>();
            auto dir = self.attr["dir"].as<rl::Vector2>();

            auto sh = rl::GetScreenHeight();
            auto sx = rl::GetScreenWidth();

            if( pos.x > sx ){ pos.x =  0; }
          elif( pos.x <  0 ){ pos.x = sx; }
            if( pos.y > sh ){ pos.y =  0; }
          elif( pos.y <  0 ){ pos.y = sh; }

            pos = rl::Vector2Add( pos, rl::Vector2Scale( dir, 2 ) ); 
            self.attr["pos"] = pos; 
        });

        auto idd = onDraw([=](){
            rl::Color color = { 255, 255, 255, 255 };
            for( auto &x: self.attr["tail"].as<array_t<rl::Vector2>>() ){
                 rl::DrawRectangle( x.x, x.y, 10, 10, color );
                 if( color.a > 50 ) color.a -= 10;
            }
        });

        self.onRemove([=](){
            console::log( "removed" );
            timer::clear( idt );
            onLoop.off( idl );
            onDraw.off( idd );
        });

    });
    
    /*─····································································─*/

    objects["items"] = optional_t<item_t>([]( item_t& self ){
      
      self.attr = {{ { "pos", rl::Vector2({ 50, 50 }) } }};

      event_t<> onCollision; onCollision.on([=](){
        uint sy = rl::GetScreenHeight(), sx = rl::GetScreenWidth();
        auto sz = objects["player"].value().attr["size"].as<int>();
        rl::Vector2 pos = {(float)(uRand%sx),(float)(uRand%sy)};
        objects["player"].value().attr["size"] = ++sz;
        self.attr["pos"] = pos;
        console::log("onCollision");
      });

      auto idl = onLoop([=]( float delta ){
        if( !objects["player"].has_value() ){ return; }
        item_t player = objects["player"].value();
        auto   pos    = self.attr["pos"].as<rl::Vector2>();

        for( auto &x: player.attr["tail"].as<array_t<rl::Vector2>>() )
        if ( rl::CheckCollisionRecs(
              { pos.x, pos.y, 10, 10 },
              { x.x, x.y, 10, 10 }
           )){ onCollision.emit(); }

      });

      auto idd = onDraw([=](){
        auto pos = self.attr["pos"].as<rl::Vector2>();
        rl::DrawRectangleV( pos, { 10, 10 }, RED );
      });

      self.onRemove([=](){
        console::log( "removed" );
        onLoop.off( idl );
        onDraw.off( idd );
      });

    });
    
    /*─····································································─*/

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

}
```

Thanks for read this tutorial 👍