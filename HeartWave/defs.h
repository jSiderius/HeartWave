#ifndef DEFS_H
#define DEFS_H

#include <string>
#include <QDebug>
#include <QLabel>
#include <QFrame>
#include <QBrush>
#include <QTimer>
#include <chrono>
#include <QVector>
#include <QPointF>
#include <QWidget>
#include <numeric>
#include <QPainter>
#include <sys/time.h>
// #include <Eigen/Core>
// #include <Eigen/Dense>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainterPath>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

#define MAX_ARR 256
#define NUM_BUTTONS 4
#define HRV_FRAMES_PER_SECOND 30.0
#define MAX_SESSION_SECONDS 300
#define SECONDS_IN_VIEW 4.0


enum direction {UP, DOWN, LEFT, RIGHT};

#endif
