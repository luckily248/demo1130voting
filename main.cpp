//LIANG Orlando
#include<iostream>
#include<fstream>       /* file io */
#include<cstdlib>
#include <time.h>       /* time */
#include<ctime>
#include <vector>
#include <sstream>
using namespace std;

vector<int> tallys;

void log(string log){
    ofstream data;
    data.open("trail.txt",fstream::app);
    data<<log<<"\n";
    data.close();
}

void create_db_and_seed(){
    //check if the DB allready exists
    ifstream infile("voter_db.txt");
    if(infile.good()){
        cout<<"voter id file already exist\n";
        return;
    }
    
    //create and seed the DB
    ofstream voter_db;
    voter_db.open("voter_db.txt");
    for(int x=0;x<10;x++){
        voter_db<<rand()%9000 +1<<"\n";
    }
    voter_db.close();
}
void create_canidates(){
    //check if the DB allready exists
    ifstream condb("canidates.txt");
    if(condb.good()){
        cout<<"canidates file already exist\n";
        return;
    }
    int canidates_amount;
    string canidate_name;
    cout<<"\namount of canidates to create: ";
    cin>>canidates_amount;
    ofstream canidatess,tallyss;
    canidatess.open("canidates.txt");
    tallyss.open("tallys.txt");
    for(int x=0;x<canidates_amount;x++){
        cout<<"\ncanadates name: ";
        cin>>canidate_name;
        canidatess<<canidate_name<<"\n";
        tallyss<<0<<"\n";
        ::tallys.push_back(0);
    }
    canidatess.close();
    
}   //admin thingy
int  ask_for_voter_id(){
    int voter_id;
    cout<<"    Electrinic Vote \n"
    <<"Enter voter ID: ";
    cin>>voter_id;
    return voter_id;
}
bool search_db_for_id(int voter_id){
    string line;
    fstream search_db ("voter_db.txt");
    if(search_db.is_open()){
        while(getline(search_db,line)){
            if(stoi(line)==voter_id){
                search_db.close();
                return true;
            }
        }
        search_db.close();
    }
    return false;
}
bool isVoted(int voter_id){
    string line;
    fstream search_db ("voted_db.txt");
    if(search_db.is_open()){
        while(getline(search_db,line)){
            if(stoi(line)==voter_id){
                search_db.close();
                return true;
            }
        }
        search_db.close();
    }
    return false;
}
bool isAllvote(){
    bool r=false;
    int count=0;
    string line;
    
    fstream search_db ("voted_db.txt");
    if(search_db.is_open()){
        while(getline(search_db,line)){
            count++;
        }
        search_db.close();
    }
    if (count==10) {
        r=true;
    }
    return r;
}
void printCanidates(){
    string line;
    int n=0;
    fstream search_db ("canidates.txt");
    if(search_db.is_open()){
        while(getline(search_db,line)){
            cout<<n<<"."<<line<<"\n";
            n++;
        }
        search_db.close();
    }
}
void printTally(){
    string line;
    fstream search_db ("tallys.txt");
    if(search_db.is_open()){
        while(getline(search_db,line)){
            cout<<line<<"\n";
        }
        search_db.close();
    }
}
void printVoterID(){
    string line;
    fstream search_db ("voter_db.txt");
    if(search_db.is_open()){
        while(getline(search_db,line)){
            cout<<line<<"\n";
        }
        search_db.close();
    }
}
void printVotered(){
    string line;
    fstream search_db ("voted_db.txt");
    if(search_db.is_open()){
        while(getline(search_db,line)){
            cout<<line<<"\n";
        }
        search_db.close();
    }
}
void printTrail(){
    string line;
    fstream search_db ("trail.txt");
    if(search_db.is_open()){
        while(getline(search_db,line)){
            cout<<line<<"\n";
        }
        search_db.close();
    }
}
void logtally(int row){
    //cout<<tallys.at(row);
    tallys.at(row)=tallys.at(row)+1;
    ofstream data;
    data.open("tallys.txt");
    for (vector<int>::iterator it=tallys.begin(); it!=tallys.end(); it++) {
        data<<*it<<"\n";
    }
    data.close();
}
void vote(int userid,int row){
    logtally(row);
    ofstream data;
    data.open("voted_db.txt",fstream::app);
    data<<userid<<"\n";
    data.close();
    stringstream ss;
    ss<<"user "<<userid<<" vote for No."<<row;
    cout<<ss.str()<<"\n";
    log(ss.str());
}


