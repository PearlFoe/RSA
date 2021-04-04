#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <cstring>
#include <cmath>

using namespace std;

int getRandomNumber(int min, int max);
int64_t getPrimeNumber(int min);
int64_t countModul(int64_t a, int64_t b);
bool isPrime(long int prime);
int64_t countEilerFunc(int64_t a, int64_t b);
int64_t getE(int64_t f);
int64_t getD(int64_t e, int64_t f);
void getEncodedMessage(char *message, int64_t *publicKey, int64_t *encodedMessage);
void getDecodedMessage(int64_t *encodedMessage, int messageLength, int64_t *secretKey, int64_t *decodedMessage);

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    char message[] = "Message text! 123456";

    int64_t prime1 = getPrimeNumber(0);
    int64_t prime2 = getPrimeNumber(0);
    cout<<"First prime number: "<<prime1<<endl<<"Second prime number: "<<prime2<<endl;

    int64_t module = countModul(prime1, prime2);
    cout<<"Module: "<<module<<endl;

    int64_t eilerFunc = countEilerFunc(prime1, prime2);
    cout<<"Eiler Function: "<<eilerFunc<<endl;

    int64_t e = getE(eilerFunc);
    cout<<"E: "<<e<<endl;

    int64_t d = getD(e, eilerFunc);
    cout<<"D: "<<d<<endl;

    int64_t publicKey[]{e, module};
    int64_t secretKey[]{d, module};
    cout<<"Open key: "<<'{'<<e<<", "<<module<<'}'<<endl;
    cout<<"Secret key: "<<'{'<<d<<", "<<module<<'}'<<endl;
    cout<<endl;

    int64_t encodedMessage[strlen(message)];
    getEncodedMessage(message, publicKey, encodedMessage);

    int64_t decodedMessage[strlen(message)];
    getDecodedMessage(encodedMessage, strlen(message), secretKey, decodedMessage);

    cout<<"Entered message: "<<message<<endl;
    cout<<"Encrypted message: ";
    for(int i = 0; i < strlen(message); i++){
        cout<<encodedMessage[i];
    }
    cout<<endl<<"Decrypted message: ";
    for(int i = 0; i < strlen(message); i++){
        cout<<char(decodedMessage[i]);
    }
    cout<<endl;


    return 0;
}

int getRandomNumber(int min, int max){
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int64_t countModul(int64_t a, int64_t b){
    return a*b;
}

bool isPrime( long int prime){
    long int i, j;

    j = (long int)sqrt((long double)prime);

    for ( i = 2; i <= j; i++)
    {
        if ( prime % i == 0 )
        {
            return false;
        }
    }

    return true;
}

int64_t getPrimeNumber(int min){
    int64_t n[100];
    int index = 0;
    if(min < 2)
        min = 2;

    for(long int i=min; i<min+100000; i++){
        if(isPrime(i)){
            n[index] = i;
            index++;
        }
        if(index > 99)
            break;
    }

    return n[getRandomNumber(0, 99)];
}

int64_t countEilerFunc(int64_t a, int64_t b){
    return (a-1)*(b-1);
}

int64_t getE(int64_t f){
    int64_t e = f;
    while(e>=f){
        e = getPrimeNumber(0);
    }
    return e;
}

int64_t getD(int64_t e, int64_t f){
    int64_t d = 1;
    while((d*e)%f != 1){
        d++;
    }
    return d;
}

void getEncodedMessage(char *message, int64_t *publicKey, int64_t *encodedMessage){
    int messageLength = strlen(message);

    for(int i = 0; i < messageLength; i++){
        int symbolCode = int(message[i]);
        int result = 1;
        for (long int j = 0; j < publicKey[0]; j++ )
        {
            result = result * symbolCode;
            result = result % publicKey[1];
        }
        encodedMessage[i] = static_cast<int64_t>(result);
    }
}

void getDecodedMessage(int64_t *encodedMessage, int messageLength, int64_t *secretKey, int64_t *decodedMessage){

    for(int i = 0; i < messageLength; i++){
        int symbolCode = int(encodedMessage[i]);
        int result = 1;
        for (long int j = 0; j < secretKey[0]; j++ )
        {
            result = result * symbolCode;
            result = result % secretKey[1];
        }
        decodedMessage[i] = static_cast<int64_t>(result);
    }
}







