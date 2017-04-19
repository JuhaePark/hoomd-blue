// Copyright (c) 2009-2017 The Regents of the University of Michigan
// This file is part of the HOOMD-blue project, released under the BSD 3-Clause License.

// Maintainer: mphoward

/*!
 * \file mpcd/SRDCollisionMethod.h
 * \brief Declaration of mpcd::SRDCollisionMethod
 */

#ifndef MPCD_SRD_COLLISION_METHOD_H_
#define MPCD_SRD_COLLISION_METHOD_H_

#ifdef NVCC
#error This header cannot be compiled by nvcc
#endif

#include "CollisionMethod.h"
#include "CellThermoCompute.h"

namespace mpcd
{

class SRDCollisionMethod : public mpcd::CollisionMethod
    {
    public:
        //! Constructor
        SRDCollisionMethod(std::shared_ptr<mpcd::SystemData> sysdata,
                           unsigned int cur_timestep,
                           unsigned int period,
                           int phase,
                           unsigned int seed,
                           std::shared_ptr<mpcd::CellThermoCompute> thermo);

        //! Destructor
        virtual ~SRDCollisionMethod();

        //! Implementation of the collision rule
        virtual void collide(unsigned int timestep);

        //! Get the MPCD rotation angle
        double getRotationAngle() const
            {
            return m_angle;
            }

        //! Set the MPCD rotation angle
        /*!
         * \param angle MPCD rotation angle in radians
         */
        void setRotationAngle(double angle)
            {
            m_angle = angle;
            }

        //! Get the cell rotation vectors from the last call
        const GPUVector<double3>& getRotationVectors() const
            {
            return m_rotvec;
            }

    protected:
        std::shared_ptr<mpcd::CellThermoCompute> m_thermo;  //!< Cell thermo
        GPUVector<double3> m_rotvec;    //!< MPCD rotation vectors
        double m_angle; //!< MPCD rotation angle (radians)

        //! Randomly draw cell rotation vectors
        virtual void drawRotationVectors(unsigned int timestep);

        //! Apply rotation matrix to velocities
        virtual void rotate(unsigned int timestep);
    };

namespace detail
{
//! Export SRDCollisionMethod to python
void export_SRDCollisionMethod(pybind11::module& m);
} // end namespace detail

} // end namespace azplugins

#endif // MPCD_SRD_COLLISION_METHOD_H_
