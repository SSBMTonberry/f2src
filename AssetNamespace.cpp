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

