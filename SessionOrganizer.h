/* 
 * File:   SessionOrganizer.h
 * Author: Kapil Thakkar
 *
 */

#ifndef SESSIONORGANIZER_H
#define	SESSIONORGANIZER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h> 

#include "Conference.h"
#include "Track.h"
#include "Session.h"
#include<ctime>
using namespace std;


/**
 * SessionOrganizer reads in a similarity matrix of papers, and organizes them
 * into sessions and tracks.
 * 
 * @author Kapil Thakkar
 *
 */
class SessionOrganizer {
private:
    double ** distanceMatrix;

    int parallelTracks ;
    int papersInSession ;
    int sessionsInTrack ;
    int solutioncount;
    clock_t start;
    clock_t end;
    Conference *conference;

    double processingTimeInMinutes ;
    double tradeoffCoefficient ; // the tradeoff coefficient


public:

    SessionOrganizer();
    SessionOrganizer(string filename);
    
    
    /**
     * Read in the number of parallel tracks, papers in session, sessions
     * in a track, and the similarity matrix from the specified filename.
     * @param filename is the name of the file containing the matrix.
     * @return the similarity matrix.
     */
    void readInInputFile(string filename);
    double scoreChangeCalculator(int i,int j,int k,int l,int p,int m);
    
    
    /**
     * Organize the papers according to some algorithm.
     */
    void organizePapers();
    
    
    /**
     * Get the distance matrix.
     * @return the distance matrix.
     */
    double** getDistanceMatrix();
    
    
    /**
     * Score the organization.
     * @return the score.
     */
    double scoreOrganization();
    
        void localsearch();
        void localbestsearch();
        void localsearchrandom();
    void printSessionOrganiser(char *);
};

#endif	/* SESSIONORGANIZER_H */

