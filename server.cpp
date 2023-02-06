#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include<string>
#include <fstream>
#include <sstream>
#include <mysql.h>

using namespace std;
MYSQL *conn;
int cititor_comenzi(const char * comanda)
{
    if(strcmp(comanda,"Logare") == 0)
    {
       return 1;
    }
    else if (strcmp(comanda,"Inregistrare")==0)
    {
        return 2;
    }
    else if(strcmp(comanda,"Orarul zilei")==0)
    {
        return 3;
    }
    else if(strcmp(comanda,"Plecari in urmatoarea ora")==0)
    {
        return 4;
    }
    else if(strcmp(comanda,"Sosiri in urmatoarea ora")==0)
    {
        return 5;
    }
    return 0;
}
int hashh(string parola)
{
  int nr_magic=567856;
  int hash;
  for(int i=0;i<parola.length();i++)
  {
    hash=hash^(parola[i]);
    hash=hash*nr_magic;
  }
  return hash;
}
char * to_hex(int hash)
{
    string hexhash;
    stringstream hexstream;
    hexstream << hex << hash;
    hexhash=hexstream.str();
    char * ch= new char[hexhash.length()+1];
    copy(hexhash.begin(),hexhash.end(),ch);
    return ch;
}
int scenariu(int nr_scenariu,const char * cont)
{
    int ok=0;
    char user[256],pass[256];
    int i;
    int n  = strlen(cont);
     for(i=0;i<n;i++)
     {
        if(  !((cont[i] >='a' && cont[i] <= 'z' )  || (cont[i] >='A' && cont[i] <= 'Z' ) ))
        {
            strcpy(pass,cont+i);
            break;
        }
    }
        strncpy(user,cont,i);
     strcpy(pass,to_hex(hashh(pass)));
   
   if(nr_scenariu == 1)
   {
     int nume=0,key=0;
       MYSQL_RES *res1;
       MYSQL_RES *res2;
       MYSQL_ROW row1;
       MYSQL_ROW row2;
   if(mysql_query(conn ,"Select cont from utilizatori"))
   {
      perror(mysql_error(conn));
      exit(1);
   }
   res1=mysql_use_result(conn);
   int count=mysql_num_fields(res1);
   while((row1=mysql_fetch_row(res1)))
   {
       for(int j=0;j<count;j++)
       {
          char rw[256];
          //cout<<row1[j]<<endl;
          strcpy(rw,row1[j]);
          //cout<<rw;
         // char *rw=row1[j];         // nu e ok !!!
          if(strcmp(user,rw)==0)
          {
            nume=1;
            break;
          }
       }
       if(nume==1){
        break;
       }
   }
   if(res1 != NULL)
       mysql_free_result(res1);
   if(mysql_query(conn ,"Select parola from utilizatori"))
   {
      perror(mysql_error(conn));
      exit(1);
   }
   res2=mysql_use_result(conn);
   int count2=mysql_num_fields(res2);
   while((row2=mysql_fetch_row(res2)))
   {
   for(int p=0;p<count2;p++)
   {
     char rw[256];
     strcpy(rw,row2[p]);        //nu e ok!!!
     if(strcmp(pass,rw)==0)
     {
        key=1;
        break;
     }
     if(key==1)
     {
        break;
     }
   }
   }
   if(res2 != NULL)
       mysql_free_result(res2);
   if(nume==1&&key==1)
   {
    ok=1;
   }
   else 
   {
    ok=0;
   }
   return ok;
   }
   if(nr_scenariu==2)
   {
    int nume=0,key=0;
       MYSQL_RES *res1;
       MYSQL_RES *res2;
       MYSQL_ROW row1;
       MYSQL_ROW row2;
   if(mysql_query(conn ,"Select cont from utilizatori"))
   {
      perror(mysql_error(conn));
      exit(1);
   }
   res1=mysql_use_result(conn);
   int count1=mysql_num_fields(res1);
   while((row1=mysql_fetch_row(res1)))
   {
       for(int j=0;j<count1;j++)
       {
          char rw[256];
          strcpy(rw,row1[j]);             
          if(strcmp(user,rw)==0)
          {
            nume=1;
            break;
          }
       }
       if(nume==1)
       {
        break;
       }
   }
   if(res1 != NULL)
       mysql_free_result(res1);
   if(mysql_query(conn ,"Select parola from utilizatori"))
   {
      perror(mysql_error(conn));
      exit(1);
   }
   res2=mysql_use_result(conn);
   int count2=mysql_num_fields(res2);
   while((row2=mysql_fetch_row(res2)))
   {
   for(int p=0;p<count2;p++)
   {
     char rw[256];
     strcpy(rw,row2[p]);                  
     if(strcmp(pass,rw)==0)
     {
        key=1;
        break;
     }
   }
   if(key==1)
   {
    break;
   }
   }
   if(res2 != NULL)
       mysql_free_result(res2);
   if(nume==1)
   {
    ok=0;
   }
   else 
   {
    char comanda[256]; 
    comanda[0] = 0;
    strcat(comanda, "Insert into utilizatori values('");
    strcat(comanda, user);
    strcat(comanda,"','");
    strcat(comanda,pass);
    strcat(comanda,"')");
   if(mysql_query(conn ,comanda))
   {
       perror(mysql_error(conn));
        exit(1);
   }
    ok=1;
   }
   return ok;
   }
   return ok;
}
void scenariu2( char *imput,char * output,int nr_comanda)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    output[0]=0;
    cout<<imput<<endl;
    char inter[10000];
    if(nr_comanda==3){
   strcpy( inter, "select nume_s_ruta,rute.id_ruta,nume_oprire,id_oprire,ora_plecare,ora_finalizare from opriri natural join timp_opriri join trasee on timp_opriri.id_traseu = trasee.id_traseu join rute on rute.id_ruta = trasee.id_ruta where nume_oprire = ");
    cout<<imput<<endl;
    strcat(inter,"'");
    cout<<inter<<endl;
    strcat(inter,imput);
    cout<<inter<<endl;
    strcat(inter, "'");
    cout<<inter<<endl;
    strcat(inter," order by ora_finalizare");
    cout<<inter<<endl;
    }
    else if(nr_comanda==4)
    {
    strcpy( inter, "select nume_s_ruta,rute.id_ruta,nume_oprire,id_oprire,ora_plecare,ora_finalizare from opriri natural join timp_opriri join trasee on timp_opriri.id_traseu = trasee.id_traseu join rute on rute.id_ruta = trasee.id_ruta where nume_oprire = ");
    cout<<imput<<endl;
    strcat(inter,"'");
    cout<<inter<<endl;
    strcat(inter,imput);
    cout<<inter<<endl;
    strcat(inter, "'");
    cout<<inter<<endl;
    strcat(inter," and ora_finalizare between cast(sysdate() as time) and cast(date_add(sysdate(),interval 60 minute)as time) order by ora_finalizare");
    cout<<inter<<endl;
    }
    else if(nr_comanda==5)
    {
        strcpy( inter, "select nume_s_ruta,rute.id_ruta,nume_oprire,id_oprire,ora_plecare,ora_finalizare from opriri natural join timp_opriri join trasee on timp_opriri.id_traseu = trasee.id_traseu join rute on rute.id_ruta = trasee.id_ruta where nume_oprire = ");
    cout<<imput<<endl;
    strcat(inter,"'");
    cout<<inter<<endl;
    strcat(inter,imput);
    cout<<inter<<endl;
    strcat(inter, "'");
    cout<<inter<<endl;
    strcat(inter," and ora_plecare between cast(sysdate() as time) and cast(date_add(sysdate(),interval 60 minute)as time) order by ora_plecare");
    cout<<inter<<endl;
    }
    if(mysql_query(conn,inter))
    {
        perror(mysql_error(conn));
        exit(1);
    }
    res=mysql_use_result(conn);
    int count=mysql_num_fields(res);
    output[0]=0;
    while((row=mysql_fetch_row(res)))
   {
   for(int p=0;p<count;p++)
   {
      strcat(output,row[p]);
      strcat(output," ");
   }
   strcat(output,"\n");
   }
   if(res != NULL)
       mysql_free_result(res);
}
void * threadMain ( void * pArg ) {
   
    int * pToSocket = (int *) pArg;
    int code;
    int l;
    int sock = * pToSocket;
    char comanda[256];
    int n;
    char Parola[256];
    char user[256];
    int logat=0;
    char imput[256],output[1000000];
    // int nr_conturi,ok=0;
    // int logat=0;
    while(true) {
        comanda[0]=0;
        read(sock, &l, sizeof(int));
        read(sock, comanda, l);
        comanda[l]=0;
        int cod_comanda = cititor_comenzi(comanda);
        if(cod_comanda ==1 && logat==0)
        {
          read(sock,&l, sizeof(int));
          read(sock,user,l);
          logat=scenariu(1,user);
          write(sock,&logat,sizeof(int));
          
        }
        else if(cod_comanda ==2&&logat==0)
        {
            read(sock,&user,sizeof(user));
            logat=scenariu(2,user);
            cout<<logat<<" ";
            write(sock,&logat,sizeof(logat));
        }
        else if(cod_comanda==3&&logat==1)
        { 
            bzero(imput,256);
            bzero(output,1000000);
            read(sock,&imput,sizeof(imput));
            //cout<<"!@#$%^&*UHVCFTYJ\n";
            //cout<<"am citit orasul"<<imput<<" ";
            scenariu2(imput,output,cod_comanda);
            //cout<< "******************" << output << '\n';
            n = strlen(output);
            write(sock, &n, sizeof(int));
            write(sock,&output,n);
            //cout << "************CODE********* " << code << '\n';
        }
        else if(cod_comanda ==4&&logat==1)
        { 
            bzero(imput,256);
            bzero(output,1000000);
            //cout<<"AM AJUNS AICI";
            recv(sock,&l,sizeof(int),0);
            //cout<<l<<" ";
            recv(sock,&imput,l,0);
            //cout<<"am citit orasul"<<imput<<" ";
            scenariu2(imput,output,cod_comanda);
            //cout<<"output"<<output;
            n=strlen(output);
            write(sock,&n,sizeof(int));
            write(sock,&output,n);
            //cout << "************CODE********* " << code << '\n';
        }
        else if(cod_comanda ==5&&logat==1)
        { 
            bzero(imput,256);
            bzero(output,1000000);
            //cout<<"AM AJUNS AICI";
            recv(sock,&l,sizeof(int),0);
            //cout<<l<<" ";
            recv(sock,&imput,l,0);
            //cout<<"am citit orasul"<<imput<<" ";
            scenariu2(imput,output,cod_comanda);
            //cout<<"output"<<output;
            n=strlen(output);
            write(sock,&n,sizeof(int));
            write(sock,&output,n);
            //cout << "************CODE********* " << code << '\n';
        }

       }
        close(sock);
        cout<<"am citit "<<Parola;
        //cout<<nr_conturi;
    return nullptr;
}

