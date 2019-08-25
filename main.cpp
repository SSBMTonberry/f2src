//
// Created by robin on 01.05.17.
//


#include "AssetGeneratorConfig.h"
#include <string>
#include "fmt/format.h"
#include "fmt/printf.h"
const std::string VERSION = fmt::format("{0}.{1}.{2}", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

//#define _CRT_SECURE_NO_DEPRECATE

#include "AssetParser.h"


int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        std::string action {argv[1]};
        if(action.length() > 0 && action[0] == '-')
        {
            if(action == "-v" || action == "--version")
            {
                std::cout << "\nCurrent version: " << VERSION << "\n";
                return EXIT_SUCCESS;
            }
            else if(action == "-h" || action == "--help")
            {
                std::cout << "\nThis program generates C++ source files with binary data for all files and sub-folders\n" <<
                             "of a given source folder. This makes it possible to compile the file data into a program\n" <<
                             "and access the files by memory.\n\n"
                             "This program requires no arguments to work, but by doing so everything is done\n" <<
                             "relative to the current folder you're in while running, which can result in a VERY large file if placed wrong.\n" <<
                             "Two files will be generated: <output>.h and <output>_mapper.h. The latter is used to make\n" <<
                             "it intellisense-/autocomplete-friendly, by referencing the file data by name in a much smaller file.\n" <<
                             "On a general basis the mapper-file should be included in the program you want to use the files. \n\n"
                             "You can control this program's behavior by using up to three optional arguments:\n" <<
                             "Call: <source-folder> <destination-folder> <output (no file-extension)>\n" <<
                             "Example: ./test/ ./output/ files\n" <<
                             "Defaults:\n" <<
                             "source-folder: ./\n" <<
                             "destination-folder: ./\n" <<
                             "output: files\n\n" <<
                             "-v OR --version   - Get the current program version.\n" <<
                             "-h OR --help      - Get help and program description.\n" <<
                             "-f OR --file      - Create source for a single file.\n" <<
                             "-r OR --recursive - Run recursively through all files and folders relative to source-folder.\n" <<
                             "-d OR --directory - Run through all files in source folder.\n" <<
                             "                    This is the default behavior when no parameters are used.\n";
                return EXIT_SUCCESS;
            }
            else if(action == "-f" || action == "--file")
            {
                std::cout << "\n Running in single file mode... \n";
            }
            else if(action == "-r" || action == "--recursive")
            {
                std::cout << "\n Running in recursive mode... \n";
            }
            else if(action == "-d" || action == "--directory")
            {
                std::cout << "\n Running in directory mode... \n";
            }
            else
            {
                std::cout << "\n" << action << " is not a valid action! Use the -h or --help argument for help :)\n";
                return EXIT_FAILURE;
            }
        }
    }
    AssetParser parser;
    std::cout << "Initializing..." << "\n";
    if(parser.initialize(argc, argv))
        parser.run();
    else
    {
        std::cout << "\nInitialization FAILED! Exiting program...\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
