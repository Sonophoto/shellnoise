** Shellnoise is inspired by antirez/linenoise and uses linenoise as
the foundation for a simple, single header library for making shells**

This should be ready to go by 01-Mar-2016, but should always be 
considered beta code until you test it thoroughly yourself.

Shellnoise was created to enable me to quickly develop a new command 
processor for any library for manual testing and executing funcitons.
Shellnoise is licensed under the same BSD license as Redis and linenoise.

Documentation is the code since only programmers are going to use this 
anyway (I've never read a single char of documentation on linenoise other
than the code ;-)

**For a quickstart please see:**

https://github.com/antirez/linenoise/blob/master/example.c


To use this system:

use make file to build shellnoise.o

'#include shellnoise.h'

and link with `-lshellnoise`

**OR**

merge shellnoise.h and shellnoise.c into a single file header
compilation unit

**OR**

If you want C++, please see: 

'https://github.com/yhirose/cpp-linenoise'

be aware that the above is only linenoise with UTF-8 extensions but you
are welcome to raid this project and make a shellnoise.cpp! Please let
me know if you do.


