/*    
    This file is a part of Stonefish.

    Stonefish is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Stonefish is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

//
//  LinkActuator.h
//  Stonefish
//
//  Created by Patryk Cieślak on 23/11/2018.
//  Copyright (c) 2018 Patryk Cieslak. All rights reserved.
//

#ifndef __Stonefish_LinkActuator__
#define __Stonefish_LinkActuator__

#include "actuators/Actuator.h"

namespace sf
{
    class FeatherstoneEntity;
    class SolidEntity;
    
    //! An abstract class representing an actuator that can be attached to a rigid body.
    class LinkActuator : public Actuator
    {
    public:
        //! A constructor.
        /*!
         \param uniqueName a name of the link actuator
         */
        LinkActuator(std::string uniqueName);
        
        //! A method used to attach the actuator to a specified link of a multibody tree.
        /*!
         \param multibody a pointer to a rigid multibody object
         \param linkId an index of the link
         \param origin a transformation from the link origin to the actuator origin
         */
        virtual void AttachToLink(FeatherstoneEntity* multibody, unsigned int linkId, const Transform& origin);
        
        //! A method used to attach the actuator to a specified rigid body.
        /*!
         \param solid a pointer to a rigid body
         \param origin a transformation from the body origin to the actuator origin
         */
        virtual void AttachToSolid(SolidEntity* solid, const Transform& origin);
        
        //! A method returning actuator frame in the world frame.
        Transform getActuatorFrame();
       
    protected:
        SolidEntity* attach;
        Transform o2a;
    };
}

#endif
