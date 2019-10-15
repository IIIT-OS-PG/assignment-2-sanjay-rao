#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
#include<fstream>
#include<string.h>
#include<vector>
#include <sstream>
using namespace std;
string user="";
int client()
{
   while(1)
   {
     string s,s1,s2;
     getline(cin,s);
     vector<string> result;
     istringstream iss (s);
     for(string s; iss >> s; )
        result.push_back(s);
     int argc = result.size();
     if(strcmp(result[0].c_str(),"create_user") == 0)
     {
        if(argc!=3)
        {
         cout << "Usage:create_user user_id passwd" << endl;
         exit(1);
        }
        user = result[1];
        //cout << user<< endl;
        ofstream myfile;
        myfile.open("clients_info.txt",ios::app);
        ifstream myfile1;
        myfile1.open("clients_info.txt");
        string s = result[1];
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
     
     else if(strcmp(result[0].c_str(),"login")==0)
     {
        ifstream myfile;
        myfile.open("clients_info.txt");
        string s = result[1],s2;
        s += " ";
        s += result[2];
        int f=0;
        while(getline(myfile,s2))
        {
          if(strcmp(s2.c_str(),s.c_str())==0)
          {
             f=1;
             break;
          }
        }
        if(f==1)
        {
           user = result[1];
           //cout << user << endl;
           cout << "Login Successful" << endl;
        }
        else
        {
           //cout << user << endl;
           cout << "Invalid User!!!" << endl;
        }
     }
     else if(strcmp(result[0].c_str(),"create_group") == 0)
     {
        ofstream myfile;
        myfile.open("clients_group_info.txt",ios::app);
        string s = user;
        s += " ";
        s += result[1];
        //cout << s+user << endl;
        myfile << s << "\n";
        myfile.close();
     }
  }
  return 0;
}
