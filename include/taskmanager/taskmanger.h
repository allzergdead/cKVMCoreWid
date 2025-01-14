#ifndef TASKMANGER_H
#define TASKMANGER_H
#include <stdio.h>
#ifdef __linux__
    #include <pthread.h>
    #include <semaphore.h>
    #include <stdio.h>
    #include <unistd.h>
#elif
    #include <windows.h>
#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <mutex>

#include <map>
enum THD_STATUS//线程状态
{
    running_status,     //被占用状态
    free_status,        //空闲状态
};


struct Task {
#ifdef __linux__
        pthread_t ptht;
        void *arg;
        void *(*fun)(void*) =nullptr;
#elif
        LPSECURITY_ATTRIBUTES lpThreadAttributes = nullptr;//SD
        SIZE_T dwStackSize = 0;//initialstacksize
        LPTHREAD_START_ROUTINE lpStartAddress = nullptr;//threadfunction
        LPVOID lpParameter = nullptr;//threadargument
        DWORD dwCreationFlags = 0;//creationoption
        LPDWORD lpThreadId = nullptr;//threadidentifier
    #endif
    bool xAutoClear = false;
    std::string strMark;
};
struct TaskResult {
    std::string strMark;
    int iState = 0;
    void *ref;
};

enum threadState {
    waitting = 0,
    busy = 1
};

struct ThreadParameter {


};

class TaskManger
{
private:
    class Thread
    {
    public :
        Thread(TaskManger *arg);
        ~Thread();
        int execute(Task *task);
        Task taskParam;
#ifdef __linux__
        pthread_t nHandle;
        sem_t thdSem;
#elif
        HANDLE nHandle;
#endif
        bool xClear;
        threadState state;
        TaskManger *pool;

    };
public:
    TaskManger();
    ~TaskManger();
    std::vector<TaskResult> taskResults;
    int taskResultsSize = 0;
    //初始化函数，参数为 线程池最多多少条线程
    int init(int threadNum);
    //将任务装填到任务表中，受线程池总数限制，会等待有空闲线程再执行
    int addTask( void * lpStartAddress,void * lpParameter);
    #ifdef __linux__
    int addTask( void *(*fun)(void*),void * lpParameter);
    #endif
    //直接生成一个额外的线程执行任务，不受线程池管控
    int addTaskEx(void* lpStartAddress, void* lpParameter);
    //空闲线程数
    int idelThreadNum();
    //总线程数
    int allThreadNum();
    //任务表中当前的任务数
    int taskSzie();
    //中断所有线程任务，并且调用线程的异常结束处理方法,暂时没有实现，需要修改一部分代码
    int stopAllThread();
    //中断目标线程，并且调用线程的异常结束处理方法，暂时没有实现，需要修改一部分代码
    int stopThread(unsigned long id);



    int pushBack(Thread *_thread);
    void setExCreat(bool value);

    int iTaskSize = 10000;
    int iWaitingTask = 0;
    int iIdelThread = 0;
    bool xAlarm = true;
    static void* managerMainThread(TaskManger* self);
    static void* childThread(Thread* _thread);
    static void* childThreadEx(Thread* _thread);

    static void* managerMainThreadLinux(void* self);
    static void* childThreadLinux(void* _thread);
    static void* childThreadExLinux(void* _thread);
    static void* selfClock(void* arg);
    bool inited = false;
    int getOut = 0;
    int exThread = 0;
    std::mutex exMtx;

    bool xDead = false;
    std::string name;
    static std::vector<TaskManger *> mainManger;
    static std::map<TaskManger *, TaskManger*> mangerMap;
private:
    std::vector<Thread *> threads;
    //std::vector<Thread *> exThreads;
    std::vector<Thread *> busyThreads;
    int _threadNum = 0;
    std::vector<Task> tasks;
    Thread *getThread();
    int executeTask(Task _task);
    int creatThread();
#ifdef __linux__
    pthread_t mainThreads;
    pthread_t hAddTaskEvent;
    sem_t mainThreadSem;
    void mainThreadWait();
    void mainThreadRun();

    static void threadWait(Thread *thd);
    static void threadRun(Thread *thd);
#elif
    HANDLE mainThreads;
    HANDLE hAddTaskEvent;
#endif
    std::mutex mtx;
    std::mutex threadMtx;
    bool xExCreat = false;

};

#endif // TASKMANGER_H
