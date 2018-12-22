#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
 _createActions();
 _createMenus();
 _createToolbars();
 _connectActions();

  QGraphicsView *view = new QGraphicsView();
  _area= new SceneArea (0,0,600,800,this);
  
  view->setScene(_area);
  setCentralWidget(view);
  statusBar()->showMessage(tr("Ready"));

  _signalMapper = new QSignalMapper(this);
  _signalMapper->setMapping(_freehandAct, TOOLS_ID_FREEHAND);
  _signalMapper->setMapping(_lineAct, TOOLS_ID_LINE);
    _signalMapper->setMapping(_rectangleAct, TOOLS_ID_RECTANGLE);
  _signalMapper->setMapping(_ellipseAct, TOOLS_ID_CIRCLE);
    _signalMapper->setMapping(_polygoneAct, TOOLS_ID_POLYGON);
  _signalMapper->setMapping(_textAct, TOOLS_ID_TEXT);


_signalMapperStyle = new QSignalMapper(this);
  _signalMapperStyle->setMapping(_lineAction, Qt::SolidLine);
  _signalMapperStyle->setMapping(_dashAction, Qt::DashLine);


  _connectSignals();
}


void MainWindow::_createMenus(void) {
  QMenuBar* menubar = menuBar();
  _fileMenu = menubar->addMenu( tr("&File") );
  _toolMenu = menubar->addMenu("&Tools");
  _styleMenu = menubar->addMenu(tr("&Style"));
  _helpMenu = menubar->addMenu( tr("&Help") );

}

void MainWindow::_createToolbars(void) {
  _toolBar = addToolBar( tr("File") );
}

void MainWindow::_createActions(void) {
 _newAction = new QAction( QIcon(":/Images/new.png"), tr("&New..."), this );
 _newAction->setShortcut( tr("Ctrl+N") );
 _newAction->setToolTip( tr("New Tooltip") );
 _newAction->setStatusTip( tr("New Status") );
 _newAction->setData(QVariant("New data to process"));

  _openAction = new QAction(QIcon(":/Images/open.png"),tr("&Open..."), this );
 _openAction->setShortcut( tr("Ctrl+O") );
 _openAction->setToolTip( tr("Load Tooltip") );
 _openAction->setStatusTip( tr("Load Status") );
 _openAction->setData(QVariant("Load data to process"));

  _saveAction = new QAction(QIcon(":/Images/save.png"),tr("&Save"), this );
 _saveAction->setShortcut( tr("Ctrl+S") );
 _saveAction->setToolTip( tr("Save Tooltip") );
 _saveAction->setStatusTip( tr("Save Status") );
 _saveAction->setData(QVariant("Save data"));

   _saveasAction = new QAction(tr("&Save As"), this );
 _saveasAction->setShortcut( tr("Maj+Ctrl+S") );
 _saveasAction->setToolTip( tr("Save As Tooltip") );
 _saveasAction->setStatusTip( tr("Save AS Status") );
 _saveasAction->setData(QVariant("Save as data"));

 _exitAction = new QAction(tr("&Exit"), this );
 _exitAction->setShortcut( tr("Ctrl+Q") );
 _exitAction->setToolTip( tr("Exit Tooltip") );
 _exitAction->setStatusTip( tr("Exit Status") );
 _exitAction->setData(QVariant("Exit data"));


 _aboutAction = new QAction(tr("About"), this);
 _aboutAction->setShortcut(tr("Ctrl+A"));
 _aboutAction->setStatusTip(tr("It' a beautiful work"));
 _aboutQtAction = new QAction(tr("About Qt"), this);
 _aboutAction->setShortcut(tr("Ctrl+Q"));
 _aboutQtAction->setStatusTip(tr("Thank's a lot, you're so cute !"));

  _toolsQag = new QActionGroup( this );
  _freehandAct = new QAction(tr("&Freehand"),  this);
  _lineAct = new QAction(tr("&Line"), this);
  _rectangleAct = new QAction(tr("&Rectangle"),  this);
  _ellipseAct = new QAction(tr("&Ellipse"),  this);
  _polygoneAct = new QAction(tr("&Polygon"),  this);
  _textAct = new QAction(tr("&Text"),  this);

  _freehandAct->setCheckable(true);
  _lineAct->setCheckable(true);
   _rectangleAct->setCheckable(true);
  _ellipseAct->setCheckable(true);
  _polygoneAct->setCheckable(true);
  _textAct->setCheckable(true);



_penStylesQag = new QActionGroup(this);
_lineAction = new QAction(tr("&Solid line"), this );
_dashAction = new QAction(tr("&Dash line"), this );
_colorAction = new QAction(tr("&Color"), this );
 _brushAction = new QAction(tr("&Brush Color"), this );
 //_penAction = new QAction(tr("&Pen"), this );
//_fillAction = new QAction(tr("&Fill"), this );
// _fontAction = new QAction(tr("&Font"), this );

 _lineAction->setCheckable(true);
 _dashAction->setCheckable(true);
  _lineAction->setChecked(true);


}

