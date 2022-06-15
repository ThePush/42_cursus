<div align="center">
  <center><h1>libft 📚</h1></center>
<img src="https://user-images.githubusercontent.com/91064070/147372964-01fcc9aa-bf79-4870-8d4b-06f502f86a4e.png" />

## Goal of the project

The goal of this project is to re code some useful functions from the [standard linux library](https://man7.org/linux/man-pages/man7/libc.7.html) so we students can use them for our future projects later on.

Some other functions as well as functions to handle [linked lists](https://www.geeksforgeeks.org/linked-list-set-1-introduction/) have been added.
</div>

## Skills involved

* Basic knowledge of C language
* Type casting
* Use of linked lists


## How it works

### Standard library functions

```ft_atoi``` converts a string to an integer

```ft_bzero``` zeroes a byte string

```ft_calloc``` allocates memory for an array  and zeroes its elements

```ft_isalnum``` checks if a character is alphanumeric

```ft_isalpha``` checks if a character is alphabetic

```ft_isascii``` checks if a character fits into the ASCII character set

```ft_isdigit``` checks if a character is a number

```ft_isprint``` checks if a character is printable

```ft_itoa``` converts an integer into a string

```ft_memchr``` looks for a character into a memory area

```ft_memcmp``` compares two memory areas

```ft_memcpy``` copies two memory areas that must not overlap

```ft_memmove``` copies two memory areas and handle their potential overlaping

```ft_memset``` fills a memory area with a character

```ft_split``` cuts a string into new strings using a separator and stores the result into an array of strings

```ft_strchr``` locates a character in a string

```ft_strdup``` duplicates a string

```ft_strlen``` returns the length of a string

```ft_strncmp``` compares the n first characters of two strings

```ft_strnstr``` locates a substring in a string

```ft_strrchr``` locates a character in a string, beginning the search by the end

```ft_strtrim``` removes a set of character at the beginning and the end of a string

```ft_substr``` creates a string from another string, beginning at desired index and ending at desired length

```ft_tolower``` converts an uppercase character into lowercase

```ft_toupper``` converts a lowercase character into uppercase

When in doubt : [RTFM](https://linux.die.net/man/3/)

### 42 school's functions

```ft_putchar_fd``` writes a character on the designed file descriptor

```ft_putendl_fd``` writes a string on the designed file descriptor, appending a newline

```ft_putnbr_fd``` writes an integer on the designed file descriptor

```ft_putstr_fd``` writes a string on the designed file descriptor

```ft_striteri``` applies a function to each character of a string

```ft_strjoin``` concatenes two strings into one

```ft_strmapi``` applies a function to each character of a string and returns a newly creating string with those modifications

### Linked lists manipulation functions

```ft_lst_add_back``` adds a new element to the end of a list

```ft_lst_add_front``` adds a new element to the beginning of a list

```ft_lstclear``` clears elements of a list starting from a given element

```ft_lstdelone``` deletes one element of a list

```ft_lstiter``` applies a function to all elements of a list

```ft_lstlast``` returns the last element of a list

```ft_lstmap``` applies a function to each element of a list and returns a newly created list

```ft_lstnew``` initialises a new list 

```ft_lstsize``` counts the number of elements in a list

## Usage

The [makefile](https://en.wikipedia.org/wiki/Make_(software)) will compile a [static library](https://en.wikipedia.org/wiki/Static_library) with ```ar rcs```.

```shell
# run
make
# then compile your project with the libft.a file to use the functions into your own program
cc <projet.c> libft.a -o <project_name>
```
