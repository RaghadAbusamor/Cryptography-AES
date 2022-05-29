#include "Debug\cryptopp600\aes.h"
#include "Debug\cryptopp600\cryptlib.h"
#include "Debug\cryptopp600\filters.h"
/**/#include "Debug\cryptopp600\osrng.h"
#include "Debug\cryptopp600\hex.h"
#include "Debug\cryptopp600\modes.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
using namespace std::chrono;
using namespace std;
using namespace CryptoPP;
using CryptoPP::AutoSeededRandomPool;
using CryptoPP::StringSink;
using CryptoPP::StreamTransformation;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::AES;
using CryptoPP::ECB_Mode;


//1.Initialization of key data
void InitKey(byte* key, size_t size) {
    for ( size_t i = 0; i < size; ++i ) {
        key[i] = rand();
    }
}

string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

void main()
{
	
	//get the bits from python code


	
	//get the bits from python code

///////////////////////read from file 

ifstream fin;
fin.open("imageBits.txt");
char c;
string thefile;
  fin>> noskipws;
  while(fin>>c) thefile+=c;
  fin.close();

/////////////////////////
	
	//Initialize common key and IV with appropriate values
	byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    byte iv[CryptoPP::AES::BLOCKSIZE];
 
    // Initialize common key and IV with appropriate values
    InitKey(key, sizeof(key));
    InitKey(iv, sizeof(iv));
////	cout<<thefile;

    string plainText = thefile;
 // /////////////////////////////////////  cout<< "Plain Text : " << plainText << endl;
	
auto start = high_resolution_clock::now(); ///
	//Create an encrypted object
	CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption enc;
    enc.SetKeyWithIV(key, sizeof(key), iv);
	string encText;
    CryptoPP::StreamTransformationFilter encFilter(enc, new CryptoPP::StringSink(encText));
 
    // encryption
    encFilter.Put(reinterpret_cast<const byte*>(plainText.c_str()), plainText.size());
    encFilter.MessageEnd();
 
 /////////////////////// cout<< "Encrypted Text : " << encText <<endl;
    CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption dec;
    dec.SetKeyWithIV(key, sizeof(key), iv);        
    //Creation of conversion filter for decryption
    string decText;
    CryptoPP::StreamTransformationFilter decFilter(dec, new CryptoPP::StringSink(decText));
    decFilter.Put(reinterpret_cast<const byte*>(encText.c_str()), encText.size());
    decFilter.MessageEnd();
///////////////////////////////////write the encText to file named chiper
	ofstream fout;
  fout.open ("cipher.txt");
  fout<<encText ;
  fout.close();


   // Get ending timepoint
    auto stop = high_resolution_clock::now();
  
  cout<<"               The image is encrypted                "<<endl<<
	  "           GO TO PAYTHON CODE TO SEE THE IMAGE     "<<endl;

  
    // Get duration. Substart timepoints to 
    // get durarion. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<microseconds>(stop - start);
  
    cout <<"     Time taken by function: "
         << duration.count() << " microseconds" << endl;
  ///////////////////////////////////////////////  cout << "Decrypted Text : " << decText << endl;
	
	system("PAUSE");
}