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
  
```
<Name@UBUNTU:~>pinfo 7777
pid -- 7777
Process Status -- {R/S/S+/Z}
memory -- 123456 {Virtual Memory}
Executable Path -- /usr/bin/gcc 
```
  
 Process status codes:
1. R/R+: Running
2. S/S+: Sleeping in an interruptible wait
3. Z: Zombie
4. T: Stopped (on a signal)

 Note: “+” implies that the process is in the foreground
 
 ### 5. Finished background processes:
  If the background process exits then the shell displays the appropriate message to the user.
 
 ### 6. Repeat command(for foreground proccesses):
`repeat` command is responsible for executing the given
instruction multiple times. The first argument to the command specifies the number of
times the following command is to be run.

### 7. Input/Output Redirection:
Using the symbols `<`, `>` and `>>`, the output of commands, usually written to stdout, can be redirected to another file, or the input taken from a file other than stdin. Both
input and output redirection can be used simultaneously
  
### 8. Command Pipelines:
 A pipe, identified by |, redirects the output of the command on the left as input to the command on the right. C-Shell is able to support any number of pipes.
  
### 9. I/O Redirection within Command Pipelines:
  C-Shell is able to handle input/output redirection within command pipelines. 

### 10. User-defined commands:
  
 - `jobs`: This command prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with
their job number (a sequential number assigned by your shell), process ID and their state, which can either be running or stopped. There may be flags specified
as well. If the flag specified is -r, then print only the running processes else if the flag is -s then print the stopped processes only.
  
 - `sig` : Takes the job number (assigned by shell) of a running job and sends the signal corresponding to signal number to that process. The shell 
throws an error if no job with the given number exists.
  
  Example 
  ```
<tux@linux:~> sig 2 9
# sends SIGKILL (signal number 9) to the process firefox (job # list as per the previous example), causing it to terminate
  ```
  
 - `fg` : Brings the running or stopped background job corresponding to job number to the foreground, and changes its state to running.The shell throws an
error if no job with the given job number exists.
  
  Example:
  ```
<tux@linux:~> fg 4
# brings [4] gedit to the foreground
  ```
 
  
  - `bg`: Changes the state of a stopped background job to running (in the background). The shell should throwserror if no background job corresponding to the given job number exists, and do nothing if the job is already running in the background.
  
  ### 11. Replay command:
  `replay`: executes a particular command in fixed time interval for a certain period
  
  Example:
  ```<Name@UBUNTU:~> replay -command echo "hi" -interval 3 -period 6```
  
  ### 12. Signal Handling:
  1. `CTRL-Z`:
It pushes any currently running foreground job into the background, and changes its state from running to stopped. This has no effect on the
shell if there is no foreground process running.
  
2. `CTRL-C`:
  It interrepts any currently running foreground job, by sending it the SIGINT signal. This has no effect on the shell if there is no foreground
process running.
  
3. `CTRL-D`:
  It logs you out of shell, without having any effect on the actual terminal.

  
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


