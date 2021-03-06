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
#include "murldelegate.h"
#include "mproperty.h"
#include "ftmp.h"

class View;

//#define DATA_DIR(arg) QString("/Users/dzb/qt/my17/17data/").append(arg)
//#define DATA_OUT_DIR( arg ) QString("/Users/dzb/qt/17out/").append(arg)

//#define DATA_DIR(arg) QString("/Users/dzb/qt/northking/data/").append(arg)
//#define DATA_OUT_DIR( arg ) QString("/Users/dzb/qt/northking/out/").append(arg)


//#define DATA_DIR(arg) QString("./data/").append(arg)
//#define DATA_OUT_DIR( arg ) QString("./out/").append(arg)


//#define DATA_DIR(arg) QString("/Users/dizhanbin/work/qt/17data/").append(arg)
//#define DATA_OUT_DIR( arg ) QString("/Users/dizhanbin/work/qt/17out/").append(arg)


#if defined(Q_OS_WIN32)

#define DATA_ROOT(arg) QString(QCoreApplication::applicationDirPath()).append("/").append(arg)

#define DATA_DIR(arg) QString(QCoreApplication::applicationDirPath()).append("/17data/").append(arg)

#define DATA_PLATE_DIR(arg) QString(QCoreApplication::applicationDirPath()).append("/17data/plate/").append(arg)

#define DATA_OUT_DIR( arg ) QString(QCoreApplication::applicationDirPath()).append("/17out/").append(arg)

#else

#define DATA_ROOT(arg) QString(QCoreApplication::applicationDirPath()).append("/../../../").append(arg)

#define DATA_DIR(arg) QString(QCoreApplication::applicationDirPath()).append("/../../../17data/").append(arg)

#define DATA_PLATE_DIR(arg) QString(QCoreApplication::applicationDirPath()).append("/../../../17data/plate/").append(arg)

#define DATA_OUT_DIR( arg ) QString(QCoreApplication::applicationDirPath()).append("/../../../17out/").append(arg)


#endif



#define model_field_title_name "字段名"
#define model_field_title_type "类型"
#define model_field_title_defv "默认值"
#define model_field_title_descript "描述"

#define model_field_type_string "String"
#define model_field_type_int "int"
#define model_field_type_float "float"
#define model_field_type_array "List"
#define model_field_type_object "Object"
#define model_field_type_long "long"
#define model_field_type_double "double"

#define model_type_count 7

#define source_package_common ".data"


#define model_data_none "none"


#define  T_SYS  1//系统事件
#define  T_BUSINESS  (1<<1)//业务事件

#define   TAB_INDEX_GCXX 1001


typedef enum  {
    PT_MODEL,
    PT_BUSINESS,

} property_type;


class  MElement //: public QObject//左下角 元素
{
public:
    QString name;
    QString iconpath;
    QString ele_id;
    QString descript;

    QString c_android;
    QString c_ios;

    QString group;

    QList<MProperty*> properties;

public:
    MElement(){

    };

    MElement(const MElement * copy){

        this->name = copy->name;
        this->iconpath = copy->iconpath;
        this->ele_id = copy->ele_id;
        this->descript = copy->descript;
        this->c_android = copy->c_android;
        this->group = copy->group;
        this->properties = copy->properties;
    }
    ~MElement(){

        while( properties.size() > 0 )
        {

            MProperty * me = properties.at(0);
            properties.removeFirst();
            delete me;
        }

    };

};

class MForm : public QObject
{
public:
    QString formid;
    int x,y,w,h;
    QList<MProperty*> properties;

    MForm():x(100),y(100),w(60),h(80){


    }
     ~MForm(){

        while( properties.size() > 0 )
            properties.takeAt(0);

    }


};

class MLine
{
public:
    QString lineid;
    QString from;
    QString to;

    QList<MProperty*> properties;

    MLine(){



    }
    ~MLine(){

       while( properties.size() > 0 )
           properties.takeAt(0);

   }


};


class MData{

public :

    QString key;
    QString value;
    QString descript;

    MData(){

    }




    bool operator >(const MData * arg){
        return key.compare(arg->key)>0;
    }

    bool operator <(const MData * arg){
        return key.compare(arg->key)<0;
    }
    bool operator ==(const MData * arg){
        return key.compare(arg->key)==0;
    }

    bool operator >=(const MData * arg){
        return key.compare(arg->key)>=0;
    }
    bool operator <=(const MData * arg){
        return key.compare(arg->key)<=0;
    }




};


class MPropertyEdit{

 public:

     QString descript;
     QList<MProperty*> properties;

     MPropertyEdit(){}
     ~MPropertyEdit(){

         while( properties.count()>0)
             properties.takeAt(0);

     }

};


namespace my17 {

        enum Event{

