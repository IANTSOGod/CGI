#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//ajoute une barre de recherche
void addsearchBar(){
    printf("<form action=\"http://localhost/cgi-bin/site.cgi\" method=\"get\"><div style=\"margin-top:0px;display:flex;justify-content: center;background: black;\"><input type=\"text\" placeholder=\"Entrez ici\" style=\"height:30px\" name=\"search\"><button><img src=\"file:///home/iantso/C/komi.jpg\" width=\"50px\" alt=\"Envoyer\"></button></div></form>");
}
int getLine(){
    int cpt=0;
    char tmp[256];
    FILE* file1=fopen("/home/mit/C/devoir1.txt","r");
    for(int i=0;fgets(tmp,sizeof(tmp),file1);i++){
        cpt+=1;
    }
    fclose(file1);
    return cpt;
}
int main(){
    printf("Content-Type: text/html\n\n");
    printf("<!Doctype HTML><html><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Manager</title></head><body style=\"margin:0px\">");
    //variable de stockage des entrees
    char* data=getenv("QUERY_STRING");

    char username[100];
    char value[100];
    char password[100];
    char pvalue[100];

    char mois[100];
	char jour[100];
	char heure[100];
	char action[100];
	char user[100];
            
    //entree existente 
    if (data!=NULL){

        //sectionner les données entrées
        sscanf(data,"%[^=]=%[^&]&%[^=]=%[^&]&",username,value,password,pvalue);
        
        //Données de la part d'un bouton
        if(strcmp(username,"btn")==0){
            addsearchBar();
            char tmp[250];
            FILE* file1=fopen("/home/mit/C/devoir1.txt","r");
            int cpt=getLine();
            
            int c=0;
            int nbrBtn=ceil(cpt/10.0);
		    printf("<form action=\"http://localhost/cgi-bin/site.cgi\" method=\"get\" style=\"margin-left:300px;\">");
		    for(int i=0;i<nbrBtn;i++){
			    printf("<button name=\"btn\" value=\"%d\">%d</button>",i+1,i+1);
		    }
		    printf("</form></div>");

            for(int i=0;fgets(tmp,sizeof(tmp),file1);i++){
			    c+=1;
			    sscanf(tmp,"%[^ ] %[^ ] %[^ ] %[^ ] %s",mois,jour,heure,action,user);
                if(strcmp(mois,"Oct")==0){
                    strcpy(mois,"Oktobra");
                }
                else if(strcmp(mois,"Jan")==0){
                    strcpy(mois,"Janoary");
                }

                else if(strcmp(mois,"Fev")==0){
                    strcpy(mois,"Febroary");
                }
                else if(strcmp(mois,"Mar")==0){
                    strcpy(mois,"Martsa");
                }
                else if(strcmp(mois,"Avr")==0){
                    strcpy(mois,"Aprily");
                }
                else if(strcmp(mois,"Mai")==0){
                    strcpy(mois,"May");
                }
			    if (c>((atoi(value)*10)-10) && c<((atoi(value)*10)+1)){
                    printf("<p>%s %s %s %s %s</p>",jour,mois,heure,action,user);
			    }
		    }
            fclose(file1);   
        }

        //Données de la part d'un login
        else if((strcmp(value,"IANTSOGod")==0) && (strcmp(pvalue,"Razafindrazaka01")==0)){
            printf("<div style=\"margin-left:500px;margin-top:200px;border-box:5px solid green;border-radius:30px;width:800px;height:400px;background:linear-gradient(to bottom,green,chartreuse)\"><h1 style=\"display:flex;justify-content:center;\">Login successfull</h1></br><h2 style=\"display:flex;justify-content:center;font-family:cursive\">Welcome back,%s</h2><br>",value);
            
            //on utilise la balise button pour avoir un retour afin de charger la principale
            printf("<form action=\"http://localhost/cgi-bin/site.cgi\" method=\"get\"><button name=\"start\" style=\"margin-top:100px;margin-left:300px;width:140px;height:60px;font-family:cursive;font-size:30px;background:linear-gradient(to bottom,blue,aquamarine);display:flex;justify-content:center\">Get started!</button></form></div>");           
        }

        //Si le login est réussi
        else if(strcmp(username,"start")==0){
            addsearchBar();
        }

        //si on effectue une recherche
        else if(strcmp(username,"search")==0){
            addsearchBar();
            char tmp[256];
            int cpt=0;
            FILE* file=fopen("/var/log/auth.log","r");
            FILE* file1=fopen("/home/mit/C/devoir1.txt","w");
                for(int i=0;fgets(tmp,sizeof(tmp),file);i++){
                    if (strstr(tmp,"for user")){
					    sscanf(tmp,"%[^ ] %[^ ] %[^ ] %*[^:] %*[^ ] %*[^ ] session %[^ ] for user %[^(](",mois,jour,heure,action,user);
					    if(strcmp(value,user)==0){
                            
						    //on met l'utile dans devoir1.txt
						    fprintf(file1,"%s %s %s %s %s\n",mois,jour,heure,action,user);
						    //on compte les données utiles
						    cpt++;
					    }
				    }
                }
            int nbrBtn=ceil(cpt/10.0);
		    printf("<form action=\"http://localhost/cgi-bin/site.cgi\" method=\"get\" style=\"margin-left:300px;\">");
		    for(int i=0;i<nbrBtn;i++){
			    printf("<button name=\"btn\" value=\"%d\">%d</button>",i+1,i+1);
		    }
		    printf("</form></div>");
            fclose(file1);
            fclose(file);
        }

        //si on commence à ouvrir le site
        else{
            printf("<form action=\"http://localhost/cgi-bin/site.cgi\" method=\"get\" style=\"border-style:8px black solid;border-radius:50px;background:linear-gradient(to bottom,green,chartreuse);margin-top:150px;margin-left:300px;margin-right:300px;\"><h1 style=\"display:flex;justify-content:center;font-family:cursive;font-size:50px;\">Login</h1><br><input type=\"text\" name=\"username\" placeholder=\"Username\" style=\"margin:100px;margin-left:300px;width:220px;height:40px;border-radius:20px;font-size:20px;\"><br><input type=\"password\" name=\"password\" placeholder=\"Password\" style=\"margin-top:0px;margin-left:300px;width:220px;height:40px;border-radius:20px;font-size:20px;\"><br><input type=\"submit\"  value=\"Confirm\" style=\"font-size:30px;margin-left:600px;border-radius:20px;height:50px;margin-top:100px;\"><br></form>");
        }
    }
    printf("</body></html>");
    return 0;
}