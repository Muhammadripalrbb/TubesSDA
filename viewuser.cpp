#include "viewuser.h"
#include "ui_viewuser.h"
#include <QMessageBox>

ViewUser::ViewUser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewUser)
{
    ui->setupUi(this);

    // Inisialisasi model untuk QTableView
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);

    // Inisialisasi kolom pada model
    QStringList headers;
    headers << "ID" << "Nama" << "Umur" << "Tanggal Masuk" << "Tanggal Keluar" << "Kontak Pasien";
    model->setHorizontalHeaderLabels(headers);
}

ViewUser::~ViewUser()
{
    delete ui;
}
void ViewUser::on_addButton_clicked()
{
    QStringList rowData;
    rowData << ui->idLineEdit->text() << ui->nameLineEdit->text() << ui->ageLineEdit->text()
            << ui->entryDateEdit->text() << ui->exitDateEdit->text() << ui->contactLineEdit->text();

    if(rowData.contains("")) {
        QMessageBox::warning(this, "Warning", "Please fill in all fields!");
        return;
    }

    patientsData.push_back(rowData);
    displayData();
}

void ViewUser::displayData()
{
    model->removeRows(0, model->rowCount());
    for(int i = 0; i < patientsData.size(); ++i) {
        QStringList rowData = patientsData[i];
        QList<QStandardItem *> rowItems;
        foreach(QString text, rowData) {
            rowItems.append(new QStandardItem(text));
        }
        model->appendRow(rowItems);
    }
}

int ViewUser::sequentialSearch(const QString& namaCari)
{
    for(int i = 0; i < patientsData.size(); ++i) {
        QStringList rowData = patientsData[i];
        if (rowData.contains(namaCari)) {
            return i;
        }
    }
    return -1;
}

void ViewUser::on_pushButtonCari_clicked()
{
    QString namaCari = ui->searchLineEdit->text();
    int index = sequentialSearch(namaCari);
    if (index != -1) {
        QMessageBox::information(this, "Pencarian Berhasil", QString("ID pasien '%1' ditemukan di indeks %2").arg(namaCari).arg(index));
        ui->tableView->selectRow(index);
    } else {
        QMessageBox::warning(this, "Pencarian Gagal", QString("ID pasien '%1' tidak ditemukan.").arg(namaCari));
    }
}
