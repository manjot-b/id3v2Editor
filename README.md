This is a GUI application that lets the user 
edit the tags/metadata stored in mp3 and mp4 (m4a)
files.

INSTALL
To get up and running you first need to compile the taglib
library. Simply follow these steps.

1.	Download and install CMake and Qt Creator

2.	Open up the CMake GUI and set source code folder to libraries/taglib
	(the folder with all the cmake files and 3rdparty and bindings folder etc)
	
3.	in libraries/taglib create a new folder called "build" and set the path
	for the build to be this newly created folder

4.	Hit configure and set the generator to MinGW Makefiles. Press Finish
	(Make sure you have the mingw/bin folder to you PATH. It will be in the 
	Qt/Tools/mingw/bin)
	
5.	Click Generate

6.	