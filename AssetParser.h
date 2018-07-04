//
// Created by robin on 28.06.17.
//

#ifndef F2SRC_ASSETPARSER_H
#define F2SRC_ASSETPARSER_H

#include "AssetGeneratorConfig.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstdarg>
#include <cctype>
#include <initializer_list>
#include <sstream>
#include <fstream>

#if MSVC
    #include <filesystem>
    namespace fs = std::filesystem;
#elif MINGW
    #if __MINGW64_VERSION_MAJOR > 5
        #include <filesystem>
        namespace fs = std::filesystem;
    #else
        #include <experimental/filesystem>
        namespace fs = std::experimental::filesystem;
    #endif
#else
    #if __GNUC__ < 8 //GCC major version less than 8
        #include <experimental/filesystem>
        namespace fs = std::experimental::filesystem;
    #else
        #include <filesystem>
        namespace fs = std::filesystem;
    #endif
#endif

//#include "fmt/string.h"
#include "fmt/printf.h"
#include "AssetContainer.h"
#include "MappingItem.h"

class AssetParser
{
    /*!
     * 30.06.2018 - NOT IMPLEMENTED - PLANNED FOR A FUTURE RELEASE!
     */
    enum class Mode
    {
        /*!
        * When no parameters are presented
        */
        None = 0,
        /*!
         *  -h OR --help - Prints help information (Command itself works as of version 1.0.0)
         */
        Help = 1,
        /*!
         *  -v OR --version - Prints the current version  (Command itself works as of version 1.0.0)
         */
        Version = 2,
        /*!
         * -bf OR --blacklistfile - All parameters followed by this will be blacklisted, if they are files.
         *                          Must be called before any files are listed
         * Call: -bf <file1> <file2> <file3> ...
         * Example: -bf ./test.txt ./folder/Readme.md ./program
         */
        BlacklistFile = 3,
        /*!
         * -bd OR --blacklistdir - All parameters followed by this will be blacklisted, if they are folders.
         * Call: -bf <directory1> <directory2> <directory3> ...
         * Example: -bd ./folder ./anotherfolder ./folder1/folder2
         */
        BlackListDirectory = 4,
        /*!
         * -f OR --file - Will create .h-files based on a list of files. No blacklist will be taken into consideration, as this is a file chosen by the user, but the file is valiated.
         * Call: -f <file1> <file2> <file3> ...
         * Example: -f ./file.png ./folder/anotherfile.png ./music.ogg
         */
        SingleFiles = 5,
        /*!
         * -d OR --dir - Will create .h-files based on a list of directories(including their sub-directories). Blacklisted files are ignored, but blacklisted directories are not.
         * Call: -d <directory1> <directory2> <directory3> ...
         * Example: -d ./sprites ./music "./shaders/shaders with spaces"
         */
        Directories = 6,
        /*!
         * -a OR --all - All files and subdirectories in the folder where the executable lies. Use for cases where you quickly want to generate a
         *               lot of files.
         * Call: -a
         */
        All = 7,
        /*!
         * -o OR --output - Name of the files that are going to get generated and the output directory. If this is not
         *                  specified, the default name "files" will be used, and output will be the same directory
         *                  as the executable. Files that will be produced are "files.h" and "files_mapper.h"
         * Call: -o <name> <output_directory>
         * Example: -o my_files <output_directory>
         */
        Output = 8
    };

    public:
        AssetParser();
        AssetParser(int argc, char* argv[]);
        virtual ~AssetParser();

        void run();
        void runBasic(); //30.06.2018 - Same as run() for now, but will be used when logic for Mode is implemented

        bool initialize(int argc, char* argv[]);
        bool initialize(const std::string &loadPath, const std::string &outputPath, const std::string &filename = "files");

        void addToFilenameBlacklist(const char *name);
        void addToFilenameBlacklist(const std::initializer_list<std::string> &list);

        void createDefaultBlackList();

        void parse();
        bool loadAssets();
        void createAssetFile();
        void createMapperFile();
        std::string createByteDataStringFromFile(const std::string &loadingPath, const std::string &filePath);
        MappingItem createMappingItemFromFile(const std::string &loadingPath, const std::string &filePath,
                                                               const std::string &fileNamespace, AssetNamespace *nsRef);

        bool isBlacklisted(const std::string &text);

        void setLoadPath(const std::string &m_loadPath);
        void setOutputPath(const std::string &m_outputPath);

        const std::string &getLoadPath() const;
        const std::string &getOutputPath() const;
        const std::vector<std::string> getBlacklist() const;
        const void printBlacklist() const;

        static void StringReplace(std::string *str, const std::string &toReplace, const std::string &replaceWith);
        static bool StringContains(const std::string &str, const std::string &text);
        static std::vector<std::string> SplitString(const std::string &s, char delim);
        static std::string StringToUpper(std::string s);
        static bool IsDirectory(const fs::directory_entry &entry);
        static std::string GetPath(const fs::directory_entry &entry);

    protected:
        template <typename Out>
        static void split(const std::string &s, char delim, Out result);

        std::string m_loadPath = "";
        std::string m_outputPath = "";
        std::string m_mapperOutputPath = "";
        std::string m_filename = "files"; //Name of the output file. Default:files
        std::vector<std::string> m_blacklistedFiles;
        std::vector<std::string> m_blacklistedDirectories; //New 29.06.2018 - NOT IMPLEMENTED - PLANNED FOR FUTURE RELEASE
        std::vector<std::string> m_files;
        AssetContainer m_container;
        Mode m_currentMode = Mode::None;
};


#endif //F2SRC_ASSETPARSER_H
