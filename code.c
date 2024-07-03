#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// Structure de données pour un utilisateur
typedef struct user_data {
    char *fullName;
    int age;
    int moneyBalance;
    char *password;
    struct user_data *next;
} user_data;
// Vérifie si le choix de l'utilisateur est valide (entre 1 et 7)
bool check_choice(char *s)
{
    if (atoi(s) < 1 || atoi(s) > 7)
        return false;
    return true;
}
// Affiche le menu des options du programme
void menu(void)
{
    printf("\t\t1) Ajouter un compte\n");
    printf("\t\t2) Afficher les donnees d un compte utilisateur\n");
    printf("\t\t3) Modifier un compte client\n");
    printf("\t\t4) Deposer/retirer (ajouter ou prendre de l argent)\n");
    printf("\t\t5) Supprimer un utilisateur\n");
    printf("\t\t6) Afficher tous les utilisateurs\n");
    printf("\t\t7) Quitter\n\n");
    printf("\t\t*****************************************************\n");
    printf("\t\t*****************************************************\n");
    printf("\t\t***VEUILLEZ INSERER L OPERATION QUE VOUS SOUHAITEZ***\n");
    printf("\t\t*****************************************************\n");
    printf("\t\t*****************************************************\n\n");
}
// Ajoute un nouvel utilisateur à la liste des utilisateurs
void push(user_data **data, char *name, char *password, int money, int age)
{
    user_data *newUser = (user_data *)malloc(sizeof(user_data));
    newUser->fullName = strdup(name);
    newUser->password = strdup(password);
    newUser->moneyBalance = money;
    newUser->age = age;
    newUser->next = *data;
    *data = newUser;
}
// Affiche les informations d'un utilisateur en fonction de son nom
void afficher_utilisateur_compte(user_data *data, char *name)
{
    while (data != NULL)
    {
        if (strcmp(data->fullName, name) == 0)
        {
            printf("Nom de l utilisateur : %s\n", data->fullName);
            printf("Age de l utilisateur : %d\n", data->age);
            printf("Solde d argent de l'utilisateur : %d\n", data->moneyBalance);
            return;
        }
        data = data->next;
    }
    printf("Utilisateur introuvable\n");
}
 
// Modifie les informations d'un compte utilisateur (nom, âge, mot de passe)
void edit_user_account(user_data **data, char *name, int new_age, char *new_name, char *new_password)
{
    while ((*data) != NULL)
    {
        if (strcmp((*data)->fullName, name) == 0)
        {
            (*data)->age = new_age;
            free((*data)->fullName);
            free((*data)->password);
            (*data)->fullName = strdup(new_name);
            (*data)->password = strdup(new_password);
            return;
        }
        (*data) = (*data)->next;
    }
    printf("Utilisateur introuvable\n");
}
 
// Supprime un utilisateur de la liste des utilisateurs
void delete_user(user_data **data, char *name)
{
    user_data *p = *data;
    user_data *q = NULL;
    if (p != NULL && strcmp(p->fullName, name) == 0)
    {
        *data = p->next;
        free(p);
        return;
    }
    while (p != NULL && strcmp(p->fullName, name) != 0)
    {
        q = p;
        p = p->next;
    }
    if (p == NULL)
        return;
    q->next = p->next;
    free(p);
}
 
// Modifie le solde d'argent d'un utilisateur (ajouter ou retirer)
void edit_money(user_data **data, char *name, int flag, int amount)
{
    while ((*data) != NULL)
    {
        if (strcmp((*data)->fullName, name) == 0)
        {
            if (flag == 1)
                (*data)->moneyBalance += amount;
            else if (flag == 2)
            {
                int temp = (*data)->moneyBalance - amount;
                if (temp < 0)
                    printf("Cette operation ne peut pas être effectuee, votre solde passera en dessous de zero\n");
                else
                    (*data)->moneyBalance -= amount;
            }
            return;
        }
        (*data) = (*data)->next;
    }
    printf("Nom d utilisateur non valide\n");
}
 
// Affiche la liste de tous les utilisateurs
void display_user_list(user_data *data)
{
    printf("Liste des utilisateurs :\n");
    while (data != NULL)
    {
        printf("Nom de l utilisateur : %s\n", data->fullName);
        printf("Age de l utilisateur : %d\n", data->age);
        printf("Solde d argent de l utilisateur : %d\n", data->moneyBalance);
        printf("--------------------------\n");
        data = data->next;
    }
}
 
