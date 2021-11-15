#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXIMAL_AIRLINES 10
#define DEST 6
#define DIM 2


char* destinations[]={"Miami", "Rio", "Moscow", "Shanghai", "Barcelona",
"Melbourne"};

int fillPricesTable(double flightsPrices[][DEST],int n,double* dollarRate);

void compute(double flightsPrices[][DEST],int length,
				double* max,double* min,int* bestAirLine);

void bestPrice(double flightsPrices[][DEST],int length,
		double bestPrices[DEST][DIM],double dollarRate);

void printBestPrices(double bestPrices[DEST][DIM]);

void printMinMaxAvg(double max, double min, int bestAirLine);

void errorPrice(int row);

void errorDollar();


int main()
{
	int num_of_airlines=0, bestAirLine=0;
	double prices[MAXIMAL_AIRLINES][DEST];
    double max=0, min=0, dollarRate=0;
	double bestPrices[DEST][DIM];

    num_of_airlines = fillPricesTable(prices, MAXIMAL_AIRLINES, &dollarRate);
    if(num_of_airlines==-1) return-1;
	compute(prices, num_of_airlines, &max, &min, &bestAirLine);
    printMinMaxAvg(max, min, bestAirLine);
	bestPrice(prices, num_of_airlines, bestPrices, dollarRate);
	printBestPrices(bestPrices);


    return 0;
}

int fillPricesTable(double flightsPrices[][DEST],int n,double* dollarRate){
    while((!scanf("%lf", dollarRate))||*dollarRate<=0) {
            errorDollar();
    }
    int num_of_airlines=0;
    int i=0;
    while(scanf("%lf", &flightsPrices[num_of_airlines][i])!=EOF){
        if(flightsPrices[num_of_airlines][i]<=0){
                        errorPrice(num_of_airlines);
                        return -1;
        }
        if(i<DEST-1) i++;
        else if(num_of_airlines<n-1){
            num_of_airlines++;
            i=0;
            }
            else break;
    }
    return num_of_airlines-1;
}

void compute(double flightsPrices[][DEST],int length,
				double* max,double* min,int* bestAirLine){
    *max=0;
    *min=flightsPrices[0][0];
    double bestAverage=0;
    for(int company=0; company<=length; company++){
        double sum=0;
        for(int flight=0; flight<DEST; flight++){
            if(flightsPrices[company][flight]>(*max)) *max=
            flightsPrices[company][flight];

            if(flightsPrices[company][flight]<(*min)) *min=
            flightsPrices[company][flight];
            sum+=flightsPrices[company][flight];
        }
        if(bestAverage>((double)(sum)/DEST)||bestAverage==0){
            bestAverage=(double)sum/DEST;
            *bestAirLine=company;
        }
    }
}


void printBestPrices(double bestPrices[DEST][DIM]){
		for(int i=0; i<DEST; i++){
		printf("Best offer for %s is ", destinations[i]);
		printf("Airline # %d price: %.2f shekels\n", (int)(bestPrices[i][0]), bestPrices[i][1]);
	}
}

void printMinMaxAvg(double max, double min, int bestAirLine){
    printf("Maximal price: %.2f\nMinimal price: %.2f\nBest Airline: %d\n", max, min, bestAirLine);

}

void errorPrice(int row){
	printf("ERROR: invalid price in airline # %d\n", row);
}

void errorDollar(){
	printf("ERROR: invalid dollar rate, try again!\n");
}

void bestPrice(double flightsPrices[][DEST],int length,
		double bestPrices[DEST][DIM],double dollarRate){
    for(int i=0; i<DEST; i++){
        for(int k=0; k<DIM; k++){
            bestPrices[i][k]=0;
        }
    }
    for(int country=0; country<DEST; country++){
        for(int company=0; company<length+1;company++){
            double price_in_nis=(double)flightsPrices[company][country]*(double)dollarRate;
            if(price_in_nis<bestPrices[country][1]||
               bestPrices[country][1]==0){
                bestPrices[country][1]=price_in_nis;
                bestPrices[country][0]=company;
            }
        }
    }
}
