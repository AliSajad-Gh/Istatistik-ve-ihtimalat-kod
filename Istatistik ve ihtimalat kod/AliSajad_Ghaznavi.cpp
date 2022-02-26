#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
 

void doldur(FILE *dosya2,int *hasta,int gun){
	int *ptr;
	int sayi;
	for(ptr=hasta;ptr<hasta+gun;ptr++){
		fscanf(dosya2,"%d",ptr);
	}
}

void sirala(int *hasta,int gun){
	int *ptr,*p;
	int temp;
	for(ptr=hasta;ptr<hasta+gun-1;ptr++){
		for(p=ptr+1;p<hasta+gun;p++){
			if(*p<*ptr){
				temp=*p;
				*p=*ptr;
				*ptr=temp;
			}
		}
	}
}

float aritmetikort(int *hasta,int gun){
	int *ptr;
	float toplam;
	for(ptr=hasta;ptr<hasta+gun;ptr++){
		toplam+=*ptr;
	}
	return (toplam/(float)gun);
}

void yazdir(int *hasta,int gun){
	
	int *ptr,i=1;
	for(ptr=hasta;ptr<hasta+gun;ptr++,i++){
		printf("%d.gun: %d \n",i,*ptr);
	}
}

void tepedeger(FILE *dosya,int *hasta,int gun){
	int *ptr,*p;
	int sayac=1;
	int tekraradet=1; 
	
	for(ptr=hasta;ptr<hasta+gun;ptr++)
	{
		sayac=1;
		for(p=ptr+1;p<hasta+gun;p++){
			if(*ptr==*p){
				sayac++;
			}
		}
		if(sayac>tekraradet){
			tekraradet=sayac;
		}
	}
	 
	for(ptr=hasta;ptr<hasta+gun;ptr++){
		
		sayac=1;
		for(p=ptr+1;p<hasta+gun;p++){
			
			if(*ptr==*p){
				sayac++;
			}
		}
		if((sayac==tekraradet)&&(tekraradet!=1)){
			
				fprintf(dosya,"%d adet %d var.Tepedeger=%d\n",tekraradet,*ptr,*ptr);
			
			
		}
	}
	if(tekraradet==1){
			printf("Tepedeger yok\n");
		}
	
}
int degisim_araligi(int *hasta,int gun){
	int *ptr=hasta;
	
	int ilk=ptr[0];
	int son=ptr[gun-1];
	return (son-ilk);
}

float ortmutlaksapma(int *hasta,int gun){
	int *ptr;
	float toplam=0.0;
	float aort=aritmetikort(hasta,gun);
	for(ptr=hasta;ptr<hasta+gun;ptr++){
		if(aort>*ptr)
		{ 
			toplam+=aort-*ptr;
		}
		else{
			toplam+=*ptr-aort;
		}
	}
	return (toplam/gun);
}

float varyans_bulma(int *hasta,int gun){
	int *ptr;
	float aort=aritmetikort(hasta,gun);
	float varyans;
	for(ptr=hasta;ptr<hasta+gun;ptr++){
		varyans+=pow((aort-*ptr),2); 
	}
	return (varyans/(gun-1)); 
}


float medyan(int *hasta,int gun){
	float ortanca;
	int *ptr=hasta;
	
	if(gun%2==0){ 
		float toplam=*(ptr+(gun/2))+*(ptr+((gun/2)-1)); 
		ortanca=toplam/2;
		return ortanca;
	}
	else{         
		ortanca=*(ptr+(gun/2));
		return ortanca;
	}
}


float standartsapma(int *hasta,int gun){
	return sqrt(varyans_bulma(hasta,gun)); 
}

float degisim_katsayisi(int *hasta,int gun){
	return (standartsapma(hasta,gun)/aritmetikort(hasta,gun)); 
}


int medyan_indexi_bulma(int *hasta,int ilk,int son){ 
	int index = son - ilk + 1;
    index = (index + 1) / 2 - 1;
    return index + ilk;
}
int ceyrekler_acikligi(int *hasta,int gun){ 
	int *ptr=hasta;
    int medyan_index = medyan_indexi_bulma(ptr, 0,gun);
    int alt_ceyrek = ptr[medyan_indexi_bulma(ptr, 0, medyan_index)]; 
    int ust_ceyrek = ptr[medyan_indexi_bulma(ptr, medyan_index , gun)];
    return (ust_ceyrek - alt_ceyrek);
}


