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


#ifndef XMLTOJSON_H
#define XMLTOJSON_H

#include <QFile>
#include <QDebug>

#include <QDomElement>
#include <QDomDocument>
#include <QDomNode>

#include <QJsonObject>
#include <QJsonArray>


namespace LTDev {

class XmlToJson
{
public:
    /**
     * @brief Constructor
     */
    XmlToJson();

    /**
     * @brief Parses the XML file
     */
    static QDomDocument parse(const QString& xmlFilePath);

    /**
     * @brief Converts the XML file passed into a QJsonObject
     */
    static QJsonObject convert(const QString& xmlFilePath);

    /**
     * @brief Converts the XML document passed into a QJsonObject
     */
    static QJsonObject convert(const QDomDocument& xmlDoc);

    /**
     * @brief Converts the XML element passed into a QJsonObject
     */
    static QJsonObject convert(const QDomElement& xmlElement);


private:
    /**
     * @brief Returns the array of the element's attributes
     */
    static QJsonArray attributes(QDomElement xmlElement);

    /**
     * @brief Returns the array of the element's children
     */
    static QJsonArray elements(QDomElement xmlElement);

    /**
     * @brief Returns the json object containing the processing instruction of the passed node
     */
    static QJsonObject processingInstruction(const QDomNode &xmlNode);
};

}

#endif // XMLTOJSON_H
