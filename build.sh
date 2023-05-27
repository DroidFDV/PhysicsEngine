# If there are no arguments or if the argument is equivalent to "help"
if [ "$1" == "" ] || [ "$1" == "help" ]
then
    # echo -e allow us to use arguments, like \n that breaks the line
    echo -e "\n"
    echo "Enter 'build.bat action' where action is one of the following:"
    echo -e "\n"
    echo   "create_project    Will create the resources needed to a new project into the current directory"
    echo   "compile           Will generate make file then compile using the make file."
    echo   "run               Will generate make file then compile using the make file then run the project"
    echo   "clean             Remove all binaries and intermediate binaries and project files."
    echo   "codelite          Generate CodeLite project files"
    echo   "gmake2            Generate GNU makefiles for Linux"
    echo   "vs2005            Generate Visual Studio 2005 project files"
    echo   "vs2008            Generate Visual Studio 2008 project files"
    echo   "vs2010            Generate Visual Studio 2010 project files"
    echo   "vs2012            Generate Visual Studio 2012 project files"
    echo   "vs2013            Generate Visual Studio 2013 project files"
    echo   "vs2015            Generate Visual Studio 2015 project files"
    echo   "vs2017            Generate Visual Studio 2017 project files"
    echo   "vs2019            Generate Visual Studio 2019 project files"
    echo   "xcode4            Generate Apple Xcode 4 project files"

elif [ "$1" == "compile" ]
then
    # Create makefile gmake
    premake5 gmake2
    cd build
    make

elif [ "$1" == "run" ]
then
    # Create makefile gmake
    premake5 gmake2
    cd build
    make
    cd Core/bin/Debug 
    ./Engine
    # Run
    # cd build
    # Create a variable that will get the folder that has the word "...linux..." in its name
    # var=$(find -name *linux*)
    # ./$var/ProjectFolder/ProjectFolder
    # cd ..
fi
exit
