//
// Created by robin on 28.07.17.
//

#ifndef F2SRC_MAPPINGITEM_H
#define F2SRC_MAPPINGITEM_H

#include <stdlib.h>

#include <fstream>
//#include "fmt/string.h"
#include "fmt/format.h"

class MappingItem
{
    public:
        MappingItem();

        void setVariableName(const std::string &variableName);
        void setSizeVariableName(const std::string &sizeVariableName);
        void setSizeValueName(const std::string &sizeValueName);
        void setValueNamespace(const std::string &valueNamespace);
        void setRootNamespace(const std::string &rootNamespace);
        void setValueName(const std::string &valueName);

        const std::string &getVariableName() const;
        const std::string &getSizeVariableName() const;
        const std::string &getSizeValueName() const;
        const std::string &getValueNamespace() const;
        const std::string &getValueName() const;
        const std::string &getRootNamespace() const;

        std::string generateVariableData();
        std::string generateSizeData();

        const std::string VARIABLE_TYPE_STR = "static const unsigned char *";
        const std::string SIZE_TYPE_STR = "static const size_t";

    private:
        std::string m_variableName = "";
        std::string m_sizeVariableName = "";
        std::string m_rootNamespace = ""; //Usually "files", or whatever is the root namespace of files.h
        std::string m_valueNamespace = "";
        std::string m_valueName = "";
        std::string m_sizeValueName = "";

};


#endif //F2SRC_MAPPINGITEM_H
