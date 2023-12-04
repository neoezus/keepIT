#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define THE_KEY "key"
#define max_size 256



// Procédure qui permet d'afficher le mennu pour la gestion des passwords
void Affichier_Mennu(){
    printf("\n\n-------mennu--------");
    printf("\n1. Listing passwords\n"
    "2.Getting a password \n"
    "3.Editing passwords \n"
    "4.Deleting passwords \n"
    "5.Generate a password"
    "\n6. Exit");
}
// fonction qui permet de chiffrer le mot de passe a partir d'une clé passé en paramatére.
char *encrypt(char *plaintext_password,char *KEY)
{
    int len = strlen(plaintext_password); 

    // allocate memory for the result string
    char *result = malloc(len + 1);

    // initialize the result string
    result[0] = '\0';

    // compute the XOR of the input strings
    for (int i = 0; i < len; i++) {
        result[i] = plaintext_password[i] + KEY[ i % strlen(KEY) ];
    }
    result[len] = '\0'; // null-terminate the result string

    return result;
}
// fonction qui permet de déchiffrer le un mot de passe chiffré partir d'une clé
char *decrypt(char *encrypted_password,char *KEY)
{
    int len = strlen(encrypted_password);

    // allocate memory for the result string
    char *result = malloc(len + 1);

    // initialize the result string
    result[0] = '\0';

    // compute the XOR of the input strings
    for (int i = 0; i < len; i++) {
        result[i] = encrypted_password[i] - KEY[ i % strlen(KEY)];
    }
    result[len] = '\0'; // null-terminate the result string

    return result;
}
// fonction permet de vérifier si un fichier existe déja ou non.
int file_exists (char *filename)
{
    // try to open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // the file does not exist
        return 1 ;
    }

    // the file exists
    fclose(file);
    return 0;
}
// fonction qui permet d'etablir une session  aprés avoir créé le fichier vault.txt 
int open_session()
{
    printf("\nusername :");
    char *username=malloc(max_size);
    scanf("%s",username);
    printf("\npassword:");
    char *password=malloc(max_size);
    scanf("%s",password);
    FILE *file = fopen("vault.txt", "r");
    if (file == NULL) {
        // unable to open the file
        fprintf(stderr, "Error: unable to open file 'vault.txt' for writing.\n");
    }
    char *contenu=malloc(max_size);
    fgets(contenu,256,file);
    char *username_crypt= malloc(max_size);
        int j=3; int k=0;
        while (contenu[j]!=':') {username_crypt[k]=contenu[j];k++; j++;} // recupéré l'username crypté du ID -1
        if (strcmp(encrypt(username,THE_KEY),username_crypt)==0) return 0;
        else return 1;

}
 // procédure qui permet créé le fichier vault.txt et l'inisialisé avec le 1 iere password ID -1 
void create_vault(char* filename)
{
    char *username=malloc(max_size), 
    *password=malloc(max_size), 
    *encrypted_username=malloc(max_size); 
    char *encrypted_password= malloc(max_size);
    printf("\nWelcome on LockIT\n"
           "It's the first time you open LockIT, we created `vault.txt`."
           "\nYou must choose a username and a password to decode your vault !\n\n");
    printf("\nUsername: ");
    gets(username);
    printf("\nPassword: ");
    gets(password);
    encrypted_username = encrypt(username,THE_KEY);
    encrypted_password = encrypt(password,THE_KEY);

    FILE *file = fopen(filename, "w"); // open file to write  
    if (file == NULL) {
        // unable to open the file
        fprintf(stderr, "Error: unable to open file '%s' for writing.\n", filename);
    }

    // write the username and password to the file
    fprintf(file, "-1:%s:-1\n", encrypted_username);
    printf("\nYour vault file has been initialized");
    // close the file
    fclose(file);
}

// procédure permet de lister les password qui existe dans le fichier vault.txt
void list_password(){
    printf("\nlist of password:\n");    
    FILE *file = fopen("vault.txt", "r"); 
if (file == NULL) {
        // unable to open the file
        fprintf(stderr, "Error: unable to open file 'vault.txt' for writing.\n" );
          }
char *contenu=malloc(max_size);
int i=0;
while(fgets(contenu,256,file))
{
    if (i==0){i++;} // exepction de password avec ID -1
    else {
        int j;
        if (i>10 )  { j=3;} // si le ID>10 la longere de ID est 2 + longeure (:)
        else {j=2;} 
        while (contenu[j]!=':') j++; // pour retourner la postion du debut de password
        int k=0;j++;
        char *password =malloc(strlen(contenu)-j);
        // recupérer le password
        while(j<strlen(contenu)-1)
        {
            password[k]=contenu[j];
            j++;k++;
        }
      printf("%d:{%s}\n",i,decrypt(password,THE_KEY)); // afichier le password recupérer déchifré 
      i++;  
    }
    
    }
fclose(file);
}


