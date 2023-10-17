#ifndef TEST_H
#define TEST_H

#include <QtTest/QTest>

class Test : public QObject
{
    Q_OBJECT
private slots:
    void test1();
    void test2();
    void test3();
public:
};

#endif // TEST_H
