#include <QJsonDocument>
#include <QJsonObject>
#include <curl/curl.h>
#include <QByteArray>
#include <QUrl>
#include <QUrlQuery>
#include <iostream>
#include <chrono>
#include <ostream>
#include <fstream>
#include <QCoreApplication>
#include <QJsonArray>
#include <list>
#include "api.h"

using namespace std;

// Function to be called by libcurl when there is data to be written
size_t write_data(void *ptr, size_t size, size_t nmemb, QByteArray *data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

QByteArray downloadUrl(const QUrl &url) {
    qDebug() << "Downloading from" << url.toString(QUrl::RemoveFilename).toStdString().c_str();
    auto start = chrono::high_resolution_clock::now();
    CURL *curl = curl_easy_init();
    QByteArray data;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.toString().toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    auto stop = chrono::high_resolution_clock::now();
    qDebug() << "Downloaded" << data.size() << "bytes in" << chrono::duration_cast<chrono::seconds>(stop - start).count() << "seconds";
    return data;
}

QJsonDocument searchHGNC(QMap<QString, QString> params) {
    QUrl url("https://clinicaltables.nlm.nih.gov/api/genes/v4/search");
    params["sf"] = "symbol,alias_symbol";
    params["df"] = "symbol,alias_symbol";
    QUrlQuery query;
    for (auto it = params.begin(); it != params.end(); ++it) {
        query.addQueryItem(it.key(), it.value());
    }
    url.setQuery(query);
    qDebug() << "url:" << url.toString();
    QByteArray data = downloadUrl(url);
    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc;
}

QJsonDocument searchPanther(QString geneInputList) {
    QUrl url("http://pantherdb.org/services/oai/pantherdb/enrich/overrep");
    QMap<QString, QString> params;
    params["annotDataSet"] = "GO:0008150";
    params["organism"] = "9606";
    params["geneInputList"] = geneInputList;
    QUrlQuery query;
    for (auto it = params.begin(); it != params.end(); ++it) {
        query.addQueryItem(it.key(), it.value());
    }
    url.setQuery(query);
    QByteArray data = downloadUrl(url);
    QString string = QString::fromUtf8(data.constData(), data.size());
    // qDebug() << string;
    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc;
}

void saveTxt(QByteArray data, QString filename) {
    std::ofstream outfile(filename.toStdString(), ios::out);
    // qDebug() << "data is" << data.data();
    outfile << data.data() << std::endl;
    outfile.close();
}

string getGeneontology() {
    QUrl url("http://current.geneontology.org/ontology/go.obo");
    QByteArray data = downloadUrl(url);
    return data.toStdString();
}

vector<string> getOverrep(vector<string> geneLists) {
    vector<string> labelList = {};
    for (vector<string>::iterator geneList = geneLists.begin(); geneList != geneLists.end(); ++geneList) {
        QJsonDocument doc = searchPanther(QString::fromStdString(*geneList));
        labelList.push_back(doc.object()["results"].toObject()["result"].toArray().first().toObject()["term"].toObject()["label"].toString().toStdString());
    } return labelList;
}

void printExample() {
}

void test() {}
