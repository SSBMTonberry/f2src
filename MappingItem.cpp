//
// Created by robin on 28.07.17.
//

#include "MappingItem.h"

MappingItem::MappingItem()
{

}

const std::string &MappingItem::getVariableName() const
{
    return m_variableName;
}

void MappingItem::setVariableName(const std::string &variableName)
{
    m_variableName = variableName;
}

const std::string &MappingItem::getValueNamespace() const
{
    return m_valueNamespace;
}

void MappingItem::setValueNamespace(const std::string &valueNamespace)
{
    m_valueNamespace = valueNamespace;
}

const std::string &MappingItem::getValueName() const
{
    return m_valueName;
}

void MappingItem::setValueName(const std::string &valueName)
{
    m_valueName = valueName;
}

void MappingItem::setSizeVariableName(const std::string &sizeVariableName)
{
    m_sizeVariableName = sizeVariableName;
}

void MappingItem::setSizeValueName(const std::string &sizeValueName)
{
    m_sizeValueName = sizeValueName;
}

const std::string &MappingItem::getSizeVariableName() const
{
    return m_sizeVariableName;
}

const std::string &MappingItem::getSizeValueName() const
{
    return m_sizeValueName;
}

void MappingItem::setRootNamespace(const std::string &rootNamespace)
{
    m_rootNamespace = rootNamespace;
}

const std::string &MappingItem::getRootNamespace() const
{
    return m_rootNamespace;
}

std::string MappingItem::generateVariableData()
{
    std::string data = (m_valueNamespace.length() > 0) ? fmt::format("{0} {1} = {2}::{3}::{4};", VARIABLE_TYPE_STR, m_variableName, m_rootNamespace, m_valueNamespace, m_valueName) :
                                                         fmt::format("\t{0} {1} = {2}::{3};", VARIABLE_TYPE_STR, m_variableName, m_rootNamespace, m_valueName);

    return data; //data;
}

std::string MappingItem::generateSizeData()
{
    std::string data = (m_valueNamespace.length() > 0) ? fmt::format("{0} {1} = {2}::{3}::{4};", SIZE_TYPE_STR, m_sizeVariableName, m_rootNamespace, m_valueNamespace, m_sizeValueName) :
                                                         fmt::format("\t{0} {1} = {2}::{3};", SIZE_TYPE_STR, m_sizeVariableName, m_rootNamespace, m_sizeValueName);
    return data;
}


