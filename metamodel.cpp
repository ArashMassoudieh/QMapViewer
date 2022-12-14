#include "metamodel.h"
#include <QJsonObject>
#include "layer.h"
MetaModel::MetaModel():QMap<QString,VariableList>()
{

}

MetaModel& MetaModel::operator=(const MetaModel& other)
{
    QMap<QString,VariableList>::operator=(other);
    return *this;
}

MetaModel::~MetaModel()
{

}
MetaModel::MetaModel(const MetaModel& other):QMap<QString,VariableList>(other)
{

}
MetaModel::MetaModel(const QJsonDocument& qjdoc):QMap<QString,VariableList>()
{
    //fillMetaModelDataIntoMap(qjdoc); //This function is for collecting meta data and comparing with model layer data, still working on it.

    QJsonObject qjobject = qjdoc.object();
    foreach(const QString& key, qjobject.keys()) {
        QJsonValue subValues = qjobject.value(key);
        VariableList varlist = VariableList(key, subValues.toObject());
        QString objecttype = subValues["type"].toString();
        if (objecttype == "node")
            varlist.SetObjectType(object_type::node);
        else if (objecttype == "link")
            varlist.SetObjectType(object_type::link);
        operator[](key) = varlist;
    }
}

bool MetaModel::getloadIcon(const QString &fileName){
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    QJsonDocument JsonDoc = QJsonDocument().fromJson(jsonFile.readAll());
    qDebug()<<"ModelJsonDoc2000 '"<<JsonDoc << "' 00000000";
    QJsonObject JsonObject = JsonDoc.object();
    foreach(const QString& key, JsonObject.keys()) {
        QJsonValue value = JsonObject.value(key);
        qDebug() << "Key = " << key << ", Value = " << value.toString();
        if(key == "sub-catchment"){
            auto iconUrl =  value.toObject().value("icon").toString();
            auto name =  value.toObject().value("name").toString();
               this->setLayerName(name);
        }
    }

    return true;
}


