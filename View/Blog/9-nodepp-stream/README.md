# Nodepp for C++ Stream Manipulation: A Comprehensive Overview

![Image](https://miro.medium.com/v2/resize:fit:720/format:webp/1*ugLl2qCFe-p8uejT-O0eaw.png)

The concept of streams in computing usually describes the delivery of data in a steady, continuous flow. You can use streams for reading from or writing to a source continuously, thus eliminating the need to fit all the data in memory at once.

Using streams provides two major advantages. One is that you can use your memory efficiently since you do not have to load all the data into memory before you can begin processing. Another advantage is that using streams is time-efficient. You can start processing data almost immediately instead of waiting for the entire payload. These advantages make streams a suitable tool for large data transfer in I/O operations.

In this article we'll dive deep into the world of C++ stream manipulation with Nodepp, a powerful and versatile library designed to enhance your input/output operations. This comprehensive guide will provide you with a solid foundation in stream concepts, explore the core features of Nodepp, and demonstrate practical examples to help you master its usage.

## Key Topics Covered:

- **Introduction to C++ Streams:** Understand the fundamental concepts of streams, including input streams, output streams, and their role in C++ programs.
- **Stream Manipulation Techniques:** Learn how to effectively manipulate streams using Nodepp, including reading, writing content to a file.
- **Real-World Examples:** See Nodepp in action through practical examples and code snippets that illustrate its application in various scenarios.

This article will help you understand streams and how to work with them. So, don’t be afraid. We can figure this out!

## What is a File Stream in Nodepp for?:

Imagine file streams as a digital river, flowing data between your C++ program and files on your computer. Nodepp is like a skilled boatman, helping you navigate this river with ease and efficiency.

## Why use NodePP?

- **Simplicity:** Nodepp makes working with file streams a breeze, with intuitive functions and a clean API.
- **Performance:** It's optimized for speed, ensuring your programs run efficiently.
- **Flexibility:** Nodepp supports various file operations, from reading and writing to seeking specific positions within a file.

NodePP provides a streaming API in the `fs.h` library to work with streams. All NodePP streams are an instance of or inherit from the `file_t` class. They emit different events you can listen for at various intervals during the data transmission process. The native stream module provides an interface consisting of different functions for listening to those events that you can use to read and write data, manage the transmission life cycle, and handle transmission errors.

Let's get started!

Here's a basic example to give you a taste of what Nodepp can do:

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto file = fs::readable( "PATH_TO_FILE" );

    file.onData([]( string_t data ){
        // Event Emitted every time nodepp reads a chunk
        console::log( data );
    });

    file.onClose([](){
        // Event Emitted when file is completely readed
        console::success( "DONE" );
    });

    stream::pipe( file );

}
```

## There are 3 types of streams in NodePP:

- **Writable:** lets us write content to a file.
- **Readable:** lets us read contents from a file.
- **Duplex:**   let us write and read content from a file as needed.

If you have already worked with NodePP, you may have come across streams. For example, in a NodePP based HTTP server, `http_t` is a `DuplexStream`, but the same happend with `socket_t` and `ssocket_t`. **DuplexStreams** are usefull to read or write data from a socket as needed. Lets take a look.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/http.h>

using namespace nodepp;

void onMain(){

    auto server = http::server([=]( http_t cli ){ 

        if( cli.method == "POST" ){
            // read POST body
            console::log( cli.read() );
        }

        // write response
        cli.write_header( 200, header_t({
            { "content-type", "text/html" }
        }));
        
        cli.write( "Welcome to Nodepp!" );
        cli.close();

    });

    server.listen( "localhost", 3000, [=]( socket_t server ){
        console::log("-> http://localhost:3000 <-");
    });

}
```

In the example above, we have created an HTTP Server using `http::server()`. Next, we defined `server.listen()` to enable the server to listen for incoming requests. Finally, we utilize `read()` or `write()` to send or receive data from the client. As mentioned earlier, `http_t` types are `DuplexStreams` and are usefull to write or read content from the socket as needed.

## Why streams

Streams basically provide two major advantages compared to other data handling methods:

#### **Memory Efficiency:** 
One of the primary benefits of streams is their ability to handle large amounts of data without requiring it all to be loaded into memory at once. This is particularly useful when dealing with massive datasets, such as large files or streams of data from APIs. By processing data in smaller chunks, streams help to minimize the risk of running into memory-related issues, such as out-of-memory errors. This means that applications can operate more smoothly and efficiently, even when working with substantial data volumes.

#### **Time Efficiency:** 
Streams also enhance time efficiency by allowing for immediate processing of data as it becomes available. Instead of waiting for an entire payload to be transmitted before starting the processing, streams enable developers to begin working with the data right away. This leads to faster response times and improved performance, especially in applications that require real-time data handling. For instance, when streaming video or audio, users can start viewing or listening almost immediately, rather than waiting for the entire file to download.

## **A Practical Example**

### How to create a readable stream

