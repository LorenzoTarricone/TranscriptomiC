#ifndef API_H
#define API_H

#include <QJsonDocument>
#include <curl/curl.h>
#include <QByteArray>
#include <QUrl>
#include <QUrlQuery>

size_t write_data(void *ptr, size_t size, size_t nmemb, QByteArray *data);
QByteArray downloadUrl(const QUrl &url);
QJsonDocument searchHGNC(QMap<QString, QString> params);
QJsonDocument searchDavid(QMap<QString, QString> params);
void printExample();

#endif // API_H

