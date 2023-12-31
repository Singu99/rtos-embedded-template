#include "rx_controller.hpp"

rx_controller::rx_controller()
    : Runnable(__func__, Runnable::initThreadAttr(__func__, 4096, osPriorityNormal))
{
}

void rx_controller::Init()
{

}

void rx_controller::Run()
{
    while (true)
    {
        if (m_ghst.FrameStatus() != RX_FRAME_PENDING)
        {
            m_ghst.ProcessFrame();
            output = m_ghst.ReadRawRc(0);
        }       
    }
}