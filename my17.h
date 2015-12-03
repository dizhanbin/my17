#ifndef MY17_H
#define MY17_H
#include <stdio.h>
#include "nlog.h"

#include <QtGui>
#include <QStyledItemDelegate>
#include <QLineEdit>
#include "mmodeldelegate.h"
#include "mbusinessdelegate.h"
#include "meventdelegate.h"



#define model_field_title_name "字段名"
#define model_field_title_type "类型"
#define model_field_title_defv "默认值"
#define model_field_title_descript "描述"

#define model_field_type_string "String"
#define model_field_type_int "int"
#define model_field_type_float "float"




/*
const QString & model_field_title_index(int index)
{
          switch(index)
          {
            case 0: return model_field_title_name;
            case 1: return model_field_title_type;
            case 2: return model_field_title_defv;
            case 3: return model_field_title_descript;

          }
        return "index out range";
};
*/

typedef enum  {
    PT_MODEL,
    PT_BUSINESS,

} property_type;

class  MElement//左下角 元素
{
public:
    QString name;
    QString iconpath;

public:
    MElement(){

    };
    ~MElement(){};

};



namespace my17 {

        enum Event{

            event_none=0,
            event_req_add_business,
            event_req_add_model,
            event_req_menu_init,//menu init...

            event_req_toolbar_del,
            event_req_toolbar_add,

            event_req_business_item_double_click,

            event_req_model_selected,

            event_req_model_data_changed,

            event_req_model_field_selected,
            event_req_model_field_changed,//index


            event_req_business_selected,
            event_req_business_data_changed,

            event_req_event_item_selected,
            event_req_event_item_data_changed,



        };

        enum TodoResult{
          todo_none,
          todo_done,
          todo_done_only,

        };



        class R
        {



          private:



            void loadElements(){

                MElement * e0 = new MElement();
                e0->name = "事件";
                e0->iconpath = ":/image/001.png";
                elements.push_back( e0 );

                MElement * e1 = new MElement() ;
                e1->name = "网络请求";
                e1->iconpath = ":/image/002.png";
                elements.push_back( e1 );

                MElement * e2 = new MElement() ;
                e2->name = "发送事件";
                e2->iconpath = ":/image/005.png";
                elements.push_back( e2 );

                MElement * e3 = new MElement() ;
                e3->name = "判断";
                e3->iconpath = ":/image/004.png";
                elements.push_back( e3 );

            }
         protected:
            R(){

                loadElements();


            }

          public:

              QVector<MElement*> elements;
              ~R(){

                NLog::i("release R");
                while(elements.size()>0)
                {
                    MElement * e = elements.at(0);
                    elements.removeAt(0);
                    delete e;
                }

              }

            static R* getInstance();



           inline  const QString   model_title_index(int i)  {
                  switch(i)
                  {
                    case 0: return model_field_title_name;
                    case 1: return model_field_title_type;
                    case 2: return model_field_title_defv;
                    case 3: return model_field_title_descript;

                  }
                return "index out range";
            }

            inline const QString  model_field_type_index(int i)  {
                  switch(i)
                  {
                    case 0: return model_field_type_string;
                    case 1: return model_field_type_int;
                    case 2: return model_field_type_float;
                  }
                return "index out range";
            }


            inline  const QString   event_title_index(int i)  {
                   switch(i)
                   {
                     case 0: return "事件名";
                     case 1: return "类型";
                     case 2: return "描述";

                   }
                 return "index out range";
             }
            inline  const QString   event_type_index(int i)  {
                   switch(i)
                   {
                     case 0: return "系统事件";
                     case 1: return "业务事件";
                   }
                 return "index out range";
             }


        };


        class D{

        private:
            D(){}


        public:

            ~D(){

                NLog::i("release D");

                while ( !business.isEmpty() )
                   delete business.takeFirst();

                while ( !models.isEmpty() )
                   delete models.takeFirst();

                while ( !events.isEmpty() )
                   delete events.takeFirst();


            }


            static D* getInstance();

        public:
            QVector<MBusinessDelegate*> business;
            QVector<MModelDelegate*> models;
            QVector<MEventDelegate*> events;

            MBusinessDelegate * newBusiness()
            {

                MBusinessDelegate * b = new MBusinessDelegate();
                b->name = "业务_new";
                business.push_back(b);
                return b;
            }

            MBusinessDelegate * getBusiness(int index)
            {

                return business.at(index);
            }


            MModelDelegate * newModel()
            {

                MModelDelegate * model = new MModelDelegate();
                model->name = "Model";
                models.push_back(model);
                return model;

            }
            MModelDelegate * getModel(int index)
            {
                return models.at(index);
            }
            int getIndex(MModelDelegate * model)
            {

                return models.indexOf(model);

            }
            int getIndex(MBusinessDelegate * md)
            {

                return business.indexOf(md);

            }

            MEventDelegate * newEvent()
            {
                MEventDelegate * event = new MEventDelegate();
                event->event_name="Event_new";
                events.push_back(event);
                return event;
            }

            MEventDelegate * getEvent(int index)
            {

                return events.at(index);
            }

        };




};



#define RP my17::R::getInstance()

#define DP my17::D::getInstance()


#endif // MY17_H
