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

#ifndef XMLJSONCONVERTER_H
#define XMLJSONCONVERTER_H

#include "cpp/jsontoxml.h"
#include "cpp/xmltojson.h"


namespace LTDev {

class XmlJsonConverter
{
public:
    XmlJsonConverter();

    /**
     * @brief Library version
     */
    inline static QString version() {return QString(LIBRARY_VERSION);}

    /**
     * @brief Converts the XML file passed into a QJsonObject
     */
    static QJsonObject toJson(const QString& xmlFilePath);

    /**
     * @brief Converts the XML document passed into a QJsonObject
     */
    static QJsonObject toJson(const QDomDocument& xmlDoc);

    /**
     * @brief Converts the XML element passed into a QJsonObject
     */
    static QJsonObject toJson(const QDomElement& xmlElement);

    /**
     * @brief Converts the Json file passed into a QDomDocument
     */
    static QDomDocument toXml(const QString &jsonFilePath);

    /**
     * @brief Converts the Json object passed into a QDomDocument
     */
    static QDomDocument toXml(const QJsonObject &jsonObj);

    /**
     * @brief Creates a file with the content passed. Returns true if creation is successfull, false otherwise.
     */
    static bool save(const QString &fileContent, const QString &filePath);
};

}

#endif // XMLJSONCONVERTER_H
