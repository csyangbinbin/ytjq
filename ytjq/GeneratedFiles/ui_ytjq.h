/********************************************************************************
** Form generated from reading UI file 'ytjq.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YTJQ_H
#define UI_YTJQ_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_ytjqClass
{
public:
    QVBoxLayout *verticalLayout;
    QWebView *webView;

    void setupUi(QDialog *ytjqClass)
    {
        if (ytjqClass->objectName().isEmpty())
            ytjqClass->setObjectName(QString::fromUtf8("ytjqClass"));
        ytjqClass->resize(870, 625);
        verticalLayout = new QVBoxLayout(ytjqClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        webView = new QWebView(ytjqClass);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        verticalLayout->addWidget(webView);


        retranslateUi(ytjqClass);

        QMetaObject::connectSlotsByName(ytjqClass);
    } // setupUi

    void retranslateUi(QDialog *ytjqClass)
    {
        ytjqClass->setWindowTitle(QApplication::translate("ytjqClass", "ytjq", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ytjqClass: public Ui_ytjqClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YTJQ_H
