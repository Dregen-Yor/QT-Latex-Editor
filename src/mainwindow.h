#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <memory>
#include <QMainWindow>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QTabBar>
#include <QToolBar>
#include <QTextEdit>
#include <QObject>
#include <QFile>
#include <QFileDialog>
#include<qscilexertex.h>
#include<qscilexerlua.h>
#include<qsciscintilla.h>
#include<QMessageBox>
#include <QStatusBar>
#include<QDir>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KTextEditor/View>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::shared_ptr<Ui::MainWindow> ui;
    std::shared_ptr<QsciLexerTeX> texLexer;
    std::shared_ptr<QString> filename[20];
    std::shared_ptr<QTabWidget> tabwidget;
    std::shared_ptr<QsciScintilla> editor[20];
    std::shared_ptr<QsciLexerLua> textLexer;
    std::shared_ptr<QMenu> menuFile, menuHelp,menuTool, menuEdit;
    std::shared_ptr<QAction> actionSave, actionRun, actionOpen, actionUpload, actionDownload;
    std::shared_ptr<QAction> actionNew, actionCopy, actionPaste, actionAbout;
    std::shared_ptr<KTextEditor::Editor> editor_;
    QString currentFile;
    int cnt=0;
private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void runpdf();
    void download();
    void upload();
    void currentTab();
    void on_tabClose(const int x);
private:
    void init(std::shared_ptr<QsciScintilla> textedit);
    int newfile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    bool boolSave();
    bool saveFile(const QString &fileName);
    int currentEditor();
    void loadFile(const QString &fileName);
    QString getname(const int now);
    void createAction();
    void createMenu();
};
#endif // MAINWINDOW_H

