#include <QJsonDocument>
#include <curl/curl.h>
#include <QByteArray>
#include <QUrl>
#include <QUrlQuery>
#include "api.h"

// Function to be called by libcurl when there is data to be written
size_t write_data(void *ptr, size_t size, size_t nmemb, QByteArray *data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

QByteArray downloadUrl(const QUrl &url) {
    CURL *curl = curl_easy_init();
    QByteArray data;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.toString().toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return data;
}

QJsonDocument searchHGNC(QMap<QString, QString> params) {
    QUrl url("https://clinicaltables.nlm.nih.gov/api/genes/v4/search");
    params["sf"] = "symbol,alias_symbol";
    params["df"] = "symbol,alias_symbol";QUrlQuery query;
    for (auto it = params.begin(); it != params.end(); ++it) {
        query.addQueryItem(it.key(), it.value());
    }
    url.setQuery(query);
    qDebug() << "url:" << url.toString();
    QByteArray data = downloadUrl(url);
    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc;
}

QJsonDocument searchDavid(QMap<QString, QString> params) {
    QUrl url("https://clinicaltables.nlm.nih.gov/api/genes/v4/search");
    QUrlQuery query;
    for (auto it = params.begin(); it != params.end(); ++it) {
        query.addQueryItem(it.key(), it.value());
    }
    url.setQuery(query);
    QByteArray data = downloadUrl(url);
    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc;
}


void printExample() {
    //Example call
    QMap<QString, QString> params;
    params["terms"] = "BRCA1";
    QJsonDocument doc = searchHGNC(params);
    qDebug() << "API Test";
    qDebug() << qPrintable(doc.toJson());
}
