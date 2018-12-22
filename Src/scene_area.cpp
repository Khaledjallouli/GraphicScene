#include "scene_area.h"
#include <QPolygonF>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsEffect>


SceneArea::SceneArea(qreal x, qreal y, qreal width, qreal height, QObject * parent = 0) : QGraphicsScene(x, y, width, height, parent) {
  qDebug() << "Scene::Scene(void)";

  _startPoint = _endPoint = _offset = QPointF(0,0);
  _parent = parent;

    _item=NULL;
    _tmp_item=NULL;

    _mouse_pressed = false;

    _currentColor = QColor(0,0,0,255);  
    qDebug() << _currentColor;          

    // je commence avec freehand 
    _currentTool = toolsID::TOOLS_ID_FREEHAND;
    ((QWidget*)_parent)->setCursor(Qt::OpenHandCursor);
}




void SceneArea::mousePressEvent(QGraphicsSceneMouseEvent* evt) {
  qDebug() << "Scene::mousePressEvent(void)";
  qDebug() <<  "evt->pos() : " << evt->pos(); 
  qDebug() <<  "evt->scenePos() : " <<  evt->scenePos(); 

    _mouse_pressed = true;

 for (int i =0; i<items().size();i++) {
    items().value(i)->show();
    qDebug() << "item number : " << i;
    qDebug() << "items().value(i)->scenePos() : " << items().value(i)->scenePos();
    qDebug() << "items().value(i)->pos()  : " << items().value(i)->mapToScene(items().value(i)->pos());
  }

_startPoint = _endPoint = evt->scenePos();
  _item=itemAt(_startPoint);
  if (_item) {
    QList<QGraphicsItem *>   items = collidingItems(_item);
    for (int i =0; i< items.size();i++) {
    qDebug() << "colliding item number : " << i;
     //items.value(i)->hide();
    }
    _offset =  _startPoint - _item->pos();
//    _item->setPos(_startPoint - _offset );
//    _item->setPos( _item->pos());
    _item->grabMouse();
  }
 
}

void SceneArea::mouseMoveEvent(QGraphicsSceneMouseEvent* evt) 
{

 //QPen pen(_currentColor);

    _endPoint = evt->scenePos();

    if (_tmp_item != NULL) {
        removeItem(_tmp_item);
        _tmp_item = NULL;
    }

    if (_currentTool == (int)toolsID::TOOLS_ID_POLYGON && !_polygon.empty()) {
        _tmp_item = addLine(_polygon.last().x(),_polygon.last().y(), _endPoint.x(), _endPoint.y(), _pen);
    }
    else if (_mouse_pressed) {
        float x1 = _startPoint.x();
        float y1 = _startPoint.y();
        float w = _endPoint.x() - _startPoint.x();
        float h = _endPoint.y() - _startPoint.y();
        if (w < 0) {
            w = -w;
            x1 = _endPoint.x();
        }
        if (h < 0) {
            h = -h;
            y1 = _endPoint.y();
        }

        switch (_currentTool) {
            case toolsID::TOOLS_ID_FREEHAND:
                if (_item)
                    _item->setPos(_endPoint - _offset);
                break;
            case toolsID::TOOLS_ID_LINE:
                _tmp_item = addLine( _startPoint.x(), _startPoint.y(), _endPoint.x(), _endPoint.y(), _pen);
                break;
            case toolsID::TOOLS_ID_CIRCLE:
                _tmp_item = addEllipse(
                        x1, y1,
                        w, h,
                        _pen
                        );
                break;
            case toolsID::TOOLS_ID_RECTANGLE:
                _tmp_item = addRect(
                        x1, y1,
                        w, h,
                        _pen
                        );
                break;
            default:
                break;
        }
    }




}

