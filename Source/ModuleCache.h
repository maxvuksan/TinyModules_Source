#pragma once
#include <unordered_map>
#include <string>
#include <juce_opengl/juce_opengl.h>
#include "ModuleType.h"


/*
	ModuleData is the data structure cached for each module
*/
struct ModuleData
{
	std::string name;
	
	int moduleType;	// casted to ModuleType
};





class Module;

/*
	ModuleCache is responsible for caching data for each module type,
*/
class ModuleCache{

	public:

		static void Init();
		/*
			caches all the base modules
		*/
		static void CacheBaseModulesData();

		/*
			@param moduleKey	the key (name) to store the modules data under
		*/
		static void CacheModuleData(const std::string& moduleKey, ModuleType moduleType);

		/*
			@returns a const reference to a specific modules cached data
		*/
		const static ModuleData& GetModuleData(const std::string& moduleKey);
		const static std::unordered_map<std::string, ModuleData>& GetAllModuleData();

	private:
		static std::unordered_map<std::string, ModuleData> moduleData;
};
