#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QtWidgets>
#include <QDialog>


class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = nullptr);
    ~FindDialog();

private:
    QLabel      *label;
    QLine       *lineEdit;
    QCheckBox   *caseCheckBox;
    QCheckBox   *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;
};
#endif // FINDDIALOG_H
