#pragma once
#include <A4Engine/Export.hpp>
#include <unordered_map>
#include <entt/entt.hpp>
#include <vector>

// should it be singleton ??
// or use somehting similar to observer
class A4ENGINE_API SaveLoadSystem
{
public:
	SaveLoadSystem() = default;
	~SaveLoadSystem() = default;
	
	// Set State
	void Save();
	// Get State
	void Load();

private:
	std::unordered_map<int, std::vector<entt::entity&>> m_saves;
};