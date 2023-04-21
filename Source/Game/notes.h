#pragma once
/*
- You need to find a way to introduce behaviour more quickly, like 'pausable'. Probably through inheritance. Or another design

- Next step is to rework the queue, and make the component system more extendable

C++ Stuff
- Check how inline affect performance
- Learn templated polymorphism

Ideas
- Maybe create UI tools in Python, like animation slicer
- Maybe create a script for the huge boilerplate code of each entity

Improvements
- I think I don't need the double queue system
- Should refactor so that each system has one queue of event, and dispatch them to the components. This would be aligned in memory, and get rid of all the queues
- You need to get rid of all these shared pointers of events. Events should be on the stack
- You need to specify the logic between input and logic event. It is not clear if the input system should throw logic or input events
- Might want to get rid of the forward declarations
*/
