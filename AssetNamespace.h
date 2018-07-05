//
// Created by robin on 30.06.17.
//

#ifndef F2SRC_ASSETNAMESPACE_H
#define F2SRC_ASSETNAMESPACE_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>

#include <fstream>

//#include "fmt/string.h"
#include "MappingItem.h"
#include <numeric>

class AssetNamespace
{
    public:
        AssetNamespace();
        virtual ~AssetNamespace();

        void initialize(const std::string &basePath, const std::string &currentPath);
        void setTabs(int tabs);
        void setPath(const std::string &path);
        void setNamespace(const std::string &ns);

        const std::string & getPath() const;
        std::vector<std::string> const & getData() const;
        std::vector<MappingItem> & getFileMapperData();

        void addData(const std::string &data);
        void addFileMapperData(const MappingItem &data);
        void writeData(std::ofstream &fout);
        void writeFilemapperData(std::ofstream &fout);

        const std::string &getNamespace() const;

        std::vector<std::string> splitString(const std::string &str, const std::string &delimiter);

    protected:

        std::string m_path = "";
        std::string m_namespace = "";
        std::vector<std::string> m_data;
        std::vector<MappingItem> m_fileMapperData;
        int m_tabs = 0;                     //Number of tabs to increment string with
};


#endif //F2SRC_ASSETNAMESPACE_H
