# DA2_T02G06
Repositório para o segundo projeto de DA - grupo T02G06

## Installing Dependencies

This project uses [Google's OR-Tools](https://developers.google.com/optimization), and therefore you need to install that tool to run it. You should install it under "ortools" in this project's root folder. Make sure that under "ortools" there are folders named "lib" and "include". You can find tutorials on how to install [here](https://developers.google.com/optimization/install/cpp). Installing OR-Tools from binaries is generally quicker and less error prone, you just need to download the compressed files, extract them, rename the folder where "lib" and "include" are, and place it under this folder's root folder. Don't forget to follow the tutorial's "Prerequisites" section.

Alternatively to installing OR-Tools under "ortools" in this project's root folder, you can edit this [line](CMakeLists.txt#L7) so that it looks like this (don't forget to replace with the actual path of the folder where you have the "lib" and "include" folders of OR-Tools):

```cmake
set(ORTOOLS_ROOT, <path to your OR-Tools installation>)
```

## Compiling and Running

Before compiling, you should install all the dependencies. Read the section on [installing dependencies](#installing-dependencies).

After installing dependencies, on most Unix-like environments (Like Linux, MacOS, WSL in Windows, ...), you can open a terminal and use the following command in this project's root folder to (re)compile and run the code:

```bash
./run.sh
```

Alternatively, manually use the [CMakeLists](CMakeLists.txt) file to generate the Makefile and then compile and run the executable.

