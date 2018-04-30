# Wilkinson - Test 1

## Command Line Parameters:

When there is one parameter on the command line after the name of the program, it will load the file associated with that name. If there is no extension on the name given, the default extension of “.exp” must be added to the file name before opening the file. Conversely, if there is a /h or /? As the parameter, then a “help message” must be displayed to the user and the program terminates.


When there are two parameters on the command line after the name of the program, the first parameter must be the word EXECUTE or RECORD. The next parameter is a “script” file, which is composed of commands, as stated from the above section which deals with input from the command line. If the word EXECUTE is present, then the program must read the file and perform all of the statements within the file. If the word in RECORD, then the program must save to a file all of the commands that the user enters in via the command line. Script files must have an extension of “.spt”; and, as above, the “.spt” must be added if the user did not provide it.


If there are more than two parameters on the command line, then the program must “error out.” This means to notify the user that the program will be quitting and why it did so.

## Extra Credit:

Addition of the ability to allow for function composition such as F = G(H), where G and H are algebraic expressions (50 points)

Addition of the ability to allow for operations such as F = (2X + 4)^3, without the use of the LET command (this implies that the LET command is depreciated and that the ability of raising an algebraic expression to a positive power is available) (100 points)
Addition of the ability to solve for all of the zeros of the polynomial expression using Newton's Algorithm (100 points).

Addition of the ability to do all of the above in multivariate form (x, y, z is the limit). (250 points)

Addition of the ability to factor expressions. (100 points)

