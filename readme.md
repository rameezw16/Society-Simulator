# Guide

The UML file is available as uml.png. Note that only the signature of the methods is given. This is to avoid clutter, as the names are available in the respective .h files.

The UML diagram was generated using the https://www.plantuml.com/ web server. The code was available at uml-code.txt.

This is a little explanation of our project and the code. Our project is a creative, procedurally generated, approach to the classic sheep-grass simulation, as well as an extension with terrain and seasons. 

Maximum vegetation levels, dirt, water bodies, people, are all completely randomly generated based on the seed. People have personalities (corresponding to the Big 5 traits in psychology) which are also randomly generated. Seasons come and go based on a set timer, and "seasons" within human population are observed. The cycle observed is as follows. 

1. People are seeded
2. They eat vegetation
3. Because they are healthy, they reproduce
4. Because the population of humans increases, the vegetation is reduced
5. Due to a low amount of vegetation, people die.
6. Because of low people, the vegetation increases
7. Repeat from 3.

This is an interesting conclusion.

Comments are given in the .h files of the major features.

* Usage
- First build the game, if the CMakeLists is out of date, then run "cmake .." from the build folder, otherwise run either "cmake --build build" from the root of the project or "make" from within the build folder.
- The program accepts a seed. Observe how the terrain is completely different at different values, and the placement of the people too. 
- Terminate the program by sending SIGINT to the terminal, or by closing the window

Example command:
./main 9 (will generate a random world, seed it with the value 9, and then add people)
./main (will generate a random world, and use the default seed of 1985, and then add people)

We had a lot of fun working on the project, and really learned a lot. About teamwork, about agent based modelling (which I used in a project for a different class for economic simulations, which I would love to show you), and about programming and computers. Many days were spent in GDB trying to track down some obscure, cryptic error. 

Unfortunately due to other projects and deadlines, the code is a little messy at places, but is fully functional and safe. We hope you'll understand.

Thank you for an interesting class. We hope to have you again as our professor, in better health next time.
