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

#include "jsontoxml.h"

namespace LTDev {


/**
 * @brief Constructor
 */
JsonToXml::JsonToXml()
{

}


/**
 * Parses the Json file
 *
 * @param jsonFilePath: the path of the file to parse
 *
 * @return QJsonObject
 */
QJsonObject JsonToXml::parse(const QString &jsonFilePath)
{
    // Check if file exists
    if(!QFile::exists(jsonFilePath)){
        qWarning() << "File not exists: "<< jsonFilePath;
        return QJsonObject();
    }

    QFile file(jsonFilePath);

    QString lines;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        while (!stream.atEnd())
        {
            lines.append(stream.readLine());
        }
    }
    file.close();

    return QJsonDocument::fromJson(lines.toUtf8()).toVariant().toJsonObject();
}


/**
 * Converts the Json file passed into a QDomDocument
 *
 * @param jsonFilePath: the path of the file to convert
 *
 * @return QDomDocument
 */
QDomDocument JsonToXml::convert(const QString &jsonFilePath)
{
    QJsonObject obj = parse(jsonFilePath);
    return convert(obj);
}


/**
 * Converts the Json object passed into a QDomDocument
 *
 * @param jsonObj: the json to convert
 *
 * @return QDomDocument
 */
QDomDocument JsonToXml::convert(const QJsonObject &jsonObj)
{
    QDomDocument doc;

    QJsonObject rootObj;

    // Check if the json object is a document or an element
    bool isDocument = jsonObj.contains("root") && jsonObj.contains("instruction");

    if(isDocument){
        // Add document instruction first
        addDocumentInstruction(doc, jsonObj.value("instruction").toObject());

        // Retrieve document root
        rootObj = jsonObj.value("root").toObject();
    } else {
        rootObj = jsonObj;
    }

    // Append root element
    QDomElement root = addElement(doc, doc, rootObj);

    // Append children elements
    addElements(doc, root, rootObj);

    return doc;
}


/**
 * Updates the xml document and adds to the node the xml element extracted
 * from the json object. Returns the added element.
 *
 * @param doc: the xml document
 * @param node: the node to which the element extracted from json will be added
 * @param jsonObj: the json object from which extract the xml tree
 *
 * @return QDomElement
 */
QDomElement JsonToXml::addElement(QDomDocument &doc, QDomNode &node, const QJsonObject &jsonObj){
    // Extract xml values from json
    QString tag = jsonObj.value("tag").toString();
    QString text = jsonObj.value("text").toString();
    QJsonArray attributes = jsonObj.value("attributes").toArray();

    // Create element
    QDomElement el = doc.createElement( tag );
    node.appendChild( el );

    // Append element's text
    if ( !text.isNull() ) {
        QDomText txt = doc.createTextNode( text );
        el.appendChild( txt );
    }

    // Append element's attributes
    foreach (const QJsonValue &v, attributes) {
        QJsonObject attr = v.toObject();

        QString name = attr.value("key").toString();
        QString value = attr.value("value").toString();
        el.setAttribute(name, value);
    }

    return el;
}


/**
 * Updates the xml document and adds to the node all the children nodes
 * recursively extracted from the json object.
 *
 * @param doc: the xml document
 * @param node: the node to which the element extracted from json will be added
 * @param jsonObj: the json object from which extract the xml tree
 */
void JsonToXml::addElements(QDomDocument &doc, QDomNode &node, const QJsonObject &jsonObj){
    QJsonArray elements = jsonObj.value("elements").toArray();

    foreach (const QJsonValue &v, elements) {
        QJsonObject obj = v.toObject();

        // Retrieve the current element added to the node
        QDomElement nd = addElement(doc, node, obj);

        // Recursively add children's elements
        addElements(doc, nd, obj);
    }
}


/**
 * Adds to the document the instruction specified in the json
 *
 * @param doc: the xml document
 * @param jsonInstruction: the json object from which extract the document instructions
 */
void JsonToXml::addDocumentInstruction(QDomDocument &doc, const QJsonObject &jsonInstruction){
    QString target = jsonInstruction.value("target").toString();
    QString data = jsonInstruction.value("data").toString();

    // Create processing instruction
    QDomProcessingInstruction ins = doc.createProcessingInstruction(target, data);
    doc.appendChild(ins);
}


}
