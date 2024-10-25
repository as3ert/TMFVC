# OpenGL-tutorial
OpenGL-tutorial repository for winter semester 2024/25

The entire tutorial is based on OpenGL version 4.6 Core so check your OpenGL version using the [GLview extensions viewer](https://www.realtech-vr.com/home/?page_id=142).

On linux you can run a simple command to check this: 
```
glxinfo | grep OpenGL
```

Please ensure that you have the latest drivers for you graphics card.

## Windows
Download the latest version of [Visual Studio](https://visualstudio.microsoft.com/de/downloads/).

Download the [64bit Windows installer for CMake](https://cmake.org/download/) and install.

Clone the GLFW github repository from source: https://github.com/glfw/glfw.git. Installation steps are described below.

If you are not running OpenGL version 4.6, download GLAD (Make sure to select the C/C++ version depending on your OpenGL version, Core; ignore all else) and replace the content of the glad folder provided in this project i.e. the KHR and glad incude folders and glad.c source file with the ones you downloaded.
Also make sure to edit the source file Main.cpp and change the OpenGL MAJOR and MINOR version accordingly and rest of the process should be the same.

*Disclaimer:* The process for compiling the tutorial on Windows is a bit more involved than on a Linux distribution. 
Please follow the following steps properly in order to avoid problems with the build.

### Compiling GLFW 
After cloning GLFW using 

```
git clone https://github.com/glfw/glfw.git
```

in the cmd prompt on windows, execute the following commands:

```
cd glfw
mkdir build && cd build

cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```
Next, open the `GLFW.sln` file generated in the build folder using Visual Studio.

**Make sure the solution configuration is set to debug and the solution platform to x86.**

Build it, using right-click and `Build`. If the commands were excuted properly, you shall have no errors for this build.

### Compiling the opengl_tutorial project

Clone this repository via

```
git clone https://github.tik.uni-stuttgart.de/ishasharma/OpenGL-tutorial.git
```

and copy the following files from the recently compiled glfw or glfw3 using the file explorer: 

From **glfw > build > src > Debug** on your file explorer, copy the `glfw3.lib` file and paste it in **OpenGL_tutorial > glfw > lib**. 

From **glfw > include**, paste the `GLFW` folder into **OpenGL_tutorial > glfw > include**.

Now, run the following commands:
```
cd OpenGL_tutorial
mkdir build && cd build
cmake ..
```

Open the `opengl_tutorial.sln` file using Visual Studio and configure the following properites:

Go to "Project", "Properties", and select "All Platforms" for your Platform  (for x86 and x64, if applicable). Then go to "VC++ Directories". 

Open up "Include Directories", and point to the "include" folder in your "glfw" folder and do the same thing for glad.

Click Ok and repeat for the "Library Directories" with the glfw "lib" folder. 

Next, go to "Linker", "Input",  and open up "Additional Dependencies". 

Here, make sure you have the `glfw3.lib`, and `opengl32.lib`. 
If not, add them (even though it's called "opengl32", it's still the 64bit version, this is just a naming convention).

Make sure, the C/C++ language standard is set to the latest, for example: Preview - Features from the **Latest C++ Working Draft (/std:c++latest)**; otherwise, you will not get access to std libraries such as `filesystem`.

Next, run build on the project and if everything was done correctly it should build without errors.

Launch the app using CTRL+F5 **after** selecting on your main solution node the Properties > single startup project > opengl_tutorial.

## Linux

Install GLFW using your package manager for, e.g., Ubuntu using: 

` sudo apt install glfw `

Install cmake:
` sudo apt install cmake `

Then, run the following commands to clone and build the linux binaries:

```
git clone https://github.tik.uni-stuttgart.de/ishasharma/OpenGL-tutorial.git
cd OpenGL-tutorial
mkdir build && cd build
cmake ..
make
```

you can run the app using:
`./opengl_tutorial`.

## Mac (using [Asahi Linux](https://asahilinux.org))
We highly encurage using [Asahi Linux](https://asahilinux.org) since it is designed for Apple Silicon Macs (M1, M2, etc.) to provide a fully open-source Linux experience.

Important to note: **Backup your Mac** using TimeMachine on an external drive **before** installation because the disk size will be shared between MacOS and Fedora Linux. Furthermore, you need approx. 100 GB of free disk space.

To start the process in the terminal run
```
curl https://alx.sh | sh
```
and follow the installation instructions of Asahi Linux. We freed up and assigned approximately 60GB of disk space to Asahi Linux. 
*As the installer proposes, if you have not enough disk space, due to TimeMachine Backups, consider to delete old Snapshots via [How to delete Time Machine local snapshots in macOS](https://appleinsider.com/articles/21/06/26/how-to-delete-time-machine-local-snapshots-in-macos).*

In some point of the installation process you need to choose an OS. For testing purpuses we installed ``Fedore Asahi Remix 40 with GNOME``.

If the installation worked and you can start your mac on Fedora you can almost exactly follow the instructions from Linux (keep in mind there are [Differences from Fedora to Ubuntu](https://fedoraproject.org/wiki/Differences_to_Ubuntu)).

Use the following commands on Fedora to install glfw (GLFW development library), g++ (GNU C++ compiler, needed to compile C++ code), cmake, and the Mesa implementation of OpenGL.
```
sudo dnf install glfw-devel
sudo dnf install g++
sudo dnf install cmake
sudo dnf install mesa-libGL-devel
```
Then run
```
git clone https://github.tik.uni-stuttgart.de/ishasharma/OpenGL-tutorial.git
cd OpenGL-tutorial
mkdir build && cd build
cmake ..
make
```

## Example
In the end, running the `./opengl_tutorial` should lead to
![alt text](exampleOutput.jpg)

