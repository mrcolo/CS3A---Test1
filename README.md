# Wilkinson - Test 1

Command Line Parameters:

When there is one parameter on the command line after the name of the program, it will load the file associated with that name. If there is no extension on the name given, the default extension of “.exp” must be added to the file name before opening the file. Conversely, if there is a /h or /? As the parameter, then a “help message” must be displayed to the user and the program terminates.


When there are two parameters on the command line after the name of the program, the first parameter must be the word EXECUTE or RECORD. The next parameter is a “script” file, which is composed of commands, as stated from the above section which deals with input from the command line. If the word EXECUTE is present, then the program must read the file and perform all of the statements within the file. If the word in RECORD, then the program must save to a file all of the commands that the user enters in via the command line. Script files must have an extension of “.spt”; and, as above, the “.spt” must be added if the user did not provide it.


If there are more than two parameters on the command line, then the program must “error out.” This means to notify the user that the program will be quitting and why it did so.


Program Requirements

All values must be stored in a class called Fraction. This class must be able to handle all operations between decimals, fractions, and integers with mixedNumbers
All data must be stored as a Fraction with all output given as a Fraction.
Only ONE input stream function in the main.cpp can be written for reading of input (whether it comes from a command line or a file). Thus, the input function must be passed a parameter telling it which stream is to be used for the reading of commands. 
If the commands are coming from a file, they must be echoed to the screen. If the user is entering them, they must not be echoed.
All strings used must be C++ strings.
Exceptions must be used accordingly. Such as when a file does not exist, divide by zero, invalid input, and so forth.
There must be a class called expression that will store the expressions entered. This class must have Fractions for each term of the expression. (Hint: dynamic arrays or vectors)
Terms of the expression must be stored in either a structure or a class (preferred).
 

Hints:

You can never forget anything learned in any CS course. Data storage sizes are very important, and mismatches can cause severe problems.
cplusplus.com is your friend.
“Divide and Concur” this program. First, jointly design the header files, then split up the coding. Then combine headers, the main, and so forth to make a working program.
Rules of the Test:

You may use any resource you wish, as long as it can be FULLY DOCUMENTED within your code.
You may work in teams of two and submit one test for the team.
You must be prepared to answer any question about your program when you demonstrate its functionality during lab.
Your program must, as discussed in class, conform to object oriented design constructs. (In short, this means that if a mixed number needs to do something, all code for what needs to be done must be in the mixed number class, its friends, and so forth)
Extra Credit:

Addition of the ability to allow for function composition such as F = G(H), where G and H are algebraic expressions (50 points)
Addition of the ability to allow for division of expressions, such as F = G/H (50 points)
Addition of the ability to allow for operations such as F = (2X + 4)^3, without the use of the LET command (this implies that the LET command is depreciated and that the ability of raising an algebraic expression to a positive power is available) (100 points)
Addition of the ability to solve for all of the zeros of the polynomial expression using Newton's Algorithm (100 points).
Addition of the ability to do all of the above in multivariate form (x, y, z is the limit). (250 points)
Addition of the ability to factor expressions. (100 points)


## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Installing

A step by step series of examples that tell you have to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone who's code was used
* Inspiration
* etc

