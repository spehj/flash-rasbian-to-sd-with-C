#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>

#define NPOD 1048576/* privzeta velikost bloka za prepis z read/write = 1MB*/

int main(int argc, char *argv[])
{
    char *pom; // Kazalec za alokacijo pomnilnika
    int fi, fo; /* fi je input, fo je output */
    ssize_t n_pod, p_pod; // Koliko podatkov potrebujemo (n_pod)
    if (argc == 4)
    {   
        /* Ce je velikost bloka za prepis podana, jo preberemo in shranimo. */
        sscanf(argv[3], "%ld", &n_pod);
    }
    else if (argc == 3)
    {   /* Ce velikost bloka za prepis ni podana, uporabimo privzeto. */
        n_pod = NPOD;
    }
    else
    {
        printf("\nUPORABA: %s <vhodna dat> <izhodna dat> [velikost bloka]\n\n", argv[0]);
        exit(1);
    }


    /* odpremo datoteko za branje, ime datoteke doloca argv[1] */
    if ((fi = open(argv[1], O_RDONLY)) == -1)
    { /* O_RDONLY je 0 */
        printf("%s: napaka open %s\n", argv[0], argv[1]);
        exit(2);
    }
    /* odpremo(ustvarimo) datoteko za pisanje, ime doloca argv[2] */
    /* 0644 pomeni da lastnik lahko bere, pise, skupina bere, ostali berejo */
    if ((fo = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    {
        printf("%s: napaka creat %s\n", argv[0], argv[2]);
        exit(3);
    }
    /* Zagotovimo si pomnilnik za podatke, najvec Npodatkov */
    if ((pom = malloc(n_pod)) == NULL)
    {
        printf("%s: napaka malloc\n", argv[0]);
        exit(4);
    }


    /* prepisujemo podatke do konca datoteke */
    printf("Zacenjamo pisanje podatkov v datoteko %s\n", argv[2]);
    printf("%s: velikost bloka %ld bajtov\n", argv[0], n_pod);

    while ((p_pod = read(fi, pom, n_pod)) != 0)
    {   
        /* Preverimo da ni napake pri branju */
        if (p_pod == -1)
        {
            printf("%s: napaka read %s\n", argv[0], argv[1]);
            exit(5);
        }

        /* Zapisujemo podatke iz bufferja v datoteko z deskriptorjem fo */
        /* V primeru da se zapisano stevilo podatkov ne ujema s pripravljenimi podatki */
        /* Koncaj pisanje */
        if (write(fo, pom, p_pod) != p_pod)
        {
            printf("%s: napaka write %s\n", argv[0], argv[2]);
            exit(6);
        }
    }

    /* Sporocilo, ce pride do napake pri zapiranju izvorne in koncne datoteke */
    if ((close(fi) == -1) || (close(fo) == -1))
    {
        printf("%s: napaka close\n", argv[0]);
        exit(7);
    }
    exit(0);
}
