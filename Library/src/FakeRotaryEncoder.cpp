//
//  FakeRotaryEncoder.cpp
//  Stonefish
//
//  Created by Patryk Cieslak on 10/05/2014.
//  Copyright (c) 2014 Patryk Cieslak. All rights reserved.
//

#include "FakeRotaryEncoder.h"

#pragma mark Constructors
FakeRotaryEncoder::FakeRotaryEncoder(std::string uniqueName, RevoluteJoint* joint, btScalar frequency, unsigned int historyLength) : RotaryEncoder(uniqueName, joint, frequency, historyLength)
{
    Reset();
}

FakeRotaryEncoder::FakeRotaryEncoder(std::string uniqueName, FeatherstoneEntity* mb, unsigned int joint, btScalar frequency, unsigned int historyLength) : RotaryEncoder(uniqueName, mb, joint, frequency, historyLength)
{
    Reset();
}

#pragma mark - Methods
void FakeRotaryEncoder::Reset()
{
    angle = lastAngle = GetRawAngle();
    angularVelocity = GetRawAngularVelocity();
    
    SimpleSensor::Reset();
}

void FakeRotaryEncoder::InternalUpdate(btScalar dt)
{
    //new angle
    btScalar actualAngle = GetRawAngle();
        
    //accumulate
    if(lastAngle * actualAngle < btScalar(0.))
    {
        if(lastAngle > M_PI_4)
            angle += ((actualAngle + FULL_ANGLE) - lastAngle);
        else if(lastAngle < -M_PI_4)
            angle += (actualAngle - (lastAngle + FULL_ANGLE));
        else
            angle += (actualAngle-lastAngle);
    }
    else
        angle += (actualAngle-lastAngle);
    
    lastAngle = actualAngle;
    
    //angular velocity
    angularVelocity = GetRawAngularVelocity();
    
    //save sample
    btScalar m[2];
    m[0] = angle;
    m[1] = angularVelocity;
    
    Sample s(2, m);
    AddSampleToHistory(s);
}

#pragma mark - Internal
btScalar FakeRotaryEncoder::GetRawAngularVelocity()
{
    if(multibody == NULL)
    {
        return revolute->getAngularVelocity();
    }
    else
    {
        btScalar mbAV(0);
        btMultibodyLink::eFeatherstoneJointType jt = btMultibodyLink::eInvalid;
        multibody->getJointVelocity(multibodyJoint, mbAV, jt);
        
        if(jt == btMultibodyLink::eRevolute)
            return mbAV;
        else
            return btScalar(0);
    }
}