#ifndef JSONOPENPERSISTENCE_H
#define JSONOPENPERSISTENCE_H

#include <QHash>

class JsonOpenPersistence
{
public:
  QHash<QString, bool> readAllowances() const;
  QString readModifier() const;
  bool readEnabled() const;
  void save(const QHash<QString, bool>& allowances, const QString& openModifier);

private:
    const QString _file = "openValidation.dat";
};

#endif // JSONOPENPERSISTENCE_H
