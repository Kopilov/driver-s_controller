#pragma once

namespace drivers_controller {
//Распиновка

/*
Силовые контакторы (12 шт)
От D2 до D13, в порядке, соответствующем оригинальному описанию
QK10
QK1
QK9
QK2
QK3
QK4
QK11
QK12
QK5
QK6
QK7
QK8
*/ 
int powerOutOffset = 2;
int powerOutN = 12;

/*
Перевод номера (позиции с 0) силового контактора в эквивалентный номер пина
*/
int getPowerOutPin(int contactorPosition) {
  return contactorPosition + powerOutOffset;
}

/*
Индикаторы эквивалентного положения главного барабана (18 шт)
От D14 до D31 в порядке «ход-0-тормоз»
8
7
6
X3
X2
X1
5
4
3
2
1
0
1
2
3
4
5
6
*/
int powerInOffset = 14;
int powerInN = 18;

/*
Перевод значения «позиция главного барабана» (тормоз от -6 до -1, нейтраль 0, далее ускорение)
в эквивалентный номер пина 
*/
int getPowerInPin(int powerPosition) {
  return powerInN - 1 - powerPosition - 6 + powerInOffset; 
}

/*
Контакторы реверса (12 шт)
От D32 до D43, в порядке, соответствующем оригинальному описанию
QS1
QS3
QS2
QS4
QS5
QS7
QS6
QS8
QS9
QS10
QS11
QS12
*/
int directionOutOffset = 32;
int directionOutN = 12;

/*
Перевод номера (позиции с 0) контактора реверса в эквивалентный номер пина
*/
int getDirectionOutPin(int contactorPosition) {
  return contactorPosition + directionOutOffset;
}

/*
Индикаторы эквивалентного положения реверсивного барабана (3 шт)
От D44 до D46 в порядке «назад-0-вперёд»
*/
int directionInOffset = 44;
int directionInN = 3;

/*
Перевод значения «позиция реверсивного барабана» (назад -1, нейтраль 0, вперёд 1)
в эквивалентный номер пина 
*/
int getDirectionInPin(int directionPosition) {
  return directionPosition + 1 + directionInOffset; 
}

/*
Тумблер реверса
D48 назад
D49 вперёд
*/
int directionSetBackward = 48;
int directionSetForward = 49;

/*
Основной джойстик
D50 добавить скорость
D51 снизить скорость
*/
int powerSetIncrement = 50;
int powerSetDecrement = 51;

}