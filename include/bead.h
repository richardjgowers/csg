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

#ifndef _bead_H
#define	_bead_H

#include <string>
#include <votca/tools/types.h>
#include <votca/tools/vec.h>
#include <votca/tools/property.h>
#include <assert.h>
#include "beadtype.h"
#include "topologyitem.h"

namespace votca { namespace csg {
using namespace votca::tools;

using namespace std;
class Molecule;

/**
    \brief information about a bead
 
    The Bead class describes an atom or a coarse grained bead. It stores information like the id, the name, the mass, the
    charge and the residue it belongs to. The coordinates are stored in the configuration class.

    \todo change resnr to pointer
    \todo make sure bead belongs to topology
*/
class Bead : public TopologyItem
{
public:   
    virtual ~Bead() {}

    /// get the id of the bead
    const int &getId() const { return _id; }
    /// get the name of the bead
    const string &getName() const { return _name; }
    
    /// get the bead type id
    const BeadType *getType() const { return _type; }

    /// get the residu number of the bead
    const int &getResnr() const { return _resnr; }
    /// get the mass of the bead
    const double &getM() const { return _m; }
    /// get the charge of the bead
    const double &getQ() const { return _q; }
    
    /// set the mass of the bead
    void setM(const double &m) { _m=m; }
    /// set the crg of the bead
    void setQ(const double &q) { _q=q; }

    /// get the symmetry of the bead
    /// 1: sphere
    /// 2: ellipsoid with 2 equal axis
    /// 3: ellispoid with 3 different axis
    const byte_t getSymmetry() const { return _symmetry; }

        /// set position of a bead
    void setPos(const vec &r);
    /// get the position of a bead
    const vec &getPos() const;

    /// set velocity of a bead
    void setVel(const vec &r);
    /// get the velocity of a bead
    const vec &getVel() const;
    
    /// set orientation U of a bead
    void setU(const vec &u);
    /// get orientation U of a bead
    const vec &getU() const;

    /// set orientation V of a bead
    void setV(const vec &v);
    /// get orientation V of a bead
    const vec &getV() const;

    /// set orientation W of a bead
    void setW(const vec &w);
    /// get orientation W of a bead
    const vec &getW() const;
        
       
    /// direct access (read/write) to the position of a bead
    vec &Pos() { return _pos; }
    /// direct access (read/write) to the velocities of a bead
    vec &Vel() { return _vel; }
    /// direct access (read/write) to the orientation U of a bead
    vec &U() { return _u; }
    /// direct access (read/write) to the orientation U of a bead
    vec &V() { return _v; }
    /// direct access (read/write) to the orientation U of a bead
    vec &W() { return _w; }
    /// direct access (read/write) to the force of a bead
    vec &F() { return _f; }
 
    /// set force acting on a bead
    void setF(const vec &F);
    /// get the force acting on a bead
    const vec &getF() const;

    /// does this configuration store positions?
    bool HasPos() {return _bPos; }
    /// does this configuration store velocities?
    bool HasVel() {return _bVel; }
    /// does this configuration store forces?
    bool HasF() {return _bF; }
    /// does this configuration store u-orientations?
    bool HasU() {return _bU; }
    /// does this configuration store v-orientations?
    bool HasV() {return _bV; }
    /// does this configuration store w-orientations?
    bool HasW() {return _bW; }
        
    void HasPos(bool b);
    void HasVel(bool b);
    void HasF(bool b);
    void HasU(bool b);
    void HasV(bool b);
    void HasW(bool b);
    
    Molecule *getMolecule() { return _mol; }

    vector<int> &ParentBeads() { return _parent_beads; };

    template<typename T>
    void setUserData(T *userdata) { _userdata = (void*)userdata; }

    template<typename T>
    T *getUserData() { return (T *)_userdata; }

    Property &Options() { return *_options; }

    void setOptions(Property &options) { _options = &options; }

protected:
    int _id;
    vector<int> _parent_beads;
    BeadType *_type;
    Molecule *_mol;
    
    // TODO: this is so far a pointer. this should change! each bead should have own options.
    Property *_options;

    byte_t _symmetry;
    string _name;
    
    int _resnr;
    
    double _m;
    double _q;
    
    vec _pos, _vel, _f, _u, _v, _w, _eigenvec1, _eigenvec2,_eigenvec3;
    double _val1,_val2,_val3;
    
    bool _bPos;
    bool _bVel;
    bool _bU;
    bool _bV;
    bool _bW;
    bool _bF;
    bool _b1,_b2,_b3;
    
    /// constructur
    Bead(Topology *owner, int id, BeadType *type, byte_t symmetry, string name, int resnr, double m, double q)
        : TopologyItem(owner), _id(id), _type(type), _symmetry(symmetry), _name(name), _resnr(resnr), _m(m), _q(q)
    {_bPos=false;
    _bVel=false;
    _bU=false;
    _bV=false;
    _bW=false;
    _bF=false;
    _b1=false;
    _b2=false;
    _b3=false;}

    void *_userdata;
    
    friend class Topology;

    friend class Molecule;
};

inline void Bead::setPos(const vec &r)
{
    _bPos=true;
    _pos = r;
}

inline const vec &Bead::getPos() const
{
    assert(_bPos);
    return _pos;
}

inline void Bead::setVel(const vec &r)
{
   _bVel=true;
   _vel = r;
}

inline const vec &Bead::getVel() const
{
    assert(_bVel);
    return _vel;
}

inline void Bead::setU(const vec &u)
{
    _bU=true;
    _u = u;
}

inline const vec &Bead::getU() const
{
    assert(_bU);
    return _u;
}

inline void Bead::setV(const vec &v)
{
    _bV=true;
    _v = v;
}

inline const vec &Bead::getV() const
{
    assert(_bV);
    return _v;
}

inline void Bead::setW(const vec &w)
{
    _bW=true;
    _w = w;
}

inline const vec &Bead::getW() const
{
    assert(_bW);
    return _w;
}

inline void Bead::setF(const vec &F)
{
    _bF=true;
    _f = F;
}

inline const vec &Bead::getF() const
{
    assert(_bF);
    return _f;
}

inline void Bead::HasPos(bool b)
{
    _bPos=b;
}

inline void Bead::HasVel(bool b)
{
    _bVel=b;
}

inline void Bead::HasF(bool b)
{
    _bF=b;
}

inline void Bead::HasU(bool b)
{
    _bU=b;
}

inline void Bead::HasV(bool b)
{
    _bV=b;
}

inline void Bead::HasW(bool b)
{
    _bW=b;
}

}}

#endif	/* _beadinfo_H */

