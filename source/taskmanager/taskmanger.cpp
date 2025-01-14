#include "include/taskmanager/taskmanger.h"
//#include "widStu.h"


std::vector<TaskManger*> TaskManger::mainManger;
std::map<TaskManger*, TaskManger*> TaskManger::mangerMap;
TaskManger::TaskManger()
{
	//hAddTaskEvent= CreateEventA(NULL, FALSE, FALSE, "ManagerAddTask");
}
int TaskManger::init(int threadNum)
{
	if (threadNum < 2) {
		threadNum = 2;
	}
#ifdef __linux__
    if (sem_init(&mainThreadSem, 0, 0) != 0) {
        //
    }
    pthread_create(&mainThreads,NULL,TaskManger::managerMainThreadLinux,(void *)this);
#elif
	mainThreads = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)TaskManger::managerMainThread, this, 0, nullptr);
#endif

	for (int i = 0; i < threadNum; i++) {
		creatThread();
	}
	_threadNum = threadNum;
	inited = true;
	name = "NULL";
	//addTask(selfClock, this);
	   
	mainManger.push_back(this);
	mangerMap[this] = this;
	iWaitingTask = tasks.size();
	iIdelThread = idelThreadNum();
	//try {
	//	if (!hasGroup(u8"TaskManger")) {
	//		newGroup(u8"TaskManger");
	//	}
	//	//newCVar(&idelPth, "idelPth", C_OUTPUT, 0, name, u8"¿ÕÏÐÏß³ÌÊý");
	//}
	//catch (QString e) {
	//	insertLog(-1, "TaskManger", e);
	//}

	return 0;
}
TaskManger::~TaskManger()
{
	//mangerMap.erase(this);
	//mangerMap.erase(mangerMap.find(this));
}
int TaskManger::idelThreadNum()
{
	return threads.size();
}
int TaskManger::allThreadNum()
{
	return _threadNum;
}
int TaskManger::creatThread()
{
	Thread* newThread = new Thread(this);

#ifdef __linux__
    // 初始化信号量，初始值为 0
    if (sem_init(&newThread->thdSem, 0, 0) != 0) {
        return -1;
    }
    pthread_create(&newThread->nHandle,NULL,TaskManger::childThreadLinux,(void *)newThread);
#elif
	newThread->taskParam.lpParameter = nullptr;
	newThread->taskParam.lpParameter = nullptr;
	newThread->xClear = false;
	newThread->state = waitting;
	newThread->nHandle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)TaskManger::childThread, newThread, 0, nullptr);
#endif
	pushBack(newThread);

	return 0;
}
void TaskManger::mainThreadWait()
{
#ifdef __linux__
    sem_wait(&mainThreadSem);
#elif
    SuspendThread(mainThreads);
#endif
}
void TaskManger::mainThreadRun()
{
#ifdef __linux__
    sem_post(&mainThreadSem);
#elif
    ResumeThread(mainThreads);
#endif
}
void TaskManger::threadWait(Thread *thd)
{
#ifdef __linux__
    sem_wait(&thd->thdSem);
#elif
    SuspendThread(mainThreads);
#endif
}
void TaskManger::threadRun(Thread *thd)
{
#ifdef __linux__
    sem_post(&thd->thdSem);
#elif
    ResumeThread(mainThreads);
#endif
}
int TaskManger::addTask(void* lpStartAddress, void* lpParameter)
{
	if (lpStartAddress == nullptr) {
		return -1;
	}
	if (xAlarm){
		if (tasks.size() >= iTaskSize) {
			//insertLog(-1, QString::fromStdString(name), u8"³¬³öÈÎÎñÔ¤¾¯ÏÞÖÆ£¬Çë¼ì²é³ÌÐò");
			return -1;
		}
		
	}
	Task* newTask = new Task();
#ifdef __linux__
    newTask->fun = (void *(*)(void*))lpStartAddress;
    newTask->arg = lpParameter;
#elif
	newTask->lpStartAddress = (LPTHREAD_START_ROUTINE)lpStartAddress;
	newTask->lpParameter = (LPVOID)lpParameter;
#endif
	mtx.lock();
	tasks.push_back(*newTask);
	mtx.unlock();
	iWaitingTask = tasks.size();
	iIdelThread = idelThreadNum();

	delete newTask;
    //ResumeThread(mainThreads);
    mainThreadRun();
	return 0;
}
int TaskManger::addTaskEx(void* lpStartAddress, void* lpParameter)
{
	//CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)lpStartAddress, (LPVOID)lpParameter, 0, nullptr);
	Thread* _thread = new Thread(this);
	_thread->pool = this;
#ifdef __linux__
    pthread_create(&_thread->nHandle,NULL,(void *(*)(void*))lpStartAddress,(void *)lpParameter);
#elif
	_thread->taskParam.lpStartAddress = (LPTHREAD_START_ROUTINE)lpStartAddress;
	_thread->taskParam.lpParameter = (LPVOID)lpParameter;
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)TaskManger::childThreadEx, _thread, 0, nullptr);
#endif
	return 0;
}
int TaskManger::pushBack(Thread* _thread)
{
	threadMtx.lock();
	threads.push_back(_thread);
	threadMtx.unlock();
	return 0;
}
TaskManger::Thread* TaskManger::getThread()
{
	if (threads.size() < 2) {
		return nullptr;
	}
	if (threads.size() > 0) {
		return threads[0];
	}
	else {
		if (xExCreat) {
			creatThread();
			return threads[0];
		}
		else {
			return nullptr;
		}

	}
}
int TaskManger::executeTask(Task _task)
{
	
	TaskManger::Thread* thread;
	thread = getThread();
	if (thread == nullptr) {
		
		return -1;
	}
	threads.erase(threads.begin());
	thread->execute(&_task);

	return 0;
}
void* TaskManger::managerMainThread(TaskManger* self)
{
	while (true) {
        //SuspendThread(self->mainThreads);
        self->mainThreadWait();
		self->mtx.lock();
		int exeNum = 0;
		self->threadMtx.lock();
		for (int i = 0; i < self->tasks.size(); i++) {
			int ret = self->executeTask(self->tasks[i]);
			if (ret == 0) {
				exeNum++;
			}
			else {
				break;
			}
		}
		self->threadMtx.unlock();
		for (int i = 0; i < exeNum; i++) {
			self->tasks.erase(self->tasks.begin());
		}
		//self->tasks.clear();
		self->iWaitingTask = self->tasks.size();
		self->iIdelThread = self->idelThreadNum();
		self->mtx.unlock();
	}
	return nullptr;
}
void* TaskManger::childThread(Thread* _thread)
{
	TaskManger* pool = _thread->pool;
	while (true) {
		//ResumeThread(pool->mainThreads);
        //SuspendThread(_thread->nHandle);
        threadWait(_thread);
		_thread->state = busy;

		//TaskManger* pool = _thread->pool;

		if (_thread->pool->xDead) {
			pool->creatThread();
		}	
#ifdef __linux__
        if (_thread->taskParam.fun == nullptr) {
            //
        }else {
            try {
                //_thread->taskParam.lpStartAddress(_thread->taskParam.lpParameter);
                _thread->taskParam.fun(_thread->taskParam.arg);
            }
            catch (...) {
                _thread->pool->getOut++;
            }
        }
#elif
		if (_thread->taskParam.lpStartAddress == nullptr) {
			//
		}else {
			try {
				_thread->taskParam.lpStartAddress(_thread->taskParam.lpParameter);
			}
			catch (...) {
				_thread->pool->getOut++;
			}
		}
#endif

        //ResumeThread(pool->mainThreads);
        _thread->pool->mainThreadRun();
		if (!_thread->pool->xDead){
			_thread->state = waitting;
			_thread->pool->pushBack(_thread);
		}


		

		if (_thread->pool->xDead) {
			delete _thread;
			return nullptr;
		}

	}

	//delete _thread;
	return nullptr;
}