void MainWindow::_connectActions(void) {
 _fileMenu->addAction( _newAction );
  _fileMenu->addSeparator();
 _fileMenu->addAction( _openAction );
_fileMenu->addAction( _saveAction );
_fileMenu->addAction( _saveasAction );
 _fileMenu->addSeparator();
_fileMenu->addAction( _exitAction);

 _helpMenu->addAction(_aboutAction);
 _helpMenu->addAction(_aboutQtAction);
 _toolBar->addAction(_newAction);
 _toolBar->addAction(_openAction);
  _toolBar->addAction(_saveAction);
 

 _toolsQag->addAction(_freehandAct);
 _toolsQag->addAction(_lineAct);
 _toolsQag->addAction(_rectangleAct);
 _toolsQag->addAction(_ellipseAct);
  _toolsQag->addAction(_polygoneAct);
  
 _toolsQag->addAction(_textAct);

 _toolMenu->addAction(_freehandAct);
 _toolMenu->addAction(_lineAct);
  _toolMenu->addAction(_rectangleAct);
 _toolMenu->addAction(_ellipseAct);
  _toolMenu->addAction(_polygoneAct);
 _toolMenu->addAction(_textAct);

 _penLineMenu = _styleMenu->addMenu(tr("&Line"));


  _penLineMenu->addAction(_lineAction);
 _penLineMenu->addAction(_dashAction);
   _styleMenu->addSeparator();
    _styleMenu->addAction(_colorAction);
  _styleMenu->addAction(_brushAction);


  _penStylesQag->addAction(_lineAction);
  _penStylesQag->addAction(_dashAction);
    //_styleMenu->addAction( _penAction );
 //_styleMenu->addAction(_fillAction);
 //_styleMenu->addAction(_fontAction);


}

