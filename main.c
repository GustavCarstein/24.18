#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct file_t
{
    FILE *f;
    int size;
};

struct txt
{
    char tekst[100];
};
int open_file(struct file_t* f, const char *filename);

struct file_t* find_min(const struct file_t* files, int size);

void close_file(struct file_t* f);

int main()
{
    const int R=5;
    const int Buf=100;

    printf("Podaj nazwy plikow: ");
    struct file_t baza[R],*pBaza=baza;
    int i,counter=0;

    struct txt nazwy[R],*pNazwy=nazwy;

    for(i=0; ; i++)
    {
        char Txt[Buf],*pTxt=Txt;
        fgets(pTxt,Buf,stdin);

        if(*pTxt=='\n')
            break;

        *(pTxt+strlen(pTxt)-1)='\0';
        if (counter<5)
        {
            int check=open_file((pBaza+i),pTxt);
            if(check!=1)
            {
                i--;
            }
            else
            {
                strcpy((pNazwy+counter)->tekst,pTxt);
                counter++;
            }
        }

    }
    if(counter==0)
    {
        printf("Error");
        return 1;
    }

    struct file_t test,*pTest=&test;

    printf("Podaj tekst do zapisania do pliku: ");
    const int Bufor=100000;

    for(int i=0;; i++)
    {

        pTest=find_min(pBaza,counter);
        if(pTest!=NULL)
        {
            int flag=0;
            for(int i=0; i<counter; i++)
            {
                if(((pBaza+i)->size)==pTest->size)
                {
                    flag=i;
                    break;
                }
            }
            pTest->f=fopen((pNazwy+flag)->tekst,"a");
            if(pTest->f!=NULL)
            {
                char Txt[Bufor],*pTxt=Txt;
                fgets(pTxt,Bufor,stdin);
                if(*pTxt=='\n')
                    break;
                fprintf(pTest->f,"%s",pTxt);
                close_file(pTest);
            }
        }

        for(int i=0; i<counter; i++)
        {
            open_file((pBaza+i),(pNazwy+i)->tekst);
        }
    }

    printf("Files saved");


    return 0;
}

void close_file(struct file_t* f)
{
    if(f!=NULL && (f->f)!=NULL)
    {
        fclose(f->f);
    }
}

struct file_t* find_min(const struct file_t* files, int size)
{
    if(files==NULL || files->f==NULL|| size<=0)
    {
        return NULL;
    }
    int min=0;
    int index=0;
    int i=0;
    for(i=0; i<size; i++)
    {

        if(i==0)
        {
            min=(files+i)->size;
            index=i;
        }
        if(min>(files+i)->size)
        {
            min=(files+i)->size;
            index=i;
        }
    }
    return (struct file_t*)(files+index);
}


int open_file(struct file_t* f, const char *filename)
{
    if(f==NULL || filename==NULL)
    {
        return 0;
    }

    f->f=fopen(filename,"r");
    if( f->f!=NULL)
    {

        long long int size;
        fseek(f->f,0L,SEEK_END);
        size=ftell(f->f);
        rewind(f->f);
        f->size=size;
        close_file(f);
    }
    else
    {
        return 0;
    }
    return 1;
}
