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


// Function to be called by libcurl when there is data to be written
size_t write_data(void *ptr, size_t size, size_t nmemb, QByteArray *data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

QByteArray downloadUrl(const std::string &url, CURL* curl) {
    qDebug() << "Downloading from" << url.c_str();
    auto start = std::chrono::high_resolution_clock::now();
    QByteArray data;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        curl_easy_perform(curl);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    qDebug() << "Downloaded" << data.size() << "bytes in" << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << "seconds";
    return data;
}

QByteArray DownloadSingle(const std::string &url) {
    CURL *curl = curl_easy_init();
    QByteArray data = downloadUrl(url, curl);
    curl_easy_cleanup(curl);
    return data;
}

std::vector<std::string> DownloadMany(const std::vector<std::string> &urls) {
    std::vector<std::string> datas = {};
    CURL *curl = curl_easy_init();
    for (std::vector<std::string>::const_iterator url = urls.begin(); url != urls.end(); ++url) {
        datas.push_back(downloadUrl(url->data(), curl).toStdString());
    }
    curl_easy_cleanup(curl);
    return datas;
}

std::string searchHGNC(std::string terms, CURL* curl) {
    QUrl url("https://clinicaltables.nlm.nih.gov/api/genes/v4/search");
    QMap<QString, QString> params;
    params["terms"] = QString::fromStdString(terms);
    params["sf"] = "symbol,alias_symbol";
    params["df"] = "symbol,alias_symbol";
    QUrlQuery query;
    for (auto it = params.begin(); it != params.end(); ++it) {
        query.addQueryItem(it.key(), it.value());
    }
    url.setQuery(query);
    qDebug() << "url:" << url.toString();
    QByteArray data = downloadUrl(url.toString().toStdString(), curl);
    return data.toStdString();
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
    QByteArray data = DownloadSingle(url.toString().toStdString());
    // QString string = QString::fromUtf8(data.constData(), data.size());
    // qDebug() << string;
    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc;
}

void saveTxt(QByteArray data, QString filename) {
    std::ofstream outfile(filename.toStdString(), std::ios::out);
    // qDebug() << "data is" << data.data();
    outfile << data.data() << std::endl;
    outfile.close();
}

std::string getGeneontology() {
    QUrl url("http://current.geneontology.org/ontology/go.obo");
    QByteArray data = DownloadSingle(url.toString().toStdString());
    return data.toStdString();
}

std::vector<std::string> getOverrep(std::vector<std::string> geneLists) {
    std::vector<std::string> labelList = {};
    for (std::vector<std::string>::iterator geneList = geneLists.begin(); geneList != geneLists.end(); ++geneList) {
        if (labelList.empty()) {
            labelList.push_back(std::string(""));
        } else {
        QJsonDocument doc = searchPanther(QString::fromStdString(*geneList));
        labelList.push_back(doc.object()["results"].toObject()["result"].toArray().first().toObject()["term"].toObject()["label"].toString().toStdString());
        }
    } return labelList;
}

void printExample() {
}

void test() {}
