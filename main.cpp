/* 
 * File:   main.cpp
 * Author: Kapil Thakkar
 *
 */

#include <cstdlib>

#include "SessionOrganizer.h"

using namespace std;

/*
 * 
 */
int main ( int argc, char** argv )
{
    // time_t startmain;
    // time(& startmain);
    clock_t c1;
    c1=clock();
    // Parse the input.
    if ( argc < 3 )
    {   
        cout<<"Missing arguments\n";
        cout<<"Correct format : \n";
        cout << "./main <input_filename> <output_filename>";
        exit ( 0 );
    }
    string inputfilename ( argv[1] );
    
    // Initialize the conference organizer.
    SessionOrganizer *organizer  = new SessionOrganizer( inputfilename );

    // Organize the papers into tracks based on similarity.
    organizer->organizePapers ( );

    organizer->printSessionOrganiser ( argv[2]);

    // Score the organization against the gold standard.
    double score = organizer->scoreOrganization ( );
    cout<< "score:"<<score<<endl;
    // time_t endmain;
    // time(& endmain);

    clock_t c2;
    c2=clock();   
     double totaltimetaken=(double)(c2-c1)/(CLOCKS_PER_SEC);
    cout<<"totaltimetaken: "<<totaltimetaken<<endl;

    return 0;
}

