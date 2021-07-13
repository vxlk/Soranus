// Thread Module implementation
#include "ThreadModule.hpp"

ThreadModule::ThreadModule() : numTotalThreads(4) /*temporary*/ {
	// Create general thread
	this->CheckIfCanAddThread();
	this->AddThread("General Thread");
}

template<class F, class... Args>
auto ThreadModule::Enqueue(const char* name, F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type> {
	auto thread = this->threadMap.find(name);
	if (thread == this->threadMap.end())
		thread = this->AddThread(name);
	thread->second.enqueue(std::forward<F>(f), std::forward<Args>(args));
}

ThreadWrapper ThreadModule::AddThread(const char* name) {
	this->CheckIfCanAddThread();
	auto thread = this->threadMap.find(name);
	if (thread != this->threadMap.end())
		thread->second.addThread(); // add a new thread to this cluster
	else
		//this->threadMap[name] = ThreadPool();
		this->threadMap.emplace(name, ThreadPool());
	return this->Get(name);
}

void ThreadModule::RemoveThread(const char* name) {
	auto thread = this->threadMap.find(name);
	assert(thread != this->threadMap.end(), "Cannot remove a thread that has never been added...");
	this->threadMap.erase(name);
}

ThreadWrapper ThreadModule::Get(const char* name) {
	auto thread = this->threadMap.find(name);
	assert(thread != this->threadMap.end(), "Cannot get a thread that does not exist...");
	return ThreadWrapper(thread->second, name);
}