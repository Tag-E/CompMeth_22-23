//testApp.cpp
/*File used to check the correct behavior of the
  classes and functions implemented*/

//compile with g++ -o testApp testApp.cpp Particle.cc Decay2.cc Detector.cc `$ROOTSYS/bin/root-config --libs --cflags` -Wall

#include <iostream>
#include <cmath>

// ROOT header files
#include "TRandom3.h" //random numbers
#include "TH1F.h"     //plotting
#include "TCanvas.h"

#include "Particle.h" //class to handle particles
#include "Decay2.h" //class to handle decays from 1 to 2 particles
#include "Detector.h" //class to simulate a detector

using std::cout;
using std::endl;
using std::vector;

int main(){

     //data
     int N = 10000; //number of events
     double pb_x = 300; //momentum of b meson i Mev
     //mass of particles in Mev
     double Mb = 5279.0 ; //B meson
     double Mpi = 140.0; //pi meson
     double Mk = 500.0; //K meson

     //trials:
/*
     Particle B = Particle("Mesone B",Mb,pb_x,0.0,0.0);

     B.print();
    
     Particle P = Particle("Mesone pi",Mpi);

     P.print();

     Particle K = Particle("Mesone K",Mk);

     K.print();

     Decay2 BDecay = Decay2(B,Mpi,Mk);

     cout << "p* = " << BDecay.p_star() << endl;
     TVector3 vec = BDecay.random_p3Son();
     cout << "px = " << vec.x()
         << "\npy = " << vec.y()
         << "\npz = " << vec.z()
         << "\nsum = " << sqrt(vec.x()*vec.x() +vec.y()*vec.y()+ vec.z()*vec.z()) << endl;

     vector<TLorentzVector> p4_pair;
     TLorentzVector p4_1,p4_2;

     p4_pair = BDecay.random_p4_pair();
     p4_1 = p4_pair.at(0);
     p4_2 = p4_pair.at(1);

     cout<< "\nPRE BOOST\n" << endl;

     cout << "px = " << p4_1.Px()
         << "\npy = " << p4_1.Py()
         << "\npz = " << p4_1.Pz()
         << "\nE = " << p4_1.E() << endl;

     cout << "px = " << p4_2.Px()
         << "\npy = " << p4_2.Py()
         << "\npz = " << p4_2.Pz()
         << "\nE = " << p4_2.E() << endl;

    
     p4_pair = BDecay.random_p4_pairBOOSTED();
     p4_1 = p4_pair.at(0);
     p4_2 = p4_pair.at(1);

     cout<< "\nPRE BOOST\n" << endl;
    
     cout << "px = " << p4_1.Px()
         << "\npy = " << p4_1.Py()
         << "\npz = " << p4_1.Pz()
         << "\nE = " << p4_1.E() << endl;

     cout << "px = " << p4_2.Px()
         << "\npy = " << p4_2.Py()
         << "\npz = " << p4_2.Pz()
         << "\nE = " << p4_2.E() << endl;
    
    */


     //initial setup
     Particle B = Particle("Mesone B",Mb,pb_x,0.0,0.0); //decaying Particle
     Decay2 B_to_PiK = Decay2(B,Mpi,Mk); //decay we are interested in
     Detector det3 = Detector(0.10); //detector with 3% resolution

     //vectors where we'll store the useful data 
     vector<double> M_pi, M_k, M_sum, M_sum_sm; //invariant mass of the Pi and of the K and of their sum (also smeared)
     vector<double> angleList; //opening angle between Pi and K


     //variables for the histogram
     int nbins = 100;
     double xlo = 5150.5;
     double xhi = 5350.5;
     xlo = 0;
     xhi = 6000;
     //double binwidth = (xhi-xlo) / nbins;
     TH1F hMass("hMass", "distribution of the invariant mass", nbins, xlo, xhi);
     TH1F hMass_sm("hMass_sm", "distribution of the invariant mass smeared", nbins, xlo, xhi);
     TH1F hAngle("hAngle", "distribution of the angle between", nbins, 3.0, 3.1);

     //event loop
     for(int i=0;i<N;i++){
        // I generate the two 4 momenta in the LAB reference frame
        vector<TLorentzVector> p4_pair = B_to_PiK.random_p4_pairBOOSTED(); 

        hMass.Fill(p4_pair.at(0).M());

        //M_sum.push_back((p4_pair.at(0)+p4_pair.at(1)).M()); //for Pi+K

        //smearing of the 3 momenta of the two particles
        //p4_pair.at(0).SetVect( det3.smearing( p4_pair.at(0).Vect() ) );
        //p4_pair.at(1).SetVect( det3.smearing( p4_pair.at(1).Vect() ) );

        //smearing of the 3 momenta of the two particles
        p4_pair.at(0) =  det3.smearing( p4_pair.at(0) ) ;
        //p4_pair.at(1) =  det3.smearing( p4_pair.at(1) ) ;

        hMass_sm.Fill(p4_pair.at(0).M());


        //compute the invariant mass then stack it in the vector
        //M_pi.push_back(p4_pair.at(0).M()); //for the Pi
        //M_k.push_back(p4_pair.at(1).M()); //for the K
        //M_sum_sm.push_back((p4_pair.at(0)+p4_pair.at(1)).M()); //for Pi+K smeared

        //compute the angle between 
        //angleList.push_back(p4_pair.at(0).Vect().Angle(p4_pair.at(1).Vect()));
        //cout << p4_pair.at(0).Vect().Angle(p4_pair.at(1).Vect()) << endl;

        //I also store the variables in an histogram
        //hMass.Fill(M_sum.back());
        //hMass_sm.Fill(M_sum_sm.back());
        //hMass.Fill(M_pi.back());
        //hMass_sm.Fill(M_sum_sm.back());
        //hAngle.Fill(angleList.back());
     }

     //plot of the 2 histogram
     TCanvas canv("canv", "canvas for plotting", 1280, 1024); //canvas for the plot
     hMass.GetXaxis()->SetTitle("Distribution of Invariant Mass [MeV]");
     hMass.Draw(); //plot the histogram
     hMass.SetLineColor(kRed);
     //hMass.GetYaxis()->SetLimits(0,N);
     hMass_sm.Draw("same");
     canv.SaveAs("./invMass.pdf"); //save it as pdf
     //hAngle.GetXaxis()->SetTitle("Distribution of the Angle between [Rad?]");
     //hAngle.Draw(); //plot
     //canv.SaveAs("./angle.pdf"); 

    
    return 0;
}