// procédure permet de modifier un password dans fichier vault.txt depuis le ID
void edit_password(){
      printf("\ndonner le ID du password :");
    int ID;
    scanf("%d",&ID);
    FILE *file = fopen("vault.txt", "r"); 

if (file == NULL) {
        // unable to open the file
        fprintf(stderr, "Error: unable to open file 'vault.txt' for writing.\n" );
          }
char *contenu=malloc(max_size);
int i=0;
if (ID>0) {
FILE *temp=fopen("temp.txt","a"); // créé le fichier temp  en mode ajout
while(fgets(contenu,256,file))
{
if (i==ID){  
       char *s=malloc(max_size);
        int j;
        if (i>10 )  { j=3;} // si le ID>10 la longere de ID est 2 + longeure (:)
        else {j=2;}
        while (contenu[j]!=':') j++; // recupérer la postion du mdp 
        
    
        strncpy(s,contenu,j); // copier contenu (ID+nomdumdp)
        printf("\n donner le nouveau password : ");
        char *new=malloc(max_size);
        scanf("%s",new);
        char *new_encrypt=malloc(strlen(new));
        new_encrypt=encrypt(new,THE_KEY);
        fprintf(temp,"%s:%s\n",s,new_encrypt);  // ajouter le ID du password + nomdupassword+ mouveau mdp chiffré
}
else fprintf(temp,"%s",contenu);// ajouter le restes de lignes (les autres passwords sans les modifier)

i++;
}

fclose(file);
fclose(temp);
remove("vault.txt"); // supprimer le fichier vault.txt 
rename("temp.txt","vault.txt");// renomer le fichier temporaire contenat la modifcation vers vault.txt 
}
}

// procédure permet d'affichier un password a partir du ID
void get_password(){
    
    printf("\ndonner le ID du password :");
    int ID;
    scanf("%d",&ID);
    FILE *file = fopen("vault.txt", "r"); 

if (file == NULL) {
        // unable to open the file
        fprintf(stderr, "Error: unable to open file 'vault.txt' for writing.\n" );
          }
char *contenu=malloc(max_size);
int i=0;
while(fgets(contenu,256,file))
{
    if (i==0){i++;}
    else {
        if(i==ID){
        int j;
        if (i>10 )  { j=3;} 
        else {j=2;}
        while (contenu[j]!=':') j++;
        int k=0; j++;
        char *password =malloc(strlen(contenu)-j);

        while(j<strlen(contenu)-1)
        {
            password[k]=contenu[j];
            j++;k++;
        }
        printf("\nle password equivalent au ID %d est : %s",ID,decrypt(password,THE_KEY));
        break;
        }
      i++;
    }
    
}

fclose(file);


}

// procédure qui permet de supprimer un mot de passe a partir du son ID
void delete_password(){
    printf("\ndonner le ID du password :");
    int ID;
    scanf("%d",&ID);
    FILE *file = fopen("vault.txt", "r"); 

if (file == NULL) {
        // unable to open the file
        fprintf(stderr, "Error: unable to open file 'vault.txt' for writing.\n" );
          }
char *contenu=malloc(max_size);
int i=0;
if (ID>0) {
FILE *temp=fopen("temp.txt","a");
while(fgets(contenu,256,file))
{
if (i!=ID)  fprintf(temp,"%s",contenu);// copier tout les lignes dans le fichier temp sauf la ligne ayant le ID asupprimer 
i++;
}

fclose(file);
fclose(temp);
remove("vault.txt");
rename("temp.txt","vault.txt");
}
}
// procédure permet de générer des mots de passes randoms 
void generate_password(){
    int l ;
    printf("\n\n **let's generate a password** ");
    printf("\nDonner la longeure du mot de passse : ");
    scanf("%d",&l);
    if (l<=0) { printf("password length mus be >= 1 ");}
    char *password=malloc(l+1);
    char *digits="0123456789"; // tableau des nombres
    char *lowers="abcdefghijklmnopqrstuvwxyz"; // tableau des caractéres miniscules
    char *uppers="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // tableau des caractéres majucules
    char *symbols="!@#$%^&*()";// tableau des caractéres spéciaux
    srand(time(NULL));
    for(int i=0;i<l;i++){
        int char_type=rand() % 4 ; // selection random soit un nombre soit majscule soit miniscule soit symboles
        if (char_type==0) password[i]=digits[rand() % strlen(digits)]; 
        if (char_type==1) password[i]=lowers[rand() % strlen(lowers)];
        if (char_type==2) password[i]=uppers[rand() % strlen(uppers)];
        if(char_type==3) password[i]=symbols[rand() %strlen(symbols)];
    }

printf("\npassword generated is : %s ",password);
// stocker password dans fichiers
FILE *file = fopen("vault.txt", "r"); 
if (file == NULL) {
        // unable to open the file
        fprintf(stderr, "Error: unable to open file 'vault.txt' for writing.\n" );
          }
char *contenu=malloc(max_size);
int k=0;
while(fgets(contenu,256,file))
{
k++;
}
fclose(file);
FILE *f = fopen("vault.txt", "a"); // ouvrir le fichier pour ajouter le mot de passe généré
printf("\ndonner un nom au password  :");
char *name=malloc(max_size);
scanf("%s",name);
fprintf(f,"%d:%s:%s\n",k,name,encrypt(password,THE_KEY));        
        fclose(f);

}
 // programme principale 
int main() {   
create_vault("vault.txt");
int choix=0;
int bol ;
char YN;
printf("\nvoulez vous conecctez ? Y/N : ");
     scanf("%c",&YN);
     
     if (YN=='Y' || YN=='y')
     {
        do { 
         bol=open_session();
         if (bol==0)  {printf("\nlogin sucess");}
         else printf("\nlogin failled ");
        }while(bol !=0);   
    do
    {   
    Affichier_Mennu();
    printf("\nquelle est votre choix ? :");
    scanf("%d",&choix);
    switch (choix)
    {
    case 1 :  list_password(); 
     break;
    case 2 :
         get_password();     
         break;
           
     case 3: edit_password();
              break;
     case 4 :delete_password();
            break;
     case 5 : generate_password();
           break;
    default:
        break;
    }
} while (choix!=6);
     }
    }


