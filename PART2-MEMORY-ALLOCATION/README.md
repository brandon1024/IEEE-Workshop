# IEEE Workshop Part 2 - Memory Allocation
Now let's talk memory allocation. If you've written C before, you've surely dealt with it. Although I am going to cover the basics, I also want to touch on **good** patterns (rules to follow) around dynamic memory allocation.

## The Basics of Dynamic Memory Allocation
In C, when you want a piece of memory, you have two options. You can either allocate memory on the [stack](https://www.gribblelab.org/CBootCamp/7_Memory_Stack_vs_Heap.html) or on the [heap](https://www.gribblelab.org/CBootCamp/7_Memory_Stack_vs_Heap.html).

When you allocate memory on the stack, it has to be of fixed size. You have to define its size as a constant (which must be defined at compile-time). So, you might do something like this:
```
int func()
{
    int array[50];

    array[0] = 0;
    array[49] = 49;

    return 0;
}
```

There are two things to note here. First, you need to declare the size (as mentioned before). If you don't know what size the array must be, then you can't use this method. Secondly, the array is allocated on the stack, so when the function returns, that stack frame is popped off and the array is lost.

What happens if you need the memory to be of a size that is unknown at compile-time, or you need an array that will persist even when the function returns? You use `<stdlib.h>`. Here's how you allocate some memory on the heap:
```
int func()
{
    int *array = malloc(sizeof(int) * 50);

    array[0] = 0;
    *(array + 49) = 49;

    free(array);
    return 0;
}
```

Functionally, the two examples are the same; you ask for space, and you're given space. The difference here is that you can create an array of any size, known or unknown at compile time.

Things get tricky with this fancy dynamic memory allocation stuff. Notice that I call `free(array)` before the function returns? You need to do this, because otherwise the memory you allocated will remain in the heap, and you won't have any way to reference it. This is known as a [memory leak](https://en.wikipedia.org/wiki/Memory_leak).

## Some More `<stdlib.h>` Stuff
There's a lot you can do with memory allocation in C. Here are a couple of functions in the standard library:
- `void* malloc(size_t size)`: Allocates the requested memory and returns a pointer to it.
- `void free(void *ptr)`: Deallocates the memory previously allocated by a call to calloc, malloc, or realloc.
- `void *realloc(void *ptr, size_t size)`: Attempts to resize the memory block pointed to by ptr that was previously allocated with a call to malloc or calloc.
- `void *calloc(size_t nitems, size_t size)`: Allocates the requested memory and returns a pointer to it.

A comprehensive list of functions in stdlib can be found [here](https://www.tutorialspoint.com/c_standard_library/stdlib_h.htm).

## How to Handle Memory Correctly
Memory leaks are BAD. It's really easy to lose track of memory, especially when code complexity increases. That's why it's important to develop good habits when using dynamic memory allocation.

There are no definitive rules to allocating memory. Different projects have different rules, but I'll go over the standard I follow.

### 1. Double Check (Triple Check) your `free()`'s
It goes without saying that you should `free()` your memory once you're done with it. When you write `malloc()` (or one of its variants), you should immediately (before you do anything else) write the `free()` for that memory. This will help ensure that you don't forget to free it once you're done with it.

### 2. Loosely Coupled Things are Happy Things
Ever heard that saying `Tight Cohesion, Loose Coupling`? This is an important concept in software engineering.

Sometimes, you might be tempted to have a function that returns a pointer to allocated memory, like this:
```
int *new(size_t size)
{
    int *array = malloc(sizeof(int) * size);

    // do stuff with your new array

    return array;
}
```

This is a pretty simple example, but imagine the code is a lot more complex. Allocating memory and returning a pointer to it is fine, and generally accepted, but it can quickly lead to issues with tightly coupled components, which can spread like wildfire in a large collaborative project. To avoid this, try to malloc and free a chunk of memory within the same scope if possible.

If you're having trouble seeing what I mean, let me put it another way. The function `new()` is passing on the responsibility of the `int *array` to whoever called it. It's like `new()` is saying, in a sassy voice, "Here, I'll allocate this for you, but it's not my problem anymore". So now, whoever called the function needs to deal with the memory, and `free()` it.

Here's what I prefer to do instead. Whenever possible, allocate memory outside the function, pass a reference to it to the function, and let the function do what it needs with it. Then, once the function returns, you can use what that function produced, then `free()` when you're done.

That's a bit wordy, so here's an example:
```
int func1()
{
    char *string = (char *)malloc(sizeof(char) * 13);

    int ret = func2(string, 13);
    if(ret)
        fprintf(stdout, "String: %s\n", string);
    else
        fprintf(stderr, "Something went wrong.\n");

    free(string);
}

int func2(char *string, size_t length)
{
    if(string == NULL)
        return 0;

    if(length < 13)
        return 0;

    string = "Hello World!";
    return 1;
}
```

Again, this is a pretty simple example but it demonstrates an important pattern. By passing the allocated memory to the helper function, the `char *string` is `malloc()`'d and `free()`'d in the same function. This keeps the `char *string` part of the concern of `func1()`.

Sometimes, however, you can't follow this pattern due to nature of the problem. If this is the case, be sure to document this clearly so that whoever is calling your function can easily see that they need to handle the memory. In my experience though, you can almost always restructure the problem to follow this pattern. So if you get stuck, think about it a bit more, go for a walk, pet your dog, and then after a while you'll come up with a way to keep your program tightly cohesive, and loosely coupled.

### 3. Checking `malloc()` for `NULL` Pointers
Did you know that `malloc()` could return null? It is generally poor practice to not check the pointer returned by `malloc()` (or one of its variants) before using it.

Here's how you should properly allocate memory:
```
...

int *offsets = (int *)malloc(sizeof(int) * offsets_len);
if(offsets == NULL) {
    perror("Fatal error: Cannot allocate memory.\n");
    exit(EXIT_FAILURE);
}

...
```

If malloc fails, it sets `errno` to `ENOMEM`, so `perror()` will display some useful information about this error. You can read more about it [here](https://stackoverflow.com/a/35026995).
