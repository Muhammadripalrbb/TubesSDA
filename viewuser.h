#ifndef VIEWUSER_H
#define VIEWUSER_H

#include <QMainWindow>
#include <QString>
#include <QStandardItemModel>
#include <QVector>

namespace Ui {
class ViewUser;
}

class ViewUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewUser(QWidget *parent = nullptr);
    ~ViewUser();

private slots:
    void on_addButton_clicked();
    void on_pushButtonCari_clicked(); // Perbaikan: Ganti nama fungsi pencarian
    void displayData();
    int sequentialSearch(const QString& namaCari); // Perbaikan: Menggunakan nama yang sesuai

private:
    Ui::ViewUser *ui;
    QStandardItemModel *model;
    QVector<QStringList> patientsData;
};

#endif // VIEWUSER_H
