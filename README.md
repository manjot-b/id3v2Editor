This is a GUI application that lets the user 
edit the tags/metadata stored in mp3 and mp4 (m4a)
files.

INSTALL TAGLIB
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
	
	If you recieve some CMake error "the source does not match the source", 
	just save the taglib.pro file in libraries/taglib/taglib to some 
	temporary location, download the taglib source code from their github page
	and place the source code into libraries/taglib.
	Then place taglib.pro file back in libraries/taglib/taglib. 
	Go back to step 2.
	
5.	Click Generate

6.	Now open up the taglib.pro file located in libraries/taglib/taglib
	with Qt Creator. Switch the build type from debug to release and then
	click on the hammer to build the project.
	
COMPILE PROJECT
Now all you need to do it go to the root folder and open up id3v2Editor.pro
and compile and run it!