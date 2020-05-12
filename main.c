#define MAX_NAME_LENGTH 45
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

char **sehir;///sehir kod.txt dosyasındaki şehir isimlerini tutar
int satirSayisi=0;///sehir kod.txt dosyasındaki satır sayısını tutar
int satirSayisi2=0;///sehir mesafe.txt dosyasındaki satır sayısını tutar
char *sehirPtr[MAX_NAME_LENGTH];///strtok ile ayrılan isimleri geçici olarak tutar
char satir[60];///fscanf ile alınan satırları tutar
char **sehir1;///sehir mesafe.txt dosyasındaki ilk şehirlerin isimlerini tutar
char **sehir2;///sehir mesafe.txt dosyasındaki ikinci şehirlerin isimlerini tutar
int  *kod;///sehir kod.txt dosyasındaki şehir kodlarını tutar
int  *mesafe;///sehir mesafe.txt dosyasındaki mesafeleri tutar
int **komsulukMatrisi;
int i,j,k;
int inf=SHRT_MAX;
char giris1[MAX_NAME_LENGTH];///1. şehir ismi
char giris2[MAX_NAME_LENGTH];///2. şehir ismi
int secim;///1, seçilen şehrin diğer şehirlere uzaklığını, 2 ise seçilen iki şehir arasındaki uzaklığı yazdıracağını belirtir

void menu();
void dosyadanOkuma();
void komsulukMatrisiOlustur();
void dijkstra(int baslangicIndex,int hedefIndex);

int main()
{
    dosyadanOkuma();
    komsulukMatrisiOlustur();
    menu();
    return 0;
}

void menu(){
    printf("Şehrin diğer tüm şehirlere uzaklığını görmek için 1, iki şehir arasındaki uzaklığı görmek için 2 giriniz: ");
    scanf("%d",&secim);
    if(secim!=1 && secim!=2){
        system("clear");
        printf("Hatalı giriş\n");
        menu();
    }

    if(secim==1){
        printf("Şehir adını giriniz: ");
        scanf("%s",giris1);
        for(i=0;i<satirSayisi;i++){
            if(strcmp(sehir[i],giris1)==0){
                dijkstra(i,0);
                break;
            }
        }
    }
    else {
        printf("İlk şehri giriniz: ");
        scanf("%s",giris1);
        printf("İkinci şehri giriniz: ");
        scanf("%s",giris2);
        for(i=0;i<satirSayisi;i++){
            for(j=0;j<satirSayisi;j++){
                if(strcmp(sehir[i],giris1)==0 && strcmp(sehir[j],giris2)==0){
                    dijkstra(i,j);
                    break;
                }
            }
        }
    }
}

void dosyadanOkuma(){
    FILE *fp = fopen("sehir kod.txt","r");
    fseek(fp,11,SEEK_SET);
    while(fscanf(fp,"%s",sehirPtr)!=EOF){
        satirSayisi++;
    }

    kod = (int*)malloc(satirSayisi*sizeof(int));
    sehir=(char**)malloc(satirSayisi*sizeof(char*));

    rewind(fp);
    fseek(fp,11,SEEK_SET);

    int length;
    while(fscanf(fp,"%s",satir)!=EOF){
        *sehirPtr=strtok(satir,"-");
        length=strlen(*sehirPtr);
        sehir[i]=(char *)malloc(length*sizeof(char));
        strcpy(sehir[i],*sehirPtr);
        kod[i]=atoi(strtok(NULL,"\n"));
        i++;
    }
    fclose(fp);

    fp=fopen("sehir mesafe.txt","r");
    fseek(fp,22,SEEK_SET);

    while(fscanf(fp,"%s",sehirPtr)!=EOF){
        satirSayisi2++;
    }

    sehir1=(char**)malloc(satirSayisi2*sizeof(char*));
    sehir2=(char**)malloc(satirSayisi2*sizeof(char*));
    mesafe = (int*)malloc(satirSayisi2*sizeof(int));

    rewind(fp);
    fseek(fp,22,SEEK_SET);
    i=0;
    while(fscanf(fp,"%s",satir)!=EOF){
        *sehirPtr=strtok(satir,"-");
        length=strlen(*sehirPtr);
        sehir1[i]=(char *)malloc(length*sizeof(char));
        strcpy(sehir1[i],*sehirPtr);
        *sehirPtr=strtok(NULL,"-");
        length=strlen(*sehirPtr);
        sehir2[i]=(char *)malloc(length*sizeof(char));
        strcpy(sehir2[i],*sehirPtr);
        mesafe[i]=atoi(strtok(NULL,"\n"));
        i++;
    }

}

void komsulukMatrisiOlustur(){

    komsulukMatrisi=(int**)malloc(satirSayisi*sizeof(int*));
    for(i=0;i<satirSayisi;i++){
        komsulukMatrisi[i]=(int*)malloc(satirSayisi*sizeof(int));
    }

    for(i=0;i<satirSayisi;i++){
        for(j=0;j<satirSayisi;j++){
            komsulukMatrisi[i][j]=inf;
        }
    }

    for(i=0;i<satirSayisi2;i++){
        for(j=0;j<satirSayisi;j++){
            if(strcmp(sehir1[i],sehir[j])==0){
                for(k=0;k<satirSayisi;k++){
                    if(strcmp(sehir2[i],sehir[k])==0)
                        komsulukMatrisi[j][k]=komsulukMatrisi[k][j]=mesafe[i];
                }
            }
        }
    }
}

void dijkstra(int baslangicIndex,int hedefIndex)
{
    int toplamYol[satirSayisi],pred[satirSayisi];
    bool visited[satirSayisi];
    int enKisaYol,nextnode;

    for(i=0;i<satirSayisi;i++)
    {
        toplamYol[i]=komsulukMatrisi[baslangicIndex][i];
        pred[i]=baslangicIndex;
        visited[i]=false;
    }

    toplamYol[baslangicIndex]=0;
    visited[baslangicIndex]=true;

    for(i=0;i<satirSayisi-2;i++)
    {
        enKisaYol=inf;
        for(j=0;j<satirSayisi;j++){
            if(toplamYol[j]<enKisaYol&&!visited[j])
            {
                enKisaYol=toplamYol[j];
                nextnode=j;
            }
        }
            visited[nextnode]=true;
            for(j=0;j<satirSayisi;j++)
                if(!visited[j])
                    if(enKisaYol+komsulukMatrisi[nextnode][j]<toplamYol[j])
                    {
                        toplamYol[j]=enKisaYol+komsulukMatrisi[nextnode][j];
                        pred[j]=nextnode;
                    }

    }
    if(secim==1){
        for(i=0;i<satirSayisi;i++){
            if(i!=baslangicIndex){
                printf("\n%s-%s arası en kısa yol = %d  ",sehir[baslangicIndex],sehir[i],toplamYol[i]);
                printf("Güzergah: %s",sehir[i]);

                j=i;
                do
                {
                    j=pred[j];
                    printf("<-%s",sehir[j]);
                }while(j!=baslangicIndex);
            }
        }
    }
    else {
        for(i=0;i<satirSayisi;i++){
            if(i!=baslangicIndex && i==hedefIndex){
                printf("\n%s-%s arası en kısa yol = %d  ",sehir[baslangicIndex],sehir[hedefIndex],toplamYol[hedefIndex]);
                printf("Güzergah: %s",sehir[hedefIndex]);
                j=i;
                while(j!=baslangicIndex) {
                    j=pred[j];
                    printf("<-%s",sehir[j]);
                }
            }
        }
    }
}
