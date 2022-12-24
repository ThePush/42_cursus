# Exam Rank 06

Manipulation of sockets and file descriptors.

## Usage

Compile:

```
$> clang -Wall -Wextra -Werror mini_serv.c -o mini_serv
```

Open 3 terminals and run:

```
$> ./mini_serv <port>
```

```
$> nc localhost <port>
```

```
$> nc localhost <port>
```

The first terminal will be the server, the other two will be the clients.

Try:
```
#(first terminal will be the server)
$> ./mini_serv 50000
```
```
#(second terminal will be client 0)
$> nc localhost 50000
```
```
#(third terminal will be client 1)
$> nc localhost 50000
$> Hello
$> Lor^Dem ipsum
```
```
#(second terminal)
server: client 1 just arrived
client 1: Hello
client 1: Lorem ipsum
```

The integrity of the message should not be affected by the `^D` (ctrl+D) signal.
