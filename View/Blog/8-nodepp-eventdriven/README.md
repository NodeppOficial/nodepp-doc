# Exploring Event-Driven and Asynchronous Programming in C++ with NodePP
### Written by: Enmanuel D Becerra C

Welcome to the heart of NodePP, where events reign and async is king. In this series, we'll dive into the NodePP’s event-driven architecture and its async prowess. Whether you’re a newbie or a seasoned dev, get ready to unlock the secrets of NodePP. Let’s begin the journey!

## 1. Event-Driven Architecture:

NodePP operates on an event-driven architecture, where tasks are managed asynchronously through an event loop. This loop efficiently handles multiple tasks simultaneously, akin to a traffic controller at a busy intersection. Events, like incoming requests or file operations, are queued and processed in a non-blocking manner, ensuring smooth execution without waiting for each task to complete. This architecture allows NodePP to handle numerous concurrent operations efficiently, making it ideal for building responsive and scalable applications.

## 2. Handling Events in NodePP:

In NodePP, event handling is made seamless through the `event_t` class. This class enables developers to create custom events and attach listeners to them, facilitating asynchronous communication within applications.

Here’s how you can get started with event handling in NodePP:

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/event.h>

using namespace nodepp;

void onMain() {

    event_t<> event;

    event.on([](){
        static uchar x = 0; x++; 
        console::log( "Hello World", x );
    });

    event.emit(); // Hello World 1;
    event.emit(); // Hello World 2;
    event.emit(); // Hello World 3;
    event.emit(); // Hello World 4;

}
```

## 3. Asynchronous Programming:

Asynchronous programming is a fundamental concept in NodePP that allows tasks to be executed independently of the main program flow. This approach is crucial for handling operations that may take time to complete, such as I/O operations, network requests, or database queries, without blocking the execution of other tasks.

In NodePP, asynchronous programming is essential for building high-performance, non-blocking applications. Here’s a breakdown of key mechanisms used for asynchronous programming in NodePP:

- **Callbacks:** Callbacks are functions passed as arguments to other functions, to be executed once the operation is complete. They are a fundamental building block of asynchronous programming in NodePP. However, managing multiple nested callbacks can lead to callback hell, making code difficult to read and maintain.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto file = fs::readable( "PATH_TO_FILE" );

    file.onData( []( string_t data ){
        console::log( data );
    });

    file.onClose( [](){
        console::log("DONE");
    });

    stream::pipe( file );

}
```

- **Async/Await:** Async/Await allows writing asynchronous code that looks synchronous, making it easier to understand and maintain. Async executes tasks in the background, and await is used to wait for the completion of asynchronous operations within an async function

```cpp
#include <nodepp/nodepp.h>

using namespace nodepp;

void onMain() {

  //process::await() -> await
  //process::add()   -> async

    process::add([](){
        static uchar x = 100;
    coStart
        while( x-->0 ){
            console::log( "Hello World", x );
            coDelay( 1000 );
        }
    coStop
    });

    console::log( "DONE" );

}
```

- **Promises:** Promises provide a more structured way to handle asynchronous operations and mitigate callback hell. A Promise represents the eventual completion (or failure) of an asynchronous operation and allows chaining of operations using `.then()` and `.fail()` methods. Promises improve code readability and maintainability.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/promise.h>

using namespace nodepp;

void onMain() {

    promise_t<int,except_t> ([](
        function_t<void,int>      res,
        function_t<void,except_t> rej
    ){
        res( 10 );
      //rej( except_t( "something went wrong" ) );
    })
    
    .then( []( int res ){
        console::log( res );
    })

    .fail( []( except_t rej ){
        console::log( rej );
    });

}
```

## 4. Event Loop in Action:

The event loop is the beating heart of NodePP, orchestrating the execution of asynchronous tasks efficiently. Let’s take a high-level journey through the inner workings of the event loop and how it handles asynchronous tasks in NodePP.

- **Event Queue:** When asynchronous tasks are encountered in NodePP, such as I/O operations or timers, they are not executed immediately. Instead, these tasks are placed in the event queue, awaiting their turn to be processed.

- **Event Loop Iteration:** The event loop continuously iterates, checking for tasks in the event queue that are ready to be executed. If the event queue is empty, the event loop waits for tasks to be added.

- **Execution Phase:** When a task is retrieved from the event queue, it enters the execution phase. The task is processed, and if it’s a synchronous task, it’s executed immediately.

- **Non-Blocking I/O:** For asynchronous tasks, such as I/O operations, the event loop delegates the task to the underlying system, allowing NodePP to continue executing other tasks in the meantime. When the asynchronous task completes, a callback associated with the task is placed in the callback queue.

- **Callback Queue:** Asynchronous callbacks are stored in the callback queue after their associated tasks complete. The event loop checks the callback queue during each iteration to see if there are any callbacks waiting to be executed.

- **Execution of Callbacks:** When the event loop encounters callbacks in the callback queue, it retrieves and executes them one by one. This process ensures that asynchronous tasks are executed in the order they were completed, maintaining the integrity of the program’s logic.

![Image](https://uploads-ssl.webflow.com/62c6fbddb12bb54622241c3d/62c6fbddb12bb523df242285_event_loop_animation-gif.gif)

Thanks for reading! If you enjoy reading this post, got help, knowledge, inspiration, and motivation through it. And if you want to support me — you can [“buy me a coffee.”](https://ko-fi.com/D1D8VFJZC) Your support really makes a difference ❤️