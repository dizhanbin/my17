#ifndef MESSAGECENTER_H
#define MESSAGECENTER_H

#include "my17.h"
#include <vector>

class IExec
{

  void * data;
  public:
         virtual my17::TodoResult  todo(my17::Event event,void * arg)=0;
         virtual void setData(void * d){ data = d;}
         void * getData(){ return data; }

};


class MessageCenter
{
private:
    static MessageCenter * messagecenter_instance;

    std::vector<IExec*> m_execs;

public:
    MessageCenter();

    static MessageCenter* getInstence();
    void register_todo(IExec * exec);
    ~MessageCenter();

public:
    void sendMessage(my17::Event event, void * arg);
    void sendMessage(my17::Event event);



};


#define MC MessageCenter::getInstence()


#endif // MESSAGECENTER_H
