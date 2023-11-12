#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include "JsonReader.h"

JsonReader::JsonReader()
{
}

JsonReader::JsonReader(std::string path)
{
	std::ifstream file(path);
	std::string line;
	int node_count = 0;

	if (!file.is_open())
		throw std::string{ "������ �������� �����" };

	std::getline(file, line);

	if (line != "{")
		throw std::string{ "�������� ������ �����" };

	auto node = new JsonNode();
	node->set_node_type(NodeType::OBJECT);
	node_count++;

	auto root = node;
	auto cursor = root;

	while (!file.eof())
	{
		std::getline(file, line);
		std::stringstream ss(line);

		NodeType type;

		// ������ ����
		ss >> line;
		// ������������ � �������� ���������� ����
		if (line.front() == '}')
		{
			if (cursor->get_parent() != NULL)
				cursor = cursor->get_parent();
		}
		else
		{
			// ������� ������� ��������� �� ����� � ������� ����-�������
			node = new JsonNode(line.substr(1, line.size() - 3), cursor);
			node_count++;

			// ������ ��������
			ss >> line;
			// ��������� � ���������� ����
			if (line.front() == '{')
			{
				node->set_node_type(NodeType::OBJECT);
				cursor = node;
			}
			else {
				// ������� ������� ��� �������������
				if (line.back() == ',')
					line = line.substr(0, line.size() - 1);
				// ������� �������
				if (line.front() == '\"' && line.back() == '\"')
				{
					type = NodeType::STRING;
					line = line.substr(1, line.size() - 2);
				}
				else
					type = NodeType::NUM;

				// ��������� ��������� �������
				node = new JsonNode(line, node);
				node->set_node_type(type);
				node_count++;
			}
		}
	}

	file.close();

	_json = root;
	_node_count = node_count;
}

void JsonReader::find_in_json(const std::string key)
{
	std::vector<JsonNode*> visited_nodes;
	std::queue<JsonNode*> q;

	visited_nodes.push_back(_json);
	q.push(_json);

	while (!q.empty())
	{
		auto node = q.front();
		q.pop();
		// �������� �� ���������� ����� + ����� ����������� ��� ����������� ����
		if (node->get_key() == key && node->get_childs().size() > 0)
		{
			std::cout << add_parents_keys(node) << node->to_string() << std::endl;
		}

		for (auto child_node : node->get_childs())
		{
			// ���������� �� child_node � visited_nodes
			if (std::find(
					visited_nodes.begin(),
					visited_nodes.end(),
					child_node) 
				== visited_nodes.end())
			{
				visited_nodes.push_back(child_node);
				q.push(child_node);
			}

		}
	}

	
}

std::string JsonReader::add_parents_keys(JsonNode* node)
{
	std::string res;
	std::stack<std::string> keys;
	auto parent = node->get_parent();

	keys.push(node->get_key());

	while (parent->get_key() != "")
	{
		keys.push(parent->get_key());
		parent = parent->get_parent();
	}

	while (!keys.empty())
	{
		res += "/" + keys.top();
		keys.pop();
	}

	return res + ": ";
}

JsonReader::~JsonReader()
{
}