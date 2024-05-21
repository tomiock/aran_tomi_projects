## Build Commands
The dataset is defined at compile time to import the correct header. If no header is defined or no option is provided the program will not compile.
It is well understood that compile time errors are preferable to runtime errors.
```shell
cmake -S . -B build -DUSE_SMALL_DATASET=ON
cmake --build build
```
The executable is created in the current directory.

A problem that can happen is that because the macros set to ON are stored in the cache (inside the `build` directory) then if we engage another macro, both of them are turn on.
To avoid this, we can clean the cache with the following command:
```shell
rm -rf build
```
Just delete the directory. 
