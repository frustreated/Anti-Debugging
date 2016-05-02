# Creating Anti-Debugging Environment
Repository of course materials to act as teaching artifact for future generations

##Authors
* DaeYoung Yoon
* Elias Lozano

# README
##Introduction
The purpose of this project is to implement the common anti-debugging techniques in order to gauge their effectiveness.
We developed a program that, if run, can automatically detect the presence of a debugger in any currently running process and kill these processes. In a sense, such a program would be the ultimate anti-debugging tool since it would prevent dynamic analysis on a remote machine. This is different from embedding anti-debugging techniques within the source code itself since, theoretically, it could be used to create and enforce an anti-debugging environment. 

##Developing Environment and System Requirements
* This program will detect debuggers only in Windows OS because it uses an API Library called Windows.h.
* This code was developed in Visual Studio 2010 and it ideal performance will be achieved by compiling in Visual Studio 2010.

##Program Structure
* dbgdetector.h - header file that has DBGdetector class
* dbgdetector.cpp - implementation of the class DBGdetector
* main.cpp - main method for the program that gives input to DBGdetector.

##How to Run the Program
* Simply run the Final.exe file in Windows Environment.
* Or edit and compile the program if you have Visual Studio as desired.

