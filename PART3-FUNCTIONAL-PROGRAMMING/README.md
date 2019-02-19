# IEEE Workshop Part 3 - Functional-ish Programming
Did you know that you can write functional-ish programs in C? There's actually some pretty fancy things you can do with C. Let's go over some of them.

## Variadic Functions
The term "variadic" means "varying number of arguments". If you've worked with other programming languages like Java, you've surely seen this before:
```
public String concat(Object... objects) {
    String s = "";
    for(Object o : objects) {
        s += o.toString();
    }

    return s;
}

...

String s = concat(new Long(1), new Object(), "Some String");
// s = "1java.lang.Object@6d06d69cSome String"
```

You can have variadic functions in C too. To use it, you need to include the `<stdarg.h>` library.

```
#include <stdarg.h>

...

void func1()
{
    int total = add(4, 12, -89, 45, 74);
    // total = 42
}

int add(int count, ...)
{
    va_list ap;
    int i = 0, sum = 0;

    va_start(ap, count);
    for(i = 0; i < count; i++)
        sum += va_arg(ap, int);

    va_end(ap);
    return sum;
}
```

There's a bit going on here, but lets break it down.

First, let's look at the function signature `int add(int count, ...)`. Notice that there is one parameter, followed by `...`. In C, variadic functions must have at least one parameter defined before the variadic part. So, a signature like `int add(...)` or `int add(..., int count)` is not allowed.

Next, you'll notice in the add function there is a new type called `va_list`. This is essentially a pointer to the first optional parameter, and is how you reference the argument.

Next, you'll notice three macros `va_start`, `va_arg`, and `va_end`.
- `va_start` initializes the argument pointer `va_list`. You pass to it the `va_list` and the last parameter in the function signature (in this case, count).
- `va_arg` is how you get the argument values. You pass to it the `va_list` and the type of object that you expect to have returned. The first call gives you the first argument, the second call gives you the second, and so on.
- `va_end` is used to indicate that you are finished with the argument pointer.

This covers the very basics of variadic functions in C. There's actually a lot more to them, so I've skipped over some information for brevity. If you want to read more about variadic functions, [check this out](https://www.gnu.org/software/libc/manual/html_node/How-Variadic.html#How-Variadic).

## Function Pointers
Now for the functional-ish part. The reason I say `ish` is because C is not a functional programming language, in the traditional sense. It is possible to write code in C that has the style of functional programming code.

What is "functional" code? Simply put, it's the idea of passing a function as an argument to a function. The reason functional programming is so powerful is because it allows you to essentially hot-swap logic in a function. This allows you to design algorithms that use the [strategy pattern](https://en.wikipedia.org/wiki/Strategy_pattern) to select an algorithm at runtime. This concept is a bit tricky to grasp at first, so don't worry if you don't get it the first time.

First, let's look at function pointers. Consider the following function:
```
int add(int a, int b)
{
    return a + b;
}
```

To declare and initialize a pointer to this function:
```
int (*function_ptr)(int, int) = &add;
```

Now, we can call the function using our function pointer:
```
int sum = (*function_ptr)(7, 13);
```

Now, let's pass this function to another function (woah, function-ception):
```
int operation_mod_two(int (*function_ptr)(int, int))
{
    return (*function_ptr)(7, 13) % 2;
}
```

We can also return a function pointer from a function:
```
int f1(int a, int b)
{
    return a + b;
}

int f2(int a, int b)
{
    return a % b;
}

int (*function_factory(int type))(int, int)
{
    int (*function_ptr)(int, int);
    if(type == 1)
        function_ptr = &f1;
    else
        function_ptr = &f2;

    return function_ptr;
}
```

Neat. Where this concept comes in handy is in situations in which you need to compare two things, like in a sorting algorithm, or if you need to provide a custom handler to an existing piece of code.

## Further Reading
- [GNU C - How Variadic Functions are Defined and Used](https://www.gnu.org/software/libc/manual/html_node/How-Variadic.html#How-Variadic)