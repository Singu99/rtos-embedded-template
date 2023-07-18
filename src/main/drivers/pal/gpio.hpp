#pragma once


namespace pal {

    enum class port { a = 0, b, c, d, e, f, g, h, i, j, k, unknown };
    enum class pin { p0 = 0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, unknown };

    class gpio {
    public:
        gpio();
        gpio(port port, pin pin);
        ~gpio();

        // Equals operator
        bool operator==(const gpio& other) const {
            return (m_port == other.m_port) && (m_pin == other.m_pin);
        }

        // Common interface implementation
        virtual void set() = 0;
        virtual void reset() = 0;
        virtual void toggle() = 0;
        virtual bool read() = 0;

        const port m_port;
        const pin m_pin;
    private:    
    };

}