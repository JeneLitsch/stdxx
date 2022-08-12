# stx::task_queue

## Header
stdxx/task_queue.hxx

<br>

---

<br>

## Description
The stx::task_queue is used to buffer callable object in queue and call them later on another thread safely.

<br>

---

<br>

## Member functions

<br>

### execute() 
Run all functions on the queue. The functions get called in the order in which they were pushed.

<br>

### push(Fx fx)
Adds a callable to the end of the queue.
This function returns a future to the returns value of fx.