#ifndef HELPER_H
#define HELPER_H

#include <QVector>
#include <QObject>

class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = nullptr);

signals:

public slots:
    /*генерация игрового поля головоломки
     *return -сгенерированное поле
     */
    QVector<int> newGame();

    /*обход соединённых клеток и их зажжение
     * QVector<int> bricks - сгенерированное поле
     * return - массив с указанием на зажжение соответсвтующих клеток
     */
    QVector<bool> light(QVector<int> bricks);

    /*вспомогательная функция для обхода
     * QVector<int> bricks - сгенерированное поле
     * QVector<bool> *lights - массив с указанием на зажжение соответсвтующих клеток
     * pos - номер клетки поля для обращения
     */
    void recursiveLight(QVector<int> bricks,QVector<bool> *lights,int pos);
};

#endif // HELPER_H
