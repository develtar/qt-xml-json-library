/*
MIT License

Copyright (c) 2020 Leonardo Tarollo <develtar@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "xmljsonconverter.h"

namespace LTDev {

XmlJsonConverter::XmlJsonConverter()
{
}

/**
 * Converts the XML file passed into a QJsonObject
 *
 * @param xmlFilePath: the path of the file to convert
 *
 * @return QJsonObject
 */
QJsonObject XmlJsonConverter::toJson(const QString &xmlFilePath)
{
    return XmlToJson::convert(xmlFilePath);
}

/**
 * Converts the XML document passed into a QJsonObject
 *
 * @param xmlDoc: the xml document to convert
 *
 * @return QJsonObject
 */
QJsonObject XmlJsonConverter::toJson(const QDomDocument &xmlDoc)
{
    return XmlToJson::convert(xmlDoc);
}

/**
 * Converts the XML element passed into a QJsonObject
 *
 * @param xmlElement: the xml element to convert
 *
 * @return QJsonObject
 */
QJsonObject XmlJsonConverter::toJson(const QDomElement &xmlElement)
{
    return XmlToJson::convert(xmlElement);
}

/**
 * Converts the Json file passed into a QDomDocument
 *
 * @param jsonFilePath: the path of the file to convert
 *
 * @return QDomDocument
 */
QDomDocument XmlJsonConverter::toXml(const QString &jsonFilePath)
{
    return JsonToXml::convert(jsonFilePath);
}

/**
 * Converts the Json object passed into a QDomDocument
 *
 * @param jsonObj: the json to convert
 *
 * @return QDomDocument
 */
QDomDocument XmlJsonConverter::toXml(const QJsonObject &jsonObj)
{
    return JsonToXml::convert(jsonObj);
}

/**
 * Creates a file with the content passed. Returns true if
 * creation is successfull, false otherwise.
 *
 * @param fileContent: the file content
 * @param filePath: the path of the file to create
 *
 * @return bool
 */
bool XmlJsonConverter::save(const QString &fileContent, const QString &filePath)
{
    QFile file(filePath);

    // Write into file
    if ( file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text)) {
        QTextStream stream( &file );
        stream << fileContent << endl;
        file.close();
        return true;
    }

    return false;
}

}
