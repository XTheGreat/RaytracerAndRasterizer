# Starter code for CS5721

### Prerequisite Libraries

This code uses the libpng, zlib and Boost libraries. These are relatively easy to install on Linux and macos, but will require a little effort on Windows.

## Building the code on Linux

On Ubuntu Linux, you can grab the needed libraries with these package installs:

~~~~
sudo apt-get install libpng12-dev libz-dev libboost-all-dev
~~~~

Then, building should be as simple as

~~~~
mkdir build
cd build
cmake ..
make
~~~~

## Building on Windows

Building on Windows will take a little effort. You will need to grab the PNG and ZLib code and build it. After that, you will need to get Boost. Luckily there are nice pre-built binaries for Boost that you can install.

Step 1 - Get zlib and libpng 

You can download Zlib and libpng at the following URLS:

* Zlib - Go to [https://zlib.net/](https://zlib.net/) to grab the ZLIB libraries.
* PNG - Go to [http://www.libpng.org/pub/png/libpng.html](http://www.libpng.org/pub/png/libpng.html) to grab the PNG libraries.

These libraries use CMake, so you can build them with cmake rather easily. After downloading and extracting the files, bring up your preferred developer Command Prompt (I'd suggest the Visual Studio Developer Command Prompt). Then build each. I've provided instructions below:

### zlib

In the Zlib source directory, issue the following commands. Note that I built all of this using Visual Studio 2015 which I specify with the Cmake Generator "Visual Studio 14 2015".  You can use another version of Visual Studio if you like, but I'd suggest being consistent.

~~~~
mkdir buildWindows
cd buildWindows
cmake -G "Visual Studio 14 2015" -DCMAKE_INSTALL_PREFIX="C:\CS5721Libs" ..
~~~~

You could load this up into Visual Studio if you like, but you can also build it from the Visual Studio Developer Command Prompt using the following command (which I'd recommend):

~~~~
cmake --build . --config Release --target install 
~~~~

That command will build the Release version of zlib and install it in the C:\CS5721Libs folder that was specified in the previous cmake command.


### libpng

Next, navigate to the libpng source. Then issue the following commands:

~~~~
mkdir buildWindows
cd buildWindows
cmake -G "Visual Studio 14 2015" -DCMAKE_PREFIX_PATH="C:\CS5721Libs" -DCMAKE_INSTALL_PREFIX="C:\CS5721Libs" ..
cmake --build . --config Release --target install
~~~~

### Boost

Finally, you will need to install Boost. You should grab the Precompiled Windows Binaries of Boost from the Boost Sourceforge site [https://sourceforge.net/projects/boost/files/boost-binaries/](https://sourceforge.net/projects/boost/files/boost-binaries/).  You will want to grab Boost 1.64 or earlier.  I had difficulty with getting Boost 1.66 or Boost 1.65 working my version of Visual Studio and cmake. Not sure why yet, but 1.64 works and is fine for our purposes.

Be careful to download the correct installer. Visual Studio 2015's version number is 14.0.  Also, be sure to grab the 32-bit version as all the code we'll be developing is fine being built with 32-bit support. I downloaded boost_1_64_0-msvc-14.0-32.exe. The installer will place this in the C:\local\boost_1_64_0 folder on your machine and cmake knows to look here to locate the files.

## Build the starterCode

You're now ready to build the starterCode on Windows. Navigate to the location where you cloned the starterCode repo and following these instructions to generate the Visual Studio solutions file:

~~~~
mkdir buildWindows
cd buildWindows
cmake -G "Visual Studio 14 2015" -DCMAKE_PREFIX_PATH="C:\CS5721Libs" -DBOOST_LIBRARYDIR="C:\local\boost_1_64_0\lib32-msvc-14.0" ..
~~~~

At this point, you could open up the starterCode Visual Studio Solution file that will be created in that directory and build and edit within Visual Studio.

You can also build from the command line using cmake to issue the build:

~~~~
cmake --build . --config Release
~~~~

### Try out the examples

After it builds, you can try executing

~~~~
OpenGL/Release/glfwExample
~~~~

or

~~~~
examples/Release/test_pngWrite
~~~~

Note that in the case of test_pngWrite, you will need to copy the DLL's either into the Release folder for the examples OR into the System folder that Windows uses for the installed DLLs.

