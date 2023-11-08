Christopher Andrade
UWNetID: andradec
CSE 374
11/7/23

The script tninetest requires an output file, executable, and at least a single test
file. The executable is tested to ensure it is usable and can handle both real and 
non-existant Dictionaries. The script then runs the executable with each testfile and
outputs the results of the executable and test file tests to the appropriate/given
output file.

Slides from previous classes concerning linux, and multiple forums concerning both git
and linux generally were referenced.

TESTFILE 1
2665
#
78468377368425
#
exit
Testfile1 can could be testing to ensure that the  ""#" for next word" works correctly and
that other t9-onyms can be accessed by number correctly after using the "#" keyword.

TESTFILE 2
53556
noexit
exit
Testfile2 ensures that the exit keyword only works when exit is typed by itself. The t9
script should be exited if and only if exit is entered alone.

The sample test script I created could also test compatability with larger dictionaries. 
The Dictionary provided is as expected relatively small, without testing larger dictionaries
it isnt ensured that the executable wont hang. Furthermore the dictionary provided
gives all words their own line, while dictionaries with multiple words in a line should be
compatible though are not tested for. In general Dictionaries of varying sizes and structures
should be supported and tested.
