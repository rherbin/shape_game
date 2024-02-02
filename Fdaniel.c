#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int recupScore(char *ligne)
{
    int i = 0, j;
    int scoreInt = 0;
    char score[50];
    while(ligne[i] != ' ')
    {
        score[i] = ligne[i];
        i++;
    }
    for (j=0; j<i; j++)
    {
        scoreInt += (score[j] - 48) * pow(10, i-j-1);
    }
    return scoreInt;
}


int highscore(int score) // cette fonction renvoie -1 si ce nest pas un highscore sinon il renvoie le numero de ligne (commence a 0) que devrait occuper le score
{
    FILE *fichier = fopen("score.txt", "r");
    char texte[50];
    int i = 0;
    if(fichier == NULL) // cas ou le fichier ne souvre pas
    {
        printf("le fichier ne s'ouvre pas");
        exit(1);
    }
    while(fgets(texte, 50, fichier))
    {
        printf("%d\n",recupScore(texte));
        if(recupScore(texte) < score  && i < 10)
        {
            fclose(fichier);
            return i;
        }
        i++;
    }
    fclose(fichier);
    return -1;
}

int main(){
    printf("%d", highscore(512));
}