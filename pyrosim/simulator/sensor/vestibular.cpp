#ifndef _VESTIBULAR_SENSOR_CPP
#define _VESTIBULAR_SENSOR_CPP

#include <iostream>
#include "vestibular.h"
#include "neuron.h"

VESTIBULAR_SENSOR::VESTIBULAR_SENSOR(int myID, int evalPeriod) {
	ID = myID;
	values = new double[evalPeriod];
}

void VESTIBULAR_SENSOR::Poll(dBodyID body, int t) {

        const dReal *R = dBodyGetRotation(body);

        double a[3] = {0,0,1};

        double b[3];

        b[0] = R[0]*a[0] + R[1]*a[1] + R[2]*a[2];

        b[1] = R[4]*a[0] + R[5]*a[1] + R[6]*a[2];

        b[2] = R[8]*a[0] + R[9]*a[1] + R[10]*a[2];

        double dotProduct = a[0]*b[0] + a[1]*b[1] + a[2]*b[2];

        double bLen = sqrt( pow(b[0],2.0) + pow(b[1],2.0) + pow(b[2],2.0) );

        values[t] = acos( dotProduct / bLen );
}

void VESTIBULAR_SENSOR::Update_Sensor_Neurons(int t) {

        if ( mySensorNeuron )

                mySensorNeuron->Set( values[t] );
}

#endif // _VESTIBULAR_SENSOR_CPP
