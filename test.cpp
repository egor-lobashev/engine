#include <fstream>
#include <iostream>

int main()
{
    std::ifstream pictures_folder;
    pictures_folder.open("all.txt");

    std::string name_of_picture;

    while(getline(pictures_folder,name_of_picture))
    {
        std::cout << name_of_picture<<std::endl;
    }

    pictures_folder.close();

    return 0;
}