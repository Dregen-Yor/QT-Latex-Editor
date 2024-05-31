#ifndef DIALOGLIST_H
#define DIALOGLIST_H
#include <QDialog>
#include <QList>
#include "kftexmainwindow.h"
#include "KFeditviewspace.h"

class HttpOperate;
class ListDialog : public QDialog
{
    Q_OBJECT

public:
    ListDialog(QWidget *parent = nullptr);
    ~ListDialog();
    QList<QString> m_list;
    QListWidget *listWidget;
    
private slots:
    void listItemClicked(QListWidgetItem* item);

private:
    HttpOperate* op;
};
#endif