TaskManger::Thread::Thread(TaskManger* arg)
{
	pool = arg;
}
TaskManger::Thread::~Thread()
{
}
int TaskManger::Thread::execute(Task* task)
{
	if (state != waitting) {
		return -1;
	}
	taskParam = *task;
	state = busy;
    //ResumeThread(nHandle);
    threadRun(this);
	return 0;
}



int TaskManger::taskSzie()
{
	return tasks.size();
}
void TaskManger::setExCreat(bool value)
{
	xExCreat = value;
}

void* TaskManger::selfClock(void* arg)
{
	while (true) {
		TaskManger* self = (TaskManger*)arg;
        //ResumeThread(self->mainThreads);
        self->mainThreadRun();
#ifdef __linux__
        usleep(10 * 1000);
#elif
		Sleep(10);
#endif


	}
	return  nullptr;
}
void* TaskManger::childThreadEx(Thread* _thread)
{
	_thread->pool->exMtx.lock();
	_thread->pool->exThread++;
	_thread->pool->exMtx.unlock();
#ifdef __linux__
    if (_thread->taskParam.fun == nullptr) {

    }else {
        try {
            _thread->taskParam.fun(_thread->taskParam.arg);
        }
        catch (...) {
            _thread->pool->getOut++;
        }
    }
#elif
	if (_thread->taskParam.lpStartAddress == nullptr) {
	
	}else {
		try {
			_thread->taskParam.lpStartAddress(_thread->taskParam.lpParameter);
		}
		catch (...) {
			_thread->pool->getOut++;
		}
	}
#endif

	_thread->pool->exMtx.lock();
	_thread->pool->exThread--;
	_thread->pool->exMtx.unlock();
	delete _thread;

	return nullptr;
}


//static void* managerMainThread(TaskManger* self);
//static void* childThread(Thread* _thread);
//static void* childThreadEx(Thread* _thread);

void* TaskManger::managerMainThreadLinux(void* self)
{
    return managerMainThread((TaskManger *)self);
}
void* TaskManger::childThreadLinux(void* _thread)
{
    return childThread((Thread*) _thread);
}
void* TaskManger::childThreadExLinux(void* _thread)
{
    return childThreadEx((Thread*) _thread);
}


//ÖÐ¶ÏËùÓÐÏß³ÌÈÎÎñ£¬²¢ÇÒµ÷ÓÃÏß³ÌµÄÒì³£½áÊø´¦Àí·½·¨,ÔÝÊ±Ã»ÓÐÊµÏÖ£¬ÐèÒªÐÞ¸ÄÒ»²¿·Ö´úÂë
int TaskManger::stopAllThread()
{
	return 0;
}
//ÖÐ¶ÏÄ¿±êÏß³Ì£¬²¢ÇÒµ÷ÓÃÏß³ÌµÄÒì³£½áÊø´¦Àí·½·¨£¬ÔÝÊ±Ã»ÓÐÊµÏÖ£¬ÐèÒªÐÞ¸ÄÒ»²¿·Ö´úÂë
int TaskManger::stopThread(unsigned long id) 
{
	return 0;
}
#ifdef __linux__
int TaskManger::addTask( void *(*fun)(void*),void * lpParameter)
{
    return addTask((void*)fun,lpParameter);
}
#endif








