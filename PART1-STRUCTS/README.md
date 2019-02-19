# IEEE Workshop Part 1 - Structs
This is the first part of a three-part series on writing better C programs! I go over a variety of concepts here, and each topic varies in depth. If you're unfamiliar with the concepts covered in this workshop, you should be able to pick them up pretty quickly.

## What is a struct?
A `struct`, which is short for Structure, is a user-defined data type. It's a bit an "Object" you'd see in an Object Oriented Programming language.

In a struct, you can group together multiple types of data in a block of memory.

## How do I use a struct?
Let's see an example:
```
struct my_struct {
    int some_integer;
    char some_character;
    char some_buffer[64];
    char *some_pointer;
};
```

The code above declares a custom struct type called `my_struct`. Now, when you want to use the struct:
```
void func()
{
    struct my_struct data;

    data.some_integer = 12;
    data.some_character = 'a';
    data.some_buffer = "Hello World";
}
```

The dot (`.`) operator, seen above, is used to access entities in your struct. There is another operator (`->`) used to access entities in a struct when you only have a pointer to that struct. Let's see an example:
```
int func(const struct my_struct *data)
{
    // data is not a struct itself, but a pointer to a struct.

    data->some_character = 'a';
    data->some_buffer = "Hello World";

    return data->some_integer;
}
```

## How do I pass structs around?
Easy! You have two options: pass a struct to a function directly, or pass it by reference.

Here's an example of passing a struct directly:
```
struct info_t {
    int important;
    char also_important;
}

char get_value(const struct info_t info);

int main(int argc, char *argv[])
{
    const struct info_t info = {.important = 1, .also_important = 'c'};
    char c = get_value(info);
}

char get_value(const struct info_t info)
{
    return info.also_important;
}
```

Here's an example of passing a struct by reference:
```
struct info_t {
    int important;
    char also_important;
}

char get_value(const struct info_t *info);

int main(int argc, char *argv[])
{
    const struct info_t info = {.important = 1, .also_important = 'c'};
    char c = get_value(&info);
}

char get_value(const struct info_t *info)
{
    return info->also_important;
}
```

## Initialization
Although you can initialize a struct by declaring it and then initializing all of its members, there are better ways to do this. As shown in the example above, you can initialize a struct by using curly braces `{}`. Here's an example:
```
int main(int argc, char *argv[])
{
    struct info_t {
        int important;
        char also_important;
    }

    const struct info_t info = {.important = 1, .also_important = 'c'};

    // You can also omit the struct member names and initialize them in order:
    const struct info_t info_other = {1, 'c'};
}
```

## Combining `struct` with `typedef`
You can also create your own type using the `typedef` keyword. When you do this, you won't have to use the `struct` keyword whenever you declare a struct. For example:
```
typedef struct point_decl point;
struct point_decl {
    int x;
    int y;
};

int main(int argc, char *argv[])
{
    // Notice that i'm not declaring this struct with `struct point_decl p1 ...`
    point p1 = {.x = 0, .y = 0};
}
```

## Further Reading (more cool stuff you can do with structs)
- [Bit Fields](https://www.tutorialspoint.com/cprogramming/c_bit_fields.htm): When memory space is tight, you can restrict how many bits are used for your struct entities.
- [Flexible Array Member](https://www.geeksforgeeks.org/flexible-array-members-structure-c/): You can actually declare a struct where the last member is an array of unknown length.