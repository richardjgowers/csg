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

#ifndef _topology_H
#define	_topology_H

#include <vector>
#include <map>
#include <list>

#include <assert.h>
#include <votca/tools/types.h>
#include <votca/tools/vec.h>
#include <votca/tools/matrix.h>
#include "exclusionlist.h"
#include "bead.h"
#include "molecule.h"
#include "residue.h"
#include "beadtype.h"

namespace votca { namespace csg {
using namespace votca::tools;

class Interaction;
class ExclusionList;

typedef vector<Molecule *> MoleculeContainer;
typedef vector<Bead *> BeadContainer;
typedef vector<BeadType *> BeadTypeContainer;
typedef vector<Residue *> ResidueContainer;
typedef vector<Interaction *> InteractionContainer;


using namespace std;

/**
    \brief topology of the whole system

    The Topology class stores the topology of the system like the beads, bonds, molecules and residues.

    \todo internal management for ids and indices
 **/
class Topology
{
public:
    /// constructor
    Topology() {}    
    virtual ~Topology();
    
    /// cleans up all the stored data
    virtual void Cleanup();
    
    /// creates a new Bead
    virtual Bead *CreateBead(byte_t symmetry, string name, BeadType *type, int resnr, double m, double q);

    /// returns the BeadType or creates it if it doesnt exist
    virtual BeadType *GetOrCreateBeadType(string name);

    /// creates a new molecule
    virtual Molecule *CreateMolecule(string name);

    /// checks weather molecules with the same name really contain the same number of beads
    void CheckMoleculeNaming(void);
    
    /// creates a new residue
    virtual Residue *CreateResidue(string name);
    
    /** 
        \brief create molecules based on the residue
        This function scans the topology and creates molecules based on the resiude id.
        All beads with the same resid are put int one molecule.
    */
    void CreateMoleculesByResidue();
    
    /** 
        \brief put the whole topology in one molecule
        This function creates one big molecule for all beads in the topology.
    */
    void CreateOneBigMolecule(string name);
    
    void CreateMoleculesByRange(string name, int first, int nbeads, int nmolecules);
    
    /// number of molecules in the system
    int MoleculeCount() { return _molecules.size(); }
    /// number of beads in the system
    int BeadCount() { return _beads.size(); }
    
    /// number of beads in the system
    int ResidueCount() { return _residues.size(); }
       
    /// get a molecule by an index
    Molecule *MoleculeByIndex(int index);
    
    /// get the bead container
    BeadContainer &Beads() { return _beads; }
    /// get the molecule container
    MoleculeContainer &Molecules() { return _molecules; }
    /// get the bonded interaction container
    InteractionContainer &BondedInteractions() { return _interactions; }
    
    
    // \todo change AddBondedinteraction to Create bonded interaction, that only topology can create interactions
    void AddBondedInteraction(Interaction *ic);
    std::list<Interaction *> InteractionsInGroup(const string &group);
    
    BeadType *getBeadType(const int i) const { return _beadtypes[i]; }
    Bead *getBead(const int i) const { return _beads[i]; }
    Residue *getResidue(const int i) const { return _residues[i]; }
    Molecule *getMolecule(const int i) const { return _molecules[i]; }
       
    /// a hack to get vale's topology to read
    void ClearMoleculeList(){
        _molecules.clear();
    }
    
    /// adds all the beads+molecules+residues from other topology
    void Add(Topology *top);
    void CopyTopologyData(Topology *top);

    /// \brief rename all the molecules in range
    /// range is a string which is parsed by RangeParser,
    /// check that for formating
    void RenameMolecules(string range, string name);
    
    /// set the simulation box
    void setBox(const matrix &box) { _box = box; };
    /// get the simulation box
    const matrix &getBox() { return _box; };

    /// set the time of current frame
    void setTime(double t) { _time = t; };
    /// get the time of current frame
    double getTime() { return _time; };
    
    /// set the current step
    void setStep(int s) { _step = s; };
    /// get the current step
    int getStep() { return _step; };

    /// get the smallest distance between two particles with correct treatment of pbc
    vec getDist(int bead1, int bead2) const;
    
    vec BCShortestConnection(const vec &r1, const vec &r2) const;
    
    /// calculates the vox volume
    double BoxVolume();
    
    
    void RebuildExclusions();
    ExclusionList &getExclusions() { return _exclusions; }
    
protected:
    /// bead types in the topology
    BeadTypeContainer _beadtypes;
    
    /// beads in the topology
    BeadContainer _beads;
    
    /// molecules in the topology
    MoleculeContainer _molecules;
    
    /// residues in the topology
    ResidueContainer _residues;
    
    /// bonded interactions in the topology
    InteractionContainer _interactions;
    
    ExclusionList _exclusions;
    
    map<string, int> _interaction_groups;
    map<string, int> _beadtype_map;
    
    map<string, list<Interaction *> > _interactions_by_group;
    
    matrix _box;
    double _time;
    int _step;
};

inline Bead *Topology::CreateBead(byte_t symmetry, string name, BeadType *type, int resnr, double m, double q)
{
    
    Bead *b = new Bead(this, _beads.size(), type, symmetry, name, resnr, m, q);    
    _beads.push_back(b);
    return b;
}

inline Molecule *Topology::CreateMolecule(string name)
{
    Molecule *mol = new Molecule(this, _molecules.size(), name);
    _molecules.push_back(mol);
    return mol;
}

inline Residue *Topology::CreateResidue(string name)
{
    Residue *res = new Residue(this, _molecules.size(), name);
    _residues.push_back(res);
    return res;
}

inline Molecule *Topology::MoleculeByIndex(int index)
{
    return _molecules[index];
}

}}

#include "interaction.h"

#endif	/* _topology_H */

