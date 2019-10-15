int login(vector<string> &result)
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
           cout << "Login Successful" << endl;
        }
        else
        {
           cout << "Invalid User!!!" << endl;
        }
   }
