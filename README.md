


# f2src
Files To Source (f2src) - A cross-platform program for generating source files with file data.

## Introduction
I created this program to be able to embed my files into my executable, but at the same time have a structure of the files in memory. This is done using namespaces to simulate folders. All folders are shown as lower-case, while files are shown as upper-case, so it will be easy to determine what's what. I've done some extra work to fix a few bugs before making this program open-source. The program should be fine, but if you encounter any weird bugs, please report them :)

## Examples on how to use the program (Linux)

> NOTE: The same commands apply to Windows and Mac as well. Except the program itself 
might have an extension.

**Help and program description:** `./f2src -h` 

**Get program version:** `./f2src -v`

**Generate source file for ALL the data in your current folder:**  
`./f2src` **OR**  
`./f2src -d <source-folder> <destination-folder> <output (no file-extension)>`  
**Example:** `./f2src -d ./test_files ./ my_files`

**OR THE OLD WAY:** `./f2src <source-folder> <destination-folder> <output (no file-extension)>`  
**Example:** `./f2src ./test_files ./ my_files`

**Generate source file for ALL the data in your current folder and all sub-folders and files (recursive):**  
`./f2src -r` **OR**  
`/f2src -r <source-folder> <destination-folder> <output (no file-extension)>`  
  
**Generate source file for for a single file (accepts any file and ignores the usual blacklist):**  
`./f2src -f <file> <destination folder> <output (no file-extension)>`  
**Example:** `./f2src -f ./file.png ./folder/ myname`


> No parameters are required to generate files. When no parameters are typed, these default values are used:
source-folder: ./
destination-folder: ./
output: files

```
All files are generated as variables with a '_' prefix, to make sure the variable is generated 
safely. If you however have weird letters in the file name, chances are the variable names get 
weird as a result. However, common characters that are not compatible with variable names or namespaces, 
like ' '(space), '-' AND '.' are replaced with a '_' automatically when generating.
```

## The blacklist
To make sure `f2src` doesn't include unwanted files, the program has a blacklist. As of version 1.0 you will not be able to alter or ignore this blacklist, but I've planned to have this as a feature for a later release. The paths containing the following will be blacklisted, and not included in the produced source files:

 - Any path containing `.exe`
 - Any path containing `f2src`
 - Any path containing `<output>.h` or `<output>_mapper.h`. Or `files.h` and `files_mapper.h` if default name is used.
 - Any path containing `.bat`
 - Any path containing `.sh`

## What the program generates
The program generates two files: <output_name>.h AND <output_name>_mapper.h (files.h and files_mapper.h if not specified). `files.h` will contain the actual file data, while `files_mapper.h` pretty much is used to reference to the files in `files.h`. The purpose of files_mapper.h is to make it possible to access your files inside an IDE using the intellisense/autocomplete. I found that when `files.h` got too much data, the intellisense simply stopped working after a while. 

