#ifndef SUBSYSTEM_HXX
#define SUBSYSTEM_HXX

namespace subsystem
{
    class Subsystem
    {
       public:
        Subsystem();
        ~Subsystem();

        const bool didInit() const { return m_successfullyInit; };

       private:
        bool m_successfullyInit;
    };
}  // namespace subsystem
#endif