void MainWindow::_connectSignals(void) {
 connect( _newAction, SIGNAL(triggered( )), this, SLOT(_newFile( )) );
  connect( _openAction, SIGNAL(triggered( )), this, SLOT(_loadMessage( )) );
   connect( _saveAction, SIGNAL(triggered( )), this, SLOT(_saveMessage( )) );
    connect( _saveasAction, SIGNAL(triggered( )), this, SLOT(_saveAs( )) );
     connect( _exitAction, SIGNAL(triggered( )), this, SLOT(_exit()) );

 connect(_aboutAction, SIGNAL(triggered()), this, SLOT(_about()));
 connect(_aboutQtAction, SIGNAL(triggered()), this, SLOT(_aboutQt()));

 connect(_freehandAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_lineAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_rectangleAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_ellipseAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_polygoneAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_textAct,SIGNAL(activated()),_signalMapper, SLOT(map()));


  //connect( _penAction, SIGNAL(triggered( )), this, SLOT(map( )) );
  connect( _colorAction, SIGNAL(triggered( )), this, SLOT(_color( )) );
  connect( _lineAction, SIGNAL(activated( )), _signalMapperStyle, SLOT(map()) );
  connect( _dashAction, SIGNAL(activated( )), _signalMapperStyle, SLOT(map()) );
  connect( _brushAction, SIGNAL(triggered( )), this, SLOT(_brushcolor()) );
  //connect( _fillAction, SIGNAL(triggered( )), this, SLOT(map()) );
 // connect( _fontAction, SIGNAL(triggered( )), this, SLOT(_exit()) );

  connect(_colorDialogBox, SIGNAL(colorSelected(const QColor &)), _area, SLOT(_saveColor(QColor)));
  connect(_brush_colorDialogBox, SIGNAL(colorSelected(const QColor &)), _area, SLOT(_saveBrushColor(QColor)));

  connect(_signalMapperStyle, SIGNAL(mapped(int)), this, SIGNAL(penStyleMapped(int)));
   connect(this, SIGNAL(penStyleMapped(int)), _area, SLOT(setPenStyle(int)));
 

  connect(_signalMapper,SIGNAL(mapped(int)), this, SIGNAL(toolMapped(int)));
  connect(this, SIGNAL(toolMapped(int)), _area, SLOT(setCurrentTool(int)) );

_endPolygonAction = new QAction(tr("&Close polygon"), this);
    _endPolygonAction->setEnabled(false);

  connect(_endPolygonAction, SIGNAL(triggered()), this, SLOT(endPolygon()));
  connect(_area, SIGNAL(startPolygon()), this, SLOT(enableEndPolygonAction()));

  connect(this, SIGNAL(cleanArea()), _area, SLOT(clear()));

}

void MainWindow::_color() {
    _colorDialogBox->setVisible(true);
}
void MainWindow::_brushcolor() {
    _brush_colorDialogBox->setVisible(true);
}





void MainWindow::_saveMessage(){
    bool ok;
    QString text = QInputDialog::getText(this, tr("Save..."),tr("File name:"),
            QLineEdit::Normal,"saveFile", &ok);
    if (ok && !text.isEmpty()){
        this->_save(text);
    }
}

void MainWindow::_loadMessage(){

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open graphic"), QDir::currentPath(), tr("XML files(*.xml)"));
    qDebug() << fileName ;
    if (!fileName.isEmpty()){
        this->_load(fileName); 
    }

}

