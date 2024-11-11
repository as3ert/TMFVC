# OpenGL-tutorial
OpenGL-tutorial repository for winter semester 2024/25

The entire tutorial is based on OpenGL version 4.6 Core so check your OpenGL version using the [GLview extensions viewer](https://www.realtech-vr.com/home/?page_id=142).

On linux you can run a simple command to check this: 
```
glxinfo | grep OpenGL
```

Please ensure that you have the latest drivers for you graphics card.

# Build
Build system relies on [CMake](https://cmake.org/). So please download and install according to your OS.

## Windows

Download the latest version of [Visual Studio](https://visualstudio.microsoft.com/de/downloads/).

On Windows use the **CMake GUI** to configure the project. The project is currently **all inclusive of library dependencies**, and you wouldn't be required to install anything outside of what is provided but if there are problems in installing GLFW please see information below:

### Compiling GLFW on your own(only necessary if the provided GLFW sources in this project don't work for you, otherwise go directly to "Compiling the opengl_tutorial project")
Clone the GLFW github repository from source: https://github.com/glfw/glfw.git. Installation steps are described below.

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

#### If you compiled your own GLFW then: 

- Copy the following files from the recently compiled glfw or glfw3 using the file explorer: 

- From **glfw > build > src > Debug** on your file explorer, copy the `glfw3.lib` file and paste it in **OpenGL_tutorial > glfw > lib**. 

- From **glfw > include**, paste the `GLFW` folder into **OpenGL_tutorial > glfw > include**.

#### Otherwise:

Now, run the following commands in powershell:
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

Here, make sure you have the `glfw3.lib`, and `opengl32.lib` if you compiled GLFW on your own.
If not, add them (even though it's called "opengl32", it's still the 64bit version, this is just a naming convention).

Make sure, the C/C++ language standard is set to the latest, for example: Preview - Features from the **Latest C++ Working Draft (/std:c++latest)**; otherwise, you will not get access to std libraries such as `filesystem`.

Next, run build on the project and if everything was done correctly it should build without errors.

Launch the app using CTRL+F5 **after** selecting on your main solution node the Properties > single startup project > opengl_tutorial.

## Linux

Some dependencies are required depending on the used display server.

- Debian / Ubuntu
  - X11: `sudo apt install xorg-dev`
  - Wayland: `sudo apt install libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules`
- Fedore / Red Hat
  - X11: `sudo dnf install libXcursor-devel libXi-devel libXinerama-devel libXrandr-devel`
  - Wayland: `sudo dnf install wayland-devel libxkbcommon-devel wayland-protocols-devel extra-cmake-modules`

Source: [GLFW Documentation](https://www.glfw.org/docs/3.3/compile.html#compile_deps).

If all dependencies are installed, you can just run:

```
git clone https://github.tik.uni-stuttgart.de/ishasharma/OpenGL-tutorial.git
cd OpenGL_tutorial
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
In the end, running the `./opengl_tutorial` would run the application

# Compiling for Assignment01

A special cmake switch is needed to compile sources from Assignment 1 about a textured quad that had to be aspect ratio corrected
```
cmake -Dassignment01=true ..

```

**Credits**
for OGL4Core2 goes to previous work from *Moritz Heinemann*, the sources fot the heghtfield plugin are copied from his work. 
