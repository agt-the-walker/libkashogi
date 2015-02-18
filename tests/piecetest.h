#include <QtTest/QtTest>

class PieceTest: public QObject
{
    Q_OBJECT

private slots:
    void invalid();
    void invalid_data();

    void invalidBOD();

    void unknownBOD();
    void unknownBOD_data();

    void identity();
    void identity_data();

    void defaultCode();
    void defaultCode_data();

    void invalidCode();
};