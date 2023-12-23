#include <ctype.h>
#include <stdio.h>
#include <string.h>

void lower(char *str, int size);

void from_english(char *input_word, char *file_word, char *language_from, char *language_into, FILE *file);
void from_french(char *input_word, char *file_word, char *language_from, char *language_into, FILE *file);
void from_germany(char *input_word, char *file_word, char *language_from, char *language_into, FILE *file);

int check = 0;

int main()
{
    char input_word[20], file_word[20], language_from[8], language_into[8];
    int cond = 0;
    FILE *file;
    while (1)
    {
        do
        {
            cond = 0;
            printf("Choose the language you want to translate from : \n");

            printf("English         French       Germany\n");
            scanf("%s", language_from);

            lower(language_from, strlen(language_from));

            if (!((strcmp(language_from, "english") == 0) || (strcmp(language_from, "french") == 0) ||
                  (strcmp(language_from, "germany") == 0)))
            {
                printf("Not supported language!!\n");
                cond = 1;
            }
        }
        while (cond == 1);

        do
        {
            cond = 0;
            printf("Choose the language you want to translate into : \n");

            printf("English         French       Germany\n");
            scanf("%s", language_into);

            lower(language_into, strlen(language_into));

            if (!((strcmp(language_into, "english") == 0) || (strcmp(language_into, "french") == 0) ||
                  (strcmp(language_into, "germany") == 0)))
            {
                printf("Not supported language!!\n");
                cond = 1;
            }
        }
        while (cond == 1);

        while (1)
        {

            printf("Type the word you need to translate or (-1) to exit or (c) to choose languages : ");
            scanf("%s", input_word);
            if (strcmp(input_word, "-1") == 0)
            {
                return 1;
            }
            lower(input_word, strlen(input_word));
            if (strcmp(input_word, "c") == 0)
            {
                break;
                ;
            }
            file = fopen("words.csv", "r");
            if (strcmp(language_from, "english") == 0)
            {
                from_english(input_word, file_word, language_from, language_into, file);
                check = 0;
            }
            else if (strcmp(language_from, "french") == 0)
            {
                from_french(input_word, file_word, language_from, language_into, file);
                check = 0;
            }
            else if (strcmp(language_from, "germany") == 0)
            {
                from_germany(input_word, file_word, language_from, language_into, file);
                check = 0;
            }
        }
        fclose(file);
    }
}

void lower(char *str, int size)
{
    for (int i = 0; i < size; i++)
    {
        str[i] = tolower(str[i]);
    }
}

void from_english(char *input_word, char *file_word, char *language_from, char *language_into, FILE *file)
{

    char c;
    while (fread(file_word, 1, 20, file) == 20)
    {
        for (int idx = 0; idx < 20; idx++)
        {
            if (file_word[idx] == ' ')
            {
                file_word[idx] = '\0';
                if (strcmp(file_word, input_word) == 0)
                {
                    if (strcmp(language_into, "french") == 0)
                    {
                        if (strcmp(language_from, "english") != 0)
                        {
                            do
                            {
                                printf("do you mean language from english ?\n(y) for yes (n) for no : ");
                                scanf(" %c", &c);
                                if (c == 'n')
                                {
                                    goto a;
                                }
                                if (c != 'y' && c != 'n')
                                {
                                    printf("not from choices !!!\n");
                                }
                            }
                            while (c != 'y' && c != 'n');
                        }
                        fread(file_word, 1, 20, file);
                        for (int i = 0; file_word[i] != ' '; i++)
                        {
                            printf("%c", file_word[i]);
                        }
                        printf("\n");
                        return;
                    }
                    else if (strcmp(language_into, "germany") == 0)
                    {
                        if (strcmp(language_from, "english") != 0)
                        {
                            do
                            {
                                printf("do you mean language from english ?\n(y) for yes (n) for no : ");
                                scanf(" %c", &c);
                                if (c == 'n')
                                {
                                    goto a;
                                }
                                if (c != 'y' && c != 'n')
                                {
                                    printf("not from choices !!!\n");
                                }
                            }
                            while (c != 'y' && c != 'n');
                        }
                        fseek(file, 20, SEEK_CUR);

                        fread(file_word, 1, 20, file);
                        for (int i = 0; file_word[i] != ' '; i++)
                        {
                            printf("%c", file_word[i]);
                        }
                        printf("\n");
                        return;
                    }
                    else if (strcmp(language_into, "english") == 0)
                    {
                        if (strcmp(language_from, "english") != 0)
                        {
                            do
                            {
                                printf("do you mean language from english ?\n(y) for yes (n) for no : ");
                                scanf(" %c", &c);
                                if (c == 'n')
                                {
                                    goto a;
                                    break;
                                }
                                if (c != 'y' && c != 'n')
                                {
                                    printf("not from choices !!!\n");
                                }
                            }
                            while (c != 'y' && c != 'n');
                        }
                        printf("%s\n", file_word);
                        return;
                    }
                }
                else
                {
                a:
                    fseek(file, 42, SEEK_CUR);
                    break;
                }
            }
        }
        if (file_word[19] == '.')
        {
            check++;
            if (check == 3)
            {
                printf("doesn't exist\n");
                return;
            }
            fseek(file, 0, SEEK_SET);
            from_french(input_word, file_word, language_from, language_into, file);
            break;
        }
    }
}

