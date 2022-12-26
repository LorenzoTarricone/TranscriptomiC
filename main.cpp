#include "mainwindow.h"

#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

QJsonDocument searchGenes(const QMap<QString, QString>& params)
{
    // create a network manager
    QNetworkAccessManager manager;

    // set up the API URL
    QUrl url("https://clinicaltables.nlm.nih.gov/api/genes/v4/search");

    // create a query object and add the parameters
    QUrlQuery query;
    for (auto it = params.begin(); it != params.end(); ++it) {
        query.addQueryItem(it.key(), it.value());
    }

    // add the query to the URL
    url.setQuery(query);

    // create a request and set the URL
    QNetworkRequest request(url);

    // send the request and get the response
    QNetworkReply *response = manager.get(request);
    auto data = response->readAll();

    // parse the response as a JSON document
    QJsonDocument doc = QJsonDocument::fromJson(data);

    return doc;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Example call
    QMap<QString, QString> params;
    params["term"] = "BRCA1";
    params["exact_match"] = "true";
    QJsonDocument doc = searchGenes(params);
    QString strJson(doc.toJson(QJsonDocument::Indented));
    // print the string to the console

    //try debug
    qDebug() << strJson;
    qDebug("%strJson", qUtf8Printable(strJson));

    //try print
    std::cout<<strJson.toStdString().c_str()<<std::endl;
    fprintf(stderr, "strJson: %s\n", qPrintable(strJson));
    fprintf(stderr, "strJson: %s\n",strJson.toLocal8Bit().constData());
    printf("%s\n", strJson.toStdString().c_str());

    MainWindow w;
    w.show();
    return a.exec();
}
