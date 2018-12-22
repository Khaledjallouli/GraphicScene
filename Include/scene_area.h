#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsEffect>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>
#include <QPolygonF>
#include <QStyle>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QInputDialog>
#include "enums.h"

class SceneArea : public QGraphicsScene
{
  Q_OBJECT  

  public:
   SceneArea( qreal x, qreal y, qreal width, qreal height, QObject * parent);
//   PaintArea(QWidget *parent = 0);
    void endPolygon();
    void cleanPolygonVars();
    void setCurrentTool(toolsID);

  public slots:
    void setCurrentTool(int);
    void setPenStyle(int); 

  protected :
    void mousePressEvent(QGraphicsSceneMouseEvent* );
    void mouseMoveEvent(QGraphicsSceneMouseEvent* );
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* );
    private :
        toolsID _currentTool;
        QPointF  _startPoint,_endPoint, _offset;
        QGraphicsItem * _item;
        QGraphicsItem * _tmp_item;
        bool _mouse_pressed;
        QPolygonF _polygon;
        QVector<QGraphicsItem*> _polygSideVector;
        QColor _currentColor;
        QColor _currentBrushColor;
        QObject* _parent;
        QPen _pen = QPen();
        private slots:
            void _saveColor(QColor color);
            void _saveBrushColor(QColor color);
signals:
        void startPolygon(void);

};
#endif

