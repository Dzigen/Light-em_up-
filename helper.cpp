#include "helper.h"
#include<cstdlib>
#include <ctime>
#include <QDebug>
#include <QPair>

Helper::Helper(QObject *parent) : QObject(parent)
{

}

QVector<int> Helper::newGame()
{
    /*создаём пустое игровое поле*/
    QVector<int> bricks = {
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,0,
    };

    /*создаём массив для хранения возможных свободных клеток для обращения при случайном выборе*/
    QVector< QPair<int,int> > freeBricks;

    int randomNum;

    /*номер клетки, к которой будет добавлено новое соединение*/
    int fromPos;
    /*номер клетки, которая будет подсоединена*/
    int toPos;

    /*начальная строка и столбец*/
    int basiscolomn=0;
    int basisrow=0;

    int colomn=basiscolomn;
    int row=basisrow;

    /*обрабатываем все 100 клеток*/
    for(int i=0; i<100; i++){

        /*добавляем в массив пар freeBricks возможные соединения , которые может иметь данная клетка в данной позиции поля*/

        /*проверяем,расположена ли клетка внутри поля*/
        if((colomn>0&&colomn<9)&&(row>0&&row<9)){
            if(bricks[ (row+1)*10+colomn ]==0)
                freeBricks.push_back(qMakePair(row*10+colomn,(row+1)*10+colomn));
            if(bricks[ (row-1)*10+colomn ]==0)
                freeBricks.push_back(qMakePair(row*10+colomn,(row-1)*10+colomn));
            if(bricks[ row*10+colomn+1 ]==0)
                freeBricks.push_back(qMakePair(row*10+colomn,row*10+colomn+1));
            if(bricks[ row*10+colomn-1 ]==0)
                freeBricks.push_back(qMakePair(row*10+colomn,row*10+colomn-1));

        /*проверяем,расположена ли клека на границе поля*/
        }else if( (colomn!=0 && colomn!=9) || (row!=0 && row!=9) ){

            if(colomn==0 || colomn==9){
                if(bricks[ (row+1)*10+colomn ]==0)
                    freeBricks.push_back(qMakePair(row*10+colomn,(row+1)*10+colomn));
                if(bricks[ (row-1)*10+colomn ]==0)
                    freeBricks.push_back(qMakePair(row*10+colomn,(row-1)*10+colomn));

                if(colomn==0){
                    if(bricks[ row*10+colomn+1 ]==0)
                        freeBricks.push_back(qMakePair(row*10+colomn,row*10+colomn+1));
                }else{
                    if(bricks[ row*10+colomn-1 ]==0)
                        freeBricks.push_back(qMakePair(row*10+colomn,row*10+colomn-1));
                }
            }

            if(row==0||row==9){
                if(bricks[ row*10+colomn+1 ]==0)
                    freeBricks.push_back(qMakePair(row*10+colomn,row*10+colomn+1));
                if(bricks[ row*10+colomn-1 ]==0)
                    freeBricks.push_back(qMakePair(row*10+colomn,row*10+colomn-1));

                if(row==0){
                    if(bricks[ (row+1)*10+colomn ]==0)
                        freeBricks.push_back(qMakePair(row*10+colomn,(row+1)*10+colomn));
                }else{
                    if(bricks[ (row-1)*10+colomn ]==0)
                        freeBricks.push_back(qMakePair(row*10+colomn,(row-1)*10+colomn));
                }
            }
        /*значит клека расположена в одном из углов поля*/
        }else{
            if(colomn==0){
                if(bricks[ row*10+colomn+1 ]==0)
                    freeBricks.push_back(qMakePair(row*10+colomn,row*10+colomn+1));
            }else{
                if(bricks[ row*10+colomn-1 ]==0)
                    freeBricks.push_back(qMakePair(row*10+colomn,row*10+colomn-1));
            }

            if(row==0){
                if(bricks[ (row+1)*10+colomn ]==0)
                    freeBricks.push_back(qMakePair(row*10+colomn,(row+1)*10+colomn));
            }else{
                if(bricks[ (row-1)*10+colomn ]==0)
                    freeBricks.push_back(qMakePair(row*10+colomn,(row-1)*10+colomn));
            }
       }

        /*если в массиве есть индексы свободных клеток, то осуществляем их случайный выбор*/
        if(freeBricks.size()!=0){
            /*выбираем возможную свободную клетку случайным образом*/
            srand(time(NULL));
            randomNum = rand()%freeBricks.size();

            fromPos=freeBricks[randomNum].first;
            toPos=freeBricks[randomNum].second;

            /*удаляем из массива возможных своюодных клеток,те которые уже были выбраны*/
            for(int i=0; i<freeBricks.size(); i++)
                if(freeBricks[i].second==toPos){
                    freeBricks.erase(&freeBricks[i]);
                    i--;
                 }

            /*делаем возможным толко одно соединение с базисной клеткой*/
            for(int i=0; i<freeBricks.size(); i++)
                if(freeBricks[i].first==(basisrow*10+basiscolomn)){
                    freeBricks.erase(&freeBricks[i]);
                    i--;
                 }

            /*соединяем две клетки*/
            if((fromPos / 10)==(toPos / 10)){
                if((fromPos % 10)<(toPos % 10)){
                    bricks[fromPos]+=1;
                    bricks[toPos]+=4;
                }else{
                    bricks[fromPos]+=4;
                    bricks[toPos]+=1;
                }
            }else
                if((fromPos / 10)<(toPos / 10)){
                    bricks[fromPos]+=2;
                    bricks[toPos]+=8;
                }else{
                    bricks[fromPos]+=8;
                    bricks[toPos]+=2;
                }

            /*запоминаем новую клетку*/
            colomn = toPos % 10;
            row = toPos / 10;
       }
    }

    /*перемешиваем сгенерированное поля для последующего игрового процесса*/
    /*чтобы осуществить сборку поля ,нужно нажать на каждую клетку 3 раза*/
    for(int j=0;j<100;j++)
        bricks[j]=(bricks[j] >> 1) | ((bricks[j] & 1) << 3);


    return bricks;
}

