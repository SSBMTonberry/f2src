//
// Created by robin on 28.06.17.
//


#include "AssetParser.h"

AssetParser::AssetParser() = default;


AssetParser::AssetParser(int argc, char* argv[])
{
    initialize(argc, argv);
}

AssetParser::~AssetParser() = default;

bool AssetParser::initialize(int argc, char **argv)
{
    if(argc > 1)
    {
        std::string action{argv[1]};
        setMode(action);
    }
    else
        m_currentMode = Mode::Default;

    if(m_currentMode == Mode::SingleFile)//(action == "-f" || action == "--file")
    {
        m_loadPath = (argc > 2) ? argv[2] : "";
        m_outputPath = (argc > 3) ? argv[3] : ""; //"./files.h";
        m_filename = (argc > 4) ? argv[4] : "";
        return initializeSingleFile(m_loadPath, m_outputPath, m_filename);
    }
    else if(m_currentMode == Mode::Recursive || m_currentMode == Mode::Directory) //(action == "-r" || action == "--recursive")
    {
        m_loadPath = (argc > 2) ? argv[2] : "./";
        m_outputPath = (argc > 3) ? argv[3] : "./"; //"./files.h";
        m_filename = (argc > 4) ? argv[4] : "files";
    }
    else
    {
        m_loadPath = (argc > 1) ? argv[1] : "./";
        m_outputPath = (argc > 2) ? argv[2] : "./"; //"./files.h";
        m_filename = (argc > 3) ? argv[3] : "files";
    }
    return initialize(m_loadPath, m_outputPath, m_filename);
}

bool AssetParser::initializeSingleFile(const std::string &loadPath, const std::string &outputPath, const std::string &filename)
{
    m_loadPath = loadPath;
    m_outputPath = outputPath;
    m_filename = filename;
    fs::path file = fs::path(m_loadPath);
    if(fs::is_regular_file(m_loadPath))
    {
        if (m_outputPath.empty())
            m_outputPath = file.parent_path().u8string();
        if (m_filename.empty())
            m_filename = file.stem().u8string();
    }

    if(!fs::is_regular_file(m_loadPath))
    {
        std::cout << "INVALID source file: " << m_loadPath << std::endl;
        return false;
    }
    else if(!fs::is_directory(m_outputPath))
    {
        std::cout << "INVALID destination directory: " << m_outputPath << std::endl;
        return false;
    }
    else if(StringContains(m_filename, " "))
    {
        std::cout << "INVALID output name! Outputs cannot contain spaces! " << std::endl;
        return false;
    }

    //Safety: Appending '/' to the end of path if not mentioned
    //if(m_loadPath[m_loadPath.length() - 1] != '\\' && m_loadPath[m_loadPath.length() - 1] != '/')
    //    m_loadPath.append("/");
    if(m_outputPath[m_loadPath.length() - 1] != '\\' && m_outputPath[m_loadPath.length() - 1] != '/')
        m_outputPath.append("/");

    m_mapperOutputPath = fmt::format("{0}{1}_mapper.h", m_outputPath, m_filename);//"./files_mapper.h";
    m_outputPath = fmt::format("{0}{1}.h", m_outputPath, m_filename);

    m_container.initialize(m_filename, m_loadPath); //("files", m_loadPath);

    return true;
}

bool AssetParser::initialize(const std::string &loadPath, const std::string &outputPath,
                             const std::string &filename)
{
    m_loadPath = loadPath;
    m_outputPath = outputPath;
    m_filename = filename;

    if(!fs::is_directory(m_loadPath))
    {
        std::cout << "INVALID source directory: " << m_loadPath << std::endl;
        return false;
    }
    else if(!fs::is_directory(m_outputPath))
    {
        std::cout << "INVALID destination directory: " << m_outputPath << std::endl;
        return false;
    }
    else if(StringContains(m_filename, " "))
    {
        std::cout << "INVALID output name! Outputs cannot contain spaces! " << std::endl;
        return false;
    }

    //Safety: Appending '/' to the end of path if not mentioned
    if(m_loadPath[m_loadPath.length() - 1] != '\\' && m_loadPath[m_loadPath.length() - 1] != '/')
        m_loadPath.append("/");
    if(m_outputPath[m_loadPath.length() - 1] != '\\' && m_outputPath[m_loadPath.length() - 1] != '/')
        m_outputPath.append("/");

    m_mapperOutputPath = fmt::format("{0}{1}_mapper.h", m_outputPath, m_filename);//"./files_mapper.h";
    m_outputPath = fmt::format("{0}{1}.h", m_outputPath, m_filename);

    m_container.initialize(m_filename, m_loadPath); //("files", m_loadPath);

    return true;
}

