#ifndef KFTEXMAINWINDOW_H
#define KFTEXMAINWINDOW_H
#include "kftexmdi.h"
#include <KTextEditor/MainWindow>
#include <KTextEditor/Editor>
#include <KStandardAction>
#include <KActionCollection>
#include <KActionMenu>
#include "KFviewmanager.h"
class KFViewManager;

class KFTEXMainWindow : public KFMDI::MainWindow, virtual public KParts::PartBase{
    Q_OBJECT

public:
    KFTEXMainWindow();
    ~KFTEXMainWindow() override;
    std::shared_ptr<KFViewManager> viewManager()
    {
        return m_viewManager;
    }

    KTextEditor::MainWindow *wrapper()
    {
        return m_wrapper;
    }

private:
    KTextEditor::MainWindow *m_wrapper;
    std::shared_ptr<KActionMenu> documentOpenWith = nullptr;
    bool m_modNotification = false;

    /**
     * Shutdown Kate after last file is closed
     */
    bool m_modCloseAfterLast = false;

    /**
     * keeps track of views
     */
    std::shared_ptr<KFViewManager> m_viewManager = nullptr;
    KTextEditor::Editor *m_editor = nullptr;
private:
    void setupMainWindow();
    void setupActions();
    // void toggleShowMenuBar();
public:
    KTextEditor::Editor *getEditor();
};

#endif