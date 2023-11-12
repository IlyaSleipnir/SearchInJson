#pragma once
#include <fstream>
#include <string>
#include "JsonNode.h"

class JsonReader
{
public:
	JsonReader();
	JsonReader(std::string path);

	void find_in_json(const std::string key);

	~JsonReader();

private:
	JsonNode* _json;
	int _node_count = 0;

	std::string add_parents_keys(JsonNode* node);
};
