#include "header.cpp"
#include <vector>
#include<sstream>
char server_response[256];
void * file_transfer(void *arg)
{
  
  int conn =*((int *)arg);
 FILE *fp=fopen(server_response,"r+");
    if(fp==NULL)
    {
        cout<<"error in file opening";
        exit(1);
    }
    char buffer[BUFF_SIZE];
    
    fseek(fp,0,SEEK_END);
    
    int file_size=ftell(fp);
   
    send(conn,&file_size,sizeof(file_size),0);
    
    rewind(fp);
    int n;
    while(((n=fread(buffer,sizeof(char),BUFF_SIZE,fp)) > 0) && file_size>0)
    {
        
        send(conn,buffer,n,0);
        file_size-=n;
        memset(buffer,'\0',BUFF_SIZE);
        /*if(file_size < 524288)
          break;*/
    }
   if(((n=fread(buffer,sizeof(char),file_size,fp)) > 0) && file_size>0)
    {
       send(conn,buffer,file_size,0);
        
        file_size=0;
        memset(buffer,'\0',BUFF_SIZE);
       
    }
    fclose(fp);
  close(conn);
  pthread_exit(NULL);
}

int server(int argc,char *argv[])
{
  string s1 = argv[1];
  const char delim = ':';
  vector<string> v;
  stringstream ss(s1);
  string s;
  while (getline(ss, s, delim))
  {
    v.push_back(s);
  }
 int serverfd = socket(AF_INET,SOCK_STREAM,0);
  if(serverfd < 0)
  {
      cout << "Unable to create socket" << endl;
      exit(1);
  }
  struct sockaddr_in serveraddr,cli_addr;
  struct sockaddr_storage serverStorage;
  bzero(&serveraddr,sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(atoi(v[1].c_str()));
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  int ret;
  ret = bind(serverfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
  if(ret < 0)
  {
      cout << "Unable to bind" << endl;
      exit(1);
  }
 
  if(listen(serverfd,5))
  {
      perror("");
      exit(1);
  }
  pthread_t tid;

while(1)
  {
   
  socklen_t cli_addr_size = sizeof(cli_addr);
  int conn = accept(serverfd,(struct sockaddr*)&cli_addr,&cli_addr_size);
  if(conn < 0)
    {
        perror("");
        exit(1);
    }
  
  recv(conn,server_response,sizeof(server_response),0);
   if(pthread_create(&tid,NULL,file_transfer,&conn)!=0)
    {
      perror("");
      exit(1);
    }
    pthread_detach(tid);
  }
  cout << "outside while " << endl;
  if(close(serverfd) < 0)
  {
      cout << "Unable to close the server" << endl;
      exit(1);
  }
  
  return 0;
}
