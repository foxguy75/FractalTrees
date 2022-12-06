#ifndef SUBSYSTEM_HXX
#define SUBSYSTEM_HXX

class Subsystem
{
 public:
  Subsystem();
  ~Subsystem();

  const bool didInit() const { return m_successfullyInit; };

 private:
  bool m_successfullyInit;
};

#endif
