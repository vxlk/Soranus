#pragma once

#include <external/ThreadPool.h>

#include <map>
#include <assert.h>

// A wrapper around a thread pool
// this is a useful generalization as it visualizes a cluster of threads (potentially)
// as a single entity
// The single entity is chosen by the first available thread in the pool,
// or a random thread <- (due for a better implementation at a later date?)
struct ThreadWrapper {
	ThreadWrapper(ThreadPool& t, const char* n) : pool(t), threadName(n) {}
	ThreadWrapper(ThreadPool&& t, const char* n) : pool(t), threadName(n) {}
	ThreadPool& pool;
	const char* threadName;
};

// A wrapper around our threadpool implementation
class ThreadModule {
public:
	explicit ThreadModule();
	
	// Add a thread to the thread map (by name)
	ThreadWrapper AddThread(const char* name);
	// Remove a thread from the thread map (by name)
	void RemoveThread(const char* name);
	// Get a thread from the thread map (by name)
	ThreadWrapper Get(const char* name) const;
	// Check if this pool has a thread by name
	bool Has(const char* name) const { return this->threadMap.find(name) != this->threadMap.end(); }
	// How many threads are open
	constexpr unsigned int NumberOfOpenThreads() { return this->numOpenThreads; }
	// Total number of threads set to be allowed to be opened at one time on this system
	constexpr unsigned int TotalThreadsAllowedInPool() { return this->numTotalThreads; }
	// Number of available threads to be opened
	constexpr unsigned int NumberOfAvailableThreads() { return this->numTotalThreads - this->numOpenThreads; }
	// Number of jobs in queue for thread of given name
	size_t NumberOfJobsInQueue(const char* name) const {
		this->Has(name) ? this->Get(name).pool.numTasks() : 0;
	}
	// Number of threads in a given cluster given name
	// todo: make this thread safe before using!!!!!
	size_t NumberOfThreadsUnderAlias(const char* name) const {
		this->Has(name) ? this->Get(name).pool.numWorkers() : 0;
	}

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
	constexpr void CheckIfCanAddThread() { assert(numOpenThreads < numTotalThreads); }
	std::map< std::string, ThreadPool > threadMap;
	unsigned int numOpenThreads = 0;
	unsigned int numTotalThreads = 0;
};