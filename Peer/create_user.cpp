#include<string.h>
#include <sstream>
#include<vector>
#include<fstream>
using namespace std;
int create_user(vector <string> &result)
{
        int argc = result.size();
        if(argc!=3)
        {
         cout << "Usage:create_user user_id passwd" << endl;
         exit(1);
        }
        user = result[1];    
        ofstream myfile;
        myfile.open("clients_info.txt",ios::app);
        ifstream myfile1;
        myfile1.open("clients_info.txt");
        string s = result[1],s2;
        s += " ";
        s += result[2];
        int f=0;
        while(getline(myfile1,s2))
        {
          if(strcmp(s2.c_str(),s.c_str())==0)
          {
             f=1;
             break;
          }
        }
        myfile1.close();
        if(f==0)
        {
        myfile << s << "\n";
        myfile.close();
        }
        else
        {
          cout << "User already exists" << endl;
        }
}
