# Qt Xml Json Library
The `qt-xml-json` library allows you to convert a file having an `.xml` structure (like `.xml`, `.xsd`, `.svg`) into a `.json` file, and viceversa.

Dependencies:
- `Qt`
- `QtXml`


## 1.0. Setting up the library
To include the library in your project follow these steps:
- Copy the library folder in your project folder
- Include the `.pri` file of the library, in the `.pro` file of your project


__Example__: in the provided sample we have a project named `XmlJsonConverterSample`. To use the library you need to include the library `.pri` file in the `.pro` of your project (in this case `XmlJsonConverterSample.pro`) adding this line:

```bash
# Include library files
include(../qt-xml-json-library/qt-xml-json-library.pri)
```

Where:
- `qt-xml-json-library` is the library folder
- `qt-xml-json-library.pri` is the file containing the paths of the files that will be included in your project


## 1.1. Usage
In your `.cpp` include the `xmljsonconverter.h`:

```c++
#include "xmljsonconverter.h"
```

Now you can access the class methods as follows:
```c++
// Converts the xml data loaded from a file, into a QJsonObject
QString srcXmlPath = "path/to/file-to-convert.xml";
QJsonObject jsonObj = LTDev::XmlJsonConverter::toJson(srcXmlPath);

// Saves the QJsonObject in a file
QString dstJsonPath = "path/to/dest_file.json";
LTDev::XmlJsonConverter::save(QJsonDocument(jsonObj).toJson(), dstJsonPath)

// Converts the json data loaded from the file previously created, into a QDomDocument
QDomDocument xmlDoc = LTDev::XmlJsonConverter::toXml(dstJsonPath);

// Saves the QDomDocument in a file
QString dstXmlPath = "path/to/dest_file.xml";
LTDev::XmlJsonConverter::save(xmlDoc.toString(), dstXmlPath)
```

For more informations take a look at the sample `XmlJsonConverterSample`.


### 1.1.0. Converting **XML** to **JSON**
You can convert `.xml`, `.svg`, `.xsd` or other formats having an xml structure, into `.json` as follows:

```c++
// Converts the xml data loaded from a file and converts it in QJsonObject
QString srcXmlPath = "path/to/file-to-convert.xml";
QJsonObject jsonObj = LTDev::XmlJsonConverter::toJson(srcXmlPath);
```

### 1.1.1. Converting **JSON** to **XML**
You can convert `.json` into `.xml`, `.svg`, `.xsd` or other formats having an xml structure, as follows:

```c++
// Converts the json data loaded from the file previously created, into a QDomDocument
QString srcJsonPath = "path/to/file-to-convert.json";
QDomDocument xmlDoc = LTDev::XmlJsonConverter::toXml(srcJsonPath);
```


### 1.2. Examples
Given the following xml file `2_sample_xml_shiporder.xml`:

```xml
<?xml version="1.0" encoding="UTF-8"?>

<shiporder orderid="889923"
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xsi:noNamespaceSchemaLocation="shiporder.xsd">
  <orderperson>John Smith</orderperson>
  <shipto>
    <name>Ola Nordmann</name>
    <address>Langgt 23</address>
    <city>4000 Stavanger</city>
    <country>Norway</country>
  </shipto>
  <item>
    <title>Empire Burlesque</title>
    <note>Special Edition</note>
    <quantity>1</quantity>
    <price>10.90</price>
  </item>
  <item>
    <title>Hide your heart</title>
    <quantity>1</quantity>
    <price>9.90</price>
  </item>
</shiporder>  
```

- **XML to JSON:** The result of the method `LTDev::XmlJsonConverter::toJson("path/to/2_sample_xml_shiporder.xml")` will be the following object:

```json
{
    "instruction": {
        "data": "version='1.0' encoding='UTF-8'",
        "target": "xml"
    },
    "root": {
        "attributes": [
            {
                "key": "xmlns:xsi",
                "value": "http://www.w3.org/2001/XMLSchema-instance"
            },
            {
                "key": "xsi:noNamespaceSchemaLocation",
                "value": "shiporder.xsd"
            },
            {
                "key": "orderid",
                "value": "889923"
            }
        ],
        "elements": [
            {
                "attributes": [
                ],
                "elements": [
                ],
                "tag": "orderperson",
                "text": "John Smith"
            },
            {
                "attributes": [
                ],
                "elements": [
                    {
                        "attributes": [
                        ],
                        "elements": [
                        ],
                        "tag": "name",
                        "text": "Ola Nordmann"
                    },
                    {
                        "attributes": [
                        ],
                        "elements": [
                        ],
                        "tag": "address",
                        "text": "Langgt 23"
                    },
                    {
                        "attributes": [
                        ],
                        "elements": [
                        ],
                        "tag": "city",
                        "text": "4000 Stavanger"
                    },
                    {
                        "attributes": [
                        ],
                        "elements": [
                        ],
                        "tag": "country",
                        "text": "Norway"
                    }
                ],
                "tag": "shipto"
            },
            {
                "attributes": [
                ],
                "elements": [
                    {
                        "attributes": [
                        ],
                        "elements": [
                        ],
                        "tag": "title",
                        "text": "Empire Burlesque"
                    },
                    {
                        "attributes": [
                        ],
                        "elements": [
                        ],
                        "tag": "note",
                        "text": "Special Edition"
                    },
                    {
                        "attributes": [
                        ],
                        "elements": [
                        ],
                        "tag": "quantity",
                        "text": "1"
                    },
                    {
                        "attributes": [
                        ],
                        "elements": [
                        ],
                        "tag": "price",
                        "text": "10.90"
                    }
                ],
                "tag": "item"
            },
            {
                "attributes": [
                ],
                "elements": [
                    {
                        "attributes": [
                        ],
                        "elements": [
                        ],
                        "tag": "title",
                        "text": "Hide your heart"
                    },
                    {
                        "attributes": [
                        ],
                        "elements": [
                        ],
                        "tag": "quantity",
                        "text": "1"
                    },
                    {
                        "attributes": [
                        ],
                        "elements": [
                        ],
                        "tag": "price",
                        "text": "9.90"
                    }
                ],
                "tag": "item"
            }
        ],
        "tag": "shiporder"
    }
}
```

- **JSON to XML:** The result of the method `LTDev::XmlJsonConverter::toXml("path/to/2_sample_xml_shiporder_to_json.json")` will be the following xml document:


```xml
<?xml version='1.0' encoding='UTF-8'?>
<shiporder xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="shiporder.xsd" orderid="889923">
 <orderperson>John Smith</orderperson>
 <shipto>
  <name>Ola Nordmann</name>
  <address>Langgt 23</address>
  <city>4000 Stavanger</city>
  <country>Norway</country>
 </shipto>
 <item>
  <title>Empire Burlesque</title>
  <note>Special Edition</note>
  <quantity>1</quantity>
  <price>10.90</price>
 </item>
 <item>
  <title>Hide your heart</title>
  <quantity>1</quantity>
  <price>9.90</price>
 </item>
</shiporder>
```
