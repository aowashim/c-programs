#include <stdio.h>

int cmp_str(char str1[], char str2[])
{
    int i =0;
    int cnt1 =0, cnt2 = 0;
    int rs,cm=0;
    int flag = 1;
    while(str1[i]!='\0' || str2[i]!='\0')
    {
        cnt1++; cnt2++;

        if(str1[i]<=90)
            str1[i] += 32;
        if(str2[i]<=90)
            str2[i] += 32;
        if(str1[i] == str2[i])
            rs = 0;
        if(str1[i] != str2[i])
            rs = 1;
        if (flag == 1)
        {
             if (str1[i] < str2[i])
           {
               cm = -1;
               flag = 0;
           }

            else if (str1[i] > str2[i])
            {
                cm = 1;
                flag = 0;
            }
        }
        i++;
    }

    if (flag == 1)
        return 0;

    if(cm == -1)
        return 1;
    if(cm == 1)
        return -1;
}

int main()
{
    char s1[100], s2[100];
    printf("Enter your strings : ");
    gets(s1);
    gets(s2);
    int rs = cmp_str(s1,s2);
    printf("%d",rs);
    return 0;
}