int MainWindow::_load(QString path){

    emit cleanArea();

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Not Read" ;
        return -1;
    }
    QXmlStreamReader xmlReader;  
    xmlReader.setDevice(&file);
    while (!xmlReader.atEnd()) {
        if(xmlReader.isStartElement()) {
            if ( xmlReader.name()== "GraphicsItem") {  
//                 qDebug() << "graphics";
                int type =  xmlReader.attributes().value("type").toString().toInt();
                if (type == 3){
                    auto x = xmlReader.attributes().value("x").toString().toInt();
                    auto y = xmlReader.attributes().value("y").toString().toInt();
                    auto w = xmlReader.attributes().value("w").toString().toInt();
                    auto h = xmlReader.attributes().value("h").toString().toInt();
                    auto lineStyle = xmlReader.attributes().value("lineStyle").toString().toInt();
                    auto lineColorR = xmlReader.attributes().value("lineColorR").toString().toInt();
                    auto lineColorG = xmlReader.attributes().value("lineColorG").toString().toInt();
                    auto lineColorB = xmlReader.attributes().value("lineColorB").toString().toInt();
                    auto lineColorA = xmlReader.attributes().value("lineColorA").toString().toInt(); 
        auto brushColorR = xmlReader.attributes().value("brushColorR").toString().toInt();
                    auto brushColorG = xmlReader.attributes().value("brushColorG").toString().toInt();
                    auto brushColorB = xmlReader.attributes().value("brushColorB").toString().toInt();
                    auto brushColorA = xmlReader.attributes().value("brushColorA").toString().toInt();  
        
                    QPen pen(QColor(lineColorR,lineColorG,lineColorB,lineColorA));
        pen.setStyle(Qt::PenStyle(lineStyle));
        QBrush brush(QColor(brushColorR,brushColorG,brushColorB,brushColorA));
                    _area->addRect(x,y,w,h,pen,brush);
                }
                else if (type == 4){
                    auto x = xmlReader.attributes().value("x").toString().toInt();
                    auto y = xmlReader.attributes().value("y").toString().toInt();
                    auto w = xmlReader.attributes().value("w").toString().toInt();
                    auto h = xmlReader.attributes().value("h").toString().toInt();
                    auto lineStyle = xmlReader.attributes().value("lineStyle").toString().toInt();
                    auto lineColorR = xmlReader.attributes().value("lineColorR").toString().toInt();
                    auto lineColorG = xmlReader.attributes().value("lineColorG").toString().toInt();
                    auto lineColorB = xmlReader.attributes().value("lineColorB").toString().toInt();
                    auto lineColorA = xmlReader.attributes().value("lineColorA").toString().toInt();
        auto brushColorR = xmlReader.attributes().value("brushColorR").toString().toInt();
                    auto brushColorG = xmlReader.attributes().value("brushColorG").toString().toInt();
                    auto brushColorB = xmlReader.attributes().value("brushColorB").toString().toInt();
                    auto brushColorA = xmlReader.attributes().value("brushColorA").toString().toInt();  

                    QPen pen(QColor(lineColorR,lineColorG,lineColorB,lineColorA));
        pen.setStyle((Qt::PenStyle)lineStyle);
        QBrush brush(QColor(brushColorR,brushColorG,brushColorB,brushColorA));
                    _area->addEllipse(x,y,w,h,pen,brush);
                }
                else if (type == 5){
                    auto x = xmlReader.attributes().value("x").toString();
                    auto y = xmlReader.attributes().value("y").toString();
                    auto lineStyle = xmlReader.attributes().value("lineStyle").toString().toInt();
                    auto lineColorR = xmlReader.attributes().value("lineColorR").toString().toInt();
                    auto lineColorG = xmlReader.attributes().value("lineColorG").toString().toInt();
                    auto lineColorB = xmlReader.attributes().value("lineColorB").toString().toInt();
                    auto lineColorA = xmlReader.attributes().value("lineColorA").toString().toInt();  
        auto brushColorR = xmlReader.attributes().value("brushColorR").toString().toInt();
                    auto brushColorG = xmlReader.attributes().value("brushColorG").toString().toInt();
                    auto brushColorB = xmlReader.attributes().value("brushColorB").toString().toInt();
                    auto brushColorA = xmlReader.attributes().value("brushColorA").toString().toInt();  
        
                    QPen pen(QColor(lineColorR,lineColorG,lineColorB,lineColorA));
        pen.setStyle(Qt::PenStyle(lineStyle));
        QBrush brush(QColor(brushColorR,brushColorG,brushColorB,brushColorA));
        
                    auto xs = x.split(",");
                    auto ys = y.split(",");

                    if (xs.count() == ys.count()){
                        QPolygonF _polygon;
                        for (int i=0; i<xs.count(); i++){
                            _polygon << QPointF(xs[i].toInt(), ys[i].toInt());
                        }
                        _area->addPolygon(_polygon,pen,brush);
                    }
                }
                else if (type == 6){
                    auto x = xmlReader.attributes().value("x").toString().toInt();
                    auto y = xmlReader.attributes().value("y").toString().toInt();
                    auto w = xmlReader.attributes().value("w").toString().toInt();
                    auto h = xmlReader.attributes().value("h").toString().toInt();
                    auto lineStyle = xmlReader.attributes().value("lineStyle").toString().toInt();
                    auto lineColorR = xmlReader.attributes().value("lineColorR").toString().toInt();
                    auto lineColorG = xmlReader.attributes().value("lineColorG").toString().toInt();
                    auto lineColorB = xmlReader.attributes().value("lineColorB").toString().toInt();
                    auto lineColorA = xmlReader.attributes().value("lineColorA").toString().toInt();  

                    QPen pen(QColor(lineColorR,lineColorG,lineColorB,lineColorA));
        pen.setStyle(Qt::PenStyle(lineStyle));
                    _area->addLine(x,y,w,h,pen);
                }
                else if(type==8){
                    auto text = xmlReader.attributes().value("text").toString();
                    auto font = xmlReader.attributes().value("fontFamily").toString();
                    auto x = xmlReader.attributes().value("x").toString().toInt();
                    auto y = xmlReader.attributes().value("y").toString().toInt();
                    auto colorR = xmlReader.attributes().value("colorR").toString().toInt();
                    auto colorG = xmlReader.attributes().value("colorG").toString().toInt();
                    auto colorB = xmlReader.attributes().value("colorB").toString().toInt();
                    auto colorA = xmlReader.attributes().value("colorA").toString().toInt();

                    auto item = _area->addText(text, QFont(font));
                    ((QGraphicsTextItem*)item)->setDefaultTextColor(QColor(colorR,colorG,colorB,colorA));
                    item->setPos(x, y);
                }
            }
        }
        xmlReader.readNext();
    }

    return 1;
}
int MainWindow::_save(QString name) {
    name = "//" + name + ".xml";
    QString fileName(QDir::currentPath().append(name));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return -1;
    }
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Scene");
    xmlWriter.writeAttribute("version", "v1.0");
    xmlWriter.writeStartElement("GraphicsItemList");
    qreal width, height, x, y;
    for (int i =0; i< _area->items().size();i++) {
        xmlWriter.writeStartElement("GraphicsItem");
        int number=_area->items().value(i)->type();
        xmlWriter.writeAttribute("type", QString::number(number));
        if (number == 3){
            qDebug() << "Rectangle";
            QGraphicsRectItem *rectangle;
            rectangle = qgraphicsitem_cast<QGraphicsRectItem*>(_area->items().value(i));
            x = rectangle->rect().x() + rectangle->x();
            y = rectangle->rect().y() + rectangle->y();
            width = rectangle->rect().width();
            height = rectangle->rect().height();
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("w", QString::number(width));
            xmlWriter.writeAttribute("h", QString::number(height));
            xmlWriter.writeAttribute("lineStyle", QString::number(rectangle->pen().style()));
            xmlWriter.writeAttribute("lineColorR", QString::number(rectangle->pen().color().red()));
            xmlWriter.writeAttribute("lineColorG", QString::number(rectangle->pen().color().green()));
            xmlWriter.writeAttribute("lineColorB", QString::number(rectangle->pen().color().blue()));
            xmlWriter.writeAttribute("lineColorA", QString::number(rectangle->pen().color().alpha()));
      xmlWriter.writeAttribute("brushColorR", QString::number(rectangle->brush().color().red()));
            xmlWriter.writeAttribute("brushColorG", QString::number(rectangle->brush().color().green()));
            xmlWriter.writeAttribute("brushColorB", QString::number(rectangle->brush().color().blue()));
            xmlWriter.writeAttribute("brushColorA", QString::number(rectangle->brush().color().alpha()));
        }
        else if (number ==4){
            qDebug() << "Ellipse";
            QGraphicsEllipseItem *ellipse;
            ellipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(_area->items().value(i));
            x = ellipse->rect().x() + ellipse->x();
            y = ellipse->rect().y() + ellipse->y();
            width = ellipse->rect().width();
            height = ellipse->rect().height();
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("w", QString::number(width));
            xmlWriter.writeAttribute("h", QString::number(height));
            xmlWriter.writeAttribute("lineStyle", QString::number(ellipse->pen().style()));
            xmlWriter.writeAttribute("lineColorR", QString::number(ellipse->pen().color().red()));
            xmlWriter.writeAttribute("lineColorG", QString::number(ellipse->pen().color().green()));
            xmlWriter.writeAttribute("lineColorB", QString::number(ellipse->pen().color().blue()));
            xmlWriter.writeAttribute("lineColorA", QString::number(ellipse->pen().color().alpha()));
      xmlWriter.writeAttribute("brushColorR", QString::number(ellipse->brush().color().red()));
            xmlWriter.writeAttribute("brushColorG", QString::number(ellipse->brush().color().green()));
            xmlWriter.writeAttribute("brushColorB", QString::number(ellipse->brush().color().blue()));
            xmlWriter.writeAttribute("brushColorA", QString::number(ellipse->brush().color().alpha()));
        }
        else if(number==6){
            qDebug() << "Line";
            QGraphicsLineItem *line;
            line = qgraphicsitem_cast<QGraphicsLineItem*>(_area->items().value(i));
            x = line->line().x1();
            y = line->line().y1();
            width = line->line().x2();
            height = line->line().y2();
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("w", QString::number(width));
            xmlWriter.writeAttribute("h", QString::number(height));
            xmlWriter.writeAttribute("lineStyle", QString::number(line->pen().style()));
            xmlWriter.writeAttribute("lineColorR", QString::number(line->pen().color().red()));
            xmlWriter.writeAttribute("lineColorG", QString::number(line->pen().color().green()));
            xmlWriter.writeAttribute("lineColorB", QString::number(line->pen().color().blue()));
            xmlWriter.writeAttribute("lineColorA", QString::number(line->pen().color().alpha()));
        }
        else if(number==8){
            qDebug() << "Text";
            QGraphicsTextItem * text;
            text = qgraphicsitem_cast<QGraphicsTextItem*>(_area->items().value(i));
            x = text->x();
            y = text->y();
            xmlWriter.writeAttribute("text", text->toPlainText());
            xmlWriter.writeAttribute("fontFamily", text->font().family());
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("colorR", QString::number(text->defaultTextColor().red()));
            xmlWriter.writeAttribute("colorG", QString::number(text->defaultTextColor().green()));
            xmlWriter.writeAttribute("colorB", QString::number(text->defaultTextColor().blue()));
            xmlWriter.writeAttribute("colorA", QString::number(text->defaultTextColor().alpha()));

        }
        else if (number == 5){
            qDebug() << "Polygon";
            QGraphicsPolygonItem *polygon;
            polygon = qgraphicsitem_cast<QGraphicsPolygonItem*>(_area->items().value(i));

            QString xp,yp;
            for (int j=0; j< polygon->polygon().count(); j++){
                if( xp != ""){
                    xp = xp + ",";}
                xp = xp  +  QString::number(polygon->polygon()[j].x());
                if( yp != ""){
                    yp = yp + ",";}
                yp = yp  +  QString::number(polygon->polygon()[j].y()); 
            }
            xmlWriter.writeAttribute("x", xp);
            xmlWriter.writeAttribute("y", yp);
            xmlWriter.writeAttribute("lineStyle", QString::number(polygon->pen().style()));
            xmlWriter.writeAttribute("lineColorG", QString::number(polygon->pen().color().green()));
            xmlWriter.writeAttribute("lineColorB", QString::number(polygon->pen().color().blue()));
            xmlWriter.writeAttribute("lineColorA", QString::number(polygon->pen().color().alpha()));
      xmlWriter.writeAttribute("brushColorR", QString::number(polygon->brush().color().red()));
            xmlWriter.writeAttribute("brushColorG", QString::number(polygon->brush().color().green()));
            xmlWriter.writeAttribute("brushColorB", QString::number(polygon->brush().color().blue()));
            xmlWriter.writeAttribute("brushColorA", QString::number(polygon->brush().color().alpha()));
  }

        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    file.close();
    return 1;
}

