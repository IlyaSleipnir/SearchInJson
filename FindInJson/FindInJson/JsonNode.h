#pragma once
#include <string>
#include <vector>


enum class NodeType { NUM, STRING, OBJECT, NONE };

class JsonNode
{
public:
	JsonNode();
	JsonNode(const std::string& key, JsonNode* parent);

	const std::string get_key();
	std::vector<JsonNode*> get_childs();
	JsonNode* get_parent();

	void set_key(const std::string& key);
	void add_child(JsonNode* child);
	void set_node_type(NodeType type);

	std::string to_string(int tubs = 0);

	~JsonNode();

private:
	std::string _key;
	std::vector<JsonNode*> _childs;
	JsonNode* _parent = NULL;
	NodeType _type = NodeType::NONE;

	static std::string add_tubs(int tubs);
};