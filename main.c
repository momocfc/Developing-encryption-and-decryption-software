#include <stdio.h>
#include <string.h>
#include <math.h>
#include<time.h>
#include <strings.h>
#include <stdlib.h>

int RSA(int p , int q, char k[]);
void random (int *p,int *q);
void caesar_encryption(char a[],int key);
void caesar_decryption (char B[],int key);
void remove_spaces(char txt_nospaces[], int len);
void remove_duplicates(char a[]);
void insert_x(char array[]);
void x_atend(char plaintext[]);
void i_and_j(char plaintext[], int sizep, char keyword[], int sizekey);
void fill_matrix(char arr[5][5], char keyword[]);
void print_matrix(char arr[5][5], char keyword[5]);
void encryption(char arr[5][5], char plaintext[], int rows[], int columns[], char enc[]);
void decryption(char arr[5][5], char enc[], int rows2[], int columns2[], char dyc[]);
void remove__spaces(char txt[], int len);
void encryption_railfence(char txt[], int depth, int len);
int readfile(char arr[]);
int writefile(char arr[]);
int main(void)
{
    int method;
    char plaintext[10000];
    printf("What type of input do you want to encrypt/decrypt :\n1-User input\n2-File\n");
    scanf("%d", &method);
    if (method == 2) {
        readfile(plaintext);
    } else{
        printf("Please enter the plaintext : ");
        fflush(stdin);
        gets(plaintext);
    }

    int choice;
    printf("Please choose an algorithm: \n\n");
    printf("1. RSA algorithm\n2. Caesar Cypher\n3. Playfair Cipher Algorithm\n4. Rail fence cipher\n");
    scanf("%d",&choice);
    printf("\n");

    if (choice==1)
    {
        int p=3,q;

        random(&p,&q);
        printf("q=%d p=%d \n\n",q,p);

        RSA(p,q,plaintext);

    }
    else if(choice==2)
    {
        int key;
        printf("Please enter the key : ");
        scanf("%d",&key);
        printf("\nThe ciphertext after encryption :  ");
        caesar_encryption(plaintext,key);
        writefile(plaintext);
        printf("\nThe plaintext after decryption :  ");
        caesar_decryption(plaintext,key);

    }

    else if(choice==3){
        int i, j, k;

        char keyword[30];
        char arr[5][5] = {'a', 'b', 'c', 'd', 'e',
                          'f', 'g', 'h', 'ij', 'k',
                          'l', 'm', 'n', 'o', 'p',
                          'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

        fflush(stdin);
        printf("Please enter keyword:");
        gets(keyword);
        printf("\n");

        remove_spaces(keyword, strlen(keyword));
        remove_duplicates(keyword);
        printf("keyword is:");
        puts(keyword);
        insert_x(plaintext);
        strcat(keyword, "abcdefghiklmnopqrstuvwxyz");
        remove_duplicates(keyword);
        remove_spaces(plaintext, strlen(plaintext));
        x_atend(plaintext);

        printf("plaintext is:");
        puts(plaintext);
        printf("\n\n\n");
        i_and_j(plaintext, strlen(plaintext), keyword, strlen(keyword));
        fill_matrix(arr, keyword);
        print_matrix(arr, keyword);

        int rows[100], columns[100];
        char enc[100];
        printf("\nThe ciphertext after encryption : ");
        encryption(arr, plaintext, rows, columns, enc);


        int rows2[100], columns2[100];
        char dyc[100];
        printf("\nThe plaintext after decryption : \n");
        decryption(arr, enc, rows2, columns2, dyc);

    }

    else if(choice==4){
        char txt_nospaces[100] = {};
        int depth;

        printf("Please enter the depth:");
        scanf("%d", &depth);

        int i = 0, j = 0;
        int len = strlen(plaintext);
        remove__spaces(plaintext, len);
        printf("\nThe ciphertext after encryption : ");
        encryption_railfence(plaintext, depth, len);

        printf("\n");
    }


    system("pause");
}
int readfile(char arr[])
{
    int choice;
    char ch;

    int i=0;
    FILE *textfile;


    textfile = fopen("text.txt", "r");
    if(textfile == NULL)
        return 1;
    printf("read text from text.txt:");
    while((ch=getc(textfile))!=EOF)
    {
        printf("%c",ch);
        arr[i]=ch;
        i++;
    }

    printf("\n");

    fclose(textfile);



    return 0;
}

void caesar_encryption(char a[],int key)
{
    int ch;

    for(int i=0;i<strlen(a);i++)
    {
        ch=a[i];
        key=key%26;
        if(ch >= 'a' && ch <= 'z'){
            ch = ch + key;
            if(ch > 'z'){
                ch = ch - 26;
            }
            a[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z'){
            ch = ch + key;
            if(ch > 'Z'){
                ch = ch - 26;
            }
            a[i] = ch;
        }
    }
    puts(a);


}
void caesar_decryption (char B[],int key)
{
    int ch;

    for(int i=0;i<strlen(B);i++)
    {
        ch=B[i];
        key=key%26;
        if(ch >= 'a' && ch <= 'z'){
            ch = ch - key;
            if(ch < 'a'){
                ch =ch+26 ;

            }
            B[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z'){
            ch = ch - key;
            if(ch < 'A')
            {
                ch = ch + 26;
            }

            B[i] = ch;
        }


    }
    puts(B);
}

int RSA( int p , int q, char k[])
{
    long long x=strlen(k);
    int e=1,d=0,c2,g,m,m2;
    // assume p=3,q=13 and the message is 'x' in ascii=120
    int n = p*q;                                      //n=39
    int euler=(p-1)*(q-1);                            //euler = 24
    char ch,f[10000],j[100000];

//first calculate e that is prime and comprime with euler and n


    for(int j=3;j<euler;j++){

        for(int i=2;i<=j;i++){
            if(j/i==1&&j%i==0&&n%j!=0&&euler%j!=0){
                e=j;
                break;}
            else if(j%i==0)
                break;
        }
        if(e==j)
            break;
    }                                                   //e=5
//calculate d that can be calculated by this equation (d*e%euler=1)
    for(int j=1;j!=0;j++){

        if(j*e%euler==1 ){
            d=j;
            break;}
    }                                                   //d=5
    printf ("e=%d d=%d \n",e,d);

    for(int i=0;i<x;i++)
    {
        if(k[i]==' '){
            f[i]=' ';
            j[i]=' ';
            continue;}
        if(k[i]=='\n'){
            f[i]='\n';
            j[i]='\n';
            continue;}

//here i divided the ascii code to three parts , nearby each part has 31 characters .

        if (k[i]>='A'&&k[i]<='`')
            m=k[i]-64;
        else if (k[i]>='a'&&k[i]<='~')
            m=k[i]-96;                                //m=120-96=24

        else if(k[i]>='!'&&k[i]<='@')
            m=k[i]-32;

        //this next loop calculates (m^e)%n and it makes it easier to take modulus each loop to avoid getting big number from the power

        int l = 1;
        for(int j = 0; j < e; j++)
        {
            l = l * m;

            l = l % n;
        }                                          //l=(24^5)%39=33

//this part only aims to make number smaller to be easy to print in the range that we chose

        int h=31;
        while (1){
            if (l%h==0)
                h++;
            else break;}
// g will help in decryption to restore the number that was calculated from equation c=(m^e)%n which is 33
        g=l/h;                               //g=33/31=1
        l=l%h;                               //g=33%31=2


        if (k[i]>='A'&&k[i]<='`'){
            ch=l+64;

        }
        else if (k[i]>='a'&&k[i]<='~'){
            ch=l+96;}                              //ch=2+96=98

        else if(k[i]>='!'&&k[i]<='@')
            ch=l+32;


        f[i]=ch;                             //98--->'b'
        if(f[i]==' '){
            continue;
        }
        c2=f[i];

        if (k[i]>='a'&&k[i]<='~')
            c2=c2-96;                         //c2=98-96=2

        else if (k[i]>='A'&&k[i]<='`')
            c2=c2-64;

        else if(k[i]>='!'&&k[i]<='@')
            c2=c2-32;

        c2=g*h+c2;             //c2=1*31+2=33           here we use g and h to get back the number that was calculated in c=(m^e)%n which  is 33

        l = 1;
        for(int j = 0; j < d; j++)
        {
            l = l * c2;
            l = l % n;
        }                                     //l=24
        if (k[i]>='a'&&k[i]<='~')
        {
            m2=l+96;                 //m2=24+96=120   (the input 'x')
        }

        else if (k[i]>='A'&&k[i]<='`')
        {
            m2=l+64;
        }

        else if(k[i]>='!'&&k[i]<='@')
            m2=l+32;


        j[i]=m2;                     //=120---->'x'
    }
    printf("The ciphertext after encryption :  ");
    puts(f);
    writefile(f);
    printf("\nThe plaintext after decryption :  ");
    puts(j);
}

int writefile(char arr[])
{
    int choice;
    char ch;

    int i=0;
    FILE *textfilew;



    textfilew = fopen("ciphertext.txt", "w");


    while(i<strlen(arr))
    {
        putc(arr[i],textfilew);

        i++;
    }

    printf("\n");
    printf("Cipher text Saved to ciphertext.txt succesfully\n");

    fclose(textfilew);


}


void remove_spaces(char txt_nospaces[], int len)
{
    for(int i = 0; i < len; i++)
    {
        if(txt_nospaces[i] == ' ')
        {
            for(int j=i;j<len;j++)
            {
                txt_nospaces[j]=txt_nospaces[j+1];
            }
            len--;
        }
    }
}

void remove_duplicates(char a[])
{
    int i, j, k;
    int number = strlen(a);
    for (i = 0; i < number; i++)
    {
        for (j = i + 1; j < number; j++)
        {
            if (a[i] == a[j])
            {
                for (k = j; k < number; k++)
                {
                    a[k] = a[k + 1];
                }
                j--;
                number--;
            }
        }
    }
}

void insert_x(char array[])
{

    int index = strlen(array);
    for (int i = 0; i < strlen(array); i+=2)
    {
        if (array[i] == array[i + 1])
        {
            for (int j = strlen(array); j > i; j--)
            {
                array[j + 1] = array[j];
            }
            array[i + 1] = 'x';
        }
    }
}

void x_atend(char plaintext[])
{
    int x = strlen(plaintext);
    if (x % 2 != 0)
    {

        plaintext[x] = 'x';
    }
}

void i_and_j(char plaintext[], int sizep, char keyword[], int sizekey)
{
    for (int i=0;i<sizep;i++)
    {
        if (plaintext[i]=='j')
            plaintext[i]='i';
    }

    for (int i=0;i<sizekey;i++)
    {
        if (plaintext[i]=='j')
            plaintext[i]='i';
    }
}


void fill_matrix(char arr[5][5], char keyword[])
{
    for (int i = 0, k = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            arr[i][j] = keyword[k];
            k++;
        }
    }
}
void print_matrix(char arr[5][5], char keyword[5])
{

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf(" ");
            putchar(arr[i][j]);
        }
        printf("\n");
    }
}

