
# f2src
Files To Source (f2src) - A cross-platform program for generating source files with file data.

## Introduction
I created this program to be able to embed my files into my executable, but at the same time have a structure of the files in memory. This is done using namespaces to simulate folders. All folders are shown as lower-case, while files are shown as upper-case, so it will be easy to determine what's what. I've done some extra work to fix a few bugs before making this program open-source. The program should be fine, but if you encounter any weird bugs, please report them :)

## Examples on how to use the program (Linux)
```
NOTE: The same commands apply to Windows and Mac as well. Except the program itself 
might have a extension.
```
**Help and program description:** `./f2src -h`
**Get program version:** `./f2src -v`
**Generate source file for ALL the data (recursively) in you current folder:** `./f2src`
**Generate source file (using own parameters):** 
`./f2src <source-folder> <destination-folder> <output (no file-extension)>`
**Example:** `./f2src ./test_files ./ my_files`

> No parameters are required to generate files. When no parameters are typed, these default values are used:
source-folder: ./
destination-folder: ./
output: files

```
All files are generated as variables with a '_' prefix, to make sure the variable is generated safely. 
If you however have weird letters in the file name, chances are the variable names get weird as 
a result. Common characters that are not compatible with variable names or namespaces, like 
' '(space), '-' AND '.'
```

## Using the files from memory
> There are plenty of C++ libraries that are able to load files from memory, no matter what kind of files you are using inside your application. Pictures, music, xml, json, you name it!

#### Example how to use the data from the produced source files to load image from memory (using the SFML library):
```c++
#include "files_mapper.h"

...

sf::Texture texture;
sf::Sprite sprite;	
texture.loadFromMemory(files_mapper::test_files::sprites::players::_MARIO_PNG,
					   files_mapper::test_files::sprites::players::_MARIO_PNG_SIZE);
sprite.setTexture(texture);
sprite.setOrigin((float)texture.getSize().x / 2, (float)texture.getSize().y / 2);
```
>This example is using data generated from the files under the "test_files" folder.

## Compiling
Since the code is using CMake, you should be able to compile this easily if you have CMake installed! This program does however require a compiler that supports C++17, or at least the C++17 features of `filesystem` and `nested namespaces`(Which also is used for the generated namespace files). These features have however been available for quite some time (I guess about 2 years or so), and I was able to compile this program with GCC 6.3.0 back in the days, and a MSVC version that was older than that.

>I've tested compiling this program for Windows and Linux. While the code should be compatible with Mac OSX as well, I'm probably missing some stuff that will make you able to compile the program there, as I've never ever used nor owned a Mac before, and have no way to test them. I'd be please if someone with a Mac would try to do the changes needed to compile the program :) 

In general, using `cmake --help` will give a good idea how to compile with CMake, but I will give a brief explanation for those who are a bit less familiar with CMake.

### Windows
I've successfully been able to compile the program using MSVC (Via Visual Studio 2017) and MinGW 5 (GCC 7.1.0). I have however **not** been able to compile the program with MinGW 6 (GCC 8.1.0). After some research it seems like (as of today: 07.07.2018) MinGW 6 has some struggles/bugs with the `filesystem` feature of C++17. This will probably be fixed soon, but for now: Use MinGW 5 or MSVC.

In Visual Studio 2017, you can easily just open the folder with the CMakeLists.txt-file and it will be ready to compile.

You can also, however, generate a project file by using the command line or powershell by `cd`-ing into the folder containing the CMakeLists.txt file and do: `cmake -G "Visual Studio 15 2017"`

Alternatively, this simple command should generate whatever is the default of your system: `cmake ./CMakeLists.txt`

### Linux
I've developed this primarily using Linux and the CLion IDE. I've compiled the program for GCC 6.3.0, GCC 7.1.0 and GCC 8.1.0.

### Mac
More information coming soon!

## Testing
I've done some basic tests, but I might be missing something, as I've fixed quite some bugs and added a few features the last week. I have however used an earlier version of this program for embedding all my files into my C++ programs for quite some time, for all C++ programs I write, so it should work fine!

> I've used the Catch framework for basic Unit testing, but I wouldn't rely too much on those. It doesn't cover a lot of test cases, and is used primarly to test a few of the functions used in the program. I would like to say, tho, that Catch is an AMAZING Unit test framework for C++!

Please report any bugs you find!
