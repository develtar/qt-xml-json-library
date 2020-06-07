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

#include <QCoreApplication>
#include <QDir>

#include "xmljsonconverter.h"

/**
 * @brief Converts the xml document of the src path into json, and then converts the json into xml document.
 * Saves the json and the xml document generated in the paths passed.
 *
 * @param srcXmlPath: the path from which extract the xml document
 * @param dstJsonPath: the path in which save the json
 * @param dstXmlPath: the path in which save the xml document
 *
 */
void convert(const QString &srcXmlPath, const QString &dstJsonPath, const QString &dstXmlPath){
    QJsonObject jsonObj = LTDev::XmlJsonConverter::toJson(srcXmlPath);
    if(LTDev::XmlJsonConverter::save(QJsonDocument(jsonObj).toJson(), dstJsonPath)){
        qDebug() << "Json saved: " << dstJsonPath;
    } else {
        qDebug() << "Json save failed: " << dstJsonPath;
    }

    QDomDocument xmlDoc = LTDev::XmlJsonConverter::toXml(dstJsonPath);
    if(LTDev::XmlJsonConverter::save(xmlDoc.toString(), dstXmlPath)){
        qDebug() << "Xml saved: " << dstXmlPath;
    } else {
        qDebug() << "Xml save failed: " << dstJsonPath;
    }

}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Source samples path
    QString samplesDirPath = QString(PROJECT_PATH)+"/samples";

    // Converted samples path
    QString outPath = QDir::currentPath();

    // Svg sample: svg -> json -> svg
    QString sampleSvgRectanglesSrcPath = samplesDirPath+"/1_sample_svg_rectangles.svg";
    QString sampleSvgRectanglesDstJsonPath = outPath+"/1_sample_svg_rectangles_to_json.json";
    QString sampleSvgRectanglesDstXmlPath = outPath+"/1_sample_svg_rectangles_from_json.svg";
    convert(sampleSvgRectanglesSrcPath, sampleSvgRectanglesDstJsonPath, sampleSvgRectanglesDstXmlPath);

    // Xml sample: xml -> json -> xml
    QString sampleXmlShiporderSrcPath = samplesDirPath+"/2_sample_xml_shiporder.xml";
    QString sampleXmlShiporderDstJsonPath = outPath+"/2_sample_xml_shiporder_to_json.json";
    QString sampleXmlShiporderDstXmlPath = outPath+"/2_sample_xml_shiporder_from_json.xml";
    convert(sampleXmlShiporderSrcPath, sampleXmlShiporderDstJsonPath, sampleXmlShiporderDstXmlPath);

    // Xml sample: xml -> json -> xml
    QString sampleXmlComplexRandomSrcPath = samplesDirPath+"/3_sample_xml_complex_random.xml";
    QString sampleXmlComplexRandomDstJsonPath = outPath+"/3_sample_xml_complex_random.xml_to_json.json";
    QString sampleXmlComplexRandomDstXmlPath = outPath+"/3_sample_xml_complex_random.xml_from_json.xml";
    convert(sampleXmlComplexRandomSrcPath, sampleXmlComplexRandomDstJsonPath, sampleXmlComplexRandomDstXmlPath);

    // Xsd sample: xsd -> json -> xsd
    QString sampleXsdShiporderSrcPath = samplesDirPath+"/4_sample_xsd_shiporder.xsd";
    QString sampleXsdShiporderDstJsonPath = outPath+"/4_sample_xsd_shiporder_to_json.json";
    QString sampleXsdShiporderDstXmlPath = outPath+"/4_sample_xsd_shiporder_from_json.xsd";
    convert(sampleXsdShiporderSrcPath, sampleXsdShiporderDstJsonPath, sampleXsdShiporderDstXmlPath);


    return a.exec();
}
