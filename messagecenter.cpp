#include "messagecenter.h"


MessageCenter* MessageCenter::messagecenter_instance = NULL;

MessageCenter::MessageCenter()
{
}

MessageCenter::~MessageCenter()
{

    m_execs.clear();
}

MessageCenter * MessageCenter::getInstence()
{

   if( !messagecenter_instance )
       messagecenter_instance = new MessageCenter();
   return messagecenter_instance;

}

void MessageCenter::register_todo(IExec *exec)
{

    m_execs.push_back(exec);

}



void MessageCenter::sendMessage(my17::Event event, void *arg)
{


    for(int i=0;i<m_execs.size();i++)
    {
        IExec * exec = m_execs.at(i);
        if( exec->todo(event,arg) == my17::todo_done_only )
            return;
    }


}


void MessageCenter::sendMessage(my17::Event event)
{

    sendMessage(event,NULL);

}
