#include "JsonNode.h"

JsonNode::JsonNode()
{
}

JsonNode::JsonNode(const std::string& key, JsonNode* parent = NULL)
{
	_key = key;
	_parent = parent;
	if (parent != NULL)
		parent->_childs.push_back(this);
}

const std::string JsonNode::get_key()
{
	return _key;
}

std::vector<JsonNode*> JsonNode::get_childs()
{
	return _childs;
}

JsonNode* JsonNode::get_parent()
{
	return _parent;
}

void JsonNode::set_key(const std::string& key)
{
	_key = key;
}

void JsonNode::add_child(JsonNode* child)
{
	_childs.push_back(child);
}

void JsonNode::set_node_type(NodeType type)
{
	_type = type;
}

std::string JsonNode::to_string(int tubs)
{
	std::string res;

	if (_type == NodeType::OBJECT)
		res += "{";

	tubs++;

	for (int i = 0; i < _childs.size(); i++)
	{
		auto node = _childs[i];

		if (node->_childs.size() != 0)
			res += "\n" + add_tubs(tubs);

		if (node->_type != NodeType::NUM)
			res += "\"";

		res += node->get_key();

		if (node->_type != NodeType::NUM)
			res += "\"";

		if (node->_childs.size() != 0)
			res += ": " + node->to_string(tubs);

		if (i <= _childs.size() - 2 && _childs.size() > 1)
			res += ",";
	}

	if (_type == NodeType::OBJECT)
		res += "\n" + add_tubs(tubs - 1) + "}";

	return res;
}

JsonNode::~JsonNode()
{
}

std::string JsonNode::add_tubs(int tubs)
{
	std::string str;

	for (int i = 0; i < tubs; i++)
		str += '\t';

	return str;
}