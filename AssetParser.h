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
#elif APPLE
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
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
        Default = 0,
        /*!
         *  -h OR --help - Prints help information (Command itself works as of version 1.0.0)
         */
        Help = 1,
        /*!
         *  -v OR --version - Prints the current version  (Command itself works as of version 1.0.0)
         */
        Version = 2,
        /*!
         *
         * -f OR --file - Will create .h-files based on a list of files. No blacklist will be taken into consideration, as this is a file chosen by the user, but the file is valiated.
         * Call: -f <file> <destination folder> <output (no file-extension)> ...
         * Example: -f ./file.png ./folder/ myname
         */
        SingleFile = 3,
        /*!
         * -r OR --recursive -
         * Call: -r <source-folder> <destination-folder> <output (no file-extension)> ...
         * Example: -r ./ ./ myname
         */
        Recursive = 4,
        /*!
         * -d OR --directory -
         * Call: -d <source-folder> <destination-folder> <output (no file-extension)> ...
         * Example: -d ./ ./ myname
         */
        Directory = 5
    };

    public:
        AssetParser();
        AssetParser(int argc, char* argv[]);
        virtual ~AssetParser();

        void run();
        void runBasic(); //30.06.2018 - Same as run() for now, but will be used when logic for Mode is implemented

        bool initialize(int argc, char* argv[]);
        bool initialize(const std::string &loadPath, const std::string &outputPath, const std::string &filename = "files");
        bool initializeSingleFile(const std::string &loadPath, const std::string &outputPath = "", const std::string &filename = "");

        void addToFilenameBlacklist(const char *name);
        void addToFilenameBlacklist(const std::initializer_list<std::string> &list);

        void createDefaultBlackList();

        void parse();
        void parseSingleFile();

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

        void setMode(const std::string_view &action);

        std::string m_loadPath = "";
        std::string m_outputPath = "";
        std::string m_mapperOutputPath = "";
        std::string m_filename = "files"; //Name of the output file. Default:files
        std::vector<std::string> m_blacklistedFiles;
        std::vector<std::string> m_blacklistedDirectories; //New 29.06.2018 - NOT IMPLEMENTED - PLANNED FOR FUTURE RELEASE
        std::vector<std::string> m_files;
        AssetContainer m_container;
        Mode m_currentMode = Mode::Default;
};


#endif //F2SRC_ASSETPARSER_H
