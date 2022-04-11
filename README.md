
# To run shell:

```
$ make
$ ./shell
```

- The makefile will compile the code. 
- Enter "make" command to compile the code. 
- ./shell to run the program.

# To quit the shell:

```
quit
```
# commands and functionalities provided:

-Supports the following commands :`bg`  , `cd` , `echo` , `fg` , `history` , `jobs` , `ls` , `pinfo` , `pwd` , `replay` , `repeat` , `sig` , and other external `shell commands` .

- Also supports `redirection` operations [ `>` , `<` , `>>` ] and `piping` [ `|` ] 

- Handles Ctrl_C, Ctrl_Z, Ctrl_D

- Can handle multiple commands separated by `;` .
  
- Handles processes in `foreground` & `background` environments 

# Shell files:

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

# Assumptions:

- If -l is given as a flag then if the file was modified before 6 months then year would be shown else time.
- If a file is modified 6 months before on he same date year will be printed irrespective of time.
-  The shell's home will be the directory from where it was invoked.
-  Commands and directory names cant be size greater than 1024.
- Interval or period in replay has to be positive integer.
- In jobs only -r and -s flags are supported, i.e., -rs ,-sr,etc. is not supported.


