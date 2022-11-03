<div align="center">
  <center><h1>minitalk 💬</h1></center>
<img src="https://user-images.githubusercontent.com/91064070/148063719-48bfdab3-e75c-4a06-abee-3517f6c546c2.png" />

## Goal of the project
The goal of this project is to code a data exchange program using [UNIX signals](https://en.wikipedia.org/wiki/Signal_(IPC)).

![](https://user-images.githubusercontent.com/91064070/148063842-7623286c-627b-4dac-abdd-7aa6c7e79944.gif)
</div>

## Skills involved
* Bitwise operations
* UNIX signals
* Queueing processes

## How it works
We are going to setup a server that will display some text sent from a client.

*SERVER :*
	First we need to get the [PID](https://en.wikipedia.org/wiki/Process_identifier) of the server (with ```getpid()```) and display it on the terminal for the client to use it afterward.

*CLIENT :*
	Then the client uses [```kill()```](https://man7.org/linux/man-pages/man2/kill.2.html) which sends a signal to the server by taking two parameters, the PID of the server and the signal to send : ```kill(PID, signal)```.

For this project we are only allowed to use two [POSIX signals](https://en.wikipedia.org/wiki/Signal_(IPC)#POSIX_signals) as a form of communication between the server and the client, ```SIGUSR1``` and ```SIGUSR2```.

So the trick here is to send the strings to the server in the form of a binary message, the client converts the string into binary using bitwise operations.

We apply a [mask](https://en.wikipedia.org/wiki/Mask_(computing)) to each bit of the characters by shifting bits to the left in a loop, each time the result equals zero (0) we ```kill(PID, SIGUSR1)```, each time the result is more than zero ( >0), we ```kill(PID, SIGUSR2)```.

**Example**
```c
for(shift = 7; shift >= 0, shift--){
(character & (1 << shift)
}
```
```
The letter "m" in binary is 01101101

01101101 & 10000000 = 00000000  RESULT is 0   | 0 SIGUSR1
01101101 & 01000000 = 01000000  RESULT is > 0 | 1 SIGUSR2
01101101 & 00100000 = 00100000  RESULT is > 0 | 1 SIGUSR2
01101101 & 00010000 = 00000000  RESULT is 0   | 0 SIGUSR1
01101101 & 00001000 = 00001000  RESULT is > 0 | 1 SIGUSR2
01101101 & 00000100 = 00000100  RESULT is > 0 | 1 SIGUSR2
01101101 & 00000010 = 00000000  RESULT is   0 | 0 SIGUSR1
01101101 & 00000001 = 00000001  RESULT is > 0 | 1 SIGUSR2
```

*SERVER :*
	Now the server receives the signal through a signal handler using [```sigaction()```](https://en.wikipedia.org/wiki/Sigaction) and deciphers the binary code sent by the client. It creates a string by appending all the characters received. Once all the characters have been received, the string is printed to the screen. Each time the server receives a signal from the client, it sends a signal confirmation back to the client. In this part of the program, the function ```sigaction()``` is prefered to ```signal()``` because it allows the server to get the client's PID, hence enabling it to send the confirmation signals.

*CLIENT :*
	The client prints a confirmation message to the screen at the beginning of the communication and another one at the end, both triggered by the server and the ```signal()``` function.

#### Specificity
As there is not always an automatic queueing of the signals (depending on OS), we need to use [```usleep()```](https://man7.org/linux/man-pages/man3/usleep.3.html) and ```sigaction()``` to avoid signals to overlap and trigger unwanted behaviors.

## Usage
```shell
# run
cd minitalk/ && make
```
Then open two terminals, one for the server and one for the client
```shell
# first terminal
# execute
./server
```
```shell
# second terminal
# execute
./client PID "your_message"
```