int main() {

    conn = mysql_init(NULL);
     //cout<<pass<<" "<<user<<" ";
    if (!mysql_real_connect(conn, "localhost", "root", "root", 
                                      "baza", 36000, NULL, 0)) {
		perror(mysql_error(conn));
        exit(1);
	}
    
    int serverSocket;
    
    sockaddr_in serverAddress {};

    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons ( 36000 );
    serverAddress.sin_family = AF_INET;

    serverSocket = socket ( AF_INET, SOCK_STREAM, 0 );

    int opt = 1;
    setsockopt ( serverSocket,
                 SOL_SOCKET,
                 SO_REUSEADDR,
                 & opt,
                 sizeof ( opt ));

    int retVal = bind (
            serverSocket,
            ( sockaddr * ) & serverAddress,
            sizeof ( serverAddress )
            );

    if ( retVal == -1 ) {
        std :: cerr << "Eroare la bind\n";
        return 0;
    }

    listen ( serverSocket, 1024 );

    socklen_t structureLength = sizeof ( sockaddr_in );

    while ( true ) {
        int clientSocket = accept (
                serverSocket,
                (sockaddr *) & serverAddress,
                & structureLength
        );

        int * socketToSentToThread = new int ( clientSocket );

        pthread_t threadID;
        pthread_create ( & threadID, nullptr, threadMain, socketToSentToThread );


    }
    return 0;
}
