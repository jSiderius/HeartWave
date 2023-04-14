#ifndef DEFS_H
#define DEFS_H

#include <QFile>
#include <cmath>
#include <iomanip>
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
#include <fstream>
#include <QObject>
#include <iostream>
#include <QPainter>
#include <unistd.h>
#include <sys/time.h>
#include <QTextStream>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainterPath>

#define MAX_ARR 256
#define NUM_BUTTONS 4
#define HRV_FRAMES_PER_SECOND 20.0
#define MAX_SESSION_SECONDS 300
#define SECONDS_IN_VIEW 60.0
#define COHERENCE_UPDATE_SECS 1

#define MAX_HZ_SINE_WAVE 25.0
#define MIN_HZ_SINE_WAVE 3.846
#define MAX_HZ_SINE_MULT 0.251327
#define MIN_HZ_SINE_MULT 1.63369

#define PEAK_INTEGRAL_HZ 25.0
// #define PEAK_INTEGRAL_HZ 33.333333


enum direction {UP, DOWN, LEFT, RIGHT};

#endif
