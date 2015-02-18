#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>

class TextAdventureGame;

namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;

    TextAdventureGame *game;

private:

    void resizeEvent(QResizeEvent * event);
    void keyPressEvent(QKeyEvent * event);
    bool eventFilter(QObject *obj, QEvent *ev);

    void closeEvent( QCloseEvent * event );

    void paintEvent(QPaintEvent *event);

    int ct;

public slots:

private slots:
    void on_in_textChanged();

};

#endif // MAINWINDOW_H
