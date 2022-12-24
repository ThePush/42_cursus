<div align="center">
  <center><h1>ft_printf 📝</h1></center>

<img src="https://user-images.githubusercontent.com/91064070/147373424-c4e3c444-0747-4a9e-b333-7d3a207e8c45.png" />

## Goal of the project
The goal of this project is to re code a small part of the Unix function [```printf()```](https://linux.die.net/man/3/printf). 

This code handles the following conversions : cspdiuxX%

</div>

## Skills involved
* Basic knowledge of C language
* Use of variadic functions
## How it works
We use a [variadic function](https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html), a function that can take an undetermined number of arguments.

First the function ```ft_printf()``` has to be declared with a string as the first argument and three dot as its second argument, meaning it can take a variable number of argument :
```c
int	ft_printf(const char *format, ...);
```
Next we are going to declare a ```va_list```, which is a macro of [```stdarg.h```](https://en.wikipedia.org/wiki/Stdarg.h) that contains the data types.

Then we use the macro ```va_start``` to initialise the list. It needs two arguments, the name of our ```va_list``` and the maximum number of arguments that we are going to pass to the function, in the case of printf that means potentially the whole string.

At this point it should look like this :
```c
int	ft_printf(const char *format, ...){
	va_list arguments;
	va_start(arguments, format);
}
```
Now we use ```va_arg(<va_list>, <type>)``` wich is connected to our argument list and needs to know what type of data the user is going to input for the function to handle. 
At the end of the function we use ```va_end(<va_list>)``` to stop using ```va_list``` and free it.

Here is an example of what it should look like :
```c
int	ft_printf(const char *format, ...){
	va_list arguments;
	va_start(arguments, format);
	va_arg(arguments, unsigned int);
	va_end(arguments);
}
```
In the case of ```ft_printf()```, the type of argument can change, so we a have to scan the string for a % sign, then check the following character and execute the function matching the type of conversion.

|Specifier(s)|Function|Output on [stdout](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout))|
|---|---|---|
|```%c```|```write()```|prints a single character|
|```%s```|```ft_putstr()```|prints a string|
|```%d``` ```%i```|```ft_putnbr()```|prints an integer|
|```%x```|```ft_puthex()```|prints an integer converted in hexadecimal, lowercase|
|```%X```|```ft_puthex()```|prints an integer converted in hexadecimal, uppercase|
|```%p```|```ft_puthex()```|prints a pointer address in hexadecimal|

## Usage
```shell
$> make
```
```
$> ./ft_printf_test
```

It will display a serie of tests and comparisons between ```ft_printf()``` and the real unix ```printf()``` function and its outputs.

Note that outputs may vary depending on your OS for the NULL ```%p``` test, as the return value is ```(nil)``` on Linux distributions and ```0x0``` on MacOS in case of a NULL pointer sent to ```printf()```.
