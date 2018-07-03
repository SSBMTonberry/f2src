#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

#include "../AssetParser.h"
#include "../AssetNamespace.h"
#include "../AssetGeneratorConfig.h"

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

int theAnswer() { return 6*9; }

TEST_CASE( "Life, the universe and everything", "[42][theAnswer]" ) {
    REQUIRE( theAnswer() == 54 );
}

TEST_CASE( "Test blacklist - expect a list of 10 (5 by single elements, 5 by initializer_list))", "[blacklist]" )
{
    AssetParser parser;
    parser.addToFilenameBlacklist("YES");
    parser.addToFilenameBlacklist("NO");
    parser.addToFilenameBlacklist("BROLO");
    parser.addToFilenameBlacklist("KROLO");
    parser.addToFilenameBlacklist("SNOLO");

    parser.addToFilenameBlacklist({"YO", "DUCK", "ASSES", "BLEED", "FEED"});

    REQUIRE(parser.getBlacklist().size() == 10);
}

TEST_CASE("Print all directories from test path", "[directory]" )
{
    std::string loadpath = "./../../../asset_test_files/";
    std::vector<std::string> directories;
    for (auto & p : std::experimental::filesystem::recursive_directory_iterator(loadpath))
    {
        bool isDirectory = std::experimental::filesystem::is_directory(p);
        if(isDirectory)
        {
            directories.push_back(p.path().string());
        }
    }

    REQUIRE(1 == 1);
}

TEST_CASE("Print all directories AND files from test path", "[directory]" )
{
    std::string loadpath = "./../../../asset_test_files/";
    std::vector<std::string> directories;
    for (auto & p : std::experimental::filesystem::recursive_directory_iterator(loadpath))
    {
        bool isDirectory = std::experimental::filesystem::is_directory(p);
        directories.push_back(p.path().string());
    }

    REQUIRE(1 == 1);
}

TEST_CASE("Check if namespaces are generated right", "[namespace]" )
{
    std::string loadpath = "./../../../asset_test_files/";
    std::vector<AssetNamespace*> assetNamespaces;
    for (auto & p : std::experimental::filesystem::recursive_directory_iterator(loadpath))
    {
        bool isDirectory = std::experimental::filesystem::is_directory(p);
        if(isDirectory)
        {
            //directories.push_back(p.path().string());
            AssetNamespace *asset = new AssetNamespace();
            asset->initialize(loadpath, p.path().string());
            assetNamespaces.push_back(asset);
        }
    }
    INFO("Size is " << assetNamespaces.size());
    REQUIRE(assetNamespaces.size() > 0);
}

TEST_CASE("Check AssetNamespaces for root path", "[namespace]" )
{
    std::string loadpath = "./../../../asset_test_files/";
    AssetNamespace ns;
    ns.initialize(loadpath, loadpath);
    std::string str = ns.getNamespace();
    REQUIRE(str.empty());
}

TEST_CASE("Test AssetParser", "[parser]" )
{
    //std::string loadpath = "./../../../asset_test_files/";
    std::string loadpath = "/home/robin/Projects/pixelmoundengine-clion/trunk/content/placeholders";
    ///home/robin/Projects/pixelmoundengine-clion/trunk/content/placeholders

    bool success = false;
    AssetParser parser;
    success = parser.initialize(loadpath, "./", "customname_files");
    if(success)
    {
        parser.run();
    }
    /*parser.createDefaultBlackList();
    parser.parse();
    bool success = parser.loadAssets();
    if(success)
    {
        parser.createAssetFile();
        parser.createMapperFile();
    }*/

    REQUIRE(success);
}

TEST_CASE("Test String split(several delimiters)", "[string][split]" )
{
    std::string loadpath = "/1\\2/3\\4";
    std::vector<std::string> split = AssetParser::SplitString(loadpath, '\\');
    REQUIRE(1 == 1);
}

TEST_CASE("Test String replace", "[string][replace]" )
{
    std::string str = "shiter";
    AssetParser::StringReplace(&str, "shit", "fuck");
    REQUIRE(str == "fucker");

    SECTION("Do another replace test")
    {
        std::string str2 = "kn/home/and/away/";
        AssetParser::StringReplace(&str2, "/home/and/away/", "ullerier");
        REQUIRE(str2 == "knullerier");
    }
}

TEST_CASE("Test String Contains", "[string][replace]" )
{
    std::string str = "/home/robin/Projects/pixelmoundengine-clion/trunk/content/placeholders/files.h";
    bool contains = AssetParser::StringContains(str, "files.h");
    REQUIRE(contains);

}

TEST_CASE("Test String ToUpper", "[string][to_upper]" )
{
    std::string str = "upper crap";
    str = AssetParser::StringToUpper(str);
    REQUIRE(str == "UPPER CRAP");

}