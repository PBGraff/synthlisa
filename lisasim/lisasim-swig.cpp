#include <iostream.h>

#include "lisasim.h"

#include <time.h>
#include <math.h>

void printn(CircularRotating *mylisa,int arm,double t) {
    Vector nnew, nold;
    
    mylisa->putn(nnew,arm,t);
    mylisa->oldputn(nold,arm,t);
    
    cout << " " << nnew[0] << " " << nnew[1] << " " << nnew[2];
    cout << " " << nold[0] << " " << nold[1] << " " << nold[2];
}

LISA *stdlisa() {
  return new OriginalLISA(Lstd,Lstd,Lstd);
}

TDInoise *stdnoise(LISA *mylisa) {
    return new TDInoise(mylisa,1.0,2.5e-48,1.0,1.8e-37,1.0,1.1e-26,1.0e-6);
}

void printtdi(char *filename,TDI *mytdi,int samples,double samplingtime,char *observables) {
    ofstream outfile(filename);    

    mytdi->reset();
    
    struct timeval tv;
    
    gettimeofday(&tv,0);
    double timebeg = 1.0 * tv.tv_sec + 1.0e-6 * tv.tv_usec;
    
    for(int i=0;i<samples;i++) {
        double t = i * samplingtime;

        if(i % 16384 == 0 && i != 0) {
            gettimeofday(&tv,0);
            double speed = (1.0*i) / (1.0 * tv.tv_sec + 1.0e-6 * tv.tv_usec - timebeg);
            double sest = (samples - i) / speed;

            if(speed > 0.0)
                cout << "\rEstimating " << floor(sest/60.0) << "m" << floor(sest-60.0*floor(sest/60.0)) << "s to completion [" << floor(speed) << " (multi)samples/s]                    ";
        }

        char *obs = observables;

        while(obs[0]) {
            switch(obs[0]) {
                case 't':
                    outfile << t;
                    break;
                case 'X':
                    if(obs[1] == 'm') {
                        outfile << mytdi->Xm(t);
                        obs++;
                    } else {
                        outfile << mytdi->X(t);
                    }
                
                    break;
                case 'Y':
                    outfile << mytdi->Y(t);
                    break;
                case 'Z':
                    outfile << mytdi->Z(t);
                    break;
                case 'a':
                    outfile << mytdi->alpha(t);
                    break;
                case 'b':
                    outfile << mytdi->beta(t);
                    break;
                case 'g':
                    outfile << mytdi->gamma(t);
                    break;
                case 'z':
                    outfile << mytdi->zeta(t);
                    break;
                case 'P':
                    outfile << mytdi->P(t);
                    break;
                case 'E':
                    outfile << mytdi->E(t);
                    break;
                case 'U':
                    outfile << mytdi->U(t);
                    break;
                case 'y':
                    outfile << mytdi->y(3,1,2,0,0,0,t);
                    break;
                case 'w':
                    outfile << mytdi->z(3,1,2,0,0,0,0,t);
                    break;
                default:
                    break;
            }
        
            outfile << " ";
            obs++;
        }
    
        outfile << endl;
    }

    gettimeofday(&tv,0);
    double lapse = (1.0 * tv.tv_sec + 1.0e-6 * tv.tv_usec - timebeg);
    double speed = samples / lapse;
    cout << "\rCompleted in " << floor(lapse/60.0) << "m" << floor(lapse-60.0*floor(lapse/60.0)) << "s [" << floor(speed) << " (multi)samples/s]                      " << endl;
}

void settdi(double *array, TDI *mytdi,int samples,double samplingtime,char *observables) {
    mytdi->reset();
    
    struct timeval tv;
    
    gettimeofday(&tv,0);
    double timebeg = 1.0 * tv.tv_sec + 1.0e-6 * tv.tv_usec;
    
    for(int i=0;i<samples;i++) {
        double t = i * samplingtime;

        if(i % 16384 == 0 && i != 0) {
            gettimeofday(&tv,0);
            double speed = (1.0*i) / (1.0 * tv.tv_sec + 1.0e-6 * tv.tv_usec - timebeg);
            double sest = (samples - i) / speed;

            if(speed > 0.0)
                cout << "\rEstimating " << floor(sest/60.0) << "m" << floor(sest-60.0*floor(sest/60.0)) << "s to completion [" << floor(speed) << " (multi)samples/s]                    ";
        }

        char *obs = observables;

	// for the moment, only the first observable is returned

            switch(obs[0]) {
                case 't':
                    array[i] = t;
                    break;
                case 'X':
                    if(obs[1] == 'm') {
                        array[i] = mytdi->Xm(t);
                        obs++;
                    } else {
                        array[i] = mytdi->X(t);
                    }
                
                    break;
                case 'Y':
                    array[i] = mytdi->Y(t);
                    break;
                case 'Z':
                    array[i] = mytdi->Z(t);
                    break;
                case 'a':
                    array[i] = mytdi->alpha(t);
                    break;
                case 'b':
                    array[i] = mytdi->beta(t);
                    break;
                case 'g':
                    array[i] = mytdi->gamma(t);
                    break;
                case 'z':
                    array[i] = mytdi->zeta(t);
                    break;
                case 'P':
                    array[i] = mytdi->P(t);
                    break;
                case 'E':
                    array[i] = mytdi->E(t);
                    break;
                case 'U':
                    array[i] = mytdi->U(t);
                    break;
                case 'y':
                    array[i] = mytdi->y(3,1,2,0,0,0,t);
                    break;
                case 'w':
                    array[i] = mytdi->z(3,1,2,0,0,0,0,t);
                    break;
                default:
                    break;
            }

            obs++;
    }

    gettimeofday(&tv,0);
    double lapse = (1.0 * tv.tv_sec + 1.0e-6 * tv.tv_usec - timebeg);
    double speed = samples / lapse;
    cout << "\rCompleted in " << floor(lapse/60.0) << "m" << floor(lapse-60.0*floor(lapse/60.0)) << "s [" << floor(speed) << " (multi)samples/s]                      " << endl;
}

