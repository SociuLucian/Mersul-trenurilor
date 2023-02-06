#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

using namespace std;

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
    else if(strcmp(comanda,"Exit")==0)
    {
    return 0;
    }
    return -1;
}
int main () {

    int s;
    int logat=0;
    char comanda[256];

    sockaddr_in serverAddress{};

    serverAddress.sin_port = htons(36000);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_family = AF_INET;

    s = socket(AF_INET, SOCK_STREAM, 0);

    int retVal = connect(
            s,
            (sockaddr *) &serverAddress,
            sizeof(serverAddress)
    );

    if (retVal == -1) {
        std::cerr << "Connect Failed\n";
        return 0;
    }
    int k = 0;
    int l;
    cout << k << endl;
    int ok=0;
    char Utilizator[256],Parola[256];
    char * buff;
    char plecare[256];
    char output[1000000];
    while (true) {
        
        if(logat==0)
        {
        cout<<endl;
        cout << "Bun venit!" << endl << "Alege o comanda din meniu!" << endl << "Logare" << endl << "Inregistrare"
             << endl << "Exit"<<endl;
        }
        else
        {
            cout<<endl;
            cout<<"Va rugam alegeti o comanda din meniu";
                cout << endl << "Orarul zilei" << endl << "Plecari in urmatoarea ora" << endl << "Sosiri in urmatoarea ora" << endl << "Exit"<< endl;
        }
        bzero(comanda,256);
        //cin>>comanda;
        //cin.get(comanda,26);
        fflush(stdout);
        fgets(comanda,256,stdin);
        comanda[strlen(comanda)-1]=0;
        l = strlen(comanda);
        write(s, &l, sizeof(int));
        write(s, comanda, l);
        if (cititor_comenzi(comanda)==1&&logat==0) 
        { 
            cout << "Utilizator: " << endl;
            cin >> Utilizator;
            cout << "Parola: " << endl;
            //cin >> Parola;
            buff=getpass("");
            setbuf(stdin, NULL);
            setbuf(stdout,NULL);
            strcpy(Parola,buff);
            strcat(Utilizator," ");
            strcat(Utilizator,Parola);
            l = strlen(Utilizator);
            write(s,&l, sizeof(int));
            write(s,Utilizator,l);

            read(s,&logat,sizeof(int));//e int, nu necesita sa trimitem lungimea inainte
            if (logat==1)
            {   
                cout<<endl;
                cout<<"V-ati logat cu succes!"<<endl;
            }
            else
            {
                cout<<endl;
                cout<<"Utilizator sau parola incorecte, incercati din nou!"<<endl;
            }

        }
        else if(cititor_comenzi(comanda)==2&&logat==0)
        {
            cout<<"Utilizator: \n";
            cin>>Utilizator;
            cout<<"Parola: \n";
            //cin>>Parola;
            buff=getpass("");
            setbuf(stdin, NULL);
            setbuf(stdout,NULL);
            strcpy(Parola,buff);
            strcat(Utilizator," ");
            strcat(Utilizator,Parola);
            write(s,Utilizator,sizeof(Utilizator));
            read(s,&logat,sizeof(logat));
            if(logat==0)
            {
            cout<<"Acest nume de utilizator este deja folosit!"<<endl<<"Va rugam incercati din nou!"<<endl;
            }
            else 
            {
                cout<<"Felicitari!"<<endl<< "V-ati inregistrat cu succes!"<<endl;
            }
        }
        else if(cititor_comenzi(comanda)==3&&logat==1)
        {
          bzero(plecare,256);
          bzero(output,1000000);
          cout<<"Va rugam sa introduceti orasul unde va aflati:";
          //cin>>plecare;
          //cin.get(plecare,30);
          //plecare[strlen(plecare)-1]='\0';
          fflush(stdout);
          fgets(plecare,256,stdin);
          plecare[strlen(plecare)-1]=0;
          setbuf(stdout, NULL);
          setbuf(stdin, NULL);
          //cout<<"am scris orasul"<<plecare;
          write(s,&plecare,sizeof(plecare));
          //cout<<"am scris orasul"<<plecare<< " " << "CODE = " << code;
          int len;
          recv(s,&len,sizeof(int), 0);
          recv(s,&output,len, 0);
          output[999999] = 0;
          cout<<output<<endl;
          //cout<<output;
          //cout<<"****CODE**** " << code;
        }
        else if(cititor_comenzi(comanda)==4&&logat==1)
        {
           bzero(plecare,256);
          bzero(output,1000000);
          cout<<"Va rugam sa introduceti orasul unde va aflati:";
          //cin>>plecare;
          //cin.get(plecare,30);
          //plecare[strlen(plecare)-1]='\0';
          fflush(stdout);
          fgets(plecare,256,stdin);
          plecare[strlen(plecare)-1]=0;
          //cout<<"am scris orasul"<<plecare;
          setbuf(stdout, NULL);
          setbuf(stdin, NULL);
          int pen;
          pen=strlen(plecare);
          write(s,&pen,sizeof(int));
          write(s,&plecare,pen);
          //cout<<"am scris orasul"<<plecare;
          int len;
          recv(s,&len,sizeof(int),0);
          recv(s,&output,len,0);
          output[999999] = 0;
          //cout<<"am scris orasul"<<plecare;
          //read(s,&output,sizeof(output));
          cout<<output<<endl;
        }
        else if(cititor_comenzi(comanda)==5&&logat==1)
        {
           bzero(plecare,256);
          bzero(output,1000000);
          cout<<"Va rugam sa introduceti orasul unde va aflati:";
          //cin>>plecare;
          //cin.get(plecare,30);
          //plecare[strlen(plecare)-1]='\0';
          fflush(stdout);
          fgets(plecare,256,stdin);
          plecare[strlen(plecare)-1]=0;
          //cout<<"am scris orasul"<<plecare;
          setbuf(stdout, NULL);
          setbuf(stdin, NULL);
          int pen;
          pen=strlen(plecare);
          write(s,&pen,sizeof(int));
          write(s,&plecare,pen);
          //cout<<"am scris orasul"<<plecare;
          int len;
          recv(s,&len,sizeof(int),0);
          recv(s,&output,len,0);
          output[999999] = 0;
          //cout<<"am scris orasul"<<plecare;
          //read(s,&output,sizeof(output));
          cout<<output<<endl;
        }
        else if (cititor_comenzi(comanda)==0)
            break;
        else
            cout<<"Comanda gresita! Va rugam reincercati!"<<endl;
    }
        return 0;
    }
