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

#ifndef JSONTOXML_H
#define JSONTOXML_H

#include <QDebug>

#include <QDomElement>
#include <QDomDocument>
#include <QDomNode>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <QFile>



namespace LTDev {

class JsonToXml
{
public:
    /**
     * @brief Constructor
     */
    JsonToXml();

    /**
     * @brief Parses the Json file
     */
    static QJsonObject parse(const QString &jsonFilePath);

    /**
     * @brief Converts the Json file passed into a QDomDocument
     */
    static QDomDocument convert(const QString &jsonFilePath);

    /**
     * @brief Converts the Json object passed into a QDomDocument
     */
    static QDomDocument convert(const QJsonObject &jsonObj);

private:
    /**
     * @brief Updates the xml document and adds to the node the xml element extracted
     * from the json object. Returns the added element.
     */
    static QDomElement addElement(QDomDocument &doc, QDomNode &node, const QJsonObject &jsonObj);

    /**
     * @brief Updates the xml document and adds to the node all the children nodes
     * recursively extracted from the json object.
     */
    static void addElements(QDomDocument &doc, QDomNode &node, const QJsonObject &jsonObj);

    /**
     * @brief Adds to the document the instruction specified in the json
     */
    static void addDocumentInstruction(QDomDocument &doc, const QJsonObject &jsonInstruction);
};
}

#endif // JSONTOXML_H
