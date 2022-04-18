# Download and install dependencies

We will be using Ubuntu 20.04 for our development and following is the list of dependencies we will need.

Technically it is possible to use another operating system like OSX or even Windows, but we are not focusing on that
at the moment. You are welcome to try those or you may use Oracle VirtualBox and install  Ubuntu 20.04 to make it easy
to follow. Download virtualbox from: https://www.virtualbox.org/wiki/Downloads and then download Ubuntu 20.04 desktop
image from https://ubuntu.com/download/desktop and create a virtual machine in the VirtualBox.

Once your OS is ready we start by creating a project directory.

We will be using a folder named ```grootlang``` for this bootcamp.

```shell
mkdir grootlang
```

## List of dependencies
* Git client
* A github account
* Java
* Antlr4
* C/C++ build tools
* CMake
* Antlr4 C++ runtime
* Catch2
* C++ IDE
* CLion plugin for antlr4

### Git client

On Ubuntu 20.04 install using:

```shell
sudo apt install git
```

### Github account

Please create a github account from ```https://github.com``` if you do  not have already.
Then go to https://github.com/marufabbasi/groot and add it to your favourite by clicking on the `Star` button to follow the tutorial repository. If you would like to submit pull requests you may also fork it.

### Java

On ubuntu you may install java using

```shell
sudo apt install openjdk-11-jdk
```

If you have problem with that please visit openjdk website for more instructions: https://openjdk.java.net/projects/jdk/11/

If you have a JDK/JRE from any later version that may also work.

### Antlr4

Antlr4 may be downloaded from https://www.antlr.org/download.html. But for this series of tutorials we will be using following repository that has required files already: https://github.com/marufabbasi/antlr.git

### C/C++ build tools
Install build tools using

```shell
sudo apt install build-essential
```

### Install CMake
We need cmake 3.5 or later version. Install using:

```shell
sudo apt install cmake
```

### Antlr4 C++ runtime
Antlr4 C++ runtime is part of antlr4 repository. To have a stable version I have forked it. Use following to clone and install it.

```shell
cd grootlang
git clone https://github.com/marufabbasi/antlr4
cd antlr4/runtime/Cpp
mkdir build
cd build
sudo apt install uuid-dev
cmake ..
make
sudo make install
```

### Catch2

We will use Catch2 as our testing framework. Clone and install Catch2:

```shell
cd grootlang
git clone https://github.com/marufabbasi/Catch2.git
cd Catch2
mkdir build
cd build
cmake ..
make
sudo make install
```

### C++ IDE 

For development, we will be using CLion IDE. You may get it from: https://www.jetbrains.com/clion/download/

### CLion plugin for antlr4

Install CLion ANTLR v4 from https://plugins.jetbrains.com/plugin/7358-antlr-v4

This plugin works for a lot of IDE from jetbrains including CLion.