int MainWindow::_saveAs(void) {
 qDebug() << "MainWindow::saveAs(void)";
 QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("XML files (*.xml)"));
 

  fileName = "//" + fileName + ".xml";
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return -1;
    }
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Scene");
    xmlWriter.writeAttribute("version", "v1.0");
    xmlWriter.writeStartElement("GraphicsItemList");
    qreal width, height, x, y;
    for (int i =0; i< _area->items().size();i++) {
        xmlWriter.writeStartElement("GraphicsItem");
        int number=_area->items().value(i)->type();
        xmlWriter.writeAttribute("type", QString::number(number));
        if (number == 3){
            qDebug() << "Rectangle";
            QGraphicsRectItem *rectangle;
            rectangle = qgraphicsitem_cast<QGraphicsRectItem*>(_area->items().value(i));
            x = rectangle->rect().x() + rectangle->x();
            y = rectangle->rect().y() + rectangle->y();
            width = rectangle->rect().width();
            height = rectangle->rect().height();
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("w", QString::number(width));
            xmlWriter.writeAttribute("h", QString::number(height));
            xmlWriter.writeAttribute("lineStyle", QString::number(rectangle->pen().style()));
            xmlWriter.writeAttribute("lineColorR", QString::number(rectangle->pen().color().red()));
            xmlWriter.writeAttribute("lineColorG", QString::number(rectangle->pen().color().green()));
            xmlWriter.writeAttribute("lineColorB", QString::number(rectangle->pen().color().blue()));
            xmlWriter.writeAttribute("lineColorA", QString::number(rectangle->pen().color().alpha()));
      xmlWriter.writeAttribute("brushColorR", QString::number(rectangle->brush().color().red()));
            xmlWriter.writeAttribute("brushColorG", QString::number(rectangle->brush().color().green()));
            xmlWriter.writeAttribute("brushColorB", QString::number(rectangle->brush().color().blue()));
            xmlWriter.writeAttribute("brushColorA", QString::number(rectangle->brush().color().alpha()));
        }
        else if (number ==4){
            qDebug() << "Ellipse";
            QGraphicsEllipseItem *ellipse;
            ellipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(_area->items().value(i));
            x = ellipse->rect().x() + ellipse->x();
            y = ellipse->rect().y() + ellipse->y();
            width = ellipse->rect().width();
            height = ellipse->rect().height();
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("w", QString::number(width));
            xmlWriter.writeAttribute("h", QString::number(height));
            xmlWriter.writeAttribute("lineStyle", QString::number(ellipse->pen().style()));
            xmlWriter.writeAttribute("lineColorR", QString::number(ellipse->pen().color().red()));
            xmlWriter.writeAttribute("lineColorG", QString::number(ellipse->pen().color().green()));
            xmlWriter.writeAttribute("lineColorB", QString::number(ellipse->pen().color().blue()));
            xmlWriter.writeAttribute("lineColorA", QString::number(ellipse->pen().color().alpha()));
      xmlWriter.writeAttribute("brushColorR", QString::number(ellipse->brush().color().red()));
            xmlWriter.writeAttribute("brushColorG", QString::number(ellipse->brush().color().green()));
            xmlWriter.writeAttribute("brushColorB", QString::number(ellipse->brush().color().blue()));
            xmlWriter.writeAttribute("brushColorA", QString::number(ellipse->brush().color().alpha()));
        }
        else if(number==6){
            qDebug() << "Line";
            QGraphicsLineItem *line;
            line = qgraphicsitem_cast<QGraphicsLineItem*>(_area->items().value(i));
            x = line->line().x1();
            y = line->line().y1();
            width = line->line().x2();
            height = line->line().y2();
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("w", QString::number(width));
            xmlWriter.writeAttribute("h", QString::number(height));
            xmlWriter.writeAttribute("lineStyle", QString::number(line->pen().style()));
            xmlWriter.writeAttribute("lineColorR", QString::number(line->pen().color().red()));
            xmlWriter.writeAttribute("lineColorG", QString::number(line->pen().color().green()));
            xmlWriter.writeAttribute("lineColorB", QString::number(line->pen().color().blue()));
            xmlWriter.writeAttribute("lineColorA", QString::number(line->pen().color().alpha()));
        }
        else if(number==8){
            qDebug() << "Text";
            QGraphicsTextItem * text;
            text = qgraphicsitem_cast<QGraphicsTextItem*>(_area->items().value(i));
            x = text->x();
            y = text->y();
            xmlWriter.writeAttribute("text", text->toPlainText());
            xmlWriter.writeAttribute("fontFamily", text->font().family());
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("colorR", QString::number(text->defaultTextColor().red()));
            xmlWriter.writeAttribute("colorG", QString::number(text->defaultTextColor().green()));
            xmlWriter.writeAttribute("colorB", QString::number(text->defaultTextColor().blue()));
            xmlWriter.writeAttribute("colorA", QString::number(text->defaultTextColor().alpha()));

        }
        else if (number == 5){
            qDebug() << "Polygon";
            QGraphicsPolygonItem *polygon;
            polygon = qgraphicsitem_cast<QGraphicsPolygonItem*>(_area->items().value(i));

            QString xp,yp;
            for (int j=0; j< polygon->polygon().count(); j++){
                if( xp != ""){
                    xp = xp + ",";}
                xp = xp  +  QString::number(polygon->polygon()[j].x());
                if( yp != ""){
                    yp = yp + ",";}
                yp = yp  +  QString::number(polygon->polygon()[j].y()); 
            }
            xmlWriter.writeAttribute("x", xp);
            xmlWriter.writeAttribute("y", yp);
            xmlWriter.writeAttribute("lineStyle", QString::number(polygon->pen().style()));
            xmlWriter.writeAttribute("lineColorG", QString::number(polygon->pen().color().green()));
            xmlWriter.writeAttribute("lineColorB", QString::number(polygon->pen().color().blue()));
            xmlWriter.writeAttribute("lineColorA", QString::number(polygon->pen().color().alpha()));
      xmlWriter.writeAttribute("brushColorR", QString::number(polygon->brush().color().red()));
            xmlWriter.writeAttribute("brushColorG", QString::number(polygon->brush().color().green()));
            xmlWriter.writeAttribute("brushColorB", QString::number(polygon->brush().color().blue()));
            xmlWriter.writeAttribute("brushColorA", QString::number(polygon->brush().color().alpha()));
  }

        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    file.close();
    return 1;
 
 return -1;
}
void MainWindow::setEnabledEndPolygonAction(bool enabled) {
    _endPolygonAction->setEnabled(enabled);
}

