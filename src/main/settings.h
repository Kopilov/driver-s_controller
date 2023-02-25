#pragma once

namespace drivers_controller {

/**Период длительного нажатия в мс*/
const int manualSwitchingInterval = 1000;
/**Период автоматического (аварийного) переключения в мс*/
const int autoSwitchingInterval = 100;
/**Период опроса входов в мс (продолжительность паузы в цикле при реализации без часов реального времени и прерываний)*/
const int readingPeriod = 1;
}
