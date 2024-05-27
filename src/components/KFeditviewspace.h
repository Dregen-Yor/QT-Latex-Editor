#ifndef KFEDITVIEWSPACE_H
#define KFEDITVIEWSPACE_H
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <KTextEditor/View>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <QDir>
#include <QFileDialog>
#include <QString>
#include <QUrl>
#include <QFileInfo>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>   
#include <QTabBar>
#include <QStringLiteral>
#include "../utils/http.h"
#include <KTextEditor/Plugin>
#include <QWidget>
#include "KFviewmanager.h"
class KFTEXMainWindow;
class KFViewManager;
class KFTabWidget : public QTabWidget{
    Q_OBJECT
public:
    KFTabWidget(QWidget *parent,KFViewManager *manager,KTextEditor::Editor *editor);
    ~KFTabWidget() override;
    KTextEditor::View *createView(KTextEditor::Document *doc,QString name);
    QWidget *getactiveTab();  
    KTextEditor::Document *getDocumentFromView(KTextEditor::View *view);
private:
    KFViewManager *m_manager;
    KTextEditor::Editor *m_editor;
public slots:
    void tabChanged();
    void addMath(QString txt);
    void saveFile();
    void openFile();
    void newFile();
    void on_tabWidget_tabCloseRequested(int index);
    void openRecent(QUrl url);
    void sendFile();
};
#endif