// Enregistre les données des utilisateurs dans un fichier texte
void save_user_data(user_data *data)
{
    FILE *file = fopen("user_data.txt", "wt+");
    if (file == NULL)
    {
        printf("LE FICHIER N EXITE PAS\n");
    }
    while (data != NULL)
    {
        fprintf(file, " fullName : %s\n password : %s\n moneyBalance : %d\n age : %d\n", data->fullName, data->password, data->moneyBalance, data->age);
        data = data->next;
    }
    fclose(file);
}
// Charge les données des utilisateurs à partir d'un fichier texte
void load_user_data(user_data **data)
{
    FILE *file = fopen("user_data.txt", "rt+");
    if (file == NULL)
    {
        printf("\t\t Erreur lors de l ouverture du fichier\n");
        return;
    }
    char name[100];
    char password[100];
    int money;
    int age;
    while (fscanf(file, "%s %s %d %d\n", name, password, &money, &age) != EOF)
    {
        push(data, name, password, money, age);
    }
    fclose(file);
}
int main()
{
    printf("\t\t************************************************************************\n");
    printf("\t\t************************************************************************\n");
    printf("\t\t******* BONJOUR ET BIENVENUE AU PROGRAMME DE GESTION BANCAIRE **********\n");
    printf("\t\t************************************************************************\n");
    printf("\t\t************************************************************************\n");
    printf("\t\t************************************************************************\n");
    printf("\t\t*************  CREATED BY Yahya Labser & Douaa Maher   *****************\n");

    bool is_one = true;
    static user_data *bank_users;
    bank_users = NULL;

    load_user_data(&bank_users); // Charger les données des utilisateurs à partir du fichier
    while (is_one)
    {
        menu();
        char choice[100];
        char password[100];
        int age;
        int money;
        scanf("%s", choice);
        if (check_choice(choice) == 1)
        {
            if (choice[0] == '1')
            {
                char name[100];
                printf("Inserer le nom de l utilisateur\n");
                scanf("%s", name);
                printf("Inserer le mot de passe\n");
                scanf("%s", password);
                printf("Inserer l age\n");
                scanf("%d", &age);
                push(&bank_users, name, password, money, age);
                printf("L utilisateur a ete ajoute \n");
            }
            else if (choice[0] == '2')
            {
                char name[100];
                printf("Inserer le nom de l utilisateur\n");
                scanf("%s", name);
                afficher_utilisateur_compte(bank_users, name);
                printf("Operation terminee\n");
            }
            else if (choice[0] == '3')
            {
                char name[100];
                char new_name[100];
                char new_password[100];
                int new_age;
                printf("Inserer le nom de compte que vous souhaitez modifier\n");
                scanf("%s", name);
                printf("Nouveau nom\n");
                scanf("%s", new_name);
                printf("Nouveau mot de passe\n");
                scanf("%s", new_password);
                printf("Nouvel age\n");
                scanf("%d", &new_age);
                edit_user_account(&bank_users, name, new_age, new_name, new_password);
                printf("L utilisateur a ete modifie avec succes\n");
            }
            else if (choice[0] == '4')
            {
                char name[100];
                int flag;
                printf("Inserer le nom du compte\n");
                scanf("%s", name);
                printf("Inserer 1 pour ajouter de l'argent au compte et 2 pour retirer de l argent du compte\n");
                scanf("%d", &flag);
                int amount;
                if (flag == 1)
                {
                    printf("Inserer le montant d argent que vous souhaitez ajouter\n");
                    scanf("%d", &amount);
                    edit_money(&bank_users, name, flag, amount);
                }
                else if (flag == 2)
                {
                    printf("Inserer le montant d argent que vous souhaitez retirer\n");
                    scanf("%d", &amount);
                    edit_money(&bank_users, name, flag, amount);
                }
                else
                    printf("Choix invalide\n");
                printf("Operation terminee\n");
            }
            else if (choice[0] == '5')
            {
                char name[100];
                printf("Inserer le nom de l utilisateur que vous souhaitez supprimer\n");
                scanf("%s", name);
                delete_user(&bank_users, name);
                printf("L utilisateur a ete supprime\n");
            }
            else if (choice[0] == '6')
            {
                display_user_list(bank_users);
                printf("Operation terminee\n");
            }
            else
            {
                is_one = false;
                save_user_data(bank_users); // Sauvegarder les données des utilisateurs dans le fichier avant de quitter
            }
        }
        else
            printf("Choix non valide\n");
        save_user_data(bank_users);
        load_user_data(bank_users);
    }
    printf("Merci et au revoir\n");
    return 0;
}