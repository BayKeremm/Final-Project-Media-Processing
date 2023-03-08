#include "energy_graphics_view.h"
#include <QFont>
#include <QPainter>
#include <QPainterPath>

EnergyGraphicsView::EnergyGraphicsView(MainWindow *parent)
    : QProgressBar(parent) {
  setGeometry(70, 10, 220, 30);
  setMaximum(100);
}

void EnergyGraphicsView::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  int borde = height() / 10;

  draw(&painter, QRect(borde, borde, width() - 2 * borde, height() - 2 * borde),
       2 * borde);

  painter.drawText(rect(), Qt::AlignCenter, QString("%1").arg(value()));
}

void EnergyGraphicsView::draw(QPainter *painter, QRect rect, int w) {

  int w_percentage = 2 * w + value() * (rect.width() - 2 * w) / maximum();

  // progress
  QColor progressColor = QColor(0, 255, 0); // green
  painter->setBrush(QBrush(progressColor));
  drawEllipticalRectangle(
      painter, QRect(rect.topLeft(), QSize(w_percentage, rect.height())), w);
  // background
  QColor backgroundColor = QColor(255, 255, 255); // white
  painter->setBrush(QBrush(backgroundColor));
  drawEllipticalRectangle(
      painter,
      QRect(QPoint(rect.topLeft() + QPoint(w_percentage - 2 * w, 0)),
            QSize(rect.width() - w_percentage + 2 * w, rect.height())),
      w);
  painter->setBrush(QBrush(backgroundColor));
  painter->drawEllipse(QRect(rect.topLeft() + QPoint(rect.width() - 2 * w, 0),
                             QSize(2 * w, rect.height())));
}

void EnergyGraphicsView::drawEllipticalRectangle(QPainter *painter, QRect rect,
                                                 int w) {
  painter->translate(rect.topLeft());

  QPainterPath path;

  path.moveTo(w, 0);
  path.arcTo(QRectF(0, 0, 2 * w, rect.height()), 90, 180);
  path.lineTo(rect.width() - w, rect.height());

  path.arcTo(QRectF(rect.width() - 2 * w, 0, 2 * w, rect.height()), 270, -180);
  path.lineTo(w, 0);
  painter->drawPath(path);

  painter->translate(-rect.topLeft());
}
