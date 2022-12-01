#pragma once
#include <A4Engine/Export.hpp>
#include <entt/entt.hpp>

class SaveLoadComponent
{
public:
	//SaveLoadComponent() = default;
	//~SaveLoadComponent() = default;
	
	void SaveEntity();
	void LoadEntity();
//private:
//	entt::entity& m_save;
//	entt::entity& m_load;
};