const std::string &AssetParser::getLoadPath() const
{
    return m_loadPath;
}

void AssetParser::setLoadPath(const std::string &m_loadPath)
{
    AssetParser::m_loadPath = m_loadPath;
}

const std::string &AssetParser::getOutputPath() const
{
    return m_outputPath;
}

void AssetParser::setOutputPath(const std::string &m_outputPath)
{
    AssetParser::m_outputPath = m_outputPath;
}

void AssetParser::addToFilenameBlacklist(const char *name)
{
    m_blacklistedFiles.emplace_back(name); //(fmt::to_string(name));
}

void AssetParser::addToFilenameBlacklist(const std::initializer_list<std::string> &list)
{
    for(std::string const & str : list)
    {
        m_blacklistedFiles.push_back(str);
    }
}

const std::vector<std::string> AssetParser::getBlacklist() const
{
    return m_blacklistedFiles;
}

void AssetParser::parse()
{

    m_container.clear();
    m_files.clear();

    if(m_currentMode == Mode::Directory || m_currentMode == Mode::Default)
    {
        for (auto &p : fs::directory_iterator(m_loadPath))
        {
            if (IsDirectory(p))
            {
                std::string path = GetPath(p);

                AssetNamespace asset;
                asset.initialize(m_loadPath, path);
                asset.setTabs(1);
                m_container.addAsset(asset);
            }
            else
            {
                std::string path = GetPath(p);
                if (!isBlacklisted(path))
                {
                    std::cout << "Adding file to container: " << path << "\n";
                    m_files.push_back(path);
                }
                else
                {
                    std::cout << "Path contains blacklisted file (file ignored): " << path << "\n";
                }
            }
        }
    }
    else
    {
        for (auto &p : fs::recursive_directory_iterator(m_loadPath))
        {
            if (IsDirectory(p))
            {
                std::string path = GetPath(p);

                AssetNamespace asset;
                asset.initialize(m_loadPath, path);
                asset.setTabs(1);
                m_container.addAsset(asset);
            }
            else
            {
                std::string path = GetPath(p);
                if (!isBlacklisted(path))
                {
                    std::cout << "Adding file to container: " << path << "\n";
                    m_files.push_back(path);
                }
                else
                {
                    std::cout << "Path contains blacklisted file (file ignored): " << path << "\n";
                }
            }
        }
    }
}

/*!
 * Can parse a single file
 */
void AssetParser::parseSingleFile()
{
    m_container.clear();
    m_files.clear();

    fs::path p = fs::path(m_loadPath);

    if(fs::is_regular_file(p))
    {
        if(!isBlacklisted(p.u8string()))
        {
            std::cout << "Adding file to container: " << p.u8string() << "\n";
            m_files.push_back(p.u8string());
        }
        else
        {
            std::cout << "Path contains blacklisted file (file ignored): " << p.u8string() << "\n";
        }
    }
}

bool AssetParser::loadAssets()
{
    try
    {
        for (const std::string &path : m_files)
        {
            AssetNamespace *ns = m_container.getRelatedNamespace(path);

            if (ns != nullptr)
            {
                ns->addData(createByteDataStringFromFile(ns->getPath(), path));
                ns->addFileMapperData(createMappingItemFromFile(ns->getPath(), path, ns->getNamespace(), ns));
            }
        }
    }
    catch(const std::exception &e)
    {
        return false;
    }

    return true;
}

void AssetParser::createAssetFile()
{
    //std::ofstream fout(m_outputPath, std::ofstream::out | std::ofstream::app);
    std::ofstream fout(m_outputPath);
    fout << fmt::format("#ifndef F2SRC_ASSET_{0}\n", StringToUpper(m_filename));
    fout << fmt::format("#define F2SRC_ASSET_{0}\n", StringToUpper(m_filename));

    fout << "namespace " << m_container.getNamespace() << "\n";
    fout << "{\n";
    for(std::string const & data : m_container.getRootNamespace()->getData())
    {
        fout << "\t" << data.c_str();
    }
    for(AssetNamespace &asset : m_container.getAssets())
    {
        asset.writeData(fout);
    }
    fout << "}\n";
    fout << fmt::format("#endif //F2SRC_ASSET_{0}\n", StringToUpper(m_filename));
    fout.close();
}

