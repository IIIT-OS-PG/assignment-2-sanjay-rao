  #include<string> 
   int create_group(vector<string> &result)
    {
        map<string,vector<string>> gmap;
        string key = result[1];
        gmap[key].push_back(user);
        ifstream myfile1;
        myfile1.open("clients_group_info.txt");
        ofstream myfile;
        myfile.open("clients_group_info.txt",ios::app);
        ofstream myfile2;
        myfile2.open("group_members_info.txt",ios::app);
        string s = user,s2;
        s += " ";
        s += result[1];
        int f=0;
        size_t found;
        while(getline(myfile1,s2))
        {
          found = s2.find(result[1]);
          if(strcmp(s2.c_str(),s.c_str())==0)
          {
             f=1;
             cout << f << endl;
             break;
          }
          if(found != string::npos)
          {
             break;
          }
        }
        
        if(found == string::npos)
        {
            myfile2 << result[1] + " ";
             for(int j=0;j<gmap[result[1]].size();j++)
             {
                 myfile2 << gmap[result[1]][j];
             }
             myfile2 << "\n";
             myfile2.close();
        }
        myfile1.close();
        if(f==0)
        {
          myfile << s + " " + user << "\n";
          myfile.close();
        }
        return 0;
   }
