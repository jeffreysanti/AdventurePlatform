#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "textgame.h"
#include "textbuffer.h"
#include "player.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->in->installEventFilter(this);
    game = NULL;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
    ct = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(!game)
	return;
    game->am->Update();
}

void MainWindow::on_in_textChanged()
{
    if(!game)
	return;
    game->textbuffer->InputChanged();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!game)
	return;
   if ((event->text() != "") && (!ui->in->hasFocus())) {
       ui->in->setFocus();
       ui->in->setPlainText(ui->in->toPlainText() + event->text());
   }
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(!game)
	return QMainWindow::eventFilter(obj, event);
    if (obj == ui->in)
    {
	if (event->type() == QEvent::KeyPress)
	{
	    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
	    if(keyEvent->key() == Qt::Key_Up)
	    {
		game->textbuffer->ScrollBuffer(true);
	    }
	    else if(keyEvent->key() == Qt::Key_Down)
	    {
		game->textbuffer->ScrollBuffer(false);
	    }
	    else
	    {
		// pass the event on to the parent class
		return QMainWindow::eventFilter(obj, event);
	    }
	    return true;
	}
	else
	{
	    return false;
	}
    }
    else
    {
	// pass the event on to the parent class
	return QMainWindow::eventFilter(obj, event);
    }
}

void MainWindow::resizeEvent(QResizeEvent * event)
{
    if(!game)
	return;
    game->textbuffer->RecalculateFont();
}

void MainWindow::closeEvent( QCloseEvent * event )
{
    game->textbuffer->bQuit = true;
}
