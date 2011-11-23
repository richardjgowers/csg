/*
 * File:   csg_reupdate.h
 * Author: mashaya1
 *
 * Created on October 13, 2011, 11:09 PM
 */

#ifndef CSG_REUPDATE_H
#define	CSG_REUPDATE_H
#include <boost/program_options.hpp>
#include <votca/csg/csgapplication.h>
#include <votca/tools/table.h>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <votca/csg/trajectorywriter.h>
#include <votca/tools/property.h>
#include <votca/tools/histogramnew.h>

#include "potentials.h"

using namespace votca::csg;
using namespace votca::tools;
using namespace std;


class CsgREupdate
: public CsgApplication
{
public:
    string ProgramName() { return "csg_reupdate"; }
    void HelpText(ostream &out) {
        out << "computes relative entropy update.";
            }

    bool DoTrajectory() {return true;}
    /* we perform mapping only when generating ref all-atom
     * CG-CG neighborlist histogram
     */
    bool DoMapping(){

        if (_genref) return true;
        else return false;
        
    }

    void Initialize();
    bool EvaluateOptions();
    void BeginEvaluate(Topology *top, Topology *top_atom);
    void EndEvaluate();
    void EvalConfiguration(Topology *conf, Topology *conf_atom);
    void LoadOptions(const string &file);
    
private:

protected:
    // define what functional form to use for CG potential
    // defined in typedefpotfun.h
    //typedef FunctionLJ126 PotFunction;
    
    struct PotentialInfo {
        PotentialInfo(Topology *top, int index,
                        bool bonded_, bool genref,
                        int vec_pos_, Property *options);
        int potentialIndex;
        bool bonded;
        FunctionForm *ucg;
        int vec_pos;
        pair<int, int> beadTypes;
        
        string potentialName;
        string potentialFunction;
        string type1, type2;
        int nbeads1, nbeads2;
        
        HistogramNew aahist;

        ub::vector<double> pottblgrid;


        Property *_options;
    };
    Property _options;
    list<Property *> _nonbonded;

    typedef vector<PotentialInfo *> PotentialContainer;
    PotentialContainer _potentials;

    int _nlamda;
    ub::vector<double> _lamda;
    ub::vector<double> _dlamda;
    ub::matrix<double> _HS;
    ub::vector<double> _DS;
    ub::vector<double> _dUFrame;
    double _HS_Scale;
    
    double _UavgAA;
    double _UavgCG;
    double _beta;
    double _relax;
    int _nframes;

    /*if true then program only computes reference all atom
     * trajectory CG-CG neighborlist histograms and init. CG run configuration
     * this is done in step_0 of inverse script
     */
    bool _genref;
    TrajectoryWriter *_writer;
    
    void WriteOutFiles();
    void EvalBonded(Topology *conf, PotentialInfo *potinfo);
    void EvalNonbonded(Topology *conf, PotentialInfo *potinfo);

    // Compute Avg U, dU, and d2U values in reference AA ensemble
    void AAavgBonded(PotentialInfo *potinfo);
    void AAavgNonbonded(PotentialInfo *potinfo);

    // Compute refence AA ensemble CG-CG pair neibhor distances histogram
    void AAavgHist();

    // Formulates _HS dlamda = - _DS system of Lin Eq.
    void REFormulateLinEq();

    // Solve _HS dlamda = - _DS and update _lamda
    void REUpdateLamda();

    // Checks whether solution is converged using relative error 2-norm
    void CheckConvergence();


    
};
#endif	/* CSG_REUPDATE_H */
