#ifndef YTJQ_H
#define YTJQ_H

#include <QtGui/QDialog>
#include <QTimer>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "ui_ytjq.h"
#include "NetworkCookie.h"

class ytjq : public QDialog
{
	Q_OBJECT
public:
	ytjq(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ytjq();

private slots:
		void	timeCheck() ; 

private:
	Ui::ytjqClass ui;
	QWebView *webView ; 
	QTimer *checkTimer  ;
	NetworkCookie *network_cookie_ ; 
};

#endif // YTJQ_H
