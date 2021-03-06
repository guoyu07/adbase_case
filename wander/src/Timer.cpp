#include "Timer.hpp"
#include "App.hpp"

// {{{ macros

#define ADD_AFTER_TIMER(interval, name) do { \
	uint64_t timerId##name = _timer->runAfter((interval),\
					 std::bind(&Timer:: name, this, std::placeholders::_1), nullptr);\
	_timerIds.push_back(timerId##name);\
} while (0);
#define ADD_EVERY_TIMER(interval, name) do { \
	uint64_t timerId##name = _timer->runEvery((interval),\
					 std::bind(&Timer:: name, this, std::placeholders::_1), nullptr);\
	_timerIds.push_back(timerId##name);\
} while (0);

// }}}
// {{{ Timer::Timer()

Timer::Timer(TimerContext* context) :
	_context(context) {
	_configure = _context->config;
	_timer = new adbase::Timer(_context->mainEventBase);
}

// }}}
// {{{ adbase::Timer* Timer::getTimer()

adbase::Timer* Timer::getTimer() {
	return _timer;
}

// }}}
// {{{ Timer::~Timer()

Timer::~Timer() {
	for (auto &t : _timerIds) {
		_timer->cancel(t);
	}
	delete _timer;
}

// }}}
// {{{ void Timer::init()

void Timer::init() {
	/// 间隔一段时间执行一次
	//ADD_EVERY_TIMER(1 * 1000, one);
	/// 一段时间后仅执行一次
	//ADD_AFTER_TIMER(1 * 1000, one);
	ADD_EVERY_TIMER(_configure->intervalTest, Test);
}

// }}}
// {{{ void Timer::Test()

void Timer::Test(void*) {
	//LOG_INFO << "Timer " << "Test";
	// Common::tools::FileInfo newIPFile =
	// 		Common::tools::getNewFile(_configure->ipfiledir);
	//
	// if(newIPFile.fileName.find("ip2zipcode") != -1) {
	// 	if(newIPFile.time <= BinarySearch::ipFile.time) {
	// 		LOG_INFO << "Timer " << "none new ipfile";
	// 	} else {
	// 		BinarySearch::ipFile.time = newIPFile.time;
	// 		_context->bs->reLoadZipCode(_configure->ipfiledir+newIPFile.fileName, "\t");
	// 		LOG_INFO << "Timer " << "update new ipfile:" << newIPFile.fileName;
	// 	}
	// }


}

// }}}