void encryption(char arr[5][5], char plaintext[], int rows[], int columns[], char enc[])
{
    for (int i = 0; i < strlen(plaintext); i += 2)
    {
        char a = plaintext[i];
        char b = plaintext[i + 1];

        for (int rowIndex = 0; rowIndex < 5; rowIndex++)
        {
            for (int colIndex = 0; colIndex < 5; colIndex++)
            {
                if (arr[rowIndex][colIndex] == a)
                {
                    rows[i] = rowIndex;
                    columns[i] = colIndex;
                }
                if (arr[rowIndex][colIndex] == b)
                {
                    rows[i + 1] = rowIndex;
                    columns[i + 1] = colIndex;
                }

            }
        }
    }

    for (int i = 0; i < strlen(plaintext)-1; i += 2)
    {

        if (rows[i] == rows[i + 1])
        {
            enc[i] = arr[rows[i]][columns[i] + 1];
            enc[i + 1] = arr[rows[i + 1]][columns[i + 1] + 1];

            if (columns[i] + 1 > 4)
            {
                enc[i] = arr[rows[i]][0];
            }
            if (columns[i + 1] + 1 > 4)
            {
                enc[i + 1] = arr[rows[i + 1]][0];
            }
        }

        else if (columns[i] == columns[i + 1])
        {
            enc[i] = arr[rows[i] + 1][columns[i]];
            enc[i + 1] = arr[rows[i + 1] + 1][columns[i + 1]];

            if (rows[i] + 1 > 4)
            {
                enc[i] = arr[0][columns[i]];
            }
            if (rows[i + 1] + 1 > 4)
            {

                enc[i + 1] = arr[0][columns[i + 1]];
            }
        }

        else
        {
            enc[i] = arr[rows[i]][columns[i + 1]];
            enc[i + 1] = arr[rows[i + 1]][columns[i]];
        }
    }
    writefile(enc);
    for (int i = 0; i < strlen(enc) ; i++)
    {
        printf("%c", enc[i]);
    }


    printf("\n");
}

