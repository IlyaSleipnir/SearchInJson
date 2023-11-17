using System;
using System.Collections.Generic;
using System.ComponentModel.Design.Serialization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FindInJson
{
    internal class JsonReader
    {
        JsonNode _json;
        int _nodeCount = 0;

        public JsonReader() { }
        public JsonReader(string path)
        {
            using (var file = new StreamReader(path))
            {
                int nodeCount = 0;
                string line;

                // Обработка первой строки
                line = file.ReadLine();
                if (line != "{")
                    throw new Exception("Неверный формат файла");

                var node = new JsonNode();
                node.Type = NodeType.OBJECT;
                nodeCount++;

                var root = node;
                var cursor = root;

                while ((line = file.ReadLine()) != null)
                {
                    NodeType type;
                    line = line.Trim();

                    if (line.First() == '}')
                    {
                        if (cursor.Parent != null)
                            cursor = cursor.Parent;
                    }
                    else
                    {
                        var key = line.Split(':')[0];
                        // Убираем кавычки
                        key = key.Substring(1, key.Length - 2);
                        // Убираем пробел внчале
                        var value = line.Split(':')[1].Substring(1);


                        node = new JsonNode(key, cursor);
                        nodeCount++;

                        if (value.First() == '{')
                        {
                            node.Type = NodeType.OBJECT;
                            cursor = node;
                        }
                        else
                        {
                            // Убираем запятую, если имеется
                            if (value.Last() == ',')
                            {
                                value = value.Substring(0, value.Length - 1);
                            }

                            // Убираем кавычки и помечаем узел как STRING
                            if (value.First() == '\"' && value.Last() == '\"')
                            {
                                type = NodeType.STRING;
                                value = value.Substring(1, value.Length - 2);
                            }
                            else
                            {
                                type = NodeType.NUM;
                            }

                            node = new JsonNode(value, node);
                            node.Type = type;
                            nodeCount++;
                        }
                    }
                }
                _json = root;
                _nodeCount = nodeCount;
            }
        }

        public void FindInJson(string key)
        {
            var visitedNodes = new List<JsonNode>();
            var q = new Queue<JsonNode>();

            visitedNodes.Add(_json);
            q.Enqueue(_json);

            // Обход в ширину
            while(q.Count != 0)
            {
                var node = q.Dequeue();
                // Вывод по соответсвующим ключам
                if (node.Key == key && node.Childs != null)
                {
                    Console.WriteLine($"{AddParantKeys(node)} {node}");
                }

                if (node.Childs != null)
                {
                    foreach (var child in node.Childs)
                    {
                        if (!visitedNodes.Contains(child))
                        {
                            visitedNodes.Add(child);
                            q.Enqueue(child);
                        }
                    }
                }
            }
        }

        string AddParantKeys(JsonNode node)
        {
            var res = "";
            var keys = new Stack<string>();
            var parent = node.Parent;

            keys.Push(node.Key);

            while (parent.Key != null)
            {
                keys.Push(parent.Key);
                parent = parent.Parent;
            }

            foreach (var key in keys)
            {
                res += $"/{key}";
            }

            return res + ":";
        }
    }
}
