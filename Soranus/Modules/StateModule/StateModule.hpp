#pragma once

#include <lager/event_loop/manual.hpp>
#include <lager/store.hpp>

#include <map>

struct Store {

};

struct StoreModule {
	static Store globalStore;
	// static stl container is bad i think
	static std::map<std::string, Store> componentStores;
};

struct State {

};

struct Effect {

};

struct Action {

};

struct Reducer {

};

// useEffect
// useState