For the purpose of testing and demonstration, this project got a `test_files` folder, containing test files:
![Test files](https://github.com/SSBMTonberry/f2src/blob/master/readme_files/file_tree.png?raw=true)

### The `files_mapper.h` file produced:
```c++
#ifndef ASSET_GENERATOR_FILES_FILE_MAPPER
#define ASSET_GENERATOR_FILES_FILE_MAPPER
#include "files.h"

namespace files_mapper
{
	namespace sprites
	{
	}
	namespace sprites::players
	{
		static const unsigned char * _LUIGI_PNG = files::sprites::players::_LUIGI_PNG;
		static const size_t _LUIGI_PNG_SIZE = files::sprites::players::_LUIGI_PNG_SIZE;
		static const unsigned char * _MARIO_PNG = files::sprites::players::_MARIO_PNG;
		static const size_t _MARIO_PNG_SIZE = files::sprites::players::_MARIO_PNG_SIZE;
	}
	namespace sprites::enemies
	{
		static const unsigned char * _BOB_OMB_PNG = files::sprites::enemies::_BOB_OMB_PNG;
		static const size_t _BOB_OMB_PNG_SIZE = files::sprites::enemies::_BOB_OMB_PNG_SIZE;
		static const unsigned char * _GOOMBA_PNG = files::sprites::enemies::_GOOMBA_PNG;
		static const size_t _GOOMBA_PNG_SIZE = files::sprites::enemies::_GOOMBA_PNG_SIZE;
	}
	namespace sprites::stage_objects
	{
		static const unsigned char * _MYSTERYBOX_PNG = files::sprites::stage_objects::_MYSTERYBOX_PNG;
		static const size_t _MYSTERYBOX_PNG_SIZE = files::sprites::stage_objects::_MYSTERYBOX_PNG_SIZE;
		static const unsigned char * _BRICK_PNG = files::sprites::stage_objects::_BRICK_PNG;
		static const size_t _BRICK_PNG_SIZE = files::sprites::stage_objects::_BRICK_PNG_SIZE;
	}
	namespace fonts
	{
		static const unsigned char * _KARLA_REGULAR_TTF = files::fonts::_KARLA_REGULAR_TTF;
		static const size_t _KARLA_REGULAR_TTF_SIZE = files::fonts::_KARLA_REGULAR_TTF_SIZE;
		static const unsigned char * _PROGGYTINY_TTF = files::fonts::_PROGGYTINY_TTF;
		static const size_t _PROGGYTINY_TTF_SIZE = files::fonts::_PROGGYTINY_TTF_SIZE;
		static const unsigned char * _8_BIT_WONDER_TTF = files::fonts::_8_BIT_WONDER_TTF;
		static const size_t _8_BIT_WONDER_TTF_SIZE = files::fonts::_8_BIT_WONDER_TTF_SIZE;
	}
	namespace folder_with_space
	{
		static const unsigned char * _DUMMY_FILE = files::folder_with_space::_DUMMY_FILE;
		static const size_t _DUMMY_FILE_SIZE = files::folder_with_space::_DUMMY_FILE_SIZE;
	}
	namespace misc
	{
		static const unsigned char * _TEST_JSON = files::misc::_TEST_JSON;
		static const size_t _TEST_JSON_SIZE = files::misc::_TEST_JSON_SIZE;
		static const unsigned char * _FOLDER_WITH_SPACE_PNG = files::misc::_FOLDER_WITH_SPACE_PNG;
		static const size_t _FOLDER_WITH_SPACE_PNG_SIZE = files::misc::_FOLDER_WITH_SPACE_PNG_SIZE;
	}
}
#endif //ASSET_GENERATOR_FILES_FILE_MAPPER
```

### A small part of the `files.h` file produced:
```c++
#ifndef ASSET_GENERATOR_FILES
#define ASSET_GENERATOR_FILES
namespace files
{
    ...
	
	namespace sprites::players
	{
	static const unsigned char _LUIGI_PNG[] = {
		0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,0000,0000,0000,0x0d,
		0x49,0x48,0x44,0x52,0000,0000,0000,0x10,0000,0000,0000,0x10,
		0x08,0x06,0000,0000,0000,0x1f,0xf3,0xff,0x61,0000,0000,0000,
		0xf1,0x49,0x44,0x41,0x54,0x38,0x8d,0x8d,0x52,0xbb,0x11,0x82,
		0x40,0x10,0xdd,0x65,0x4c,0x6c,0x04,0xb4,0x04,0x52,0x52,0xa0,
		0000,0xc6,0x06,0x9c,0x61,0x24,0x16,0x0b,0xd0,0x1c,0x87,0x19,
		0x1b,0xc0,0x2b,0000,0x48,0x4d,0x2d,0x41,0xa1,0x99,0x35,0x90,
		0xcf,0x7d,0xf6,0x94,0x4d,0xd8,0xbb,0x7d,0xef,0xed,0x1b,0xde,
		0x21,0x30,0x85,0xc2,0x27,0xfd,0x8e,0x92,0x27,0xb2,0xd8,0x25,
		0xe4,0x5f,0x62,0x2b,0x7d,0x78,0xbc,0xaf,0xa7,0xfe,0xbc,0xdf,
		0x7e,0x45,0xc3,0x12,0xa8,0x4d,0x01,0xc3,0xd2,0x58,0xe8,0xc8,
		0x87,0x3c,0x0e,0x68,0x24,0x8d,0x5f,0x65,0x73,0x9b,0x12,0xb5,
		0xa9,0xe2,0xd0,0x31,0x50,0x43,0x9d,0x6e,0x2f,0x99,0x08,0x18,
		0x96,0x8a,0xd0,0xd8,0x2b,0x96,0xf2,0x38,0x20,0x6e,0xbb,0x4c,
		0xd6,0x79,0xec,0x9f,0xd5,0x6d,0x6a,0x62,0x0a,0xc7,0x9a,0x82,
		0x5b,0x25,0xd0,0xef,0xc4,0x2c,0x6a,0x89,0x51,0x49,0xc1,0x16,
		0xa1,0x5b,0x25,0xd0,0x0b,0x98,0x66,0x6c,0x8c,0x1c,0xd9,0xad,
		0x12,0x4e,0x0f,0x50,0xf8,0x64,0x38,0xa2,0xa1,0x50,0xf8,0xe4,
		0x45,0x05,0x11,0x01,0x79,0x51,0xa1,0xf4,0x28,0xfc,0x11,0x66,
		0xa6,0x20,0x5f,0x6e,0xe2,0x2b,0xbb,0xf9,0x5d,0x1f,0x66,0x17,
		0x88,0x08,0xc0,0xbc,0x03,0x1b,0xd9,0x36,0x9b,0x04,0x70,0x28,
		0x79,0xd8,0x35,0x19,0x76,0x4d,0xa6,0xc6,0xa6,0xe1,0xd8,0x87,
		0x04,0000,0x70,0xa9,0x1f,0x8b,0x66,0x0e,0x07,0xf8,0x57,0x32,
		0xf6,0x03,0x72,0xf7,0x79,0x3e,0x7f,0xfe,0x2e,0xa5,0000,0000,
		0000,0000,0x49,0x45,0x4e,0x44,0xae,0x42,0x60,0x82,0x00
	};

	static const size_t _LUIGI_PNG_SIZE = sizeof(_LUIGI_PNG);

	static const unsigned char _MARIO_PNG[] = {
		0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,0000,0000,0000,0x0d,
		0x49,0x48,0x44,0x52,0000,0000,0000,0x10,0000,0000,0000,0x10,
		0x08,0x06,0000,0000,0000,0x1f,0xf3,0xff,0x61,0000,0000,0000,
		0xe0,0x49,0x44,0x41,0x54,0x38,0x8d,0x85,0x53,0x21,0x12,0xc3,
		0x20,0x10,0xdc,0x64,0x2a,0xa8,0xab,0xcc,0x57,0x5a,0x19,0x5b,
		0x19,0x99,0x27,0x20,0xa9,0x8c,0xac,0x4c,0x64,0x9e,0x50,0x19,
		0x19,0x1b,0x49,0xbf,0x52,0x59,0x57,0x1c,0x35,0x85,0xb9,0x83,
		0x0b,0x5d,0x93,0xc0,0xdd,0x2e,0xcb,0x02,0x15,0x04,0x7c,0xce,
		0x27,0x9f,0xce,0x1d,0x9f,0xef,0x4a,0xea,0xcd,0x26,0x25,0x72,
		0x49,0xec,0x90,0x16,0xe7,0x8b,0x8a,0xff,0xa6,0xed,0000,0000,
		0xd3,0xb6,0xc0,0xb4,0x1d,0xaa,0xeb,0x9c,0x2d,0x58,0xd3,0xc1,
		0x68,0x1a,0x1f,0x48,0xe1,0x4b,0xe1,0x57,0xed,0xfd,0xaa,0x99,
		0xc3,0x3a,0xeb,0xfa,0x61,0xda,0x16,0xe6,0x84,0x8e,0xa9,0x08,
		0xb3,0x34,0x9a,0xc6,0x4b,0xab,0x53,0x32,0000,0xdc,0xa6,0x57,
		0xe4,0x89,0xc9,0xa6,0x36,0x29,0xd2,0x1c,0x32,0x81,0xe0,0x42,
		0x5b,0xc7,0x02,0xa5,0xab,0x52,0xb0,0x53,0x08,0xe4,0x14,0xda,
		0x3a,0x80,0xd4,0xc4,0x2d,0xa4,0x64,0x6d,0x1d,0x13,0xa1,0x6e,
		0xa8,0x48,0x3c,0x05,0xd3,0x76,0x31,0x3c,0x6d,0x1d,0xd4,0xd0,
		0xc7,0x66,0x35,0xf4,0x51,0x90,0xf6,0x31,0x07,0x34,0x38,0x77,
		0x7f,0x48,0x3b,0x61,0xa2,0x21,0xcc,0xec,0x1e,0xec,0x91,0xf7,
		0x6a,0xc5,0xb7,0x10,0xee,0xbc,0x34,0x27,0x0a,0x8c,0x3b,0x49,
		0x97,0x6a,0xb5,0xd4,0xf0,0x0f,0xb4,0xf7,0x0b,0xf8,0x6e,0x6a,
		0xa6,0xe0,0x54,0xad,0x69,0000,0000,0000,0000,0x49,0x45,0x4e,
		0x44,0xae,0x42,0x60,0x82,0x00
	};

	static const size_t _MARIO_PNG_SIZE = sizeof(_MARIO_PNG);

	}
	
	...
}
#endif //ASSET_GENERATOR_FILES



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
I've developed this primarily using Linux and the CLion IDE. I've compiled the program for GCC 6.3.0, GCC 7.1.0, GCC 8.1.0 and GCC 9.1.0.

You can compile it easily by using an IDE like CLion, or by Following these simple steps:

 1. Open terminal and `cd` into the folder with the CMakeLists.txt file.
 2. Generate makefile: `cmake ./CMakeLists.txt`
 3. Then compile by calling: `make`

### Mac
Since this program utilizes `std::filesystem`, which is a C++17 feature that is yet to be supported by `Apple Clang` (as of 25.08.2019). You will have to download the latest version of `llvm` from `Homebrew` to be able to compile this program, then you will have to set this as your current compiler. An offical support for `std::filesystem` is said to be done during the release of Mac OSX 10.15 and XCode 11. As for `llvm` through `Homebrew`, `std::filesystem` has been supported for quite some time.

## Testing
I've done some basic tests, but I might be missing something, as I've fixed quite some bugs and added a few features the last week. I have however used an earlier version of this program for embedding all my files into my C++ programs for quite some time, for all C++ programs I write, so it should work fine!

> I've used the Catch framework for basic Unit testing, but I wouldn't rely too much on those. It doesn't cover a lot of test cases, and is used primarly to test a few of the functions used in the program. I would like to say, tho, that Catch is an AMAZING Unit test framework for C++!

## External libraries used
I've used the [{fmt}](https://github.com/fmtlib/fmt) library to easily format the strings used in the program. The sources for the library itself (v5.0.0) is included and built into the program, so no library files are needed!

Also, I've used the awesome single header test framework [Catch2](https://github.com/catchorg/Catch2/) for my rather simple tests.

## Possible plans for features in the future

 - Make functionality to be able to generate smaller files (base85 encoding or similar?).
 - Make it possible to manipulate the blacklist.
 - Make it possible to pick several single files.
- Make it possible to pick several folders from different places.

## Please report any bugs you find!
I'd like to get notified about bugs you find, to make the program better :)
