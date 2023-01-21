#ifndef API_H
#define API_H

#include <QJsonDocument>
#include <curl/curl.h>
#include <QByteArray>
#include <QUrl>
#include <QUrlQuery>

size_t write_data(void *ptr, size_t size, size_t nmemb, QByteArray *data);
QByteArray downloadUrl(const QUrl &url);
QByteArray DownloadSingle(const std::string &url);
std::string searchHGNC(std::string terms, CURL* curl);
QJsonDocument searchDavid(QMap<QString, QString> params);
void saveTxt(QByteArray data, QString filename);
void printExample();
std::string getGeneontology();
std::vector<std::string> getOverrep(std::vector<std::string> geneLists);

std::vector<std::string> getOverrep(std::vector<std::string> geneLists);

#endif // API_H

