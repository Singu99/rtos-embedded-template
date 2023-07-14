#pragma once


namespace pal {

    enum class port { a = 0, b, c, d, e, f, g, h, i, j, k };
    enum class pin { p0 = 0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p10, p11, p12, p13, p14, p15 };

    class gpio {
    public:
        gpio(port port, pin pin);
        ~gpio();



        // void set();
        // void reset();
        // void toggle();
        // bool read();
        const port m_port;
        const pin m_pin;
    private:    
    };

}