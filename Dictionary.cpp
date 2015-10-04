#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <ncurses.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

// Defining Words Class
class words{
public:
		char *word;
		char *word_type;
		char *synonym;
		char *sentence_exp1;
		char *sentence_exp2;
		char *sentence_exp3;

		words();
	    friend istream& operator>>(istream&, words*);
	    friend ostream& operator<<(ostream&, words*);
	    void search(words *, char[], int);
	    int remove(words *, char[], int);
	    void edit(words *, char[], int);
	    void save(words *,int);
	};

// Words Class Constructor
words::words(){
		word=new char[100];
		word_type=new char[20];
		synonym=new char[50];
		sentence_exp1=new char[500];
		sentence_exp2=new char[500];
		sentence_exp3=new char[500];
		strcpy(word,"0");
		strcpy(word_type,"0");
		strcpy(synonym,"0");
		strcpy(sentence_exp1,"0");
		strcpy(sentence_exp2,"0");
		strcpy(sentence_exp3,"0");
	}


// Words Class istream Overloading friend Function Definition
istream& operator>>(istream& in, words &obj){
		cin.ignore(); // Ignore the newline problem when using Getline with cin stream at the same time.
		cout<<"Enter your word: ";
		in.getline(obj.word, 100);
		cout<<"\nEnter word type: ";
		in.getline(obj.word_type, 20);
		cout<<"\nEnter word's synonym: ";
		in.getline(obj.synonym, 50);
		cout<<"\nEnter sentence example for the word: \n";
		in.getline(obj.sentence_exp1, 500);
		in.getline(obj.sentence_exp2, 500);
		in.getline(obj.sentence_exp3, 500);
	return in;
	}

// Words Class ostream Overloading friend Function Definition
ostream& operator<<(ostream& out, words &obj){
		out<<"The Entered word is: "<<obj.word;
		out<<"\nThe Word Type is: "<<obj.word_type;
		out<<"\nThe word's synonym is: "<<obj.synonym;
		out<<"\nThe three sentence example of this word is: "<<obj.sentence_exp1<<"\n"<<obj.sentence_exp2<<"\n"<<obj.sentence_exp3<<"\n";
		return out;
	}

// Words Class Search Function Definition
void words::search(words * word_list,char key[], int n){
	    word_list->save(word_list,n);
		FILE *pFile;
		pFile = fopen ("c:\Dictionary.txt" , "r");
		if (((pFile=fopen("c:\Dictionary.txt","r")) == NULL))
			cout<<"Can not open the file\n";
		FILE *number_of_data;
		number_of_data = fopen ("c:\Data_number.txt" , "r");
		if (((number_of_data=fopen("c:\Data_number.txt","r")) == NULL))
			cout<<"Can not open the file\n";
		//int *z;
		//fread(z, sizeof(int),2 , number_of_data);
		//int r;
		//r=*z;
		//cout<<"R is:"<<r;
		//n=atoi(z);
		//cout<<"*****"<<z<<"\n"<<"***"<<n;
		words *entered_word=new words[n];
		fread(entered_word, sizeof(class words),n ,pFile);
		int count=0;
		for(int i=0;i<n;i++){
			if(strcmp(entered_word[i].word,key)==0){
				cout<<entered_word[i];
				count++;
			}
		}
		if(count==0)
			cout<<"Your word is not existed in the Dictionary. Why don't you add it?!\n";
		fclose(pFile);
		fclose(number_of_data);
	}

// Words Class remove Function Definition
int words::remove(words * word_list,char to_be_removed[], int n){
		word_list->save(word_list,n);
		FILE *pFile;
		pFile = fopen ("c:\Dictionary.txt" , "r+");
			if (((pFile=fopen("c:\Dictionary.txt","r+")) == NULL))
				cout<<"Can not open the file\n";
		FILE *number_of_data;
		number_of_data = fopen ("c:\Data_number.txt" , "r+");
			if (((number_of_data=fopen("c:\Data_number.txt","r+")) == NULL))
				cout<<"Can not open the file\n";
		int *z;
		z=&n;
		fread(z, sizeof(n),2,number_of_data);
		words *whole_dictionary=new words[n];
		fread(whole_dictionary, sizeof(class words),n,pFile);
		int count=0;
		int m=n;
		for(int i=0;i<m;i++){
			if(strcmp(whole_dictionary[i].word,to_be_removed)==0){
				strcpy(whole_dictionary[i].word,"0");
			    strcpy(whole_dictionary[i].word_type,"0");
			    strcpy(whole_dictionary[i].synonym,"0");
			    strcpy(whole_dictionary[i].sentence_exp1,"0");
			    strcpy(whole_dictionary[i].sentence_exp2,"0");
			    strcpy(whole_dictionary[i].sentence_exp3,"0");
		        count++;
		        n--;
			}
		}
		if(count==0)
			cout<<"Your word is not existed in the Dictionary.\n";
		word_list->save(word_list,n);
		fwrite(word_list,sizeof(class words),n,pFile);
		int *p;
		p=&n;
		fwrite(&p, sizeof(m), 2, number_of_data);
		fclose(pFile);
		fclose(number_of_data);
		return n;
	}

