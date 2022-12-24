<div align="center">
  <center><h1>minishell 💻</h1></center>

<p align="center">
	<a href="https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html">
		<img src="https://user-images.githubusercontent.com/91064070/165978388-0e4c1a3e-25b5-43fc-ba2d-967944f3f5ec.png" />
	</a>
</p>

## Goal of the project
Write a minimalist shell based on [bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell))


![alt tag](https://user-images.githubusercontent.com/91064070/165641504-ae8123ba-9562-4a84-bd40-c337f7aaff46.png)

Teamwork made with [DimiOui](https://github.com/DimiOui)

</div>


## Skills involved
* UNIX signals
* Pipes, forks, file descriptors redirections

## Features


Here are the main features of the project, taken from the subject:

```
Your shell should:

• Display a prompt when waiting for a new command.

• Have a working history.

• Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).

• Not use more than one global variable. Think about it. You will have to explain
its purpose.

• Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).

• Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.

• Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).

• Implement redirections:
◦ < should redirect input.
◦ > should redirect output.
◦ << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
◦ >> should redirect output in append mode.

• Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.

• Handle environment variables ($ followed by a sequence of characters) which should expand to their values.

• Handle $? which should expand to the exit status of the most recently executed foreground pipeline.

• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.

• In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.

• Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
```

## How it works

(Click on the mind map to open it on a new tab)

![](https://user-images.githubusercontent.com/91064070/165968967-d965d0cd-130f-4cda-9154-c656357d19b5.png)
## Usage
```shell
$> cd minishell/ && make
```
```
$> ./minishell
```