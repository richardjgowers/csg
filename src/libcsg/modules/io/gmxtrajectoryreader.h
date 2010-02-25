/* 
 * Copyright 2009 The VOTCA Development Team (http://www.votca.org)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef _gmxtrajectoryreader_H
#define	_gmxtrajectoryreader_H

#include <string>
#include "trajectoryreader.h"

using namespace std;

namespace gmx {
#ifndef GMX4DEV
   extern "C"
   {
#endif
        #include <statutil.h>
        #include <typedefs.h>
        #include <smalloc.h>
        #include <vec.h>
        #include <copyrite.h>
        #include <statutil.h>
        #include <tpxio.h>
#ifndef GMX4DEV
    }
#endif
    // this one is needed because of bool is defined in one of the headers included by gmx
    #undef bool
}

/**
    \brief class for reading gromacs trajectory files

    This class provides the TrajectoryReader interface and encapsulates the trajectory reading function of gromacs

*/
class GMXTrajectoryReader : public TrajectoryReader
{
    public:        
        /// open a trejectory file
        bool Open(const string &file);
        /// read in the first frame
        bool FirstFrame(Topology &top);
        /// read in the next frame
        bool NextFrame(Topology &top);

        void Close();
        
    private:
        string _filename;
        
        // gmx status used in read_first_frame and _read_next_frame;
        int _gmx_status;
        /// gmx frame
        gmx::t_trxframe _gmx_frame;
        
};

#endif	/* _gmxtrajectoryreader_H */