void decryption(char arr[5][5], char enc[], int rows2[], int columns2[], char dyc[])
{
    for (int i = 0; i < strlen(enc); i += 2)
    {
        char c = enc[i];
        char d = enc[i + 1];

        for (int rowIndex = 0; rowIndex < 5; rowIndex++)
        {
            for (int colIndex = 0; colIndex < 5; colIndex++)
            {
                if (arr[rowIndex][colIndex] == c)
                {
                    rows2[i] = rowIndex;
                    columns2[i] = colIndex;
                }
                if (arr[rowIndex][colIndex] == d)
                {
                    rows2[i + 1] = rowIndex;
                    columns2[i + 1] = colIndex;
                }

            }
        }
    }

    for (int i = 0; i < strlen(enc)-1; i += 2)
    {

        if (rows2[i] == rows2[i + 1])
        {
            dyc[i] = arr[rows2[i]][columns2[i] - 1];
            dyc[i + 1] = arr[rows2[i + 1]][columns2[i + 1] - 1];

            if (columns2[i] - 1 < 0)
            {
                dyc[i] = arr[rows2[i]][4];
            }
            if (columns2[i + 1] -1 < 0)
            {
                dyc[i + 1] = arr[rows2[i + 1]][4];
            }
        }

        else if (columns2[i] == columns2[i + 1])
        {

            dyc[i] = arr[rows2[i] -1][columns2[i]];
            dyc[i + 1] = arr[rows2[i + 1] - 1][columns2[i + 1]];

            if (rows2[i] - 1 <0)
            {
                dyc[i] = arr[4][columns2[i]];
            }
            if (rows2[i + 1] - 1 < 0)
            {

                dyc[i + 1] = arr[4][columns2[i + 1]];
            }
        }

        else
        {
            dyc[i] = arr[rows2[i]][columns2[i + 1]];
            dyc[i + 1] = arr[rows2[i + 1]][columns2[i]];
        }
    }

    for (int i = 0; i < strlen(enc) ; i++)
    {
        printf("%c", dyc[i]);
    }

    printf("\n");
    int yes=0;

    for (int i = 0; i < strlen(enc) ; i++)
    {
        if (dyc[i]=='i')
        {
            dyc[i]='j';
            yes=1;
        }

    }
    for (int i=0;i<strlen(enc) ; i++)
    {
        if (yes==0)
            break;
        printf("%c", dyc[i]);
    }
    printf("\n");

}

void remove__spaces(char txt[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (txt[i] == ' ')
        {
            for (int j = i; j < len; j++)
            {
                txt[j] = txt[j + 1];
            }
            len--;
        }
    }
}

void encryption_railfence(char txt[], int depth, int len)
{
    for (int row = 0; row < depth; row++)
        for (int x = row; x < len; x += depth)
        {
            if (txt[x] == '\0') continue;
            printf("%c", txt[x]);

        }

}
void random (int *p,int *q){
    int lower=11,upper=100;
    srand(time(NULL));
    *q=(rand()%(upper-lower+1))+lower;

    for(int i=2;i<=*q;i++){
        if(*q/i==1&&*q%i==0&&*q!=*p){
            *q=i;
            break;}
        else if(*q%i==0){
            *q=(rand()%(upper-lower+1))+lower;
            i=1;
            continue;
        }

    }
}