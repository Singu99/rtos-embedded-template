#include "rx_controller.hpp"

RxController::RxController()
    : Runnable(__func__, Runnable::initThreadAttr(__func__, 4096, osPriorityNormal))
{
}

void RxController::Init()
{

}

void RxController::Run()
{

    while (true)
    {
        


    }
}