<div align="center">
  <center><h1>get_next_line ⌨</h1></center>
<img src="https://user-images.githubusercontent.com/91064070/147373286-a6039361-2208-431a-9625-384bf44a64d9.png" />

## Goal of the project
The goal of this project is to read one line either from [standard input](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)) or from [file(s) descriptor(s)](https://en.wikipedia.org/wiki/File_descriptor). Each time the function is called, the next line is read.
A line is defined by a string of characters ended either by a newline or end of file.
</div>

## Skills involved
* Basic knowledge of C language
* Use of functions open, read, close
* Use of static variables

## How it works
The file descriptor is scanned by a certain amount of characters each time, amount determined by user input ``BUFFER_SIZE=xx``, we append the strings scanned until we encounter either a [newline](https://en.wikipedia.org/wiki/Newline) or [end of file](https://en.wikipedia.org/wiki/End-of-file). If a newline or EOF is found into the concatened string, this string is split with the newline as a separator. The part of the string before the newline, including it, is returned and the remaining is saved in a [static variable](https://en.wikipedia.org/wiki/Static_variable).

At the next function call, the remain of the previous string becomes the begining of the new string, characters are appended to it until a newline or EOF is found and the process goes on.

#### Specificity
The static is declared as a [two dimensional array or array of strings](https://overiq.com/c-programming-101/array-of-strings-in-c/), each row corresponding to one file descriptor, this way the program can handle several file descriptors at once.

## Example :
Here we have a text with 2 lines and a buffer size of 9 :

```
First line
Second line
```
or :
```
First line\nSecond lineEOF
```
```shell
# BUFFER_SIZE=9

 1|2|3|4|5|6|7|8|9|   |1| 2|3|4|5|6|7|8|9|   |1|2|3|4|5  |
[F|i|r|s|t| |l|i|n|] [|e|\n|S|e|c|o|n|d| |] [|l|i|n|e|EOF|]

# First scan of 9 characters
static = [First lin]

# No newline or EOF found, so we concatene with one BUFFER_SIZE (9 characters in our example) more
static = [First line\nSecond ]

# A newline is found, we can move on the next step
# We extract the first part of the string, including the newline, NULL terminate it, and return it 
# It will be the line displayed by the first call of the function
returned line = [First line\n]

# And now we update the static variable for the next call by keeping the remaining characters
static = [Second ]
```
```shell
# If the function is called again, the static is scanned again and the process goes on
[Second ]
[Second lineEOF]
returned line = [Second lineEOF]
```
## Usage

```shell
# run
cc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c gnl_main.c -o get_next_line

# Then execute with any file that contains characters as argument
./get_next_line text text1 text2 
```
Output :
```
fd = 3
I fly like paper, get high like planes
If you catch me at the border I got visas in my name
If you come around here, I make 'em all day
I get one done in a second if you wait
I fly like paper, get high like planes
If you catch me at the border I got visas in my name
If you come around here, I make 'em all day
I get one done in a second if you wait

fd1 = 4
Sometimes I think sittin' on trains
Every stop I get to I'm clocking that game
Everyone's a winner, we're making our fame
Bona fide hustler making my name
Sometimes I think sittin' on trains
Every stop I get to I'm clocking that game
Everyone's a winner, we're making our fame
Bona fide hustler making my name

fd2 = 5
No one on the corner has swagger like us

fd42 = 42
(null)
```
The gnlmain.c is set to make the program display :
* each fd number 
* text and text1 from the begining to the end with a loop that calls get_next_line until the end of file
* the first line of text2 with only one call
* (null) for the last parameter, which is an invalid fd number (it will not segault)

Note that :
* as fd#0 is stdin, fd#1 is stdout and fd#2 is stderr, the output of the function will begin at fd = 3

* the still reachable leak reported by valgrind when calling the fonction once (as we do with text2 in our example) is actually the static variable

* if no argument is input, standard input is supported but just for testing purpose as it is actually not really useful for this project.
