#ifndef UPLOADWINDOW_H
#define UPLOADWINDOW_H

#include <QMainWindow>
#include "MenuWindow.h"
#include "upload_matrix.h"


QT_BEGIN_NAMESPACE
namespace Ui { class UploadWindow; }
QT_END_NAMESPACE

class UploadWindow : public QMainWindow
{
    Q_OBJECT

public:
    UploadWindow(QWidget *parent = nullptr);
    ~UploadWindow();

private slots:
    void on_SelectButton_clicked();
    void on_UploadButton_clicked();

    void close();


private:
    Ui::UploadWindow *ui;

    MenuWindow *PointerMenuWindow;

    QString userText;
    std::string input;

    std::string filename;

    upload_matrix inputData;
    bool readBoolean;
};
#endif // UPLOADWINDOW_H
