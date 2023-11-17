using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FindInJson
{
    enum NodeType {NUM, STRING, OBJECT, NONE};
    internal class JsonNode
    {
        string _key;
        List<JsonNode> _childs;
        JsonNode _parent = null;
        NodeType _type = NodeType.NONE;

        public string Key 
        { 
            get { return _key; } 
            set { _key = value; } 
        }
        public List<JsonNode> Childs { get { return _childs; } }
        public NodeType Type { get { return _type; } set { _type = value; } }
        public JsonNode Parent { get { return _parent; } }

        public JsonNode() { }
        public JsonNode(string key, JsonNode parent) 
        {
            _key = key;
            _parent = parent;
            if (parent != null)
                parent.AddChild(this);
        }
        public void AddChild(JsonNode child)
        {
            if (_childs == null)
                _childs = new List<JsonNode>();
            _childs.Add(child);
        }
        override public string ToString()
        {
            return ToString(0);
        }
        string ToString(int tabs)
        {
            var res = "";

            tabs++;

            for (int i = 0; i < _childs.Count; i++)
            {
                var node = _childs[i];

                if (node._childs != null)
                    res += $"\n{AddTabs(tabs)}";

                if (node._type != NodeType.NUM)
                    res += $"\"{node._key}\"";
                else
                    res += node._key;

                if (node._childs != null)
                    res += $": {node.ToString(tabs)}";

                if (i <= _childs.Count - 2 && _childs.Count > 1)
                    res += ",";
            }

            if (_type == NodeType.OBJECT)
                res = $"{{{res}\n{AddTabs(tabs - 1)}}}";

            return res;
        }
        string AddTabs(int tabs)
        {
            var str = "";

            for (int i = 0; i < tabs; i++)
                str += '\t';

            return str;
        }
    }
}