bool AssetParser::isBlacklisted(const std::string &text)
{
    for(const std::string &item : m_blacklistedFiles)
    {
        if(StringContains(text, item))
            return true;
    }

    return false;
}

void AssetParser::createDefaultBlackList()
{
    addToFilenameBlacklist({".exe", "f2src", fmt::format("{0}.h", m_filename)/*"files.h"*/, fmt::format("{0}_mapper.h", m_filename)/*"files_mapper.h"*/, ".bat", ".sh"});
}

bool AssetParser::StringContains(const std::string &str, const std::string &text)
{
    size_t find = str.find(text);
    return (find != std::string::npos) ? true : false;
}

std::string AssetParser::createByteDataStringFromFile(const std::string &loadingPath, const std::string &filePath)
{
    FILE *fp;
    int j, ch;

    //std::string *text = new std::string();

    std::string text = "";

    if ((fp = fopen(filePath.c_str(), "rb")) == NULL) {
        exit(EXIT_FAILURE);
    }
    else
    {
        fs::path file = fs::path(filePath);
        std::string variable = file.filename().u8string(); //filePath;
        //AssetParser::StringReplace(&variable, loadingPath, "");

        //variable = variable.substr(loadingPath.length()); //Ignore the __ in the start or the loading path part
        std::replace(variable.begin(), variable.end(), '\\', '_');
        std::replace(variable.begin(), variable.end(), '/', '_');
        std::replace(variable.begin(), variable.end(), '.', '_');
        std::replace(variable.begin(), variable.end(), '-', '_');
        std::replace(variable.begin(), variable.end(), ' ', '_');
        std::transform(variable.begin(), variable.end(), variable.begin(), ::toupper);

        if (variable[0] == '_')
            variable = variable.substr(1);

        text = fmt::sprintf("static const unsigned char _%s[] = {", variable.c_str());

        for (j = 0; (ch = fgetc(fp)) != EOF; j++)
        {
            if ((j % 12) == 0)
            {
                text += "\n\t\t";
            }

            text += fmt::sprintf("%#04x,", ch);
        }
        text += fmt::sprintf("%s", "0x00\n\t};\n\n");
        text += fmt::sprintf("\tstatic const size_t _%s_SIZE = sizeof(_%s);\n\n", variable.c_str(), variable.c_str());
        fclose(fp);
    }

    return text;
}

MappingItem AssetParser::createMappingItemFromFile(const std::string &loadingPath, const std::string &filePath,
                                                                    const std::string &fileNamespace, AssetNamespace *nsRef)
{
    MappingItem item;

    item.setValueNamespace(fileNamespace);
    item.setRootNamespace(m_container.getNamespace());

    //std::string variable = filePath;
    //variable = variable.substr(loadingPath.length()); //Ignore the __ in the start or the loading path part

    fs::path file = fs::path(filePath);
    std::string variable = file.filename().u8string();

    std::replace(variable.begin(), variable.end(), '\\', '_');
    std::replace(variable.begin(), variable.end(), '/', '_');
    std::replace(variable.begin(), variable.end(), '.', '_');
    std::replace(variable.begin(), variable.end(), '-', '_');
    std::replace(variable.begin(), variable.end(), ' ', '_');
    std::transform(variable.begin(), variable.end(), variable.begin(), ::toupper);

    if (variable[0] == '_')
        variable = variable.substr(1);

    item.setVariableName(fmt::sprintf("_%s", variable.c_str()));
    item.setValueName(fmt::sprintf("_%s", variable.c_str()));

    item.setSizeVariableName(fmt::sprintf("_%s_SIZE", variable.c_str(), variable.c_str()));
    item.setSizeValueName(fmt::sprintf("_%s_SIZE", variable.c_str(), variable.c_str()));


    return std::move(item);
}

bool AssetParser::IsDirectory(const fs::directory_entry &entry)
{
    return fs::is_directory(entry);
}

std::string AssetParser::GetPath(const fs::directory_entry &entry)
{
    return entry.path().u8string();
}

