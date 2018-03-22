#ifndef MODEL_TYPE_H
#define MODEL_TYPE_H

#include "model_personnelinfos.h"
#include <vector>

class Type
{
private:
    int id;
    QString label;

public:
    Type();
    Type(int ID, QString LABEL);

    std::vector<personnelInfos> getRessourcesRelatifs();
    QString getLabel() const;
    void setLabel(const QString &value);
    int getId() const;
    void setId(int value);
    static std::vector<Type> getListType();
    static Type getTypeOf(int idRessource);
};

#endif // MODEL_TYPE_H

