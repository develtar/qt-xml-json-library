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

#include "xmltojson.h"

namespace LTDev {

/**
 * @brief Constructor
 */
XmlToJson::XmlToJson()
{

}

/**
 * Parses the XML file
 *
 * @param xmlFilePath: the path of the file to parse
 *
 * @return QDomDocument
 */
QDomDocument XmlToJson::parse(const QString &xmlFilePath)
{
    // Check if file exists
    if(!QFile::exists(xmlFilePath)){
        qWarning() << "File not exists: "<< xmlFilePath;
        return QDomDocument();
    }

    QDomDocument xmlDoc;

    // Load xml file as raw data
    QFile f(xmlFilePath);
    if (!f.open(QIODevice::ReadOnly ))
    {
        qWarning() << "Error while loading file: " << xmlFilePath;
        return QDomDocument();
    }

    // Set data into the QDomDocument before processing
    xmlDoc.setContent(&f);
    f.close();

    return xmlDoc;
}


/**
 * Converts the XML file passed into a QJsonObject
 *
 * @param xmlFilePath: the path of the file to convert
 *
 * @return QJsonObject
 */
QJsonObject XmlToJson::convert(const QString &xmlFilePath)
{
    QDomDocument doc = parse(xmlFilePath);
    return convert(doc);
}


/**
 * Converts the XML document passed into a QJsonObject
 *
 * @param xmlDoc: the xml document to convert
 *
 * @return QJsonObject
 */
QJsonObject XmlToJson::convert(const QDomDocument &xmlDoc)
{
    // Retrieve document root element
    QDomElement root = xmlDoc.documentElement();

    QJsonObject jsonDoc;

    // Insert xml document instruction
    jsonDoc.insert("instruction", processingInstruction(xmlDoc.firstChild()));

    // Insert xml document root element
    jsonDoc.insert("root", convert(root));

    return jsonDoc;
}


/**
 * Converts the XML element passed into a QJsonObject
 *
 * @param xmlElement: the xml element to convert
 *
 * @return QJsonObject
 */
QJsonObject XmlToJson::convert(const QDomElement &xmlElement)
{
    return {
        {"tag", xmlElement.tagName()},
        {"attributes", attributes(xmlElement)},
        {"elements", elements(xmlElement)},
    };
}

/**
 * Returns the array of the element's attributes
 *
 * @param xmlElement: the element to parse
 *
 * @return QJsonArray
 */
QJsonArray XmlToJson::attributes(QDomElement xmlElement){
    QJsonArray jsonAttributes;

    for(int i=0; i<xmlElement.attributes().size(); i++){
        QDomNamedNodeMap attributes = xmlElement.attributes();
        QDomNode n = attributes.item(i);

        if(!n.isNull()){
            QDomAttr attr = xmlElement.attributeNode(n.nodeName());

            QJsonObject jsonAttr = {
                {"key", attr.name()},
                {"value", attr.value()}
            };

            jsonAttributes.append(jsonAttr);
        }
    }

    return jsonAttributes;
}


/**
 * Returns the array of the element's children
 *
 * @param xmlElement: the element to parse
 *
 * @return QJsonArray
 */
QJsonArray XmlToJson::elements(QDomElement xmlElement){
    QJsonArray jsonElements;

    for(QDomElement e=xmlElement.firstChild().toElement(); !e.isNull(); e = e.nextSibling().toElement()){
        QJsonArray jsonAttributes = attributes(e);

        QJsonObject jsonElement = {
            {"tag", e.tagName()},
            {"attributes", jsonAttributes},

        };

        // Insert text if the current element hasn't children
        if(e.firstChild().toElement().isNull()){
            jsonElement.insert("text", e.text());
        }


        // Recursively parse children elements
        QJsonArray childElements = elements(e);

        // Insert children elements to the current element
        jsonElement.insert("elements", childElements);

        // Append element
        jsonElements.append(jsonElement);
    }

    return jsonElements;

}

/**
 * Returns the json object containing the processing instruction of the passed node
 *
 * @param xmlNode: the processing instruction node
 *
 * @return QJsonObject
 */
QJsonObject XmlToJson::processingInstruction(const QDomNode &xmlNode){
    QString data = "", target = "";

    // Check if the passed node is a processing instruction
    if(xmlNode.isProcessingInstruction()){
        QDomProcessingInstruction instr = xmlNode.toProcessingInstruction();

        // Retrieve instruction data
        data = instr.data();
        target = instr.target();
    }

    return {
        {"target", target},
        {"data", data}
    };
}

}
