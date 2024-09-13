# The Power of Multitasking with Nodepp: Unlock the Potential of Your Arduino Projects

![Image1](https://miro.medium.com/v2/resize:fit:720/format:webp/1*cQw-qHmGVBrG48QETegBIw.jpeg)

The world of digital electronics is constantly evolving, and with it, the capabilities of development platforms like Arduino. One of the most important features that has seen great advancement in recent years is multitasking, or the ability to execute multiple tasks at the same time.

In the past, microcontrollers could only perform one task at a time. This could be a problem for projects that require controlling multiple devices or performing complex calculations. However, with the advent of multitasking, it is now possible to run multiple tasks simultaneously, opening up a world of new possibilities for Arduino projects.

In this article, we will explore the world of multitasking on Arduino UNO.

We’ll start with an introduction to the basics of multitasking, and then look at how to implement it in your projects. We’ll also discuss some of the advantages and disadvantages of multitasking, and give you some tips to optimize the performance of your multitasking projects.

By the end of this article, you will have a complete understanding of multitasking in Arduino UNO and will be ready to start creating more complex and efficient projects.

Are you ready to immerse yourself in the world of multitasking?

## What is this multitasking?

Multitasking, in the context of the Arduino UNO, is not the same as the perfect multitasking you imagine on a computer. An Arduino UNO has a single processor, so it can’t run multiple tasks completely at the same time. What we call multitasking in Arduino UNO is rather the ability to quickly switch between different tasks creating the illusion of simultaneity. This is achieved thanks to a concept called coroutines.

## What is a coroutine?

A coroutine in programming is a specialized function that allows it to suspend and resume its execution. It is similar to a subroutine, but these can store their state at the time of suspension.

![Image2](https://miro.medium.com/v2/resize:fit:720/format:webp/0*D-tx0VELwSzq62jQ.gif)

Let’s imagine a regular function like a light switch. You turn it on (execute the function) and it lights up (does its job). When you turn it off (end the function) all traces of its status disappear. A coroutine, on the other hand, is like a light switch with memory. You turn it on, it does its job to a certain point, and then you can turn it off temporarily. When you turn it back on, it returns to its previous state and continues from where you left off.

## How do we implement multitasking in Arduino?

Well, to implement multitasking in Arduino from scratch is a bit complicated, however, I want to present a framework created by me called Nodepp.

Nodepp is a framework written in C++, which will allow us to write concurrent applications on Arduino UNO, using techniques such as event loops and coroutines, allowing us to create multitasking on Arduino easily and quickly.

## Implementation

To implement Nodepp in our Arduino project, we must first install Nodepp in our project, here is the link to the [Nopdepp-Arduino Arduino Library Manager](https://www.arduino.cc/reference/en/libraries/nodepp).

Once installed, we must modify our projects a little:

```cpp
void setup(){ /* initialization logic */ }

void update(){ /* loop logic */ }
```

The previous code represents something like Hello World in Arduino, right? To use Nodepp in this project, we must change it to this other code.

```cpp
#include <nodepp.h>

using namespace nodepp;

onMain([](){
  // nodepp logic goes here
})
```

Now, to create our first microtask in Nodepp, we must use the following code.

```cpp
#include <nodepp.h>

using namespace nodepp;

onMain([](){

  process::add([](){
    // declare variables here
  coStart // start coroutine

    // coroutine's logic goes here
    coNext; // yield the coroutine

  coStop // stop coroutine
  });

})
```

As you can see, microtasks internally use coroutines, which suspend the execution of a task, allowing other microtasks to execute, and taking full advantage of the capabilities of the microcontroller’s CPU.

## Example 1

Let’s take a look at this simple example using microtasks in Arduino UNO, let’s imagine that we want to create a program capable of turning multiple outputs on and off simultaneously. See the next code.

```cpp
#include <nodepp.h>

using namespace nodepp;

onMain([](){

    // first we define the output pins as array
    ptr_t<uint> OUT ({ 12, 11 });

    // then for each, we set as output mode
    forEach( OUT, [=]( uint &pin ){
        pinMode( pin, OUTPUT );
    });

    // now, we define a new microtask
    process::add([=]( uint time ){
        static ulong stamp = millis() + time;
        static bool  b     = 0;
    coStart
        
        // and every time millis > stam
        // we just turn on/off the output
        while( millis() > stamp ){
            digitalWrite( OUT[0], b );
            stamp = millis() + time;
            b=!b; coNext;
        }

        // coGoto(0) reset the coroutine
        // and make it loop
        coGoto(0);
    
    coStop
    }, 300 ); // 300 milliseconds

    // now we must do the same whith the other pin
    process::add([=]( uint time ){
        static ulong stamp = millis() + time;
        static bool  b     = 0;
    coStart
        
        while( millis() > stamp ){
            digitalWrite( OUT[1], b );
            stamp = millis() + time;
            b=!b; coNext;
        }

        coGoto(0);

    coStop
    }, 1000 ); // 1000 milliseconds = 1 second

})
```

![image3](https://miro.medium.com/v2/resize:fit:640/format:webp/0*vDyjPzaU2utJVEMe.gif)

It’s great to see you can run multiple tasks in Arduino UNO, right? but actually there is a simplest way to do the previous example

```cpp
#include <nodepp.h>
#include <nodepp/timer.h>

using namespace nodepp;

onMain([](){

    ptr_t<uint> OUT ({ 14, 15, 16, 17, 18 });

    forEach( OUT, [=]( uint &pin ){
        pinMode( pin, OUTPUT );
    });

    timer::interval([=](){
        static bool b=0; b=!b;
        digitalWrite( OUT[0], b );
    }, 100 );

    timer::interval([=](){
        static bool b=0; b=!b;
        digitalWrite( OUT[1], b );
    }, 500 );

    timer::interval([=](){
        static bool b=0; b=!b;
        digitalWrite( OUT[2], b );
    }, 1000 );

    timer::interval([=](){
        static bool b=0; b=!b;
        digitalWrite( OUT[3], b );
    }, 1100 );

    timer::interval([=](){
        static bool b=0; b=!b;
        digitalWrite( OUT[4], b );
    }, 1500 );

})
```

![image4](https://miro.medium.com/v2/resize:fit:640/format:webp/1*fW6nBD2Mr7wGzfZ880InIw.gif)

## Example 2

Let’s take a look to this another example of microtasks. Now on this case let’s suppose that we want to create a program capable of reading data from an HC-SR04 sensor, that simultaneously turns on a sequence of LEDs that indicate how close an object is. See the next code.

```cpp
#include <nodepp.h>

using namespace nodepp;

/*─────────────────────────────────────────────────*/

ulong time = 0;

ptr_t<uint> OUT ({ 15 });
ptr_t<uint> INP ({ 14 });
ptr_t<uint> SEG ({ 8, 7, 6, 5, 4, 3, 2 });

/*─────────────────────────────────────────────────*/

template< class V, ulong N >
void print7seg( const V (&arr)[N] ){
    for( ulong x=N; x--; )
         digitalWrite( SEG[x], arr[x] );
}

/*─────────────────────────────────────────────────*/

onMain([](){

    //setting up IO pins
    for( auto &x: INP ) pinMode( x, INPUT  );
    for( auto &x: OUT ) pinMode( x, OUTPUT );
    for( auto &x: SEG ) pinMode( x, OUTPUT );

    //the HC-SR04 process
    process::add([=](){
    coStart
        
        digitalWrite( OUT[0], 1 ); coNext;
        digitalWrite( OUT[0], 0 );
        
        time = pulseIn( INP[0], HIGH ) / 58;

        coGoto(0); 
        
    coStop
    });

    // the 7-segment display process
    process::add([=](){
        uint value = time * 10 / 60;
        switch( value ){
            case 1:  print7seg({ 0, 1, 1, 0, 0, 0, 0 }); break;
            case 2:  print7seg({ 1, 1, 0, 1, 1, 0, 1 }); break;
            case 3:  print7seg({ 1, 0, 0, 1, 1, 1, 1 }); break;
            case 4:  print7seg({ 0, 0, 1, 0, 1, 1, 1 }); break;
            case 5:  print7seg({ 1, 0, 1, 1, 0, 1, 1 }); break;
            case 6:  print7seg({ 1, 1, 1, 1, 0, 1, 1 }); break;
            case 7:  print7seg({ 0, 0, 0, 1, 1, 1, 0 }); break;
            case 8:  print7seg({ 1, 1, 1, 1, 1, 1, 1 }); break;
            case 9:  print7seg({ 1, 0, 1, 1, 1, 1, 1 }); break;
            default: print7seg({ 1, 1, 1, 1, 1, 1, 0 }); break;
        }   return 1;
    });

})
```

![image5](https://miro.medium.com/v2/resize:fit:640/format:webp/0*ND6l9hJ3YdlHCZmZ.gif)

## Conclusion

Multitasking in Arduino UNO has opened up a range of possibilities for electronics and programming enthusiasts. Now you can create more complex and functional projects that can respond to multiple tasks simultaneously. While there are resource limitations on the Arduino UNO, smart programming techniques and task prioritization allow you to get the most out of it.

Remember that multitasking is not always the ideal solution. You must evaluate the needs of your project and find a balance between the desired functionality and the efficiency of the code. With the practice and knowledge gained in this article, you will be able to master multitasking on Arduino UNO and take your projects to the next level.

Dare to experiment and create! 