QVector<bool> Helper::light(QVector<int> bricks)
{
    /*создаём массив для хранения свойств свечения клеток*/
    QVector<bool> lights;

    for(int i=0;i <100; i++)
        lights.push_back(false);

   /*исполняем функцию рекурсивного обхода соединённых клеток(обход в глубину) и зажигаем их*/
   recursiveLight(bricks,&lights,0);

    return lights;
}

void Helper::recursiveLight(QVector<int> bricks,QVector<bool> *lights,int pos){

    lights->replace(pos,true);

    /*осуществляем проверку на вохможное соединение данной клетки со всех четырёх сторон*/
    /*если соединение клетки с некоторой стороны есть, переходим по нему к следующей клетке */

    /*соединение справа*/
    if( ((bricks[pos]>>0)&1) && (pos % 10 != 9)){
        if( ((bricks[pos+1]>>2)&1) && (lights->value(pos+1)!=true) )
            recursiveLight(bricks,lights,pos+1);
    }

    /*соединение снизу*/
    if( (bricks[pos]>>1)&1 && (pos / 10 != 9)){
        if( ((bricks[pos+10]>>3)&1) && (lights->value(pos+10)!=true))
            recursiveLight(bricks,lights,pos+10);
    }

    /*соединение справа*/
    if( (bricks[pos]>>2)&1 && (pos % 10 != 0) ){
        if( ((bricks[pos-1]>>0)&1) && (lights->value(pos-1)!=true) )
            recursiveLight(bricks,lights,pos-1);
    }

    /*соединение сверху*/
    if((bricks[pos]>>3)&1 && (pos / 10 != 0)){
        if( ((bricks[pos-10]>>1)&1) && (lights->value(pos-10)!=true) )
            recursiveLight(bricks,lights,pos-10);
    }

    return;
}