void MainWindow::enableEndPolygonAction() {
    setEnabledEndPolygonAction(true);
}
void MainWindow::disableEndPolygonAction() {
    setEnabledEndPolygonAction(false);
}

void MainWindow::endPolygon(void) {
    qDebug() << "main endPolygon";
    _area->endPolygon();
    setEnabledEndPolygonAction(false);
}



void MainWindow::_newFile(void) {
   qDebug() << "MainWindow::newFile(void)";
 qDebug() << "Date : " << QDate::currentDate();
 QString str = _newAction->data().toString();
 qDebug() << str ;
 statusBar()->showMessage(str);
 QMessageBox::StandardButton reply = QMessageBox::warning(
  this, "Create a new file ?", "You have some unsaved work, are you sure you want to start anew ?", 
  QMessageBox::Yes|QMessageBox::No
  );
  if (reply == QMessageBox::Yes) { 
    emit cleanArea();
  }




}

void MainWindow::_exit(void) {
  qDebug()<< "MainWindow::_exit(void)" ;
  QMessageBox::StandardButton reply = QMessageBox::question(
  this, 
  "Quit?", 
  "Are you sure you want to quit?", 
  QMessageBox::Yes|QMessageBox::No
  );
  if (reply == QMessageBox::Yes) { close(); }
}

void MainWindow::_about() {
 qDebug()<< "MainWindow::_aboutUs()" ;
 QMessageBox::information( this,
                           "Editeur graphique Version 0.1",
                           "ENIB module CAI 2, Copyright 2018: \n JALLOULI Khaled",
                           "Go back to work !");
}

void MainWindow::_aboutQt() {
 qDebug()<< "MainWindow::_aboutQt()" ;
 QMessageBox::aboutQt( this, "A propos de Qt");
 
}

