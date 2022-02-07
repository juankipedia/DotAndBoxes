#include "loginwindow.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QHash>
# include <string>

using namespace std;
const QString USERS_FILE_NAME = "DONOTREAD.txt";

typedef unsigned long long int ulli;
typedef unsigned long long int lli;
// Using single variable.
ulli rolling_hash(string &s, ulli b = 26, ulli p = 1e9 + 7){
    //hash(s) = sum(s[i] * b ^ (n - 1 - i)) % p, for all i in [i, n = s.size()]
    ulli hash = (s[0] - 'a' + 1);
    for(int i = 1; i < s.size(); i++)
        hash = ((hash * b) % p + (s[i] - 'a' + 1ULL)) % p;
    return hash;
}

// Using array. Useful for getting hash of a subsegment, complete hash at get_hash(0, s.size() - 1)
// hash stored in h[] and B ^ i = b[i]
void rolling_hash(string &s, lli h[], lli b[], lli B, lli p){
    h[0] = 0;
    h[1] = (s[0] - 'a' + 1);
    b[0] = 1;
    for(int i = 1; i < s.size(); i++){
        h[i + 1] = ((h[i] * B) % p + (s[i] - 'a' + 1LL)) % p;
        b[i] = (B * b[i - 1]) % p;
    }
}


lli get_hash(int l, int r, lli h[], lli b[], lli p){
    return (h[r + 1] - ((h[l] * b[r - l + 1]) % p) + p) % p;
}

struct DataItem {
   int data;
   string key;
};

const int SIZE = 10000007;
DataItem* hashArray[10000007];
struct DataItem *search(string key) {
   //get the hash
   int hashIndex = rolling_hash(key);

   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {

      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex];

      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }

   return NULL;
}

void insert(string key,int data) {
   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->data = data;
   item->key = key;

   //get the hash
   int hashIndex = rolling_hash(key);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != "") {
      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }

   hashArray[hashIndex] = item;
}


struct DataItem* remove(struct DataItem* item) {
   string key = item->key;

   //get the hash
   int hashIndex = rolling_hash(key);

   //move in array until an empty
   while(hashArray[hashIndex] !=NULL) {

      if(hashArray[hashIndex]->key == key) {
         struct DataItem* temp = hashArray[hashIndex];

         //assign a dummy item at deleted position
         return temp;
      }

      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }

   return NULL;
}


QHash<QString, QString> users;

void load_all_users(){
    QFile file(USERS_FILE_NAME);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        file.open(QFile::WriteOnly | QFile::Text);
        file.close();
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()){
        auto line = in.readLine().split(" ");
        users[line[0]] = line[1];
    }
    file.close();
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main_window;
    LoginWindow login_window(&main_window, users);
    load_all_users();
    login_window.show();

    return a.exec();
}
