Attendance

DESCRIPTION
Attendance allows instructors all over the world to track and keep records of their students. By Utilizing bluetooth technology of the raspberry pi,
it's able to scan, log devices to their owners and therefore be able to determine 
which student is in attendance by performing a scan at the instructors choice.

HOW TO RUN PROJECT

1. Download zip file containing all necessary files
2. Unzip files and navigate into the folder through terminal
3. type "make" which will then initiate makefile that compiled all files together

THINGS YOU CAN DO
Login using given credentials

  Username:abc
  Password:123
  
  		OR
  Username: def
  Password: 456
  
We have created some dummy rows to populate the databases in order to test functionality. List of dummy data is provided at the very bottom under DUMMY DATA.
Program will prompt the user to be able to do things like scan for bluetooth devices, read the data, modify it and even delete data.
It'll prompt the user for selection data it requires in order to perform the relevant functions.
We have made it easy for the user to be able to select functionality using prompt options.

CREDITS
Xu Wang 250 748 901 XWANG932@UWO.CA
Tsung-Ying, Tsai 251 262 078 ttsai26@uwo.ca
Artur Krupa, 251190423 akrupa3@uwo.ca
Henry Chen, 251166178 hchen869@uwo.ca
Uzair Salim, 251143778 usalim2@uwo.ca
IF YOU HAVE ANY QUESTIONS OR REQUIRE CLARIFICATIONS PLEASE CONTACT THE DEVELOPMENT TEAM AT ANY EMAIL IN THE CREDITS SECTION



DUMMY DATA

Professors
professorID|username|password
A65|abc|123
A33|def|456

STUDENT
studentID|firstname|lastname
CZ56|Tom|Elliot
CZ43|Bob|Redding
CZ67|tomas|Woodward
CZ45|Karl|Smith

Course
course name|title|professor
CS001|Intro to Compsci|A65
CS005|Intro to Website|A65
CS310|Advanced Computer Graphics|A33

Takes
courseID|student
CS001|CZ56
CS001|CZ43
CS005|CZ56
CS005|CZ67
CS310|CZ45
CS310|CZ43
