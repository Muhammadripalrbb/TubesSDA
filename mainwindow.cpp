#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewadmin.h"
#include "viewuser.h" // Include header for the user view

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui = new Ui::MainWindow();
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::loginButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loginButtonClicked()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Username and password cannot be empty!");
        return;
    }

    // Perform login validation here
    if (username == "admin" && password == "adminpass") {
        // Admin login
        QMessageBox::information(this, "Login", "Welcome, Admin!");
        // Proceed to admin view
        ViewAdmin *adminView = new ViewAdmin(this);
        adminView->show();
    } else if (username == "user" && password == "userpass") {
        // User login
        QMessageBox::information(this, "Login", "Welcome, User!");
        // Proceed to user view
        ViewUser *userView = new ViewUser(this);
        userView->show();
    } else {
        QMessageBox::critical(this, "Login Failed", "Invalid username or password!");
    }
}