std::vector<std::string> AssetParser::SplitString(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

template<typename Out>
void AssetParser::split(const std::string &s, char delim, Out result)
{
    std::stringstream ss;
    ss.str(s);
    std::string item;

    while (std::getline(ss, item, delim))
    {
        *(result++) = item;
    }
}

void AssetParser::StringReplace(std::string *str, const std::string &toReplace, const std::string &replaceWith)
{
    //*str = std::regex_replace(*str, std::regex("\\" + toReplace), "\\" + replaceWith);
    *str = std::regex_replace(*str, std::regex(toReplace), replaceWith);
}

const void AssetParser::printBlacklist() const
{
    int i = 0;
    std::cout << "// B L A C K L I S T" << std::endl;
    std::cout << "//-----------------------------------------------------------" << std::endl;
    for(const std::string &item : m_blacklistedFiles)
    {
        std::cout << i << ": " << item << std::endl;
        i++;
    }
    std::cout << "//-----------------------------------------------------------"<< std::endl;
}

void AssetParser::createMapperFile()
{
    //std::ofstream fout(m_outputPath, std::ofstream::out | std::ofstream::app);
    std::ofstream fout(m_mapperOutputPath);
    fout << fmt::format("#ifndef F2SRC_ASSET_{0}_FILE_MAPPER\n", StringToUpper(m_filename));
    fout << fmt::format("#define F2SRC_ASSET_{0}_FILE_MAPPER\n", StringToUpper(m_filename));
    //fout << "#include \"files.h\"\n\n";
    fout << fmt::format("#include \"{0}.h\"\n\n", m_filename);
    fout << "namespace " << m_container.getNamespace() << "_mapper" << "\n";
    fout << "{\n";

    for(auto & data : m_container.getRootNamespace()->getFileMapperData()) //TODO: Same logic with filemapper data
    {
        fout << data.generateVariableData().c_str() << "\n";
        fout << data.generateSizeData().c_str() << "\n";
    }

    for(AssetNamespace &asset : m_container.getAssets())
    {
        asset.writeFilemapperData(fout);
    }
    fout << "}\n";
    fout << fmt::format("#endif //F2SRC_ASSET_{0}_FILE_MAPPER\n", StringToUpper(m_filename));
    fout.close();
}

void AssetParser::run()
{
    //TODO: Make this one run based on parameters
    if(m_currentMode != Mode::SingleFile)
    {
        std::cout << "Generating default blacklist for files..." << "\n";
        createDefaultBlackList();
        printBlacklist();
    }

    if(m_currentMode == Mode::SingleFile)
    {
        std::cout << fmt::format("Parsing file: {0}...", m_loadPath) << "\n";
        parseSingleFile();
    }
    else
    {
        std::cout << "Parsing assets..." << "\n";
        parse();
    }
    std::cout << "Loading asset data..." << "\n";
    bool success = loadAssets();
    if(success)
    {
        std::cout << "Creating asset file..." << "\n";
        createAssetFile();
        createMapperFile();
    }
    else
    {
        std::cout << "Error loading assets!" << "\n";
    }
}

/*!
 * Runs the basic version that just goes through all the files in the same folder as the executable.
 */
void AssetParser::runBasic()
{
    std::cout << "Generating default blacklist for files..." << "\n";
    createDefaultBlackList();
    printBlacklist();
    std::cout << "Parsing assets..." << "\n";
    parse();
    std::cout << "Loading asset data..." << "\n";
    bool success = loadAssets();
    if(success)
    {
        std::cout << "Creating asset file..." << "\n";
        createAssetFile();
        createMapperFile();
    }
    else
    {
        std::cout << "Error loading assets!" << "\n";
    }
}

std::string AssetParser::StringToUpper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::toupper(c); });
    return s;
}

void AssetParser::setMode(const std::string_view &action)
{
    if(action == "-h" || action == "--help") m_currentMode = Mode::Help;
    else if(action == "-v" || action == "--version") m_currentMode = Mode::Version;
    else if(action == "-f" || action == "--file") m_currentMode = Mode::SingleFile;
    else if(action == "-r" || action == "--recursive") m_currentMode = Mode::Recursive;
    else if(action == "-d" || action == "--directory") m_currentMode = Mode::Directory;
    else m_currentMode = Mode::Default;

}