using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FindInJson
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var key = "";
            var path = "";
            var helpStr = "Программа считывает json из файла и выполняет поиск значений по ключу.\n" +
                "Параметры:\n" +
                "\t-f -- путь к файлу json\n" +
                "\t-k -- ключ, по которому будет выполняться поиск\n" +
                "\t-h -- вывод описания программы\n";

            for (int i = 0; i < args.Length; i++)
            {
                if (args[i].ToLower() == "-k")
                    key = args[++i];
                if (args[i].ToLower() == "-f")
                    path = args[++i];
                if (args[i].ToLower() == "-h")
                    Console.WriteLine(helpStr);
            }

            if (key != "" &&  path != "")
            {
                try
                {
                    var reader = new JsonReader(path);
                    reader.FindInJson(key);
                }
                catch (Exception ex)
                { 
                    Console.WriteLine(ex.Message);
                }
            }
        }
    }
}