            event_none=0,
            event_req_add_business,
            event_req_add_model,
            event_req_menu_init,//menu init...

            event_req_toolbar_del,
            event_req_toolbar_add,
            event_req_toolbar_save,
            event_req_toolbar_run,

            event_req_business_item_double_click,

            event_req_model_selected,
            event_req_const_selected,

            event_req_model_data_changed,//11

            event_req_model_field_selected,
            event_req_model_field_changed,//index


            event_req_business_selected,
            event_req_business_item_selected,//select one view
            event_req_business_data_changed,

            event_req_event_item_selected,
            event_req_event_item_data_changed,

            event_req_url_item_selected,
            event_req_url_item_data_changed,


            event_req_form_item_selected,//form item




            event_property_selectd,//属性编辑 MPropertyEdit
            event_property_changed,//

            event_req_var_item_selected,


        };

        enum TodoResult{
          todo_none,
          todo_done,
          todo_done_only,

        };



        class R
        {



          private:



            void loadElements();

         protected:
            R(){


                QString path = DATA_DIR ("");
                QDir dir(path);
                if( !dir.exists() )
                   dir.mkpath(path);
                loadElements();





            }

          public:

              QString result;
              QVector<MElement*> elements;//控件
              ~R(){

                //NLog::i("release R");
                while(elements.size()>0)
                {
                    MElement * e = elements.at(0);
                    elements.removeAt(0);
                    delete e;
                }

              }

            static R* getInstance();


