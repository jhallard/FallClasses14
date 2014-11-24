#include <iostream>
#include <string>


void swap(std::string & str, int first, int second)
{
    char temp = str[first];
    str[first] = str[second];
    str[second] = temp;
}



/* arr is the string, curr is the current index to start permutation from and size is sizeof the arr */
void permutation(std::string str, int curr)
{
    if(curr == str.length()-1) 
        std::cout << str << std::endl;
    else
    {
        for(int i=curr; i< str.length(); i++)
        {
            swap(str, curr, i);
            std::cout << i << "\t" << str << std::endl;
            permutation(str, curr+1);
            swap(str, curr, i);
        }
    }
}

int main()
{

    std::string str = "abc";
    permutation(str, 0);
    return 0;
}