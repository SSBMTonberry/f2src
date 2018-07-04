//
// Created by robin on 30.06.17.
//

#ifndef F2SRC_ASSETCONTAINER_H
#define F2SRC_ASSETCONTAINER_H

#include "AssetNamespace.h"

class AssetContainer
{
    public:
        AssetContainer();
        virtual ~AssetContainer();
        void initialize(const std::string &mainNamespace, const std::string &loadPath);
        void addAsset(const AssetNamespace &asset);
        std::vector<AssetNamespace> getAssets() const;

        AssetNamespace * getRelatedNamespace(const std::string &filePath);
        AssetNamespace * getRootNamespace();
        const std::string & getNamespace() const;
        void clear();

    protected:
        std::string m_namespace = ""; //The main namespace that is going to be used for generating files
        std::vector<AssetNamespace> m_assets;
        AssetNamespace m_rootNamespace;
};


#endif //F2SRC_ASSETCONTAINER_H
