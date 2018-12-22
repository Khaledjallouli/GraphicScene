#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>
#include <QActionGroup>
#include <QToolBar>
#include <QMessageBox>
#include <QDate>
#include <QSignalMapper>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QStyle>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QColorDialog>

#include "enums.h"
#include "scene_area.h"

class MainWindow : public QMainWindow
{
Q_OBJECT
  public:
    MainWindow(QWidget *parent = 0);
    void setEnabledEndPolygonAction(bool enabled);
    void disableEndPolygonAction();
  
  public slots:
    void enableEndPolygonAction();
    void endPolygon(void);

  private:
   SceneArea* _area; 
   void _createMenus(void);
   void _createToolbars(void);
   void _createActions(void);
   void _connectActions(void);
   void _connectSignals(void);

   QMenu *_fileMenu, *_toolMenu, *_editMenu, *_styleMenu, *_helpMenu,*_penLineMenu;
   QToolBar *_toolBar;
   QAction *_newAction,*_openAction,*_saveAction, *_saveasAction, *_exitAction;
   QAction *_aboutAction, *_aboutQtAction;
   QAction *_freehandAct, *_lineAct, *_rectangleAct, *_ellipseAct, *_polygoneAct, *_textAct;
   QAction *_penAction , *_colorAction, *_lineAction, *_dashAction, *_brushAction, *_fillAction, *_fontAction ; 
   QActionGroup *_toolsQag, *_penStylesQag;
   QSignalMapper *_signalMapper, *_signalMapperStyle;
QString _filename;

  QAction *_endPolygonAction;
  QColorDialog *_colorDialogBox = new QColorDialog();
  QColorDialog *_brush_colorDialogBox = new QColorDialog();

  private slots :
    void _newFile();
    void _saveMessage();
    int _saveAs();
    void _loadMessage();
    void _color();
    void _brushcolor();
    int _save(QString);
    int _load(QString);
    void _exit();
    void _about();
    void _aboutQt();
  signals:
   void toolMapped(int);
  void penStyleMapped(int);

   void cleanArea();
};
#endif