We first include the `fs.h` and `stream.h`.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {
    // Code goes here
}
```

To create a readable `file_t` instance, specify the file's path and set the mode to `r` or `r+`.

```cpp
file_t file ( "PATH", "r" );
console::log( file.read() );
```

There is another method, using `fs::readable()` function, that automatically set a file as `ReadableStream`, and then return its respective `file_t`.

```cpp
auto file = fs::readable( "PATH" );
console::log( file.read() );
```

### How to read a file asynchronously

Nodepp's `stream::pipe()` function enables asynchronous file reading by scheduling a task in the event loop and emitting events like `onRead` and `onClose` to notify your application of progress and completion.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto file = fs::readable( "PATH" );

    file.onData([]( string_t data ){
        console::log( "->", data );
    });

    file.onClose([](){
        console::log("Done");
    });

    stream::pipe( file );

}
```

### how to read a file synchronously

NodePP provides a `stream::await()` function that waits for the file to finish reading before returning the entire content as a `string_t`. This functionality allows developers to handle file streams efficiently, ensuring that they can work with the complete data only after the reading process is complete. By using `stream::await()`, you can simplify your code and avoid potential issues related to incomplete data processing.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto file = fs::readable( "PATH" );

    while( file.is_available() ){
        console::log( file.read() );
    }

}
```

### read file line by line

Also nodepp provides a `stream::line()` function that enables asynchronous file reading line by line.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto file = fs::readable( "PATH" );

    file.onData([]( string_t line ){
        console::log( "->", line );
    });

    file.onClose([](){
        console::log("Done");
    });

    stream::line( file );

}
```

### How to create a writable stream

We first include the `fs.h` and `stream.h`.

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/stream.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {
    // Code goes here
}
```

Now, we have to create a `file_t` class, to set it as readable, first, we must define the file's path and then set as readable mode using `w`.

```cpp
// create a file_t instance
file_t file ( "PATH", "w" );

// write content to a file
     file.write( "Hello " );
     file.write( "World " );
     file.write( "!!!!! " );

// Close File 
     file.close();
```

Also, there is another method, using `fs::writable()` function, that automatically set a file as readable, and then return its respective `file_t`.

```cpp
// create a file_t instance
auto file = fs::writable( "PATH" );

// write content to a file
     file.write( "Hello " );
     file.write( "World " );
     file.write( "!!!!! " );

// Close File 
     file.close();
```

### How to copy a file to another file

As mentioned previously, Nodepp's `stream::pipe()` function enables asynchronous file reading. By providing a second file_t argument that represents a `WritableStream`, you can efficiently pipe the contents of the `ReadableStream` directly to a destination file or another stream, eliminating the need for manual data handling.

```cpp
// create a file_t instance
auto fout = fs::writable( "PATH1" );
auto fint = fs::readable( "PATH2" );

// pipe content
stream::pipe( fint, fout );
```

### How to define a DuplexStream

Nodepp's socket-related classes are inherently DuplexStreams, but file streams aren't. To utilize a file as a `DuplexStream` for both reading and writing, you can create a new `file_t` instance and open it in `a` or `a+` mode. Nodepp will automatically convert the `file_t` into a `DuplexStream`, enabling bidirectional data transfer.

```cpp
auto dpx = file_t( PATH, "a" );
```

### Streams-powered Node APIs

- `socket_t` is the main node api that is stream are based on, which underlies most of the following APIs
- `process.std_input()` returns a stream connected to stdin
- `process.std_output()` returns a stream connected to stdout
- `process.std_error()` returns a stream connected to stderr
- `fs::readable()` creates a readable stream to a file
- `fs::writabl()` creates a writable stream to a file
- `tcp::connect()` initiates a stream-based connection
- `http::fetch()` returns an instance of the `http_t` class, which is a `DuplexStream`.
- `zlib::gzip::pipe()` compress data using gzip into a stream
- `zlib::gunzip::pipe()` decompress a gzip stream.
- `zlib::inflate::pipe()` compress data using deflate into a stream.
- `zlib::deflate::pipe()` decompress a deflate stream.

Here are some important events related to writable streams:

- **onUnpipe():** Triggered when **file.unpipe()** is called, indicating that a pipe connection has been removed.
- **onResume():** Emitted when **file.resume()** is called, resuming data reading after a pause.
- **onError():** Fired when an error occurs during file operations.
- **onClose():** Dispatched when the file is garbage-collected, signifying the end of its lifecycle.
- **onDrain():** Emitted when the file has finished reading all available data.
- **onStop():** Emitted when **file.stop()** is called, stopping data reading.
- **onOpen():** Triggered once the file is successfully opened.
- **onPipe():** Emitted when **stream::pipe()** is called, initiating a pipe connection.
- **onData():** Fired whenever new data is available for reading from the file.

### Conclusion

This exploration of Nodepp's fundamentals has highlighted the pivotal role of files, streams, and pipes in efficient I/O operations. By mastering these core concepts, you can write elegant and performant C++ code that effectively handles data input and output.

Thanks for reading! If you enjoy reading this post, got help, knowledge, inspiration, and motivation through it. And if you want to support me — you can [“buy me a coffee.”](https://ko-fi.com/D1D8VFJZC) Your support really makes a difference ❤️