// Words Class edit Function Definition
void words::edit(words *word_list, char to_be_edited[], int n){
		word_list->save(word_list,n);
		FILE *pFile;
		pFile = fopen ("c:\Dictionary.txt" , "r+");
			if (((pFile=fopen("c:\Dictionary.txt","r+")) == NULL))
				cout<<"Can not open the file\n";
			words *whole_dictionary=new words[n];
			fread(whole_dictionary, sizeof(class words),n,pFile);
			int count=0;
			for(int i=0;i<n;i++){
				if(strcmp(whole_dictionary[i].word,to_be_edited)==0){
					cout<<"New Word Type: ";
					gets(whole_dictionary[i].word_type);
					cout<<"New Synonym: ";
					gets(whole_dictionary[i].synonym);
					cout<<"New Example Sentenece1: ";
					gets(whole_dictionary[i].sentence_exp1);
					cout<<"New Example Sentenece2: ";
					gets(whole_dictionary[i].sentence_exp2);
					cout<<"New Example Sentenece3: ";
					gets(whole_dictionary[i].sentence_exp3);
			        count++;
				}
			}
			if(count==0)
				cout<<"Your word is not existed in the Dictionary.\n";
			fwrite(word_list,sizeof(class words),n,pFile);
			fclose(pFile);
	}

// Words Class save Function Definition
void words::save(words * word_list,int n){
		FILE *pFile;
		pFile = fopen ("c:\Dictionary.txt" , "w+");
			if (((pFile=fopen("c:\Dictionary.txt","w+")) == NULL))
				cout<<"Can not open the file\n";
		FILE *number_of_data;
		number_of_data = fopen ("c:\Data_number.txt" , "w+");
			if (((number_of_data=fopen("c:\Data_number.txt","w+")) == NULL))
				cout<<"Can not open the file\n";
		int *m;
		m=&n;
		fwrite(word_list, sizeof(class words), n, pFile);
		fwrite(m, sizeof(m), 2, number_of_data);
		fclose(pFile);
		fclose(number_of_data);
	}

// Main Function Definition
int main(){
system("clear");
int n=0;
	    words *word_list=new words[50];
		int input=-1;
		while(input!=0){
				cout<<"Dictionary program v0.13 - BUT";
				cout<<"\n Please choose a number:\n";
				cout<<"(1) - Add Word\n";
				cout<<"(2) - Search & Print Word Definition.\n";
				cout<<"(3) - Delete word.\n";
				cout<<"(4) - Edit word details.\n";
				cout<<"(5) - Save changes to the Dictionary file.\n";
				cout<<"(0) - Exit.\n";
				cin>>input;
				switch(input){
					// Exit
					case 0:
						system("clear");
						break;

					// Add Word & Input word details
					case 1:
						system("clear");
						cin>>word_list[n];
						n++;
						system("clear");
						break;

					// Search Desire Word & Show it's details
					case 2:
						system("clear");
						char name1[50];
						cout<<"Enter your desire word: ";
						cin.ignore(); // Ignore the newline problem when using gets with cin stream at the same time.
						gets(name1);
						word_list->search(word_list, name1, n);
						break;

					// Delete word
					case 3:
						system("clear");
						char name2[50];
						cout<<"Enter your desire word to be deleted: ";
						cin.ignore(); // Ignore the newline problem when using gets with cin stream at the same time.
						gets(name2);
						n=word_list->remove(word_list, name2, n);
						break;

					// Edit word detail
					case 4:
						system("clear");
						char name3[50];
						cout<<"Enter your desired stunf  dsdsassdsadsaad name to be edited: ";
						cin.ignore(); // Ignore the newline problem when using gets with cin stream at the same time.
						gets(name3);
						word_list->edit(word_list, name3, n);
						break;

					// Save the Dictionary to the file
					case 5:
						word_list->save(word_list,n);
						system("clear");
						break;

					default:
						cout<<"Your entered value isasdsadasdsdsad not valid! Why don't you try again? It's not that much hard you think.";
						break;
				}
		}
  return 0;
}



# Adding some comment at the end!!!
