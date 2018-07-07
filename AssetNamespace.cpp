//
// Created by robin on 30.06.17.
//


#include "AssetNamespace.h"

AssetNamespace::AssetNamespace()
{

}

AssetNamespace::~AssetNamespace()
{

}

void AssetNamespace::initialize(const std::string &basePath, const std::string &currentPath)
{
    m_path = currentPath;
    m_namespace = currentPath.substr(basePath.length());
    m_namespace = std::regex_replace(m_namespace, std::regex("\\\\"), "::");
    m_namespace = std::regex_replace(m_namespace, std::regex("\\/"), "::");
    std::replace(m_namespace.begin(), m_namespace.end(), '.', '_');
    std::replace(m_namespace.begin(), m_namespace.end(), '-', '_');
    std::replace(m_namespace.begin(), m_namespace.end(), ' ', '_');

    std::vector<std::string> parts = splitString(m_namespace, "::");
    //Add a '_' prefix if name starts with number
	
	std::locale loc(std::locale(""));
	std::locale::global(std::locale(""));
    
	for(auto &part : parts)
    {
        if(part.length() > 0 && std::isdigit(part[0], loc))
            part.insert(0, 1, '_');
    }

    //Compose the string back in again to make a working namespace
    m_namespace = std::accumulate(parts.begin(), parts.end(), std::string(),
                    [](const std::string& a, const std::string& b) -> std::string {
                        return a + (a.length() > 0 ? "::" : "") + b;
                    });
}

void AssetNamespace::addData(const std::string &data)
{
    m_data.push_back(data);
}

void AssetNamespace::addFileMapperData(const MappingItem &data)
{
    m_fileMapperData.push_back(data);
}

void AssetNamespace::setTabs(int tabs)
{
    m_tabs = tabs;
}

const std::string &AssetNamespace::getNamespace() const
{
    return m_namespace;
}

void AssetNamespace::setNamespace(const std::string &ns)
{
    m_namespace = ns;
}

void AssetNamespace::setPath(const std::string &path)
{
    m_path = path;
}

const std::string &AssetNamespace::getPath() const
{
    return m_path;
}

void AssetNamespace::writeData(std::ofstream &fout)
{
    std::string tabPrefix = "";
    for(int i = 0; i < m_tabs; i++)
    {
        tabPrefix += "\t";
    }

    fout << tabPrefix << "namespace " << m_namespace << "\n";
    fout << tabPrefix << "{\n";
    for(auto const & data : m_data)
    {
        fout << tabPrefix << data.c_str();
    }
    fout << tabPrefix << "}\n";
}

void AssetNamespace::writeFilemapperData(std::ofstream &fout)
{
    try
    {
        std::string tabPrefix = "";
        for (int i = 0; i < m_tabs; i++)
        {
            tabPrefix += "\t";
        }

        fout << tabPrefix << "namespace " << m_namespace << "\n";
        fout << tabPrefix << "{\n";
        for (auto & item : getFileMapperData())
        {
            fout << "\t" << tabPrefix << item.generateVariableData().c_str() << "\n";
            fout << "\t" << tabPrefix << item.generateSizeData().c_str() << "\n";
        }
        fout << tabPrefix << "}\n";
    }
    catch (std::exception &e)
    {
        std::string msg = e.what();
    }
}

std::vector<std::string> const & AssetNamespace::getData() const
{
    return m_data;
}

std::vector<MappingItem> & AssetNamespace::getFileMapperData()
{
    return m_fileMapperData;
}

std::vector<std::string> AssetNamespace::splitString(const std::string &str, const std::string &delimiter)
{
    std::vector<std::string> items;
    std::string splitStr = str;
    size_t pos = 0;
    std::string token;
    while ((pos = splitStr.find(delimiter)) != std::string::npos) {
        token = splitStr.substr(0, pos);
        items.push_back(token);
        splitStr.erase(0, pos + delimiter.length());
    }

    if(splitStr.length() > 0)
        items.push_back(splitStr);

    return items;
}

