//
// Created by robin on 30.06.17.
//

#include "AssetContainer.h"
#include "AssetParser.h"

AssetContainer::AssetContainer() = default;

AssetContainer::~AssetContainer() = default;

void AssetContainer::initialize(const std::string &mainNamespace, const std::string &loadPath)
{
    m_namespace = mainNamespace;
    m_rootNamespace.initialize(loadPath, loadPath);
    m_rootNamespace.setTabs(1);
}

void AssetContainer::addAsset(const AssetNamespace &asset)
{
    m_assets.push_back(asset);
}

void AssetContainer::clear()
{
    m_assets.clear();
}

AssetNamespace *AssetContainer::getRelatedNamespace(const std::string &filePath)
{
    for(AssetNamespace &ns : m_assets)
    {
        if(ns.getPath().length() < filePath.length() && AssetParser::StringContains(filePath, ns.getPath()))
        {
            //Check if there are any slashes or backslashes left in the path. If not, this is the one!
            std::string path = filePath.substr(ns.getPath().length() + 1);//+1 strips the last slash
            if(!AssetParser::StringContains(path, "\\") && !AssetParser::StringContains(path, "/"))
                return &ns;
        }
    }

    return &m_rootNamespace;
}

AssetNamespace *AssetContainer::getRootNamespace()
{
    return &m_rootNamespace;
}

std::vector<AssetNamespace> AssetContainer::getAssets() const
{
    return m_assets;
}

const std::string &AssetContainer::getNamespace() const
{
    return m_namespace;
}


