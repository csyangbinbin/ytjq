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

	checkTimer->start(5000); //每经过5秒钟时间检验一次验证码
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

	  //枚举所有的iframe框架元素
	  QList<QWebFrame *>	q = f->childFrames () ; 
	  qDebug() <<"frame:" <<q.size() ;

	  QWebFrame* childF = NULL ; 

	  for (int i = 0; i < q.size(); ++i) {
		 QWebFrame *t = q.at(i);
		 QUrl u = t->url() ;
		 qDebug() << i <<" : " <<u.toString() <<" :" <<t->frameName() ; 

		 if(t->frameName().startsWith("xubox_iframe")) //验证码识别框名字以xubox_iframe开头，每次会有不同
			 childF = t ; 

	  }

	  if(childF == NULL)
		  return ; 

	  QWebElement e1 = childF->findFirstElement("#validateImg");
		bool isNULL = e1.isNull() ; 
		qDebug() << "e1:"<<e1.isNull() <<  e1.attribute("src"); ; 

		if(!isNULL)
		{
			//发现验证码
			QImage image(105,25 , QImage::Format_RGB32) ; 
			QPainter painter(&image);
			e1.render(&painter);
			image.save(YZIMG_SAVE_NAME) ;  //保存验证码为JPG格式的图片

			img_parse_result  parse_ret = parseImg(YZIMG_SAVE_NAME) ; //对图片进行OCR识别

			if(parse_ret.parse_success)
			{
				//验证码分析成功
				printf("验证码分析成功:%d   %d\r\n" , parse_ret.first_number , parse_ret.second_number	 ) ; 
			int value = parse_ret.first_number+  parse_ret.second_number ; //验证码每次都是两个数相加

			QString cmd ;
			cmd.sprintf("document.getElementById(\"result\").value=\"%d\"" ,value );
			qDebug() << "CMD:" <<cmd ;
			childF->evaluateJavaScript(cmd) ; //执行JS指令，将结果填入input框中

			//执行模拟点击确定按钮(由于原网页使用了 Jquery库，所以这里使用了Jquery的函数)
			childF->evaluateJavaScript("$(\".queding_btn\").trigger(\"click\");") ;
			}
			else
			{
				//验证码分析失败
				printf("验证码分析失败!\r\n");
			}
		}
}