/* 
 * File:   SessionOrganizer.cpp
 * Author: Kapil Thakkar
 * 
 */

#include "SessionOrganizer.h"
#include "Util.h"
#include <random>
#include <cstdlib>
SessionOrganizer::SessionOrganizer ( )
{
    parallelTracks = 0;
    papersInSession = 0;
    sessionsInTrack = 0;
    processingTimeInMinutes = 0;
    tradeoffCoefficient = 1.0;
    solutioncount=0;
}

SessionOrganizer::SessionOrganizer ( string filename )
{
    readInInputFile ( filename );
    solutioncount=0;
    conference = new Conference ( parallelTracks, sessionsInTrack, papersInSession );
}

//KEEP IN MIND OF FACTOR ------tradeoffCoefficient
double SessionOrganizer::scoreChangeCalculator(int i,int j,int k,int l,int p,int m){
//i j k
//l p m
    double score1inJ=0.0,score2inJ=0.0,score1inP=0.0,score2inP=0.0;
    int index1 = conference->getPaper ( i, j, k );
    int index2 = conference->getPaper ( l, p, m );
    int temp1,temp2;

    for ( int a = 0; a < parallelTracks; a++ ){
        for ( int b = 0; b < papersInSession ; b++ ){
            if(a==i){
                temp1 = conference->getPaper ( a, j, b );
                if(b!=k){score1inJ = score1inJ + (1-distanceMatrix[index1][temp1]);}
            }
            else{
                temp1=  conference->getPaper ( a, j, b );
                score1inJ = score1inJ + tradeoffCoefficient * distanceMatrix[index1][temp1];
            }

            if(a==l){
                temp2 = conference->getPaper ( a, p, b );
                if(b!=m){score2inP = score2inP + (1-distanceMatrix[index2][temp2]);}
            }
            else{
                temp2=  conference->getPaper ( a, p, b );
                score2inP = score2inP + tradeoffCoefficient * distanceMatrix[index2][temp2];
            }
         
        }
    }

    conference->setPaper ( i, j, k, index2 );
    conference->setPaper ( l, p, m, index1 );

for ( int a = 0; a < parallelTracks; a++ ){
    for ( int b = 0; b < papersInSession ; b++ ){
        if(a==i){
                temp1 = conference->getPaper ( a, j, b );
                if(b!=k){score2inJ = score2inJ + (1-distanceMatrix[index2][temp1]);}
            }
            else{
                temp1=  conference->getPaper ( a, j, b );
                score2inJ = score2inJ + tradeoffCoefficient * distanceMatrix[index2][temp1];
            }

            if(a==l){
                temp2 = conference->getPaper ( a, p, b );
                if(b!=m){score1inP = score1inP + (1-distanceMatrix[index1][temp2]);}
            }
            else{
                temp2=  conference->getPaper ( a, p, b );
                score1inP = score1inP + tradeoffCoefficient * distanceMatrix[index1][temp2];
            }

    }
}
    conference->setPaper ( i, j, k, index1 );
    conference->setPaper ( l, p, m, index2 );
// cout<<"score1inJ:"<<score1inJ<<endl;
// cout<<"score2inJ:"<<score2inJ<<endl;
// cout<<"score1inP:"<<score1inP<<endl;
// cout<<"score2inP:"<<score2inP<<endl;

    double totalchange= score1inP - score2inP + score2inJ - score1inJ;
    return totalchange;

}

void SessionOrganizer::localsearchrandom(){

// bool havebetter=false;
// if(solutioncount%100==0) {
//     double scorecurr=scoreOrganization ( );
//     cout<<"scorecurr: "<<scorecurr<<endl;
// }
 cout<<"at random+++++"<<endl;

bool flag=true;
                                    std::mt19937 rng;
                                    rng.seed(std::random_device()());
                                    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,100000); 
while(flag){
    if(solutioncount%100==0) {
       // double scorecurr=scoreOrganization ( );
        cout<<"scorecurr: "<<endl;
    }
    solutioncount++;
    bool havebetter=false;

    for ( int i = 0; i < parallelTracks; i++ ){
        for ( int j = 0; j < sessionsInTrack ; j++ ){
            for ( int k = 0; k < papersInSession; k++ ){
                for ( int l = i ; l < parallelTracks ; l++){
                    for(int p=0 ; p < sessionsInTrack  ; p++ ){
                        for ( int m = 0; m < papersInSession ; m++ ){
   
                                            end=clock();

                                    double duration1=(double) (end- start)/CLOCKS_PER_SEC ;
                                    
                                if(processingTimeInMinutes*60 -6 < duration1){cout<<duration1<<endl;;return ;}
                  
                                int t1=dist6(rng)%sessionsInTrack;
                                int t2=dist6(rng)%sessionsInTrack;
                                int p1=dist6(rng)%parallelTracks;
                                int p2=dist6(rng)%parallelTracks;
                                int k1=dist6(rng)%papersInSession;
                                int k2=dist6(rng)%papersInSession;
                                if(p2==p1&&t1==t2)continue;

                                    double scoreChange=scoreChangeCalculator(p1, t1, k1 ,p2, t2, k2 );

                                    int index1 = conference->getPaper ( p1, t1, k1 );
                                    int index2 = conference->getPaper ( p2, t2, k2 );
                                    conference->setPaper ( p1, t1, k1, index2 );
                                    conference->setPaper ( p2, t2, k2, index1 );
                                            
                                   //double scorenow=scoreOrganization ( );
                                   //cout<<"scorenow: "<<scorenow<<endl;
                                    //if(scorenow - scorecurr ==scoreChange )cout<<"Yesssss: "<<scoreChange<<endl;
                            if(scoreChange > 0){havebetter=true; break;}
                            else{
                                    conference->setPaper ( p1, t1, k1, index1 );
                                    conference->setPaper ( p2, t2, k2, index2 );
                            }
                        }
                        if(havebetter==true)break;
                    }
                if(havebetter==true)break;        
                }
            if(havebetter==true)break;
            }
        if(havebetter==true)break;
        }
    if(havebetter==true)break;
}
    if(havebetter==true){
        flag=true;
    }
    else{
        flag=false;
    }
}

    cout<<"local optima"<<endl;
}



    

