<div align="center">
  <center><h1>push_swap 🔢</h1></center>
  <img src="https://user-images.githubusercontent.com/91064070/166066935-5ae202d2-6110-473a-9f2c-6bdee5f97aa7.png">

## Goal of the project

This project involves sorting data on a stack, with a limited set of instructions, and the smallest number of moves. To make this happen, we have to manipulate various sorting algorithms and choose the most appropriate solution(s) for optimized data sorting.
</div>

## Skills involved
* Linked lists
* Data sorting algorithms
* Bitwise

## How it works
We are given a set of moves to sort a list of random numbers using two stacks.

Said moves are:

```
sa (swap a): Swap the first 2 elements at the top of stack a.
Do nothing if there is only one or no elements.

sb (swap b): Swap the first 2 elements at the top of stack b.
Do nothing if there is only one or no elements.

ss : sa and sb at the same time.

pa (push a): Take the first element at the top of b and put it at the top of a.
Do nothing if b is empty.

pb (push b): Take the first element at the top of a and put it at the top of b.
Do nothing if a is empty.

ra (rotate a): Shift up all elements of stack a by 1.
The first element becomes the last one.

rb (rotate b): Shift up all elements of stack b by 1.
The first element becomes the last one.

rr : ra and rb at the same time.

rra (reverse rotate a): Shift down all elements of stack a by 1.
The last element becomes the first one.

rrb (reverse rotate b): Shift down all elements of stack b by 1.
The last element becomes the first one.

rrr : rra and rrb at the same time.
```

The goal is to get all the numbers sorted on stack A, using the minimum amount of operations.

* Lists of 2 or 3 elements are hard sorted.

* Lists of 4 to 45 elements are sorted using selection sort: the program looks for the lowest number in stack A and sends it to stack B, then everything is sent back in stack A, sorted.

* Lists greater than 45 elements are sorted with the radix sorting algorithm. It is a nice way to practice bitwise operations. [Extensive explanation of this method here.](https://medium.com/nerd-for-tech/push-swap-tutorial-fa746e6aba1e) With the radix algorithm, results will always be the same when trying lists with the same amount of numbers, regardless of the values of the numbers themselves, making this method really safe.
