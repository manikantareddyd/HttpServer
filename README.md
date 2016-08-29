# Http Server
A simple Http Server implemented in C++ for purely educational puposes, in case you need any reference!

## Instructions to Setup.
+ Clone the repository in an appropriate location
+ In the file **globalVariables.cpp** change the configuration values as desired for
  + > rootDir
    > > Has to match the directory path where you want your root directory to reside (Usually the index.html page directory)

    > > In this case, by default the root directory is './webfiles'

  + > PORT
    > > This will the listening port of the server. Make sure it doesn't collide with an existing in use port or is blocked by your firewall.

    > > The default listening port is 1234
+ To compile, run make
~~~
$ make
~~~
If all goes right, an executable name **http-server** must be generated

+ To run the server execute the following command
~~~
$ ./http-server PORT rootDir
~~~
PORT and rootDir are optional

Your server should be now up and running.

*Note:* This is not an optimized piece of code. Pull requests are welcome.

## Code Structure.
The names of files and functions are self explainatory. Using a good ide will help you in tracing the call stack (:P).

And yes I'm lazy.