void SceneArea::mouseReleaseEvent(QGraphicsSceneMouseEvent* evt) 
{
  qDebug() << "Scene::mouseReleaseEvent(void)";
   _mouse_pressed = false;

    QGraphicsItem *item = NULL;
//QPen pen(_currentColor);

if (_item) {
        if (_currentTool ==  toolsID::TOOLS_ID_FREEHAND) {
            _item->setPos(evt->scenePos() - _offset);
        }
        _item->ungrabMouse();
        _item=NULL;
    }
    else if (_currentTool == toolsID::TOOLS_ID_POLYGON) {
        if (!_polygon.empty()) {
            _polygSideVector << _tmp_item;
        }
        else {
            startPolygon();
        }
        _polygon << _endPoint;
    }
    else if (_startPoint != _endPoint
            && (_currentTool == toolsID::TOOLS_ID_RECTANGLE
                || _currentTool == toolsID::TOOLS_ID_CIRCLE
                || _currentTool == toolsID::TOOLS_ID_LINE)) {
        item = _tmp_item;
    }
    else if (_currentTool == toolsID::TOOLS_ID_TEXT) {
        bool ok;
        QString text = QInputDialog::getText((QWidget*)_parent, tr("Add text"),
                tr("Enter you text :"), QLineEdit::Normal,
                tr("Supercalifragilisticexpialidocious"), &ok);
        if (ok && !text.isEmpty()) {
            item = addText(text);
            ((QGraphicsTextItem*)item)->setDefaultTextColor(_currentColor);
            item->setPos(_startPoint.x(), _startPoint.y() - 12);
        }
    }

    if (item) {
        item->setFlag(QGraphicsItem::ItemIsMovable);
        if (_currentTool != toolsID::TOOLS_ID_TEXT
                && _currentTool != toolsID::TOOLS_ID_LINE) {
            ((QAbstractGraphicsShapeItem*)item)->setBrush(QBrush(_currentBrushColor));
        }
    }

    if (_currentTool == toolsID::TOOLS_ID_FREEHAND)
        ((QWidget*)_parent)->setCursor(Qt::OpenHandCursor);

    _tmp_item = NULL;
 _endPoint = evt->scenePos();
  qDebug() << items().size();
}


void SceneArea::_saveColor(QColor color){
    _currentColor = color;
    qDebug() << _currentColor;
}
void SceneArea::_saveBrushColor(QColor color){
    _currentBrushColor = color;
    qDebug() << _currentBrushColor;
}


void SceneArea::endPolygon(void) {
    //QPen pen(_currentColor);
    QGraphicsItem *poly = addPolygon(_polygon, _pen);
    if (poly)
        poly->setFlag(QGraphicsItem::ItemIsMovable);
    cleanPolygonVars();
}

void SceneArea::cleanPolygonVars(void) {
    qDebug() << "area cleanPol";
    // destroy lines
    while (!_polygSideVector.empty()) {
        removeItem(_polygSideVector.last());
        _polygSideVector.pop_back();
    }
    if (_tmp_item)
        removeItem(_tmp_item);
    _polygon.clear();
    _polygSideVector.clear();
}

void SceneArea::setCurrentTool(int tool) {
      setCurrentTool((toolsID)tool);
}


void SceneArea::setCurrentTool(toolsID tool) {
      QWidget* p = (QWidget*)_parent;
    qDebug() << "Scene::setCurrentTool(toolsID tool)" << tool;
    _currentTool = tool;
    cleanPolygonVars();
    switch(tool) {
        case toolsID::TOOLS_ID_TEXT:
            p->setCursor(Qt::IBeamCursor);
            break;
        case toolsID::TOOLS_ID_FREEHAND:
            p->setCursor(Qt::OpenHandCursor);
            break;
        default:
            p->unsetCursor();
    }
}


void SceneArea::setPenStyle(int penStyle) {
  qDebug() << "Scene::setPenStyle(Qt::PenStyle style)";
  _pen.setColor( QColor(65, 65, 65) );
  _pen.setStyle((Qt::PenStyle)penStyle);
  qDebug() << "Scene::aftersetPenStyle(Qt::PenStyle style)";
}

