#shellnoise#

**Warning - I am in process of putting this together, currently it is a mess**

**Shellnoise is inspired by antirez/linenoise and the UTF-8 extensions
made by yhirose. Shellnoise is a single header library for making very 
usable shells for any Engine, Object, or library of code. I am using the 
best of linenoise, bits of this and that and my own code to make small,
high-utility modern shells - without 20,000K lines of kitchen sinks**

This should be ready to go by 01-Apr-2016, but _should always be 
considered beta code until you test it thoroughly yourself_.

Shellnoise was created to enable me to quickly develop a new command 
processor for any library for manual testing and executing funcitons.
Shellnoise is licensed under the same BSD license as linenoise.

**Documentation** is the code since only programmers are going to use this 
anyway (I've never read a single char of documentation on linenoise other
than the code ;-) I'm trying to use a pseudo literate style of commenting.

**For a linenoise quickstart please see:**

https://github.com/antirez/linenoise/blob/master/example.c

**To use this system:**

'#include shellnoise.h' in your code

compile shellnoise.c in your make file

and build your a.out with shellnoise.o

**OR**

merge shellnoise.h and shellnoise.c into a single file header
compilation unit and use that as shellnoise.c in your makefile

**OR**

create a static (or dynamic) library 

'#include shellnoise.h' in your code

and link with `-lshellnoise`

**OR**

If you want C++, please see: 

'https://github.com/yhirose/cpp-linenoise'


(it is a goal of Shellnoise to work with C++ out of the box, but its not there yet...)

Be aware that the above is only linenoise with UTF-8 extensions but you are welcome to raid this project and make a shellnoise.cpp! Just use shellnoise.h as a guide of what to include. 

This would be a good project! Please let me know if you do. I don't really use C++ at all anymore but lots & lots of people do.