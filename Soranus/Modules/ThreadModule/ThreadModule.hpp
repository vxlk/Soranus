#pragma once

#include <external/ThreadPool.h>

#include <map>

// A wrapper around our thread implementation
struct ThreadWrapper {
	ThreadWrapper(std::thread& t, const char* n) : thread(t), threadName(n) {}
	std::thread& thread;
	const char* threadName;
};

// A wrapper around our threadpool implementation
class ThreadModule {
public:
	explicit ThreadModule();

	// Add a thread to the thread map (by name)
	void AddThread(const char* name);
	// Remove a thread from the thread map (by name)
	void RemoveThread(const char* name);
	// Get a thread from the thread map (by name)
	ThreadWrapper Get(const char* name);

	// Add a function to the list of tasks for a specific thread given by name
	// (default name is the general thread provided)
	// It is important to not overuse the general worker thread! it may get clogged
	// and you will see performance degredation, but it is good for sending work off
	// without having to think about thread organization/delegation
	template<class F, class... Args>
	auto Enqueue(const char* name, F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;
	// Add a function to the list of tasks for a specific thread given by name
	// (default name is the "general thread" provided by the Soranus application)
	// It is important to not overuse the general worker thread! it may get clogged
	// and you will see performance degredation, but it is good for sending work off
	// without having to think about thread organization/delegation
	template<class F, class... Args>
	auto Enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> 
	{ 
		return this->Enqueue("General Thread", f, args); 
	}

	~ThreadModule() = default;
private:
	std::map< std::string, ThreadPool > m_threadMap;
};