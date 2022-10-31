#pragma once
#include <fstream>
#include "nlohmann_json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
class EnemyWaveSpawner
{
public:
	EnemyWaveSpawner();
	~EnemyWaveSpawner();

private:
	json input;
};
	