            const MElement * getElement(const QString & id)
            {

                for(int i=0;i<elements.size();i++)
                {
                    MElement * ele = elements.at(i);
                    if( ele->ele_id == id )
                    {
                        return ele;
                    }
                }
                return NULL;
             }


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
                    case 3: return model_field_type_array;
                    case 4: return model_field_type_object;
                    case 5: return model_field_type_long;
                    case 6:  return model_field_type_double;
                  }
                return "index out range";
            }

            inline const QString model_field_type_index_ios(int i){

                switch(i)
                {

                    case 0: return "(copy,nonatomic) NSString * ";
                    case 1: return "int ";
                    case 2: return "float ";
                    case 3: return "(retain,nonatomic) NSArray * ";
                    case 4: return "(retain,nonatomic) NSObject * ";

                }



                return "index out range";


            }


            inline  const QString   url_title_index(int i)  {
                   switch(i)
                   {
                     case 0: return "变量名";
                     case 1: return "地址";
                     case 2: return "confluence";
                     case 3: return "描述";

                   }
                 return "index out range";
             }

            inline  const QString  event_title_index(int i)  {
                   switch(i)
                   {
                     case 0: return "事件名";
                     case 1: return "类型";
                     case 2: return "描述";

                   }
                 return "index out range";
             }
            inline  const QString   event_type_index(int i)  {


                    NLog::i("-------------------");
                    //NLog::i("i=%d",i);



                  QString str="";

                  if( i&T_SYS) str = "系统";
                  else if( i&T_BUSINESS  ) str = "业务";




                  return str;



             }

            inline  const QString   business_type_index(int i)  {
                   switch(i)
                   {
                     case 0: return "应用入口";
                     case 1: return "业务处理";
                   }
                 return "index out range";
             }





            QDateTime ids;

            qint64 ids_i;

            inline const QString  getId()
            {

               // QDateTime time = //获取系统现在的时间

                ids_i += 10;

               // ids.addMSecs(10);

                return QString::number(ids_i);

                //return ids.toString("yyyyMMddhhmmsszzz");;
            }

            MProperty * getPropertyByName(QList<MProperty*> & properties,const QString &name)
            {
                for(MProperty * p : properties)
                {

                    if( p->p_name == name )
                        return p;

                }
                return NULL;

            }


        };


        class D{

        private:
            D(){

                NLog::i("createD .....");
                loadProjectInfos();
                loadModel();
                loadEvents();
                loadVars();
                loadBusiness();
                loadUrl();
                loadForms();
                

                //load tmp



                //FTmp * ftmp = new FTmp(DATA_DIR("code_form.txt"));
                //delete ftmp;


            }


        public:

            ~D(){

                //NLog::i("release D");

                while ( !business.isEmpty() )
                   delete business.takeFirst();

                while ( !models.isEmpty() )
                   delete models.takeFirst();

                while ( !events.isEmpty() )
                   delete events.takeFirst();

                while ( !urls.isEmpty() )
                   delete urls.takeFirst();
                while( !forms.isEmpty() )
                    delete forms.takeFirst();
                cleanGolableString();



            }


            static D* getInstance();

        public:
            QVector<MBusinessDelegate*> business;
            QVector<MModelDelegate*> models;
            QVector<MEventDelegate*> events;
            QVector<MUrlDelegate*> urls;

            QVector<MForm *> forms;
            QVector<MLine *> formlines;

            QVector<MData *> projectinfos;

            void * copyvalue;

            //QVector<MData *> global_strings;

            QMap<QString,MData*> qlobal_strings;
            QMap<QString,MData*> qlobal_wwws;
            QVector<MData*>      qlobal_vars;


            QString current_business;

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

            MBusinessDelegate * getBusinessByEvent(const QString & eventname)
            {

                for(int i=0;i<business.size();i++){
                    MBusinessDelegate * md = business.at(i);
                    if( md->event == eventname){

                        return md;

                    }

                }

                return NULL ;
            }



            MModelDelegate * newModel()
            {

                MModelDelegate * model = new MModelDelegate();
                model->name = "Model";
                model->id = R::getInstance()->getId();
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
                event->event_id = R::getInstance()->getId();
                event->event_name="Event_new";
                events.push_back(event);
                return event;
            }

            MEventDelegate * getEvent(int index)
            {

                return events.at(index);
            }

            MUrlDelegate * newUrl()
            {

                MUrlDelegate * url = new MUrlDelegate();
                url->url_id = R::getInstance()->getId();
                url->url_name = "url_new";
                urls.push_back(url);
                return url;
            }

            // save load

            bool saveModel();
            void loadModel();

            bool saveEvents();
            void loadEvents();

            void loadVars();


            bool saveBusiness();
            void loadBusiness();

            bool saveUrl();
            void loadUrl();

            bool saveForms();
            void loadForms();

            bool saveProjectInfos();
            void loadProjectInfos();


            bool loadProperties(QList<MProperty *> & properties, QXmlStreamReader &reader );
            bool saveProperties(QList<MProperty *> & properties,QXmlStreamWriter &writer,const QString &tag);

            View * getView(MBusinessDelegate * mbd,const QString viewid);
            View * createView(const QString &name);
            void dealLine(MBusinessDelegate * mbd);


           int  getModelIndexById(const QString &id);
           int  getEventIndexById(const QString &id);
           int getUrlIndexById(const QString &id);



           MModelDelegate * getModelById(const QString &id);
           MEventDelegate * getEventById(const QString &id);
           MUrlDelegate * getUrlById(const QString &id);


           inline int getGlobalVar(const QString &str,QString * result);
            int getRString(const QString &str,QString * result);
            int getWString(const QString &str,QString * result);


           bool createVars();

           bool createEvent();
           bool createUrls();
           bool createForms();
           bool createBusiness();
           bool createModels();
           bool createProjectInfos();

           bool createStrings();
           bool createWWWStrings();

           bool saveVars();

           bool createFile(const QString & path,const QString & strs);


          const QString createCodes();

          MData * getProjectInfo(const QString& key);


          void cleanGolableString(){


              qlobal_strings.clear();
              qlobal_wwws.clear();
              while( !qlobal_vars.isEmpty() )
                  delete qlobal_vars.takeFirst();

          }

          void addWWWString(const QString& key,const QString& desc){


              qlobal_wwws.remove(key);
              if( !qlobal_wwws.contains(key) )
              {
                  MData * mdata = new MData();
                  mdata->key = key;
                  mdata->descript = desc;

                  qlobal_wwws.insert(key,mdata);
              }

          }

          void addVarString(const QString& key,const QString& desc,bool replace);


          void addGolableString(const QString& key,const QString& desc){

              qlobal_strings.remove(key);
              if( !qlobal_strings.contains(key) )
              {
                  MData * mdata = new MData();
                  mdata->key = key;
                  mdata->descript = desc;

                  qlobal_strings.insert(key,mdata);
              }

          }
          const QString& getPropertyValue(const QString& args,const QString& value)
           {


               //NLog::i("getPropertyValue %s v:%s",args.toStdString().c_str(),value.toStdString().c_str() );
               if( args ==  "$model" )
               {
                   MModelDelegate * mmd = getModelById(value);
                   if( mmd )
                       return mmd->name;
                   else
                   {
                       R::getInstance()->result = "";
                       return R::getInstance()->result;
                   }

               }
               else if( args ==  "$event" )
               {

                  MEventDelegate * med = getEventById(value);
                  if( med )
                  {
                      return med->event_name;
                  }

               }
               else if( args == "$url" )
               {
                   MUrlDelegate * mud = getUrlById(value);
                   if( mud )
                       return mud->url_address;

               }
               else if( args == "$boolean" )
               {
                   return value;
               }

                R::getInstance()->result = "";
                return R::getInstance()->result;
           }
            MForm * getFormById(const QString &formid);




           QString create_form_line_click_case(MForm * form);




        };







};


//Q_DECLARE_METATYPE(MElement)

#define RP my17::R::getInstance()

#define DP my17::D::getInstance()


#endif // MY17_H