void from_french(char *input_word, char *file_word, char *language_from, char *language_into, FILE *file)
{

    char c;
    fseek(file, 20, SEEK_CUR);

    while (fread(file_word, 1, 20, file) == 20)
    {
        for (int idx = 0; idx < 20; idx++)
        {
            if (file_word[idx] == ' ')
            {
                file_word[idx] = '\0';
                if (strcmp(file_word, input_word) == 0)
                {
                    if (strcmp(language_into, "english") == 0)
                    {
                        if (strcmp(language_from, "french") != 0)
                        {
                            do
                            {
                                printf("do you mean language from french ?\n(y) for yes (n) for no : ");
                                scanf(" %c", &c);
                                if (c == 'n')
                                {
                                    goto a1;
                                }
                                if (c != 'y' && c != 'n')
                                {
                                    printf("not from choices !!!\n");
                                }
                            }
                            while (c != 'y' && c != 'n');
                        }
                        fseek(file, -40, SEEK_CUR);
                        fread(file_word, 1, 20, file);
                        for (int i = 0; file_word[i] != ' '; i++)
                        {
                            printf("%c", file_word[i]);
                        }
                        printf("\n");
                        return;
                    }
                    else if (strcmp(language_into, "germany") == 0)
                    {
                        if (strcmp(language_from, "french") != 0)
                        {
                            do
                            {
                                printf("do you mean language from french ?\n(y) for yes (n) for no : ");
                                scanf(" %c", &c);
                                if (c == 'n')
                                {
                                    goto a1;
                                }
                                if (c != 'y' && c != 'n')
                                {
                                    printf("not from choices !!!\n");
                                }
                            }
                            while (c != 'y' && c != 'n');
                        }

                        fread(file_word, 1, 20, file);
                        for (int i = 0; file_word[i] != ' '; i++)
                        {
                            printf("%c", file_word[i]);
                        }
                        printf("\n");
                        return;
                    }
                    else if (strcmp(language_into, "french") == 0)
                    {
                        if (strcmp(language_from, "french") != 0)
                        {
                            do
                            {
                                printf("do you mean language from french ?\n(y) for yes (n) for no : ");
                                scanf(" %c", &c);
                                if (c == 'n')
                                {
                                    goto a1;
                                }
                                if (c != 'y' && c != 'n')
                                {
                                    printf("not from choices !!!\n");
                                }
                            }
                            while (c != 'y' && c != 'n');
                        }
                        printf("%s\n", file_word);
                        return;
                    }
                }
                else
                {
                a1:
                    fseek(file, 42, SEEK_CUR);
                    break;
                }
            }
        }

        if (file_word[19] == '.')
        {
            check++;
            if (check == 3)
            {
                printf("doesn't exist\n");
                return;
            }
            fseek(file, 0, SEEK_SET);
            from_germany(input_word, file_word, language_from, language_into, file);
            break;
        }
    }
}

void from_germany(char *input_word, char *file_word, char *language_from, char *language_into, FILE *file)
{

    char c;
    fseek(file, 40, SEEK_CUR);

    while (fread(file_word, 1, 20, file) == 20)
    {
        for (int idx = 0; idx < 20; idx++)
        {
            if (file_word[idx] == ' ')
            {
                file_word[idx] = '\0';
                if (strcmp(file_word, input_word) == 0)
                {

                    if (strcmp(language_into, "english") == 0)
                    {
                        if (strcmp(language_from, "germany") != 0)
                        {
                            do
                            {
                                printf("do you mean language from germany ?\n(y) for yes (n) for no : ");
                                scanf(" %c", &c);
                                if (c == 'n')
                                {

                                    goto a2;
                                }
                                if (c != 'y' && c != 'n')
                                {
                                    printf("not from choices !!!\n");
                                }
                            }
                            while (c != 'y' && c != 'n');
                        }
                        fseek(file, -60, SEEK_CUR);
                        fread(file_word, 1, 20, file);
                        for (int i = 0; file_word[i] != ' '; i++)
                        {
                            printf("%c", file_word[i]);
                        }
                        printf("\n");
                        return;
                    }
                    else if (strcmp(language_into, "french") == 0)
                    {
                        if (strcmp(language_from, "germany") != 0)
                        {
                            do
                            {
                                printf("do you mean language from germany ?\n(y) for yes (n) for no : ");
                                scanf(" %c", &c);
                                if (c == 'n')
                                {
                                    goto a2;
                                }
                                if (c != 'y' && c != 'n')
                                {
                                    printf("not from choices !!!\n");
                                }
                            }
                            while (c != 'y' && c != 'n');
                        }
                        fseek(file, -40, SEEK_CUR);
                        fread(file_word, 1, 20, file);
                        for (int i = 0; file_word[i] != ' '; i++)
                        {
                            printf("%c", file_word[i]);
                        }
                        printf("\n");
                        return;
                    }
                    else if (strcmp(language_into, "germany") == 0)
                    {
                        if (strcmp(language_from, "germany") != 0)
                        {
                            do
                            {
                                printf("do you mean language from germany ?\n(y) for yes (n) for no : ");
                                scanf(" %c", &c);
                                if (c == 'n')
                                {
                                    goto a2;
                                }
                                if (c != 'y' && c != 'n')
                                {
                                    printf("not from choices !!!\n");
                                }
                            }
                            while (c != 'y' && c != 'n');
                        }
                        printf("%s\n", file_word);
                        return;
                    }
                }
                else
                {
                a2:
                    fseek(file, 42, SEEK_CUR);
                    break;
                }
            }
        }
        if (file_word[19] == '.')
        {
            check++;
            if (check == 3)
            {
                printf("doesn't exist\n");
                return;
            }
            fseek(file, 0, SEEK_SET);
            from_english(input_word, file_word, language_from, language_into, file);
            break;
        }
    }
}
