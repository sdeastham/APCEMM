/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                                                                  */
/*     Aircraft Plume Chemistry, Emission and Microphysics Model    */
/*                             (APCEMM)                             */
/*                                                                  */
/* Structure Header File                                            */
/*                                                                  */
/* Author               : Thibaud M. Fritz                          */
/* Time                 : 7/26/2018                                 */
/* File                 : Structure.hpp                             */
/*                                                                  */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath> 

#include "Core/Interface.hpp"
#include "Core/Parameters.hpp"
#include "Core/Input.hpp"
#include "KPP/KPP_Parameters.h"
#include "KPP/KPP_Global.h"
#include "KPP/KPP.hpp"
#include "Util/PhysConstant.hpp"
#include "Util/PhysFunction.hpp"
#include "Core/Emission.hpp"
#include "Core/Aircraft.hpp"
#include "Core/Engine.hpp"
#include "Core/LiquidAer.hpp"
#include "Core/SZA.hpp"
#include "AIM/Aerosol.hpp"
#include "Core/Meteorology.hpp"

class Solution
{
    public:

        Solution();
        ~Solution();
        void Clear( std::vector<std::vector<double> >& vector_2D );
        void SetShape( std::vector<std::vector<double> >& vector_2D, \
                       const unsigned int n_x, \
                       const unsigned int n_y, \
                       const double value = 0.0 );
        void SetToValue( std::vector<std::vector<double> >& vector_2D, \
                         const double value = 0.0 );
        void Print( const std::vector<std::vector<double> >& vector_2D, \
                    const unsigned int i_max = 1, \
                    const unsigned int j_max = 1 ) const;
        void Initialize( char const *fileName, \
                         const Input &input,   \
                         const double airDens, \
                         const Meteorology &met, const bool DBG );
        void getData( double varArray[], double fixArray[], \
                      const unsigned int i = 0, \
                      const unsigned int j = 0 );
        void applyData( double varArray[], \
                        const unsigned int i = 0, \
                        const unsigned int j = 0 );
        void applyRing( double varArray[], double tempArray[], \
                        const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> mapRing2Mesh, \
                        const unsigned int iRing );
        void applyAmbient( double varArray[], \
                           const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> mapRing2Mesh, \
                           const unsigned int ambIndex );
        void addEmission( const Emission &EI, const Aircraft &ac, \
                          const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> &map, \
                          const std::vector<std::vector<double>> cellAreas, bool halfRing, \
                          double temperature, bool set2Saturation, \
                          AIM::Aerosol &liqAer, AIM::Aerosol &iceAer, \
                          const double Soot_Den );
        std::vector<double> getAmbient( ) const;
        std::vector<double> getLiqSpecies() const;
        std::vector<std::vector<double> > getAerosol( ) const;
        std::vector<double> getAerosolDens( ) const;
        std::vector<double> getAerosolRadi( ) const;
        std::vector<double> getAerosolArea( ) const;
        void getAerosolProp( double ( &radi )[4], double ( &area )[4], double &IWC, \
                             const std::vector<std::pair<unsigned int, unsigned int>> &indexList ) const;
        int SpinUp( std::vector<double> &amb_Value, \
                    const Input &input,             \
                    const double airDens,           \
                    const double startTime,         \
                    const bool DGB = 0 );

        unsigned int Nx() const { return size_x; };
        unsigned int Ny() const { return size_y; };
        void Debug( const double airDens );

        /* Gaseous species */
        std::vector<std::vector<double> > CO2, PPN, BrNO2, IEPOX, PMNN, N2O, N, PAN,\
                                          ALK4, MAP, MPN, Cl2O2, ETP, HNO2, C3H8, RA3P,\
                                          RB3P, OClO, ClNO2, ISOP, HNO4, MAOP, MP, ClOO,\
                                          RP, BrCl, PP, PRPN, SO4, Br2, ETHLN, MVKN,\
                                          R4P, C2H6, RIP, VRP, ATOOH, IAP, DHMOB, MOBA,\
                                          MRP, N2O5, ISNOHOO, ISNP, ISOPNB, IEPOXOO, MACRNO2, ROH,\
                                          MOBAOO, DIBOO, PMN, ISNOOB, INPN, H, BrNO3, PRPE,\
                                          MVKOO, Cl2, ISOPND, HOBr, A3O2, PROPNN, GLYX, MAOPO2,\
                                          CH4, GAOO, B3O2, ACET, MACRN, CH2OO, MGLYOO, VRO2,\
                                          MGLOO, MACROO, PO2, CH3CHOO, MAN2, ISNOOA, H2O2, PRN1,\
                                          ETO2, KO2, RCO3, HC5OO, GLYC, ClNO3, RIO2, R4N1,\
                                          HOCl, ATO2, HNO3, ISN1, MAO3, MRO2, INO2, HAC,\
                                          HC5, MGLY, ISOPNBO2, ISOPNDO2, R4O2, R4N2, BrO, RCHO,\
                                          MEK, ClO, MACR, SO2, MVK, ALD2, MCO3, CH2O,\
                                          H2O, Br, NO, NO3, Cl, O, O1D, O3,\
                                          HO2, NO2, OH, HBr, HCl, CO, MO2, ACTA,\
                                          EOH, H2, HCOOH, MOH, N2, O2, RCOOH;

        /* Liquid species */
        std::vector<std::vector<double> > SO4L, H2OL, HNO3L, HClL, HOClL, HBrL, HOBrL;

        /* Solid species */
        std::vector<std::vector<double> > H2OS, HNO3S;

        std::vector<std::vector<double> > NIT, NAT;

        /* Tracers */
        std::vector<std::vector<double> > SO4T;

        /* Aerosols */
        std::vector<std::vector<double> > sootDens, sootRadi, sootArea;

        AIM::Grid_Aerosol liquidAerosol, solidAerosol;

        unsigned int nBin_PA;
        unsigned int nBin_LA;

//        std::vector<double> LA_rE;
//        std::vector<double> LA_rJ;
//        std::vector<double> LA_vJ;
//
//        std::vector<double> PA_rE;
//        std::vector<double> PA_rJ;
//        std::vector<double> PA_vJ;
//
//        std::vector<std::vector<std::vector<double> > > PDF_LA, PDF_PA;

        double LA_nDens, LA_rEff, LA_SAD;
        double PA_nDens, PA_rEff, PA_SAD;

        AIM::Coagulation LA_Kernel, PA_Kernel;

        std::vector<double> KHETI_SLA;
        std::vector<double> AERFRAC, SOLIDFRAC;
        unsigned int STATE_PSC; 

    private:

        const unsigned int nVariables;
        const unsigned int nAer;
        const unsigned int size_x;
        const unsigned int size_y;

};

#endif /* STRUCTURE_H_INCLUDED */