#include "supertimer.h"

SuperTimerManager SpTimer;

SuperTimerManager::~SuperTimerManager()
{
    for(int i = 0;i < SpTimerBaseList.size(); ++i)
    {
        SAFE_DELETE_SINGLE(SpTimerBaseList[i])
    }
}

void SuperTimerManager::ClearTimer(int spTimerID)
{
    if( 0<=spTimerID && spTimerID < SpTimerBaseList.size() )
        SAFE_DELETE_SINGLE(SpTimerBaseList[spTimerID])
}

void SuperTimerManager::on_imdeleted(int spTimerID)
{
    if( 0<=spTimerID && spTimerID < SpTimerBaseList.size() )
        SpTimerBaseList[spTimerID] = NULL;
}