//adminID 88888
//hackerID  124816
int main(int argc, const char * argv[]){
    bool checkcan=false,checkvoter=false,checktally=false;
    int id;
    srand(time(0));           //seed random with time
    //create_db_and_seed();     //create DB if it is not found
    
    do{
        cout<<"check vote tally record:";
        ifstream tallysR("tallys.txt");
        if(tallysR.good()){
            if (tallys.size()==0) {
                string line;
                fstream search_db ("tallys.txt");
                if(search_db.is_open()){
                    while(getline(search_db,line)){
                        tallys.push_back(stoi(line));
                    }
                    search_db.close();
                }
            }
            checktally=true;
            cout<<"pass\n";
        }else cout<<"false\n";
        
        cout<<"check canidatesDB:";
        ifstream canDB("canidates.txt");
        if(canDB.good()){
            checkcan=true;
            cout<<"pass\n";
        }else cout<<"false\n";
    
    
        cout<<"check voterDB:";
        ifstream voterdb("voter_db.txt");
        if(voterdb.good()){
            checkvoter=true;
            cout<<"pass\n";
        }else cout<<"false\n";
        
        cout<<"E-voting system\n";
        cout<<"----------------\n";
        cout<<"please enter your user id:\n";
        cin>>id;
        //admin
        if (id==88888) {
            log("admin login");
            int adminc;
            
            do{
            cout<<"hello admin\n";
            cout<<"1.print tally\n";
            cout<<"2.print list of valid voter ids\n";
            cout<<"3.print list of ids who have voted\n";
            cout<<"4.paper trail\n";
            cout<<"5.logout\n";
            cin>>adminc;
            
                switch (adminc) {
                    case 1:
                        printTally();
                        break;
                    case 2:
                        printVoterID();
                        break;
                    case 3:
                        printVotered();
                        break;
                    case 4:
                        printTrail();
                        break;
                    default:
                        break;
                }
            }while (adminc!=5);
        }else //hacker
        if (id==124816){
            log("hacker login");
            int hackerc;
            do{
            cout<<"hello hacker\n";
            cout<<"1.create voter id database\n";
            cout<<"2.create canidates\n";
            cout<<"3.logout\n";
            cin>>hackerc;
                switch (hackerc) {
                    case 1:
                        log("hacker create voter id list file");
                        create_db_and_seed();
                        break;
                    case 2:
                        log("hacker create a canidates list file");
                        create_canidates();
                        break;
                        
                    default:
                        break;
                }
            }while (hackerc!=3);
        }else if (search_db_for_id(id)) {
            stringstream ss;
            ss<<"user "<<id<<" login";
            log(ss.str());
            if (isVoted(id)) {
                cout<<"you already voted\n";
                continue;
            }
            int userc=-1;
            
            cout<<"Canidates\n";
            cout<<"-------------\n";
            printCanidates();
            cin>>userc;
            if (userc!=-1) {
                vote(id,userc);
            }
            }
        else{
            stringstream ss;
            ss<<"invlid user "<<id<<" try to login";
            log(ss.str());
            cout<<"invalid userID\n";
        }
        
    }while (!isAllvote());
    cout<<"voting end\n";
}

/*
 can check if a file exists------------------------------------------------------
 bool is_file_exist(const char *fileName)
 {
 std::ifstream infile(fileName);
 return infile.good();
 }
 --------------------------------------------------------------------------------
 */

