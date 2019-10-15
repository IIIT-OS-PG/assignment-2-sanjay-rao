#include "client_header.cpp"
#include "MTS2.cpp"
#include<thread>
#include<string.h>
#include <sstream>
#include<fstream>
#include<vector>
#include<map>
#include "client_info.cpp"
#include "create_user.cpp"
#include "login.cpp"
#include "create_group.cpp"
int main(int argc,char *argv[])
{
  int sockfd;
  thread (server,argc,argv).detach();
  string s1 = argv[1];
  const char delim = ':';
  vector<string> v;
  stringstream ss(s1);
  string s;
  while (getline(ss, s, delim))
  {
    v.push_back(s);
  }
  int len = v.size();
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
        create_user(result);
     }
     
     if(strcmp(result[0].c_str(),"login")==0)
     {
        login(result);
     }
     if(strcmp(result[0].c_str(),"create_group") == 0)
     {
        
        if(user=="")
        {
           cout << "Login to create a group" << endl;
        }
        else
        create_group(result);
     }
   int l=0;
  while(1)
  {
   l+=1;
  
  if(strcmp(result[0].c_str(),"download_file") == 0)
  {

  cout << "enter the port number : ";
   int port;
   cin >> port;
   string s2;
   if(l == 1)
    s2 = result[2];
   else
    {
       cout << "Enter file name :"<<endl;
       cin >> s2;
    }
    
  char server_message[256];
  for(int i=0;i<strlen(s2.c_str());i++)
  {
    server_message[i] = s2[i];
  }
  cout << endl;
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd < 0)
  {
    cout << "Error in creating the socket" << endl;
    exit(1);
  }
  
  struct sockaddr_in server_addr;
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  
  int conn = connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
 
  if(conn < 0)
  {
     cout << "Unable to connect to the server" << endl;
     exit(1);
  }
 
  send(sockfd,server_message,sizeof(server_message),0);
  
  int file_size;
  char buffer2[BUFSIZE];     
  srand(time(0));
  int pt = rand(); 
  const char* s=to_string(pt).c_str();
  int fp=open(s,O_WRONLY | O_CREAT ,0644);
  recv(sockfd,&file_size,sizeof(file_size) ,0);
  
  int n;
 
  while(( n=recv(sockfd,buffer2,BUFSIZE,0))>0  && file_size>0)
  {
    
    write(fp,buffer2,n);          
    file_size-=n;           
    memset(buffer2,'\0',BUFSIZE);
  }
  close(fp);
  
  }
  else
   break;
  }
  }
  return 0;
}