void SessionOrganizer::localsearch(){

// bool havebetter=false;
// if(solutioncount%100==0) {
//     double scorecurr=scoreOrganization ( );
//     cout<<"scorecurr: "<<scorecurr<<endl;
// }

 cout<<"at exhaustive+++++"<<endl;

bool flag=true;

while(flag){
    if(solutioncount%100==0) {
        //double scorecurr=scoreOrganization ( );
        cout<<"scorecurr: "<<endl;
    }
    solutioncount++;
    bool havebetter=false;

    for ( int i = 0; i < parallelTracks; i++ ){
        for ( int j = 0; j < sessionsInTrack ; j++ ){
            for ( int k = 0; k < papersInSession; k++ ){
                for ( int l = i ; l < parallelTracks ; l++){
                    for(int p=0 ; p < sessionsInTrack  ; p++ ){
                        for ( int m = 0; m < papersInSession ; m++ ){
   
                                            end=clock();

                                    double duration1=(double) (end- start)/CLOCKS_PER_SEC ;
                                    double timeallowed=processingTimeInMinutes*48;
                                    
                                if(timeallowed < duration1){cout<<duration1<<endl;return ;}
                  
                                    double scoreChange=scoreChangeCalculator(i, j, k, l, p, m);
                                    //cout<<"scorecurr: "<<scorecurr<<endl;
                                    //cout<<"scoreChange: "<<scoreChange<<endl;
                                    int index1 = conference->getPaper ( i, j, k );
                                    int index2 = conference->getPaper ( l, p, m );
                                    conference->setPaper ( i, j, k, index2 );
                                    conference->setPaper ( l, p, m, index1 );
                                                
                                   //double scorenow=scoreOrganization ( );
                                   //cout<<"scorenow: "<<scorenow<<endl;
                                    //if(scorenow - scorecurr ==scoreChange )cout<<"Yesssss: "<<scoreChange<<endl;
                            if(scoreChange > 0){havebetter=true; break;}
                            else{
                                //cout<<"score: "<<scorenow<<" "<<scorecurr<<endl;
                                conference->setPaper ( i, j, k,index1 );
                                conference->setPaper ( l, p, m,index2 );
                            }
                        }
                        if(havebetter==true)break;
                    }
                if(havebetter==true)break;        
                }
            if(havebetter==true)break;
            }
        if(havebetter==true)break;
        }
    if(havebetter==true)break;
}
    if(havebetter==true){
        flag=true;
    }
    else{
        flag=false;
    }
}

    cout<<"local optima"<<endl;
}

void SessionOrganizer::localbestsearch(){
    double scorecurr=scoreOrganization ( );
    cout<<"scorecurr: "<<scorecurr<<endl;

double localbestscore=scorecurr;
int ibest,jbest,kbest,lbest,pbest,mbest,ind1best,ind2best;
solutioncount++;

    for ( int i = 0; i < parallelTracks; i++ ){
        for ( int j = 0; j < sessionsInTrack ; j++ ){
            for ( int k = 0; k < papersInSession; k++ ){
                for ( int l = i ; l < parallelTracks ; l++){
                    for(int p=0 ; p < sessionsInTrack  ; p++ ){
                        for ( int m = 0; m < papersInSession ; m++ ){
                  
                                    
                                    int index1 = conference->getPaper ( i, j, k );
                                    int index2 = conference->getPaper ( l, p, m );
                                    conference->setPaper ( i, j, k, index2 );
                                    conference->setPaper ( l, p, m, index1 );
                            
                                    double scorenow=scoreOrganization ( );
                                    
                                    conference->setPaper ( i, j, k,index1 );
                                    conference->setPaper ( l, p, m,index2 );
                            if(scorenow > localbestscore){
                                localbestscore=scorenow;
                                ibest=i; jbest=j; kbest=k;
                                lbest=l; pbest=p; mbest=m;
                                ind1best=index1;
                                ind2best=index2;
                            }
                        }
                    }
                }
            }
        }
    }

    if(localbestscore>scorecurr){
            conference->setPaper ( ibest, jbest, kbest, ind2best );
            conference->setPaper ( lbest, pbest, mbest, ind1best );
            SessionOrganizer::localbestsearch();
    }
    else{
        cout<<"Local Optima: "<<localbestscore<<"\nscorecurr: "<<scorecurr<<endl;
    }    
}

