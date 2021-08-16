#pragma once

#include "IUI.hpp"
#include "IRepository.hpp"
#include "IScene.hpp"

// The soranus interface, apps should implement this interface
struct ISoranus {
	// Get the Soranus Scene Interface
	// The scene in this case is a tree of objects that represent
	// side-effects of time based events
	virtual IScene* Scene() const = 0;

	// Get the Soranus Repository Interface
	// The repository is a collection of generic in memory
	// representations of generic data, contained in a repository
	// located on disc
	virtual IRepository* Repo() const = 0;

	// Get the Soranus User Interface Interface
	// For now this is only command line
	virtual IUI* UI() const = 0;
};