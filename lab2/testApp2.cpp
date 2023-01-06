//testApp2.cpp
/*File used to check the correct behavior of the
  classes and functions implemented*/

//compile with g++ -o testApp2 testApp2.cpp Particle.cc Decay2.cc Detector.cc `$ROOTSYS/bin/root-config --libs --cflags` -Wall


#include <iostream>
#include <cmath>
#include <vector>

// ROOT header files
//#include "TRandom3.h" //random numbers
#include "TH1F.h"     //plotting
#include "TCanvas.h"
#include "TVector3.h" //for 3 Vectors

#include "Particle.h" //class to handle particles
#include "Decay2.h" //class to handle decays from 1 to 2 particles
#include "Detector.h" //class to simulate a detector

using std::cout;
using std::endl;
using std::vector;

double pi = M_PI;       //I rename pi of cmath library
double invPi = 1.0/pi ; //useful to avoid division
//rad to deg conversion
double toDeg(double rad){
    return rad*180.0*invPi;
}


int main(){

     //data
     int N = 10000; //number of events
     double pb_x = 300; //momentum of b meson i Mev
     //mass of particles in Mev
     double Mb = 5279.0 ; //B meson
     double Mpi = 140.0; //pi meson
     double Mk = 500.0; //K meson

     //Some test for the class Particle
     /*
     Particle B = Particle("Mesone B",Mb,pb_x,0.0,0.0), C;
     B.print();
     C = Particle("C",0.0,pb_x,0.0,0.0);
     C.print();
     C.setm(Mb);
     C.print();
     */


    //Some test for the class decay
    /*
    Particle B = Particle("Mesone B",Mb,pb_x,0.0,0.0);
    Decay2 BtoPiK = Decay2(B,Mpi,Mk);
    BtoPiK.info();
    double ps;
    ps = BtoPiK.p_star();
    cout << "pstar = " << ps << endl;
    TVector3 vec = BtoPiK.random_p3Son();
    cout << "px = " << vec.x()
         << "\npy = " << vec.y()
         << "\npz = " << vec.z()
         << "\nsum = " << vec.Mag() << endl;
     vector<TLorentzVector> p4_pair;
     TLorentzVector p4_1,p4_2;
     p4_pair = BtoPiK.random_p4_pair();
     p4_1 = p4_pair.at(0);
     p4_2 = p4_pair.at(1);
     cout << "p4 Pi COM" << endl;
     p4_1.Print();
     cout << "p4 K COM" << endl;
     p4_2.Print();
     cout<<"BOOOST!!"<<endl;
     vector<TLorentzVector> p4_pairB;
     TLorentzVector p4_1B,p4_2B;
     p4_pairB = BtoPiK.random_p4_pairBOOSTED();
     p4_1B = p4_pairB.at(0);
     p4_2B = p4_pairB.at(1);
     cout << "p4 Pi Lab" << endl;
     p4_1B.Print();
     cout << "p4 K Lab" << endl;
     p4_2B.Print();
     cout <<"mag: 1= "<< p4_1B.Mag()<< "\n      2= "<< p4_2B.Mag() 
          <<"\n      1+2= " << (p4_1B+p4_2B).Mag() <<endl;
     */

/*
    
    //Some test of the class detector
    
    Particle B = Particle("Mesone B",Mb,pb_x,0.0,0.0);
    Decay2 BtoPiK = Decay2(B,Mpi,Mk);

    Detector det3 = Detector(0.1); //detector with 3 percente resolution
    TVector3 vec = BtoPiK.random_p3Son(); //some vector just to try smearing
    cout << "before smearing" << endl;
    vec.Print();
    vec = det3.smearing(vec);
    cout << "after smearing" << endl;
    vec.Print();

    TVector3 vec2(1.0,0.0,0.0);
    TH1F hProva0("hProva", "prova, delta", 100, 0, 2.0);
    TH1F hProva("hProva", "prova, gaus(1,0.1)", 100, 0, 2.0);

    for(int i=0;i<N;i++){
     TVector3 vec2(1.0,0.0,0.0);
     hProva0.Fill(vec2.Mag());
     TVector3 vecsm = det3.smearing(vec2);
     hProva.Fill(vecsm.Mag()); 
    }

    //canvas adjustements
     TCanvas canv("canv", "canvas for plotting", 1280, 1024); //canvas for the plots
     canv.SetRightMargin(0.09); //to avoid text cropping
     canv.SetLeftMargin(0.15);
     canv.SetBottomMargin(0.15);

     //plot prova delta
     hProva0.Draw(); //plot the histogram
     hProva0.SetLineColor(kRed);
     canv.SaveAs("./prova0.pdf");
     //plot prova gaus
     hProva.Draw(); //plot the histogram
     hProva.SetLineColor(kRed);
     canv.SaveAs("./prova.pdf");
*/  


     Particle B = Particle("Mesone B",Mb,pb_x,0.0,0.0); //B meson
     Decay2 BtoPiK = Decay2(B,Mpi,Mk); //decay of a B meson into pi and k
     Detector det3 = Detector(0.1); //detector with 3 percent resolution

     //variables for the histogram
     int nbins = 100;
     double xlo = 5150.5;
     double xhi = 5350.5;
     //double binwidth = (xhi-xlo) / nbins;
     TH1F hMassTrue("hMassTrue", "Distribution of the invariant mass (True value)", nbins, xlo, xhi);
     TH1F hAngle("hAngle", "Distribution of the angle between Pi and K (Lab frame)", nbins, 170, 185);
     TH1F hMassMeas("hMassMeas", "Distribution of the invariant mass (Measured value)", nbins, xlo, xhi);
     TH1F hMassMeas2("hMassMeas2", "Distribution of the invariant mass (Measured value)", nbins, xlo-1000.0, xhi+1000.0);

     //as extra check, I plot the histo of the momentum, true and measured
     TH1F hPTrue_pi("hPTrue_pi", "Distribution of the pi momentum magnitude (True value)", nbins, BtoPiK.p_star()-800, BtoPiK.p_star()+800);
     TH1F hPMeas_pi("hPMeas_pi", "Distribution of the pi momentum (measured value)", nbins, BtoPiK.p_star()-800, BtoPiK.p_star()+800);
     TH1F hPTrue_k("hPTrue_k", "Distribution of the k momentum magnitude (True value)", nbins, BtoPiK.p_star()-800, BtoPiK.p_star()+800);
     TH1F hPMeas_k("hPMeas_k", "Distribution of the k momentum magnitude (measured value)", nbins, BtoPiK.p_star()-800, BtoPiK.p_star()+800);

     //event loop
     for(int i=0;i<N;i++){

     //First I get the 4-momenta in the lab frame

     vector<TLorentzVector> p4_pair_Boosted; //pair of boosted vector
     TLorentzVector p4_pi_0,p4_k_0;

     p4_pair_Boosted = BtoPiK.random_p4_pairBOOSTED(); //I get the boosted vector
     p4_pi_0 = p4_pair_Boosted.at(0);
     p4_k_0 = p4_pair_Boosted.at(1);

     //Then I compute the invariant mass...

     double invMassTrue; //invariant mass in the decay
     invMassTrue = (p4_pi_0+p4_k_0).Mag(); //I compute the invariant mass
     hMassTrue.Fill(invMassTrue); //fill the histo with data

     //..and the angle between the 2 decay product

     double angle; //ange between Pi and K in lab frame
     angle = toDeg( p4_pi_0.Vect().Angle(p4_k_0.Vect()) ); //I compute the angle (in deg)
     hAngle.Fill(angle); //fill the histo with data

     //Now comes the *SMEARING*

     //3momentun of pi and k in lab frame (true value)
     TVector3 p3_pi_0 = p4_pi_0.Vect();
     TVector3 p3_k_0 = p4_k_0.Vect();

     //magnitude of pi and k 3momentum in lab frame (true value)
     double p_pi_0 = p3_pi_0.Mag(); 
     double p_k_0 = p3_pi_0.Mag();

     //3momentum of pi and k after smearing (lab frame, measured value)
     TVector3 p3_pi_meas = det3.smearing(p3_pi_0);
     TVector3 p3_k_meas = det3.smearing(p3_k_0);

     /* The effect of the momentum measurement is simulated 
        via the smearing function of the detector class.
        The measurement of energy is not simulated so for
        the measured 4 momenta the smeared p and the true
        value of E are used.
        *****
        In this way the distribution of the invariant mass, bein it
        sqrt(E**2 - P**2)
        is asymmetric, with a long tail on the right --> Why? non sure about calculations
        *****
     */

     //4momentum of pi and k after smearing (lab frame, measured value)
     TLorentzVector p4_pi_meas = TLorentzVector(p3_pi_meas,p4_pi_0.E());
     TLorentzVector p4_k_meas = TLorentzVector(p3_k_meas,p4_k_0.E());


     //Now I can compute the invariant mass...

     double invMassMeas; //invariant mass in the decay
     invMassMeas = (p4_pi_meas+p4_k_meas).Mag(); //I compute the invariant mass
     hMassMeas.Fill(invMassMeas); //fill the histo with data

     /*Now I try to compute the invariant mass in another way:
       After the smearing I recompute the energy using the smeared momentum
     */
     TLorentzVector p4_pi_meas2 = TLorentzVector(p3_pi_meas, sqrt(p3_pi_meas.Mag2() +Mpi*Mpi) );
     TLorentzVector p4_k_meas2 = TLorentzVector(p3_k_meas, sqrt(p3_k_meas.Mag2() +Mk*Mk) );
     hMassMeas2.Fill((p4_pi_meas2+p4_k_meas2).Mag()); //fill the histo with data


     //extra check:
     hPTrue_pi.Fill(p_pi_0);
     hPMeas_pi.Fill(p3_pi_meas.Mag());
     //extra check:
     hPTrue_k.Fill(p_k_0);
     hPMeas_k.Fill(p3_k_meas.Mag());

     }

     //canvas adjustements
     TCanvas canv("canv", "canvas for plotting", 1280, 1024); //canvas for the plots
     canv.SetRightMargin(0.09); //to avoid text cropping
     canv.SetLeftMargin(0.15);
     canv.SetBottomMargin(0.15);

     //plot of the invariant mass (True Value)
     hMassTrue.GetXaxis()->SetTitle("Invariant Mass [MeV]");
     hMassTrue.GetYaxis()->SetTitle("Occurences");
     hMassTrue.Draw(); //plot the histogram
     hMassTrue.SetLineColor(kRed);
     canv.SaveAs("./true-mass.pdf");

     //plot of the angle distribution (True Value)
     hAngle.GetXaxis()->SetTitle("Angle [deg]");
     hAngle.GetYaxis()->SetTitle("Occurences");
     hAngle.Draw(); //plot the histogram
     hAngle.SetLineColor(kRed);
     canv.SaveAs("./opening-angle.pdf");

     //plot of the invariant mass (true+measured value)
     hMassMeas.GetXaxis()->SetTitle("Invariant Mass [MeV]");
     hMassMeas.GetYaxis()->SetTitle("Occurences");
     hMassMeas.Draw(); //plot the histogram
     hMassMeas.SetLineColor(kBlue);
     hMassTrue.Draw("sames"); //overlay of true measurement
     hMassTrue.SetLineColor(kRed);
     canv.SaveAs("./measured-mass.pdf");

     //plot of the invariant mass (true+measured value) (*With enegy modification*)
     hMassMeas2.GetXaxis()->SetTitle("Invariant Mass [MeV]");
     hMassMeas2.GetYaxis()->SetTitle("Occurences");
     hMassMeas2.Draw(); //plot the histogram
     hMassMeas2.SetLineColor(kBlue);
     hMassTrue.Draw("sames"); //overlay of true measurement
     hMassMeas2.Draw("sames");
     hMassTrue.SetLineColor(kRed);
     canv.SaveAs("./measured-mass_energymod.pdf");

     //plot of the pi momentum mag (true+measured value)
     hPTrue_pi.GetXaxis()->SetTitle("Momentum magnitude [MeV]");
     hPTrue_pi.GetYaxis()->SetTitle("Occurences");
     hPTrue_pi.Draw(); //plot the histogram
     hPTrue_pi.SetLineColor(kRed);
     hPMeas_pi.Draw("sames"); //overlay of true measurement
     hPMeas_pi.SetLineColor(kBlue);
     canv.SaveAs("./measured-pi_momentum.pdf");
     //plot of the k momentum mag (true+measured value)
     hPTrue_k.GetXaxis()->SetTitle("Momentum magnitude [MeV]");
     hPTrue_k.GetYaxis()->SetTitle("Occurences");
     hPTrue_k.Draw(); //plot the histogram
     hPTrue_k.SetLineColor(kRed);
     hPMeas_k.Draw("sames"); //overlay of true measurement
     hPMeas_k.SetLineColor(kBlue);
     canv.SaveAs("./measured-k_momentum.pdf");



    

     return 0;
}