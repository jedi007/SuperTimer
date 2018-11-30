#ifndef SUPERTIMER_H
#define SUPERTIMER_H
/*************************************************

Author: jedi007 (@https://github.com)

Date: 2018-11-30

Description: Use 'setTimeOut' and 'setInterval' like javascript

Example: 'SpTimer.setTimeOut(this, &RRDAT::saveHRVimages, 6000);'Execute the function after 6 seconds

**************************************************/

#include <QObject>

#define SAFE_DELETE_SINGLE(p) if (p) { delete p; p = NULL; }
#define SPTIMERMANAGER_CONNECT  connect( spTimer, SIGNAL(imdeleted(int)), this, SLOT(on_imdeleted(int)) );\
                                SpTimerBaseList.append(spTimer);\
                                return spTimer->spTimerID = SpTimerBaseList.size()-1;

class SuperTimerBase : public QObject
{
    Q_OBJECT

public:
    explicit SuperTimerBase(QObject *parent = 0) : QObject(parent){}
    virtual ~SuperTimerBase(){}
    int spTimerID;

protected:
    virtual void timerEvent(QTimerEvent *event) = 0;

signals:
    void imdeleted(int index);
};

template <class T, class T2>
class SuperTimer : public SuperTimerBase
{
public:
    explicit SuperTimer(bool tmode, T* const tObj, void (T::*const tpf)(), int delayTime, T2* const tcbObj, void (T2::*const tpf_cbfunc)() )
    : infinite(tmode),Obj(tObj),pf(tpf),cbObj(tcbObj),pf_cbfunc(tpf_cbfunc)
    {
        startTimer(delayTime);
    }
    virtual ~SuperTimer(){}

protected:
    virtual void timerEvent(QTimerEvent *event)
    {
        Q_UNUSED(event);
        (Obj->*pf)();

        if(cbObj&&pf_cbfunc)(cbObj->*pf_cbfunc)();

        if(!infinite)
        {
            emit imdeleted(spTimerID);
            delete this;
        }
    }

private:
    const bool infinite;
    T* const Obj;
    void (T::*const pf)();
    T2* const cbObj;
    void (T2::*const pf_cbfunc)();
};

class SuperTimerManager : public QObject
{
    Q_OBJECT

public:
    SuperTimerManager(){}
    ~SuperTimerManager();

    template <typename T, typename T2=SuperTimerManager>//给予默认值仅仅为了可以给下面的函数赋空值
    int setTimeOut( T* const obj, void (T::*const pf)(), int delayTime , T2* const cbObj=NULL, void (T2::*const pf_cbfunc)()=NULL )
    {
        SuperTimer<T,T2> *spTimer = new SuperTimer<T,T2>(false, obj, pf, delayTime, cbObj, pf_cbfunc);
        SPTIMERMANAGER_CONNECT
    }

    template <typename T, typename T2=SuperTimerManager>
    int setInterval( T* const obj, void (T::*const pf)(), int delayTime , T2* const cbObj=NULL, void (T2::*const pf_cbfunc)()=NULL )
    {
        SuperTimer<T,T2> *spTimer = new SuperTimer<T,T2>(true, obj, pf, delayTime, cbObj, pf_cbfunc);
        SPTIMERMANAGER_CONNECT
    }

    void ClearTimer( int spTimerID );

private slots:
    void on_imdeleted(int spTimerID);

private:
    QList<SuperTimerBase*> SpTimerBaseList;
};
extern SuperTimerManager SpTimer;

#endif // SUPERTIMER_H
