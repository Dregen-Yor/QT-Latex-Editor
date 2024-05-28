#ifndef KFTEXMAINWINDOW_H
#define KFTEXMAINWINDOW_H
#include <KActionCollection>
#include <KActionMenu>
#include <KLocalizedString>
#include <KParts/MainWindow>
#include <KStandardAction>
#include <KTextEditor/Editor>
#include <KTextEditor/MainWindow>
#include <KTextEditor/Plugin>
#include <QDomDocument>
#include <QEvent>
#include <QFrame>
#include <QKeySequence>
#include <QMenu>
#include <QMenuBar>
#include <QPointer>
#include <QSplitter>
#include <QStackedWidget>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
#include "KFviewmanager.h"
#include <glog/logging.h>
class KFViewManager;
class MainWindow;
class KFTEXMainWindow : public KParts::MainWindow,
                        virtual public KParts::PartBase {
    Q_OBJECT

   public:
    explicit KFTEXMainWindow(QWidget* parent = nullptr);
    ~KFTEXMainWindow() override;

    KTextEditor::MainWindow* wrapper() { return m_wrapper; }
    KFViewManager* viewManager();
    QFrame* centralWidget() const;
    void addRecentOpenedFile(const QUrl &url);

   private:
    KTextEditor::MainWindow* m_wrapper;
    KActionMenu* documentOpenWith = nullptr;

    QFrame* m_centralWidget;
    QAction *run_pdf;
    KFViewManager* m_viewManager = nullptr;
    KRecentFilesAction *m_fileOpenRecent = nullptr;
    void setupMenu();
    QMenu* m_fileMenu;
    QMenu* m_runMenu;
    QMenu* m_AboutMenu;
    KTextEditor::Editor* m_editor = nullptr;
   private:
    void setupMainWindow();
    void setupActions();

   public:
    KTextEditor::Editor* getEditor();
};

#endif