void SessionOrganizer::organizePapers ( )
{
    start=clock();

    int paperCounter = 0;
    for ( int i = 0; i < conference->getSessionsInTrack ( ); i++ )
    {
        for ( int j = 0; j < conference->getParallelTracks ( ); j++ )
        {
            for ( int k = 0; k < conference->getPapersInSession ( ); k++ )
            {
                conference->setPaper ( j, i, k, paperCounter );
                paperCounter++;
            }
        }
    }
    cout<<"paperCounter"<<paperCounter<<endl;
if(paperCounter<100)SessionOrganizer::localsearch();
 else{SessionOrganizer::localsearchrandom();}
    cout<<"after LC"<<endl;
}

void SessionOrganizer::readInInputFile ( string filename )
{
    vector<string> lines;
    string line;
    ifstream myfile ( filename.c_str () );
    if ( myfile.is_open ( ) )
    {
        while ( getline ( myfile, line ) )
        {
            //cout<<"Line read:"<<line<<endl;
            lines.push_back ( line );
        }
        myfile.close ( );
    }
    else
    {
        cout << "Unable to open input file";
        exit ( 0 );
    }

    if ( 6 > lines.size ( ) )
    {
        cout << "Not enough information given, check format of input file";
        exit ( 0 );
    }

    processingTimeInMinutes = atof ( lines[0].c_str () );
    papersInSession = atoi ( lines[1].c_str () );
    parallelTracks = atoi ( lines[2].c_str () );
    sessionsInTrack = atoi ( lines[3].c_str () );
    tradeoffCoefficient = atof ( lines[4].c_str () );

    int n = lines.size ( ) - 5;
    double ** tempDistanceMatrix = new double*[n];
    for ( int i = 0; i < n; ++i )
    {
        tempDistanceMatrix[i] = new double[n];
    }


    for ( int i = 0; i < n; i++ )
    {
        string tempLine = lines[ i + 5 ];
        string elements[n];
        splitString ( tempLine, " ", elements, n );

        for ( int j = 0; j < n; j++ )
        {
            tempDistanceMatrix[i][j] = atof ( elements[j].c_str () );
        }
    }
    distanceMatrix = tempDistanceMatrix;

    int numberOfPapers = n;
    int slots = parallelTracks * papersInSession*sessionsInTrack;
    if ( slots != numberOfPapers )
    {
        cout << "More papers than slots available! slots:" << slots << " num papers:" << numberOfPapers << endl;
        exit ( 0 );
    }
}

double** SessionOrganizer::getDistanceMatrix ( )
{
    return distanceMatrix;
}

void SessionOrganizer::printSessionOrganiser ( char * filename)
{
    conference->printConference ( filename);
}

double SessionOrganizer::scoreOrganization ( )
{
    // Sum of pairwise similarities per session.
    double score1 = 0.0;
    for ( int i = 0; i < conference->getParallelTracks ( ); i++ )
    {
        Track tmpTrack = conference->getTrack ( i );
        for ( int j = 0; j < tmpTrack.getNumberOfSessions ( ); j++ )
        {
            Session tmpSession = tmpTrack.getSession ( j );
            for ( int k = 0; k < tmpSession.getNumberOfPapers ( ); k++ )
            {
                int index1 = tmpSession.getPaper ( k );
                for ( int l = k + 1; l < tmpSession.getNumberOfPapers ( ); l++ )
                {
                    int index2 = tmpSession.getPaper ( l );
                    score1 += 1 - distanceMatrix[index1][index2];
                }
            }
        }
    }

    // Sum of distances for competing papers.
    double score2 = 0.0;
    for ( int i = 0; i < conference->getParallelTracks ( ); i++ )
    {
        Track tmpTrack1 = conference->getTrack ( i );
        for ( int j = 0; j < tmpTrack1.getNumberOfSessions ( ); j++ )
        {
            Session tmpSession1 = tmpTrack1.getSession ( j );
            for ( int k = 0; k < tmpSession1.getNumberOfPapers ( ); k++ )
            {
                int index1 = tmpSession1.getPaper ( k );

                // Get competing papers.
                for ( int l = i + 1; l < conference->getParallelTracks ( ); l++ )
                {
                    Track tmpTrack2 = conference->getTrack ( l );
                    Session tmpSession2 = tmpTrack2.getSession ( j );
                    for ( int m = 0; m < tmpSession2.getNumberOfPapers ( ); m++ )
                    {
                        int index2 = tmpSession2.getPaper ( m );
                        score2 += distanceMatrix[index1][index2];
                    }
                }
            }
        }
    }
    double score = score1 + tradeoffCoefficient*score2;
    return score;
}
