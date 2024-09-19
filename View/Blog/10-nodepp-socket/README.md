# Simplifying Socket Programming in C++ with Asynchronous I/O with Nodepp

![IMAGE](https://miro.medium.com/v2/resize:fit:720/format:webp/1*a5MjmrToUv_3I2uSePDDEw.png)

Simplify network programming in C++ with Nodepp, a powerful and efficient library designed for asynchronous I/O operations. Nodepp's intuitive API and non-blocking architecture make it easy to create scalable and high-performance network applications. 

In this article you will learn:

- The basics of socket programming: TCP and UDP
- How to create a simple server and client using Nodepp
- Advanced topics like asynchronous I/O and event-driven programming

Let's get started: 

## What is TCP?

**TCP** or **Transmission Control Protocol**, is a fundamental internet protocol within the **TCP/IP** suite. It ensures reliable data exchange between clients and servers by establishing a reliable connection and guaranteeing the delivery of data in the correct order.

TCP is used for a variety of applications, including:

- **Web browsing:** HTTP, the protocol used for web browsing, is built on top of TCP.
- **Email:** SMTP, the protocol used for sending email, is also built on top of TCP.
- **Remote access:** SSH, the protocol used for secure remote access, uses TCP.
- **File transfer:** FTP, the protocol used for transferring files, uses TCP.

#### Features of TCP:

- **Connection-oriented:** TCP establishes a virtual connection between two communicating devices before data is exchanged. This connection ensures that data is delivered in the correct order and that any lost or corrupted data is retransmitted.
- **Reliable:** TCP uses acknowledgments and retransmissions to ensure that data is delivered reliably. When a sender sends a data packet, it waits for an acknowledgment from the receiver. If the acknowledgment is not received within a certain time, the sender retransmits the packet.
- **Flow control:** TCP uses a windowing mechanism to control the rate at which data is sent. This helps to prevent the receiver from being overwhelmed with data.
- **Error correction:** TCP uses checksums to detect errors in data packets. If an error is detected, the packet is retransmitted.

#### TCP Server

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/tcp.h>

using namespace nodepp;

void onMain(){

    auto server = tcp::server();

    server.onConnect([=]( socket_t cli ){
    
        cli.onData([=]( string_t data ){
            console::log( data );
        });

        cli.onClose([=](){
            console::log("closed");
        });

        cli.write("Hello World!");

    });

    server.listen( "localhost", 8000, []( socket_t srv ){
        console::log("-> tcp://localhost:8000 <-");
    });

}
```

In the example above, we've implemented a **simple TCP server** using NodePP 

1. **Creating the Server Instance**: We begin by creating a `tcp_t` instance with `tcp::server()`.
2. **Listening for Incoming Messages**: Using `server.listen()`, we enable our server to listen for incoming messages.
3. **Processing Incoming Messages**: Finally, we handle these messages with the `server.onConnect()` method.

Additionally, there are other important events to consider, such as `cli.onClose()` for handling client disconnections and `cli.onData()` for managing incoming data messages. 

This structure allows for efficient message management and enhances the overall functionality of the TCP server. 

#### TCP Client

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/tcp.h>

using namespace nodepp;

void onMain(){

    auto client = tcp::client();

    client.onOpen([=]( socket_t cli ){
    
        cli.onData([=]( string_t data ){
            console::log( data );
        });

        cli.onClose.once([=](){
            console::log("closed");
        });

        cli.write("Hello World!");

    });

    client.connect( "localhost", 8000 );

}
```

In the example above, we've developed a **simple TCP client** using NodePP.

1. **Creating the Client Instance**: We start by instantiating a `tcp_t` object with `tcp::client()`.
2. **Connecting to a Server**: To establish a connection to a remote server, we use the `client.connect()` method.
3. **Handling Incoming Messages**: We manage incoming messages with the `client.onOpen()` method, which is triggered when the connection is successfully established.

Moreover, there are additional key events to be aware of, such as `cli.onClose()` for managing client disconnections and `cli.onData()` for processing incoming data messages.

This structure not only facilitates effective message handling but also enhances the overall performance and functionality of the TCP client.

## What is UDP?

**UDP** stands for **User Datagram Protocol**. It's a communication protocol used to send messages (transported as datagrams in packets) to other hosts on an Internet Protocol (IP) network. UDP is a simple message-oriented transport layer protocol. Although UDP provides integrity verification (via checksum) of the header and payload, it provides no guarantees to the upper layer protocol for message delivery and the UDP layer retains no state of UDP messages once sent.

UDP is used for a variety of applications, including:

- **Voice over IP (VoIP):** UDP is used to transmit voice data over the internet.
- **Video conferencing:** UDP is used to transmit video and audio data for video conferencing.
- **Streaming media:** UDP is used to stream audio and video content over the internet.
- **Online gaming:** UDP is used to transmit game data between players.
- **DNS (Domain Name System):** UDP is used to resolve domain names into IP addresses.
- **Routing protocols:** UDP is used by some routing protocols, such as RIP (Routing Information Protocol).
- **Messaging protocols:** UDP is used by some messaging protocols, such as NNP (Network News Protocol).

#### Features of UDP:

- **Lightweight:** UDP is a lightweight protocol with minimal overhead, making it suitable for applications that require low latency and high performance.
- **Connectionless:** UDP is a connectionless protocol, meaning that there is no need to establish a connection before sending data. This makes UDP suitable for applications that do not require reliable delivery of all packets, such as real-time applications.
- **Best-effort delivery:** UDP provides best-effort delivery, meaning that it does not guarantee that all packets will be delivered. This makes UDP suitable for applications that can tolerate some packet loss, such as real-time applications.
- **Datagram-based:** UDP is a datagram-based protocol, meaning that it transmits data in individual datagrams. This makes UDP suitable for applications that do not require reliable delivery of all packets, such as real-time applications.
- **Checksum:** UDP includes a checksum to verify the integrity of the header and payload. This helps to ensure that data is not corrupted during transmission.
- **No flow control:** UDP does not provide flow control, meaning that it does not regulate the rate at which data is sent. This makes UDP suitable for applications that do not require reliable delivery of all packets, such as real-time applications.
- **No retransmission:** UDP does not provide retransmission, meaning that it does not resend lost packets. This makes UDP suitable for applications that do not require reliable delivery of all packets, such as real-time applications.

These features make UDP a good choice for applications that require low latency, high performance, and can tolerate some packet loss. However, UDP is not suitable for applications that require guaranteed delivery of all packets, such as file transfers or database transactions.

#### UDP Server

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/udp.h>

using namespace nodepp;

void onMain(){

    auto server = udp::server();

    server.onConnect([=]( socket_t cli ){
    
        cli.onData([=]( string_t data ){
            console::log( data );
        });

        cli.onClose([=](){
            console::log("closed");
        });

        cli.write("Hello World!");

    });

    server.listen( "localhost", 8000, []( socket_t srv ){
        console::log("-> udp://localhost:8000 <-");
    });

}
```

In the example above, we've implemented a **simple UDP server** using NodePP 

1. **Creating the Server Instance**: We begin by creating a `udp_t` instance with `udp::server()`.
2. **Listening for Incoming Messages**: Using `server.listen()`, we enable our server to listen for incoming messages.
3. **Processing Incoming Messages**: Finally, we handle these messages with the `server.onConnect()` method.

Additionally, there are other important events to consider, such as `cli.onClose()` for handling client disconnections and `cli.onData()` for managing incoming data messages. 

This structure allows for efficient message management and enhances the overall functionality of the UDP server. 

#### UDP Client

```cpp
#include <nodepp/nodepp.h>
#include <nodepp/udp.h>

using namespace nodepp;

void onMain(){

    auto client = udp::client();

    client.onOpen([=]( socket_t cli ){
    
        cli.onData([=]( string_t data ){
            console::log( data );
        });

        cli.onClose.once([=](){
            console::log("closed");
        });

        cli.write("Hello World!");

    });

    client.connect( "localhost", 8000 );

}
```

In the example above, we've developed a **simple UDP client** using NodePP.

1. **Creating the Client Instance**: We start by instantiating a `udp_t` object with `udp::client()`.
2. **Connecting to a Server**: To establish a connection to a remote server, we use the `client.connect()` method.
3. **Handling Incoming Messages**: We manage incoming messages with the `client.onOpen()` method, which is triggered when the connection is successfully established.

Moreover, there are additional key events to be aware of, such as `cli.onClose()` for managing client disconnections and `cli.onData()` for processing incoming data messages.

This structure not only facilitates effective message handling but also enhances the overall performance and functionality of the UDP client.

# Conclusion

As you've seen before, Nodepp stands out as a valuable tool for developers looking to simplify socket programming in C++. Its asynchronous I/O model, combined with an elegant API and high-performance capabilities, makes it an excellent choice for building robust, network-intensive applications. Whether you're developing a web server, a real-time communication tool, or any other networked application, Nodepp can significantly enhance your development experience and application performance.

Thanks for reading! If you enjoy reading this post, got help, knowledge, inspiration, and motivation through it. And if you want to support me — you can [“buy me a coffee.”](https://ko-fi.com/D1D8VFJZC) Your support really makes a difference ❤️