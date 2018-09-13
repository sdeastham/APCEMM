/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                                                                  */
/* Utility Data Initialization                                      */
/*                                                                  */
/* Generated by KPP-2.2.3 symbolic chemistry Kinetics PreProcessor  */
/*       (http://www.cs.vt.edu/~asandu/Software/KPP)                */
/* KPP is distributed under GPL, the general public licence         */
/*       (http://www.gnu.org/copyleft/gpl.html)                     */
/* (C) 1995-1997, V. Damian & A. Sandu, CGRER, Univ. Iowa           */
/* (C) 1997-2005, A. Sandu, Michigan Tech, Virginia Tech            */
/*     With important contributions from:                           */
/*        M. Damian, Villanova University, USA                      */
/*        R. Sander, Max-Planck Institute for Chemistry, Mainz, Germany */
/*                                                                  */
/* File                 : KPP_Monitor.c                             */
/* Time                 : Tue Sep  4 17:12:00 2018                  */
/* Working directory    : /home/fritzt/Documents/kpp-2.2.3/Research/UCX_Forw_C_2 */
/* Equation file        : KPP.kpp                                   */
/* Output root filename : KPP                                       */
/*                                                                  */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "KPP_Parameters.h"
#include "KPP_Global.h"
#include "KPP_Sparse.h"



 /* Names of chemical species */

  const char *  SPC_NAMES[] = {
     "CO2","PPN","BrNO2","IEPOX","PMNN","N2O","N","PAN",
     "ALK4","MAP","MPN","Cl2O2","ETP","HNO2","C3H8","RA3P",
     "RB3P","OClO","ClNO2","ISOP","HNO4","MAOP","MP","ClOO",
     "RP","BrCl","PP","PRPN","SO4","Br2","ETHLN","MVKN",
     "R4P","C2H6","RIP","VRP","ATOOH","IAP","DHMOB","MOBA",
     "MRP","N2O5","ISNOHOO","ISNP","ISOPNB","IEPOXOO","MACRNO2","ROH",
     "MOBAOO","DIBOO","PMN","ISNOOB","INPN","H","BrNO3","PRPE",
     "MVKOO","Cl2","ISOPND","HOBr","A3O2","PROPNN","GLYX","MAOPO2",
     "CH4","GAOO","B3O2","ACET","MACRN","CH2OO","MGLYOO","VRO2",
     "MGLOO","MACROO","PO2","CH3CHOO","MAN2","ISNOOA","H2O2","PRN1",
     "ETO2","KO2","RCO3","HC5OO","GLYC","ClNO3","RIO2","R4N1",
     "HOCl","ATO2","HNO3","ISN1","MAO3","MRO2","INO2","HAC",
     "HC5","MGLY","ISOPNBO2","ISOPNDO2","R4O2","R4N2","BrO","RCHO",
     "MEK","ClO","MACR","SO2","MVK","ALD2","MCO3","CH2O",
     "H2O","Br","NO","NO3","Cl","O","O1D","O3",
     "HO2","NO2","OH","HBr","HCl","CO","MO2","ACTA",
     "EOH","H2","HCOOH","MOH","N2","O2","RCOOH" }; 

 /* Indexes of species to look at */

  int  LOOKAT[] = {
       0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11,
      12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
      24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
      36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
      48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
      60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71,
      72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83,
      84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
      96, 97, 98, 99,100,101,102,103,104,105,106,107,
     108,109,110,111,112,113,114,115,116,117,118,119,
     120,121,122,123,124,125,126,127,128,129,130,131,
     132,133,134 }; 

 /* Indexes of species to monitor */

  int  MONITOR[] = { };

 /* Names of atoms for mass balance */

  char *  SMASS[] = {
     0 }; 

 /* Equation names */

  const char *  EQN_NAMES[] = {
     "       NO + O3 --> NO2 + O2      ",
     "       O3 + OH --> HO2 + O2      ",
     "      O3 + HO2 --> OH + 2 O2     ",
     "      O3 + NO2 --> NO3 + O2      ",
     "      O3 + MO2 --> CH2O + HO2 + O2",
     "          2 OH --> H2O + O       ",
     "          2 OH --> H2O2          ",
     "      HO2 + OH --> H2O + O2      ",
     "     H2O2 + OH --> H2O + HO2     ",
     "      NO + HO2 --> NO2 + OH      ",
     "         2 HO2 --> H2O2 + O2     ",
     "       OH + CO --> CO2 + HO2     ",
     "      CH4 + OH --> H2O + MO2     ",
     "      NO + MO2 --> CH2O + HO2 + NO2",
     "     HO2 + MO2 --> MP + O2       ",
     "         2 MO2 --> CH2O + MOH + O2",
     "         2 MO2 --> 2 CH2O + 2 HO2",
     "       MP + OH --> H2O + MO2     ",
     "       MP + OH --> CH2O + H2O + OH",
     "    ATOOH + OH --> ATO2 + H2O    ",
     "    ATOOH + OH --> MGLY + H2O + OH",
     "     CH2O + OH --> H2O + HO2 + CO",
     "      NO2 + OH --> HNO3          ",
     "     HNO3 + OH --> H2O + NO3     ",
     "       NO + OH --> HNO2          ",
     "     HNO2 + OH --> H2O + NO2     ",
     "     HO2 + NO2 --> HNO4          ",
     "          HNO4 --> HO2 + NO2     ",
     "     HNO4 + OH --> H2O + NO2 + O2",
     "     NO3 + HO2 --> NO2 + OH + O2 ",
     "      NO + NO3 --> 2 NO2         ",
     "      NO3 + OH --> HO2 + NO2     ",
     "     NO3 + NO2 --> N2O5          ",
     "          N2O5 --> NO3 + NO2     ",
     "    OH + HCOOH --> CO2 + H2O + HO2",
     "      OH + MOH --> CH2O + HO2    ",
     "     NO3 + NO2 --> NO + NO2 + O2 ",
     "    CH2O + NO3 --> HNO3 + HO2 + CO",
     "     ALD2 + OH --> 0.95 MCO3 + 0.05 CH2O + H2O + 0.05 HO2 + 0.05 CO",
     "    ALD2 + NO3 --> HNO3 + MCO3   ",
     "    MCO3 + NO2 --> PAN           ",
     "           PAN --> MCO3 + NO2    ",
     "     MCO3 + NO --> CO2 + NO2 + MO2",
     "     C2H6 + OH --> ETO2 + H2O    ",
     "     ETO2 + NO --> ALD2 + HO2 + NO2",
     "     C3H8 + OH --> B3O2          ",
     "     C3H8 + OH --> A3O2          ",
     "     A3O2 + NO --> RCHO + HO2 + NO2",
     "      PO2 + NO --> ALD2 + CH2O + HO2 + NO2",
     "     ALK4 + OH --> R4O2          ",
     "     R4O2 + NO --> 0.05 A3O2 + 0.18 B3O2 + 0.32 ACET + 0.32 ETO2 + 0.13 RCHO ... etc.",
     "     R4O2 + NO --> R4N2          ",
     "     R4N1 + NO --> 0.3 R4O2 + 0.57 RCHO + 0.75 ALD2 + 0.39 CH2O + 2 NO2 ... etc.",
     "     ATO2 + NO --> 0.04 R4N2 + 0.96 MCO3 + 0.96 CH2O + 0.96 NO2",
     "      KO2 + NO --> 0.07 R4N2 + 0.93 ALD2 + 0.93 MCO3 + 0.93 NO2",
     "     RIO2 + NO --> 0.047 ISOPNB + 0.1 DIBOO + 0.07 ISOPND + 0.123 HC5 + 0.26 MACR ... etc.",
     "          RIO2 --> 0.5 GLYX + 0.5 GLYC + 0.5 HAC + 0.5 MGLY + CH2O + 2 HO2 ... etc.",
     "     VRO2 + NO --> 0.12 MVKN + 0.53 GLYC + 0.35 MGLY + 0.53 MCO3 + 0.35 CH2O ... etc.",
     "     MRO2 + NO --> 0.15 MACRN + 0.728 HAC + 0.122 MGLY + 0.122 CH2O + 0.85 HO2 ... etc.",
     "          MRO2 --> HAC + OH + CO ",
     "     MAN2 + NO --> 0.5 PROPNN + 0.5 MGLY + 0.5 CH2O + 1.5 NO2 + 0.5 OH ... etc.",
     "     B3O2 + NO --> ACET + HO2 + NO2",
     "     INO2 + NO --> 0.7 ISN1 + 0.23 HC5 + 0.035 MACR + 0.035 MVK + 0.07 CH2O ... etc.",
     "    INO2 + NO3 --> 0.7 ISN1 + 0.23 HC5 + 0.035 MACR + 0.035 MVK + 0.07 CH2O ... etc.",
     "    ISN1 + NO3 --> 0.4 ISNOOB + 0.6 ISNOOA + 0.6 HNO3",
     "  ISNOOA + NO3 --> R4N2 + HO2 + NO2 + CO",
     "   ISNOOA + NO --> R4N2 + HO2 + NO2 + CO",
     "  ISNOOA + NO2 --> PMN           ",
     "  ISNOOA + HO2 --> 0.75 RP + 0.25 O3 + 0.25 RCOOH",
     "  ISNOOB + NO3 --> GLYX + R4N2 + 2 NO2",
     "   ISNOOB + NO --> 0.94 GLYX + 0.94 R4N2 + 1.88 NO2",
     "  ISNOOB + HO2 --> INPN          ",
     "  ISNOOB + MO2 --> 0.7 GLYX + 0.7 R4N2 + 0.75 CH2O + 0.5 HO2 + 0.7 NO2 ... etc.",
     "     ISN1 + O3 --> 0.7 GLYX + 0.3 R4N2 + 0.75 CH2O + 0.5 HO2 + 0.7 NO2 ... etc.",
     "     ISN1 + OH --> 0.655 ISNOHOO + 0.345 ISNOOA",
     "  ISNOHOO + NO --> 0.919 GLYX + 0.934 R4N2 + 0.934 HO2",
     " ISNOHOO + HO2 --> INPN          ",
     " ISNOHOO + MO2 --> 0.7 GLYX + 0.7 R4N2 + 0.75 CH2O + 1.2 HO2 + 0.25 MOH ... etc.",
     "        2 INO2 --> 0.5 ISOPND + 1.2 ISN1 + 0.23 HC5 + 0.035 MACR + 0.035 MVK ... etc.",
     "     PRN1 + NO --> ALD2 + CH2O + 2 NO2",
     "    ALK4 + NO3 --> HNO3 + R4O2   ",
     "     R4N2 + OH --> R4N1 + H2O    ",
     "     OH + ACTA --> CO2 + H2O + MO2",
     "     RCHO + OH --> RCO3 + H2O    ",
     "    RCO3 + NO2 --> PPN           ",
     "           PPN --> RCO3 + NO2    ",
     "    MAO3 + NO2 --> PMN           ",
     "           PMN --> MAO3 + NO2    ",
     "     RCO3 + NO --> ETO2 + NO2    ",
     "     MAO3 + NO --> CO2 + 0.5 MCO3 + 0.5 CH2O + NO2 + 0.5 CO + 0.5 MO2",
     "    RCHO + NO3 --> RCO3 + HNO3   ",
     "     ACET + OH --> ATO2 + H2O    ",
     "    A3O2 + MO2 --> 0.25 ROH + 0.75 RCHO + 0.75 CH2O + HO2 + 0.25 MOH",
     "     PO2 + MO2 --> 0.25 ROH + 0.16 HAC + 0.09 RCHO + 0.5 ALD2 + 1.25 CH2O ... etc.",
     "    R4O2 + HO2 --> R4P           ",
     "    R4N1 + HO2 --> R4N2          ",
     "    ATO2 + HO2 --> 0.85 ATOOH + 0.15 MCO3 + 0.15 CH2O + 0.15 OH",
     "     KO2 + HO2 --> 0.85 ATOOH + 0.15 ALD2 + 0.15 MCO3 + 0.15 OH",
     "    RIO2 + HO2 --> 0.88 RIP + 0.047 MACR + 0.073 MVK + 0.12 CH2O + 0.12 HO2 ... etc.",
     "    VRO2 + HO2 --> 0.1 VRP + 0.578 GLYC + 0.102 MGLY + 0.033 RCHO + 0.187 MEK ... etc.",
     "    MRO2 + HO2 --> MRP           ",
     "    MAN2 + HO2 --> 0.85 ISNP + 0.075 PROPNN + 0.075 MGLY + 0.075 CH2O + 0.075 HO2 ... etc.",
     "    B3O2 + HO2 --> RB3P          ",
     "    INO2 + HO2 --> INPN          ",
     "    PRN1 + HO2 --> PRPN          ",
     "      MEK + OH --> KO2 + H2O     ",
     "    ETO2 + MO2 --> 0.75 ALD2 + 0.75 CH2O + HO2 + 0.25 EOH + 0.25 MOH",
     "     MEK + NO3 --> KO2 + HNO3    ",
     "    R4O2 + MO2 --> 0.25 ROH + 0.03 A3O2 + 0.09 B3O2 + 0.16 ACET + 0.16 ETO2 ... etc.",
     "    R4N1 + MO2 --> 0.25 ROH + 0.15 R4O2 + 0.54 RCHO + 0.38 ALD2 + 0.95 CH2O ... etc.",
     "    ATO2 + MO2 --> 0.2 HAC + 0.5 MGLY + 0.3 MCO3 + 0.5 CH2O + 0.3 HO2 + 0.5 MOH ... etc.",
     "     KO2 + MO2 --> 0.25 ROH + 0.25 MEK + 0.5 ALD2 + 0.5 MCO3 + 0.75 CH2O ... etc.",
     "    RIO2 + MO2 --> 0.24 ROH + 0.3 HC5 + 0.18 MACR + 0.28 MVK + 1.22 CH2O ... etc.",
     "        2 RIO2 --> 0.48 ROH + 0.5 HC5 + 0.36 MACR + 0.56 MVK + 0.92 CH2O ... etc.",
     "   HC5OO + MO2 --> 0.25 ROH + 0.13 GLYC + 0.18 HAC + 0.29 MGLY + 0.25 MEK ... etc.",
     "    VRO2 + MO2 --> 0.25 ROH + 0.36 GLYC + 0.14 MGLY + 0.25 MEK + 0.36 MCO3 ... etc.",
     "    MRO2 + MO2 --> 0.15 ROH + 0.595 HAC + 0.255 MGLY + 1.255 CH2O + 1.7 HO2 ... etc.",
     "    MAN2 + MO2 --> 0.375 PROPNN + 0.375 MGLY + 0.25 R4N2 + 0.625 CH2O + 0.375 HO2 ... etc.",
     "    B3O2 + MO2 --> 0.25 ROH + 0.75 ACET + 0.75 CH2O + HO2 + 0.25 MOH",
     "    INO2 + MO2 --> 0.25 ISOPND + 0.6 ISN1 + 0.115 HC5 + 0.018 MACR + 0.018 MVK ... etc.",
     "    PRN1 + MO2 --> 0.25 ROH + 0.25 RCHO + 0.5 ALD2 + 1.25 CH2O + 0.5 HO2 ... etc.",
     "      OH + EOH --> ALD2 + HO2    ",
     "      ROH + OH --> RCHO + HO2    ",
     "        2 ETO2 --> 2 ALD2 + 2 HO2",
     "        2 ETO2 --> ALD2 + EOH    ",
     "    ETO2 + HO2 --> ETP           ",
     "    A3O2 + HO2 --> RA3P          ",
     "     PO2 + HO2 --> PP            ",
     "    MCO3 + HO2 --> 0.41 MAP + 0.15 O3 + 0.44 OH + 0.44 MO2 + 0.15 ACTA ... etc.",
     "    RCO3 + HO2 --> 0.41 RP + 0.44 ETO2 + 0.15 O3 + 0.44 OH + 0.15 RCOOH ... etc.",
     "    MAO3 + HO2 --> 0.41 MAOP + 0.59 CH2O + 0.15 O3 + 0.44 OH + 0.39 CO ... etc.",
     "     PRPE + OH --> PO2           ",
     "     PRPE + O3 --> 0.1 CH4 + 0.12 CH2OO + 0.12 CH3CHOO + 0.5 ALD2 + 0.5 CH2O ... etc.",
     "      PMN + OH --> HAC + NO2 + CO",
     "      PMN + O3 --> MCO3 + CH2O + NO3",
     "     GLYC + OH --> 0.361 CO2 + 0.134 GLYX + 0.732 CH2O + 0.773 HO2 + 0.227 OH ... etc.",
     "     GLYC + OH --> OH + CO + HCOOH",
     "    PRPE + NO3 --> PRN1          ",
     "     GLYX + OH --> HO2 + 2 CO    ",
     "     MGLY + OH --> MCO3 + CO     ",
     "    GLYX + NO3 --> HNO3 + HO2 + 2 CO",
     "    MGLY + NO3 --> HNO3 + MCO3 + CO",
     "      MVK + OH --> VRO2          ",
     "     MACR + OH --> 0.53 MAO3 + 0.47 MRO2",
     "      HAC + OH --> MGLY + HO2    ",
     "      HAC + OH --> 0.5 CO2 + OH + 0.5 CO + 0.5 MO2 + 0.5 ACTA + 0.5 HCOOH ... etc.",
     "   A3O2 + MCO3 --> RCHO + HO2 + MO2",
     "    PO2 + MCO3 --> ALD2 + CH2O + HO2 + MO2",
     "   A3O2 + MCO3 --> RCHO + ACTA   ",
     "    PO2 + MCO3 --> 0.65 HAC + 0.35 RCHO + ACTA",
     "     ISOP + O3 --> 0.128 PRPE + 0.044 MVKOO + 0.12 CH2OO + 0.054 VRO2 + 0.066 MACROO ... etc.",
     "      MVK + O3 --> 0.12 CH2OO + 0.12 MGLOO + 0.5 MGLY + 0.1 ALD2 + 0.28 MCO3 ... etc.",
     "     MACR + O3 --> 0.211 CH2OO + 0.022 MGLYOO + 0.88 MGLY + 0.099 MCO3 ... etc.",
     "    MACR + NO3 --> MAN2          ",
     "    MACR + NO3 --> HNO3 + MAO3   ",
     "    RCO3 + MO2 --> ETO2 + CH2O + HO2",
     "    MAO3 + MO2 --> MCO3 + 2 CH2O + HO2",
     "    RCO3 + MO2 --> CH2O + RCOOH  ",
     "    MAO3 + MO2 --> CH2O + RCOOH  ",
     "     INPN + OH --> MEK + NO2 + OH",
     "     INPN + OH --> 0.36 INO2 + 0.64 R4N2 + 0.64 OH",
     "     PRPN + OH --> 0.791 PROPNN + 0.209 PRN1 + 0.791 OH",
     "      ETP + OH --> 0.36 ETO2 + 0.64 ALD2 + 0.64 OH",
     "     RA3P + OH --> 0.36 A3O2 + 0.64 RCHO + 0.64 OH",
     "     RB3P + OH --> 0.209 B3O2 + 0.791 ACET + 0.791 OH",
     "      R4P + OH --> 0.209 R4O2 + 0.791 RCHO + 0.791 OH",
     "       RP + OH --> RCO3          ",
     "       PP + OH --> 0.209 PO2 + 0.791 HAC + 0.791 OH",
     "      RIP + OH --> 0.387 RIO2 + 0.613 HC5 + 0.613 OH",
     "      RIP + OH --> IEPOX + OH    ",
     "    IEPOX + OH --> IEPOXOO       ",
     " IEPOXOO + HO2 --> 0.2 CO2 + 0.275 GLYX + 0.275 GLYC + 0.725 HAC + 0.275 MGLY ... etc.",
     "  IEPOXOO + NO --> 0.2 CO2 + 0.275 GLYX + 0.275 GLYC + 0.725 HAC + 0.275 MGLY ... etc.",
     "      IAP + OH --> 0.654 DHMOB + 0.346 HC5OO + 0.654 OH",
     "      VRP + OH --> 0.209 VRO2 + 0.791 MEK + 0.791 OH",
     "      MRP + OH --> MRO2          ",
     "      MRP + OH --> CO2 + HAC + OH",
     "     MAOP + OH --> MAO3          ",
     "     MAOP + OH --> MAOPO2        ",
     " MAOPO2 + MCO3 --> 2 CO2 + HAC + OH + MO2",
     " MAOPO2 + MCO3 --> MEK + ACTA    ",
     "  MAOPO2 + MO2 --> 0.7 CO2 + 0.3 ROH + 0.7 HAC + CH2O + 0.7 HO2 + 0.7 OH ... etc.",
     "      2 MAOPO2 --> 2 CO2 + 2 HAC + 2 OH",
     "  MAOPO2 + HO2 --> CO2 + HAC + 2 OH",
     "   MAOPO2 + NO --> CO2 + HAC + NO2 + OH",
     "   MAOPO2 + NO --> HNO3          ",
     "      MAP + OH --> MCO3          ",
     "    C2H6 + NO3 --> ETO2 + HNO3   ",
     "      HC5 + O3 --> 0.055 GAOO + 0.055 MGLYOO + 0.5 GLYC + 0.5 MGLY + 0.445 MCO3 ... etc.",
     "        2 MCO3 --> 2 MO2         ",
     "    MCO3 + MO2 --> CH2O + HO2 + MO2",
     "    MCO3 + MO2 --> CH2O + ACTA   ",
     "   R4O2 + MCO3 --> 0.05 A3O2 + 0.18 B3O2 + 0.32 ACET + 0.32 ETO2 + 0.13 RCHO ... etc.",
     "   ATO2 + MCO3 --> MCO3 + CH2O + MO2",
     "    KO2 + MCO3 --> ALD2 + MCO3 + MO2",
     "   RIO2 + MCO3 --> CO2 + 0.113 DIBOO + 0.14 HC5 + 0.294 MACR + 0.453 MVK ... etc.",
     "  HC5OO + MCO3 --> 0.29 DHMOB + 0.17 MOBA + 0.216 GLYX + 0.234 GLYC + 0.216 HAC ... etc.",
     "   VRO2 + MCO3 --> 0.6 GLYC + 0.4 MGLY + 0.6 MCO3 + 0.4 CH2O + 0.4 HO2 ... etc.",
     "   MRO2 + MCO3 --> 0.857 HAC + 0.143 MGLY + 0.143 CH2O + 0.85 HO2 + 0.857 CO ... etc.",
     "   B3O2 + MCO3 --> ACET + HO2 + MO2",
     "   R4N1 + MCO3 --> 0.3 R4O2 + 0.57 RCHO + 0.75 ALD2 + 0.39 CH2O + NO2 + MO2 ... etc.",
     "   MAN2 + MCO3 --> CO2 + 0.5 PROPNN + 0.5 MGLY + 0.5 CH2O + 0.5 HO2 + 0.5 NO2 ... etc.",
     "   INO2 + MCO3 --> 0.7 ISN1 + 0.23 HC5 + 0.035 MACR + 0.035 MVK + 0.07 CH2O ... etc.",
     "   PRN1 + MCO3 --> ALD2 + CH2O + NO2 + MO2",
     "   R4O2 + MCO3 --> MEK + ACTA    ",
     "   ATO2 + MCO3 --> MEK + ACTA    ",
     "    KO2 + MCO3 --> MEK + ACTA    ",
     "   RIO2 + MCO3 --> MEK + ACTA    ",
     "  HC5OO + MCO3 --> MEK + ACTA    ",
     "   VRO2 + MCO3 --> MEK + ACTA    ",
     "   MRO2 + MCO3 --> MEK + ACTA    ",
     "   R4N1 + MCO3 --> RCHO + NO2 + ACTA",
     "   MAN2 + MCO3 --> RCHO + NO2 + ACTA",
     "   INO2 + MCO3 --> RCHO + NO2 + ACTA",
     "   PRN1 + MCO3 --> RCHO + NO2 + ACTA",
     "   B3O2 + MCO3 --> ACET + ACTA   ",
     "   ETO2 + MCO3 --> ALD2 + HO2 + MO2",
     "   ETO2 + MCO3 --> ALD2 + ACTA   ",
     "   RCO3 + MCO3 --> ETO2 + MO2    ",
     "   MAO3 + MCO3 --> MCO3 + CH2O + MO2",
     "         2 NO3 --> 2 NO2 + O2    ",
     "     NO2 + MO2 --> MPN           ",
     "           MPN --> NO2 + MO2     ",
     "   ISOPNB + O3 --> 0.61 MVKN + 0.39 MACRN + CH2O + 0.27 OH",
     "   ISOPND + O3 --> 0.5 ETHLN + 0.5 PROPNN + 0.5 GLYC + 0.5 HAC + 0.27 OH ... etc.",
     "           HO2 --> O2            ",
     "           NO2 --> 0.5 HNO2 + 0.5 HNO3",
     "           NO3 --> HNO3          ",
     "    N2O5 + H2O --> 2 HNO3        ",
     "      SO2 + OH --> SO4 + HO2     ",
     "       Br + O3 --> BrO + O2      ",
     "     BrO + HO2 --> HOBr + O2     ",
     "      Br + HO2 --> HBr + O2      ",
     "      OH + HBr --> H2O + Br      ",
     "         2 BrO --> 2 Br + O2     ",
     "         2 BrO --> Br2 + O2      ",
     "      BrO + NO --> Br + NO2      ",
     "    BrNO3 + Br --> Br2 + NO3     ",
     "      Br2 + OH --> HOBr + Br     ",
     "      HOBr + O --> BrO + OH      ",
     "       O + HBr --> Br + OH       ",
     "      BrO + OH --> Br + HO2      ",
     "      Br + NO3 --> BrO + NO2     ",
     "     CH2O + Br --> HO2 + HBr + CO",
     "     ALD2 + Br --> MCO3 + HBr + CO",
     "     ACET + Br --> ATO2 + HBr + CO",
     "     C2H6 + Br --> ETO2 + HBr + CO",
     "     C3H8 + Br --> A3O2 + HBr + CO",
     "      Br + NO2 --> BrNO2         ",
     "     BrO + NO2 --> BrNO3         ",
     "   BrNO3 + H2O --> HOBr + HNO3   ",
     "          HOBr --> 0.5 Br2 + H2O ",
     "           HBr --> 0.5 Br2       ",
     "          HOBr --> 0.5 Br2 + H2O ",
     "           HBr --> 0.5 Br2       ",
     "      HC5 + OH --> HC5OO         ",
     "    HC5OO + NO --> 0.29 DHMOB + 0.17 MOBA + 0.216 GLYX + 0.234 GLYC + 0.216 HAC ... etc.",
     "    HC5OO + NO --> HNO3          ",
     "   HC5OO + HO2 --> 0.1 IAP + 0.9 GLYC + 0.9 MGLY + 0.9 HO2 + 0.9 OH",
     "   ISOPND + OH --> ISOPNDO2      ",
     "   ISOPNB + OH --> ISOPNBO2      ",
     " ISOPNDO2 + NO --> 0.13 ETHLN + 0.15 PROPNN + 0.07 MACRN + 0.15 GLYC + 0.44 HAC ... etc.",
     " ISOPNDO2 + NO --> HNO3          ",
     "ISOPNDO2 + HO2 --> 0.065 ETHLN + 0.5 ISNP + 0.075 PROPNN + 0.035 MACRN ... etc.",
     " ISOPNBO2 + NO --> 0.14 MVKN + 0.26 MACRN + 0.6 GLYC + 0.6 HAC + 0.4 CH2O ... etc.",
     " ISOPNBO2 + NO --> HNO3          ",
     "ISOPNBO2 + HO2 --> 0.07 MVKN + 0.5 ISNP + 0.13 MACRN + 0.3 GLYC + 0.3 HAC ... etc.",
     "     ISNP + OH --> 0.612 R4N1 + 0.193 ISOPNBO2 + 0.193 ISOPNDO2 + 0.612 OH ... etc.",
     "    MACRN + OH --> MACRNO2       ",
     "  MACRNO2 + NO --> 0.93 CO2 + 0.85 HAC + 0.07 MGLY + 0.08 CH2O + 0.15 NO3 ... etc.",
     " MACRNO2 + HO2 --> 0.93 CO2 + 0.85 HAC + 0.07 MGLY + 0.08 CH2O + 0.15 NO3 ... etc.",
     " MACRNO2 + NO2 --> PMNN          ",
     "          PMNN --> MACRNO2 + NO2 ",
     "    DHMOB + OH --> 0.5 HAC + 0.5 MEK + HO2 + 1.5 CO",
     "    DIBOO + NO --> 0.48 GLYX + 0.52 GLYC + 0.48 HAC + 0.52 MGLY + HO2 + NO2 ... etc.",
     "    DIBOO + NO --> HNO3          ",
     "   DIBOO + HO2 --> 0.85 R4P + 0.072 GLYX + 0.078 GLYC + 0.072 HAC + 0.078 MGLY ... etc.",
     "     MOBA + OH --> MOBAOO        ",
     "   MOBAOO + NO --> CO2 + RCHO + HO2 + NO2",
     "   MOBAOO + NO --> HNO3          ",
     "  MOBAOO + HO2 --> 0.5 CO2 + 0.5 R4P + 0.5 RCHO + 0.5 HO2 + 0.5 OH",
     "     MOBA + O3 --> CO2 + MEK + HO2 + OH",
     "    ETHLN + OH --> CO2 + CH2O + NO2",
     "   PROPNN + OH --> MGLY + NO2    ",
     "    CH2OO + NO --> CH2O + NO2    ",
     "   CH2OO + NO2 --> CH2O + NO3    ",
     "   CH2OO + SO2 --> SO4 + CH2O    ",
     "   CH2OO + H2O --> H2O2 + CH2O   ",
     "   CH2OO + H2O --> HCOOH         ",
     "   MACROO + CO --> MACR          ",
     "   MACROO + NO --> MACR + NO2    ",
     "  MACROO + NO2 --> MACR + NO3    ",
     "  MACROO + SO2 --> SO4 + MACR    ",
     "  MACROO + H2O --> MRP           ",
     "  MACROO + H2O --> H2O2 + MACR   ",
     "    MVKOO + CO --> MVK           ",
     "    MVKOO + NO --> MVK + NO2     ",
     "   MVKOO + NO2 --> MVK + NO3     ",
     "   MVKOO + SO2 --> SO4 + MVK     ",
     "   MVKOO + H2O --> H2O2 + MVK    ",
     "   MGLYOO + CO --> MGLY          ",
     "   MGLYOO + NO --> MGLY + NO2    ",
     "  MGLYOO + NO2 --> MGLY + NO3    ",
     "  MGLYOO + SO2 --> SO4 + MGLY    ",
     "  MGLYOO + H2O --> H2O2 + MGLY   ",
     "    MGLOO + CO --> MGLY          ",
     "    MGLOO + NO --> MGLY + NO2    ",
     "   MGLOO + NO2 --> MGLY + NO3    ",
     "   MGLOO + SO2 --> SO4 + MGLY    ",
     "   MGLOO + H2O --> MCO3 + MO2    ",
     "   MGLOO + H2O --> H2O2 + MGLY   ",
     "  CH3CHOO + CO --> ALD2          ",
     "  CH3CHOO + NO --> ALD2 + NO2    ",
     " CH3CHOO + NO2 --> ALD2 + NO3    ",
     " CH3CHOO + SO2 --> SO4 + ALD2    ",
     " CH3CHOO + H2O --> H2O2 + ALD2   ",
     " CH3CHOO + H2O --> ACTA          ",
     "     GAOO + CO --> GLYC          ",
     "     GAOO + NO --> GLYC + NO2    ",
     "    GAOO + NO2 --> GLYC + NO3    ",
     "    GAOO + SO2 --> SO4 + GLYC    ",
     "    GAOO + H2O --> H2O2 + GLYC   ",
     "    GAOO + H2O --> HAC           ",
     "     H2O + O1D --> 2 OH          ",
     "      O1D + N2 --> O + N2        ",
     "      O1D + O2 --> O + O2        ",
     "      O1D + H2 --> H + OH        ",
     "     N2O + O1D --> N2 + O2       ",
     "     N2O + O1D --> 2 NO          ",
     "     CH4 + O1D --> OH + MO2      ",
     "     CH4 + O1D --> CH2O + H2     ",
     "     CH4 + O1D --> H + CH2O + HO2",
     "        O + O2 --> O3            ",
     "        O + O3 --> 2 O2          ",
     "       OH + H2 --> H + H2O       ",
     "        O + OH --> H + O2        ",
     "       O + HO2 --> OH + O2       ",
     "      O1D + O3 --> 2 O2          ",
     "      O1D + O3 --> 2 O + O2      ",
     "       O + NO2 --> NO + O2       ",
     "       NO3 + O --> NO2 + O2      ",
     "        NO + O --> NO2           ",
     "       O + NO2 --> NO3           ",
     "      H2O2 + O --> HO2 + OH      ",
     "        H + O2 --> HO2           ",
     "        H + O3 --> OH + O2       ",
     "       H + HO2 --> 2 OH          ",
     "       H + HO2 --> H2O + O       ",
     "       H + HO2 --> H2 + O2       ",
     "        N + O2 --> NO + O        ",
     "        N + NO --> O + N2        ",
     "       N + NO2 --> N2O + O       ",
     "       BrO + O --> Br + O2       ",
     "      CH2O + O --> HO2 + OH + CO ",
     "     O1D + HCl --> 0.24 H + 0.24 ClO + 0.67 Cl + 0.09 O + 0.67 OH + 0.09 HCl ... etc.",
     "     O1D + HBr --> 0.15 H + 0.15 BrO + 0.65 Br + 0.2 O + 0.65 OH + 0.2 HBr ... etc.",
     "     Cl2 + O1D --> 0.25 Cl2 + 0.75 ClO + 0.75 Cl + 0.25 O",
     "      Cl2 + OH --> HOCl + Cl     ",
     "     ClO + MO2 --> ClOO + CH2O + HO2",
     "      ClO + OH --> Cl + HO2      ",
     "      ClO + OH --> HCl + O2      ",
     "     OClO + OH --> HOCl + O2     ",
     "    Cl2O2 + OH --> ClOO + HOCl   ",
     "      OH + HCl --> H2O + Cl      ",
     "     HOCl + OH --> ClO + H2O     ",
     "    ClNO2 + OH --> HOCl + NO2    ",
     "    ClNO3 + OH --> HOCl + NO3    ",
     "      CH4 + Cl --> HCl + MO2     ",
     "     CH2O + Cl --> HO2 + HCl + CO",
     "       Cl + O3 --> ClO + O2      ",
     "       Cl + H2 --> H + HCl       ",
     "     H2O2 + Cl --> HO2 + HCl     ",
     "      Cl + HO2 --> HCl + O2      ",
     "      Cl + HO2 --> ClO + OH      ",
     "       ClO + O --> Cl + O2       ",
     "     ClO + HO2 --> HOCl + O2     ",
     "      ClO + NO --> Cl + NO2      ",
     "     ClO + NO2 --> ClNO3         ",
     "         2 ClO --> Cl2 + O2      ",
     "         2 ClO --> ClOO + Cl     ",
     "         2 ClO --> OClO + Cl     ",
     "       Cl + O2 --> ClOO          ",
     "          ClOO --> Cl + O2       ",
     "         2 ClO --> Cl2O2         ",
     "         Cl2O2 --> 2 ClO         ",
     "     ClOO + Cl --> Cl2 + O2      ",
     "     ClOO + Cl --> 2 ClO         ",
     "     BrO + ClO --> OClO + Br     ",
     "     BrO + ClO --> ClOO + Br     ",
     "     BrO + ClO --> BrCl + O2     ",
     "     ClNO3 + O --> ClO + NO3     ",
     "    ClNO3 + Cl --> Cl2 + NO3     ",
     "    N2O5 + HCl --> ClNO2 + HNO3  ",
     "   ClNO3 + H2O --> HOCl + HNO3   ",
     "   ClNO3 + HCl --> Cl2 + HNO3    ",
     "   ClNO3 + HBr --> BrCl + HNO3   ",
     "   BrNO3 + HCl --> BrCl + HNO3   ",
     "    HOCl + HCl --> Cl2 + H2O     ",
     "    HOCl + HBr --> BrCl + H2O    ",
     "    HOBr + HCl --> BrCl + H2O    ",
     "            O3 --> O + O2        ",
     "            O3 --> O1D + O2      ",
     "            O2 --> 2 O           ",
     "           NO2 --> NO + O        ",
     "          H2O2 --> 2 OH          ",
     "            MP --> CH2O + HO2 + OH",
     "          CH2O --> H + HO2 + CO  ",
     "          CH2O --> CO + H2       ",
     "          HNO3 --> NO2 + OH      ",
     "          HNO2 --> NO + OH       ",
     "          HNO4 --> NO3 + OH      ",
     "          HNO4 --> HO2 + NO2     ",
     "           NO3 --> O + NO2       ",
     "           NO3 --> NO + O2       ",
     "          N2O5 --> NO3 + NO2     ",
     "          ALD2 --> 0.12 MCO3 + HO2 + 0.88 CO + 0.88 MO2",
     "          ALD2 --> CH4 + CO      ",
     "           PAN --> 0.7 MCO3 + 0.3 NO3 + 0.7 NO2 + 0.3 MO2",
     "          RCHO --> ETO2 + HO2 + CO",
     "          ACET --> MCO3 + MO2    ",
     "          ACET --> CO + 2 MO2    ",
     "           MEK --> 0.85 ETO2 + 0.15 RCO3 + 0.85 MCO3 + 0.15 MO2",
     "          GLYC --> 0.9 CH2O + 1.73 HO2 + 0.07 OH + CO + 0.1 MOH",
     "          GLYX --> 2 HO2 + 2 CO  ",
     "          GLYX --> 2 CO + H2     ",
     "          GLYX --> CH2O + CO     ",
     "          MGLY --> MCO3 + HO2 + CO",
     "           MVK --> PRPE + CO     ",
     "           MVK --> MCO3 + CH2O + HO2 + CO",
     "           MVK --> RCO3 + MO2    ",
     "          MACR --> MCO3 + CH2O + HO2 + CO",
     "           HAC --> MCO3 + CH2O + HO2",
     "          INPN --> RCHO + HO2 + NO2 + OH",
     "          PRPN --> RCHO + HO2 + NO2 + OH",
     "           ETP --> ALD2 + HO2 + OH",
     "          RA3P --> RCHO + HO2 + OH",
     "          RB3P --> ACET + HO2 + OH",
     "           R4P --> RCHO + HO2 + OH",
     "            PP --> ALD2 + CH2O + HO2 + OH",
     "            RP --> ALD2 + HO2 + OH",
     "           RIP --> 0.29 HC5 + 0.285 MACR + 0.425 MVK + 0.71 CH2O + HO2 ... etc.",
     "           IAP --> 0.26 GLYC + 0.36 HAC + 0.58 MGLY + HO2 + OH + 0.67 CO ... etc.",
     "          ISNP --> RCHO + HO2 + NO2 + OH",
     "           VRP --> 0.7 GLYC + 0.3 MGLY + 0.7 MCO3 + 0.3 CH2O + 0.3 HO2 ... etc.",
     "           MRP --> HAC + 0.5 CH2O + HO2 + OH + 0.5 CO",
     "          MAOP --> MCO3 + CH2O + OH",
     "          R4N2 --> 0.05 A3O2 + 0.18 B3O2 + 0.32 ACET + 0.32 ETO2 + 0.13 RCHO ... etc.",
     "           MAP --> OH + MO2      ",
     "         MACRN --> HAC + MGLY + 0.5 CH2O + HO2 + NO2 + 0.5 CO",
     "          MVKN --> GLYC + MCO3 + NO2",
     "        ISOPNB --> HC5 + HO2 + NO2",
     "           Br2 --> 2 Br          ",
     "           BrO --> Br + O        ",
     "          HOBr --> Br + OH       ",
     "         BrNO3 --> Br + NO3      ",
     "         BrNO3 --> BrO + NO2     ",
     "         BrNO2 --> Br + NO2      ",
     "           MPN --> CH2O + NO3 + HO2",
     "           MPN --> NO2 + MO2     ",
     "        ISOPND --> HC5 + HO2 + NO2",
     "        PROPNN --> CH2O + NO2 + CO + MO2",
     "         ATOOH --> MCO3 + CH2O + OH",
     "           N2O --> O1D + N2      ",
     "           SO4 --> SO2 + 2 OH    ",
     "            NO --> N + O         ",
     "          BrCl --> Br + Cl       ",
     "           Cl2 --> 2 Cl          ",
     "           ClO --> Cl + O        ",
     "          OClO --> ClO + O       ",
     "         Cl2O2 --> ClOO + Cl     ",
     "         ClNO2 --> Cl + NO2      ",
     "         ClNO3 --> NO3 + Cl      ",
     "         ClNO3 --> ClO + NO2     ",
     "          HOCl --> Cl + OH       ",
     "          ClOO --> Cl + O2       "
      }; 


/* INLINED global variables                                         */

/* End INLINED global variables                                     */

