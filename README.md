# C-Shell
C-Shell is a  user-defined interactive shell program written in C .It is similar to bash and supports various functionalities including creating and managing new processes.

## To run shell:

```
$ make
$ ./shell
```

- The makefile will compile the code. 
- Enter "make" command to compile the code. 
- ./shell to run the program.

## To quit the shell:

```
quit
```
### OR

<kbd>Ctrl + D</kbd> saves the current session history , and exits the terminal 

## commands and functionalities provided:

-Supports the following commands :`bg`  , `cd` , `echo` , `fg` , `history` , `jobs` , `ls` , `pinfo` , `pwd` , `replay` , `repeat` , `sig` , and other external `shell commands` .

- Also supports `redirection` operations [ `>` , `<` , `>>` ] and `piping` [ `|` ] 

- Handles Ctrl_C, Ctrl_Z, Ctrl_D

- Can handle multiple commands separated by `;` .
  
- Handles processes in `foreground` & `background` environments 

### Implementation Details:
- On execution of code, a shell prompt of the following form must appear along with
it'<username@system_name:curr_dir>'

- The 'pseudo home directory' is the directory from which your shell is invoked irrespective of your current directory.

### Specifications Implemented:

### 1. Builtin Commands:

- `echo` command displays the line of text/string that is passed as a command line argument.

- `cd` command basic funtionality is implemented along with multiple flags `.`, `..`, `-`, `~`. 
More than one command-line arguments are not allowed.

- `pwd` command prints the path of the current working directory.

### 2. ls command:
`ls` command is implemented along with its two flags `-a` and `-l`.
Following cases are handled:
● ls
● ls -a
● ls -l
● ls .
● ls ..
● ls ~
● ls -a -l
● ls -la / ls -al
● ls <Directory/File_name>
● ls -<flags> <Directory/File_name>

 ### 3. System commands with and without arguments :
  - The shell executes the system commands either in the background or in the foreground.
  
  ● Foreground processes: Shell waits for this process to complete and regain control when this process exits.
  ● Background processes: Any command invoked with "&" is treated as a background
command. This implies thatshell will spawn that process and doesn't wait for the process to exit. It will keep taking other user commands. Whenever a new background process is started,  the PID of the newly created background process is printed on shell also. 

 ### 4. pinfo command:
 - `pinfo` : prints the process-related info of shell program.
 - `pinfo <pid>` : prints the process info about the given PID.
  
  ```<Name@UBUNTU:~>pinfo 7777
pid -- 7777
Process Status -- {R/S/S+/Z}
memory -- 123456 {Virtual Memory}
Executable Path -- /usr/bin/gcc```
  
 Process status codes:
1. R/R+: Running
2. S/S+: Sleeping in an interruptible wait
3. Z: Zombie
4. T: Stopped (on a signal)

 Note: “+” implies that the process is in the foreground
  
 

## Shell files:

- ### header.h:
 Contains the various function declarations and global variables.

- Other files provide various functionalities and commands. 

- ### main.c :
  contains starter code, contains the main loop for execution.

- ### prompt.c :
 prints prompt

- ### command.c :
 calls various command functions for execution

- ### pinfo.c :
  execution of pinfo.

- ### quit.c :
 execution of quit command

- ### background.c :
  execution of background processes.
  It creates a background process and handles recieved signals when a child dies.

- ### cd.c :
  cd command execution 
  . `cd`
    Changes the directory 
    - cd [arguments] 
    This changes the current directory to the argument
    - cd .. 
    Takes back to the parent directory.
    - cd 
    Takes to the home directory
    - cd -
    Takes to previous directory

- ### pwd.c :
  pwd command execution

- ### echo.c :
  echo command execution.

- ### ls.c :
  execution of ls with flags -l and -a .

- ### foreground.c :
  execution of foreground processes.

- ### bg.c :
   execution of bg command

- ### fg.c :
   execution of fg command
   
- ### ctrl.c :
  handles ctrl_C ctrl_Z signals

- ### jobs.c :
  execution of jobs command (flags: r,s)

- ### pipelines.c:
 handles piping

- ### redirection.c :
 handles redirection

- ### replay.c:
  execution of replay command

- ### repeat.c:
  execution of repeat commmand

- ### sig.c:
  execution of sig commmand

- ### Makefile:
  compiles the code

## Assumptions:

- If -l is given as a flag then if the file was modified before 6 months then year would be shown else time.
- If a file is modified 6 months before on he same date year will be printed irrespective of time.
-  The shell's home will be the directory from where it was invoked.
-  Commands and directory names cant be size greater than 1024.
- Interval or period in replay has to be positive integer.
- In jobs only -r and -s flags are supported, i.e., -rs ,-sr,etc. is not supported.


