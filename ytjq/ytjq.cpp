#include "stdafx.h"
#include "ytjq.h"
#include <QWebFrame>
#include <QWebElement>
#include "utility.h"
#define YZIMG_SAVE_NAME	"validIMG.JPG"

ytjq::ytjq(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	network_cookie_ = new NetworkCookie(this);

	flags |=Qt::WindowMinimizeButtonHint;
	flags |=Qt::WindowMaximizeButtonHint;
	setWindowFlags(flags);

	 webView = ui.webView ; 

	  QWebSettings *settings = QWebSettings::globalSettings();
	  settings->setAttribute(QWebSettings::PluginsEnabled, true);
	  settings->setAttribute(QWebSettings::JavascriptEnabled, true);


	  webView->load(QUrl("http://www.ytjp.com.cn/"));
	  webView->show();

	  webView->page()->networkAccessManager()->setCookieJar(network_cookie_);  

	  checkTimer = new QTimer(this);
	connect( checkTimer,SIGNAL(timeout()), this, SLOT(timeCheck()) );

	checkTimer->start(5000); //ÿ����5����ʱ�����һ����֤��
}

ytjq::~ytjq()
{

}
void	ytjq::timeCheck()
{
	  QWebPage * p = webView->page();
	  if(p==NULL)
		  return ; 

	  QWebFrame *f =  p->mainFrame() ; 
	  if(f==NULL)
		  return ; 

	  //ö�����е�iframe���Ԫ��
	  QList<QWebFrame *>	q = f->childFrames () ; 
	  qDebug() <<"frame:" <<q.size() ;

	  QWebFrame* childF = NULL ; 

	  for (int i = 0; i < q.size(); ++i) {
		 QWebFrame *t = q.at(i);
		 QUrl u = t->url() ;
		 qDebug() << i <<" : " <<u.toString() <<" :" <<t->frameName() ; 

		 if(t->frameName().startsWith("xubox_iframe")) //��֤��ʶ���������xubox_iframe��ͷ��ÿ�λ��в�ͬ
			 childF = t ; 

	  }

	  if(childF == NULL)
		  return ; 

	  QWebElement e1 = childF->findFirstElement("#validateImg");
		bool isNULL = e1.isNull() ; 
		qDebug() << "e1:"<<e1.isNull() <<  e1.attribute("src"); ; 

		if(!isNULL)
		{
			//������֤��
			QImage image(105,25 , QImage::Format_RGB32) ; 
			QPainter painter(&image);
			e1.render(&painter);
			image.save(YZIMG_SAVE_NAME) ;  //������֤��ΪJPG��ʽ��ͼƬ

			img_parse_result  parse_ret = parseImg(YZIMG_SAVE_NAME) ; //��ͼƬ����OCRʶ��

			if(parse_ret.parse_success)
			{
				//��֤������ɹ�
				printf("��֤������ɹ�:%d   %d\r\n" , parse_ret.first_number , parse_ret.second_number	 ) ; 
			int value = parse_ret.first_number+  parse_ret.second_number ; //��֤��ÿ�ζ������������

			QString cmd ;
			cmd.sprintf("document.getElementById(\"result\").value=\"%d\"" ,value );
			qDebug() << "CMD:" <<cmd ;
			childF->evaluateJavaScript(cmd) ; //ִ��JSָ����������input����

			//ִ��ģ����ȷ����ť(����ԭ��ҳʹ���� Jquery�⣬��������ʹ����Jquery�ĺ���)
			childF->evaluateJavaScript("$(\".queding_btn\").trigger(\"click\");") ;
			}
			else
			{
				//��֤�����ʧ��
				printf("��֤�����ʧ��!\r\n");
			}
		}
}