int main(){
	FILE *dosya,*dosya2;
	dosya=fopen("181213090_AliSajad_Ghaznavi.txt","w");
	dosya2=fopen("input.txt","r");
	int *Khasta,*Ihasta,*Ahasta;  
	int gun=100;  
	
	Khasta=(int *)malloc(sizeof(int)*gun);
	doldur(dosya2,Khasta,gun);
	
	Ihasta=(int *)malloc(sizeof(int)*gun);
	doldur(dosya2,Ihasta,gun);
	
	Ahasta=(int *)malloc(sizeof(int)*gun);
	doldur(dosya2,Ahasta,gun);
	
	fprintf(dosya,"Konya Istanbul ve Ankara da Covid-19 son 100 günde yoðun bakimda hasta sayilari\n");
	printf("Konyada Covid19 hasta sayisi :\n");
	yazdir(Khasta,gun);
	printf("################################\n");
	
	sirala(Khasta,gun);
	fprintf(dosya,"\nKonya 100 günde Hasta sayisi);\n\n");
	fprintf(dosya,"Aritmetik Ortalama:%.2f\n",aritmetikort(Khasta,gun));
	fprintf(dosya,"Medyan=%.2f\n",medyan(Khasta,gun));
	tepedeger(dosya,Khasta,gun);
	fprintf(dosya,"Degisim Araligi= %d \n",degisim_araligi(Khasta,gun));
	fprintf(dosya,"Ortalama Mutlak Sapma= %.2f\n",ortmutlaksapma(Khasta,gun));
	fprintf(dosya,"Varyans= %.2f\n",varyans_bulma(Khasta,gun));
	fprintf(dosya,"Standart Sapma= %.4f\n",standartsapma(Khasta,gun));
	fprintf(dosya,"Degisim Katsayisi= %.4f\n",degisim_katsayisi(Khasta,gun));
	fprintf(dosya,"Ceyrekler Acikligi= %d\n",ceyrekler_acikligi(Khasta,gun));
	
	fprintf(dosya,"#################################################\n");
	
	printf("Istanbulda 100 gunde Covid19 hasta Sayisi:\n");
	yazdir(Ihasta,gun);
	printf("##################################\n");
	
	sirala(Ihasta,gun);
	fprintf(dosya,"Istanbul 100 günde hasta sayisi);\n\n");
	fprintf(dosya,"Aritmetik Ortalama:%.2f\n",aritmetikort(Ihasta,gun));
	fprintf(dosya,"Medyan=%.2f\n",medyan(Ihasta,gun));
	tepedeger(dosya,Ihasta,gun);
	fprintf(dosya,"Degisim Araligi= %d \n",degisim_araligi(Ihasta,gun));
	fprintf(dosya,"Ortalama Mutlak Sapma= %.2f\n",ortmutlaksapma(Ihasta,gun));
	fprintf(dosya,"Varyans= %.2f\n",varyans_bulma(Ihasta,gun));
	fprintf(dosya,"Standart Sapma= %.4f\n",standartsapma(Ihasta,gun));
	fprintf(dosya,"Degisim Katsayisi= %.4f\n",degisim_katsayisi(Ihasta,gun));
	fprintf(dosya,"Ceyrekler Acikligi= %d\n",ceyrekler_acikligi(Ihasta,gun));
	
	fprintf(dosya,"##############################################\n");
	
	printf("Ankarada 100 gunde Covid19 Hasta Sayisi:\n");
	yazdir(Ahasta,gun);
	printf("########################\n");
	
	sirala(Ahasta,gun);
	fprintf(dosya,"Ankara 100 günde Hasta sayisi;\n\n");
	fprintf(dosya,"Aritmetik Ortalama:%.2f\n",aritmetikort(Ahasta,gun));
	fprintf(dosya,"Medyan=%.2f\n",medyan(Ahasta,gun));
	tepedeger(dosya,Ihasta,gun);
	fprintf(dosya,"Degisim Araligi= %d \n",degisim_araligi(Ahasta,gun));
	fprintf(dosya,"Ortalama Mutlak Sapma= %.2f\n",ortmutlaksapma(Ahasta,gun));
	fprintf(dosya,"Varyans= %.2f\n",varyans_bulma(Ahasta,gun));
	fprintf(dosya,"Standart Sapma= %.4f\n",standartsapma(Ahasta,gun));
	fprintf(dosya,"Degisim Katsayisi= %.4f\n",degisim_katsayisi(Ahasta,gun));
	fprintf(dosya,"Ceyrekler Acikligi= %d\n",ceyrekler_acikligi(Ahasta,gun));
	
	fprintf(dosya,"##################################################\n");
	
	printf("Dosya olusturldu Bakabilirsiniz.");
}
