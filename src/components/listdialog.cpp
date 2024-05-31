#include "listdialog.hpp"

ListDialog::ListDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("List Dialog");
    QVBoxLayout* layout = new QVBoxLayout(this);

    // 创建 QListWidget
    listWidget = new QListWidget(this);
    op=new HttpOperate(this);
    op->GetAll();

    for(int i=1;i<=500;i++);
    layout->addWidget(listWidget);

    connect(listWidget, &QListWidget::itemClicked, this,
            &ListDialog::listItemClicked);
}
ListDialog::~ListDialog() {}

void ListDialog::listItemClicked(QListWidgetItem* item) {
    QString name= item->text();
    QJsonObject json ;
    json["filename"]=name;
    QByteArray jsonData=QJsonDocument(json).toJson();
    op->getContent(jsonData);
}