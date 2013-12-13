/* 
 * Copyright 2009-2011 The VOTCA Development Team (http://www.votca.org)
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

#ifndef HAVE_NO_CONFIG
#include <votca_config.h>
#endif

#include <votca/csg/trajectoryreader.h>
#include "modules/io/esptrajectoryreader.h"
#include "modules/io/lammpsreader.h"
#include "modules/io/xyzreader.h"

#ifdef GMX
#include "modules/io/gmxtrajectoryreader.h"
#endif
#include "modules/io/pdbreader.h"
#include "modules/io/dlpolytrajectoryreader.h"

namespace votca { namespace csg {

void TrajectoryReader::RegisterPlugins(void)
{
    TrjReaderFactory().Register<ESPTrajectoryReader>("esp");
    TrjReaderFactory().Register<LAMMPSReader>("dump");
    TrjReaderFactory().Register<XYZReader>("xyz");
#ifdef GMX
    TrjReaderFactory().Register<GMXTrajectoryReader>("trr");
    TrjReaderFactory().Register<GMXTrajectoryReader>("xtc");
    TrjReaderFactory().Register<GMXTrajectoryReader>("gro");
#endif
    TrjReaderFactory().Register<PDBReader>("pdb");
    TrjReaderFactory().Register<DLPOLYTrajectoryReader>("dlpoly");
}

}}
