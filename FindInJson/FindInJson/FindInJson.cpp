#include <iostream>
#include "JsonReader.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");

    std::string key;
    std::string path;
    std::string help_str = "Программа считывает json из файла и выполняет поиск значений по ключу.\n";
    help_str += "Параметры:\n";
    help_str += "\t-f -- путь к файлу json\n";
    help_str += "\t-k -- ключ, по которому будет выполняться поиск\n";
    help_str += "\t-h -- вывод описания программы\n";

    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "-k")
            key = argv[++i];

        if (std::string(argv[i]) == "-f")
            path = argv[++i];

        if (std::string(argv[i]) == "-h")
            std::cout << help_str << std::endl;
    }

    if (key != "" && path != "")
    {
        try
        {
            JsonReader reader(path);
            reader.find_in_json(key);
        }
        catch (std::string error)
        {
            std::cout << error << std::endl;
        }
    }
}