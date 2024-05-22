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
#include "KFviewmanager.h"
class KFTEXMainWindow;
class KFViewManager;
class KFTabWidget : public QTabWidget{
    Q_OBJECT
public:
    KFTabWidget(QWidget *parent,KFViewManager *manager,KTextEditor::Editor *editor);
    ~KFTabWidget() override;
    KTextEditor::View *createView(KTextEditor::Document *doc,QString name);
    KTextEditor::View *getactiveTab();  
    KTextEditor::Document *getDocumentFromView(KTextEditor::View *view);
private:
    std::shared_ptr<KFViewManager> m_manager;
    KTextEditor::Editor *m_editor;
private slots:
    void tabChanged();
    void addMath(QString txt);
    void saveFile();
    void openFile();
    void newFile();
};
#endif