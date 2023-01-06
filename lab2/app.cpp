//app.cpp

//compile with g++ -o app app.cpp Particle.o Decay2.o Detector.o `$ROOTSYS/bin/root-config --libs --cflags` -Wall


#include <iostream>
#include <cmath>
#include <vector>



// ROOT header files
#include "TH1F.h"     //plotting
#include "TCanvas.h"
#include "TVector3.h" //for 3 Vectors
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "Particle.h" //class to handle particles
#include "Decay2.h" //class to handle decays from 1 to 2 particles
#include "Detector.h" //class to simulate a detector

using std::cout;
using std::endl;
using std::vector;
using std::pair;

double pi = M_PI;       //I rename pi of cmath library
double invPi = 1.0/pi ; //useful to avoid division
//rad to deg conversion
double toDeg(double rad){
    return rad*180.0*invPi;
}


int main(){

    //data
    int N = 10000; //number of events
    double pb_x = 300; //momentum of b meson in Mev
    //mass of particles in Mev
    double Mb = 5279.0 ; //B meson
    double Mpi = 140.0; //pi meson
    double Mk = 500.0; //K meson

    Particle B = Particle("Mesone B",Mb,pb_x,0.0,0.0); //B meson

    Decay2 BtoPiK = Decay2(B,Mpi,Mk); //decay of a B meson into pi and k

    Detector det3 = Detector(0.03); //detector with 3 percent resolution

    Detector det1 = Detector(0.01); //detector with 1 percent resolution
    Detector det5 = Detector(0.05); //detector with 5 percent resolution
    Detector det10 = Detector(0.10); //detector with 10 percent resolution

    //variables for the histogram
    int nbins = 100;
    double xlo = 5150.5;
    double xhi = 5350.5;
    //double binwidth = (xhi-xlo) / nbins;
    TH1F hMassTrue("hMassTrue", "Distribution of the invariant mass (True value)", nbins, xlo, xhi);
    TH1F hAngle("hAngle", "Distribution of the angle between Pi and K (Lab frame)", nbins, 170, 185);

    //for the detector with 3 percent resolution
    TH1F hMassMeas("hMassMeas", "Distribution of the invariant mass (Measured value)", nbins, xlo-1000, xhi+1000);
     
    //for the detector with 1,5,10 percent resolution
    TH1F hMassMeas1("hMassMeas1", "Distribution of the invariant mass (Measured value)", nbins, xlo-1000, xhi+1000);
    TH1F hMassMeas5("hMassMeas5", "Distribution of the invariant mass (Measured value)", nbins, xlo-1000, xhi+1000);
    TH1F hMassMeas10("hMassMeas10", "Distribution of the invariant mass (Measured value)", nbins, xlo-1000, xhi+1000);


    //vector to store significant quantity about the decay
    //Each element of the vector is reletad to one of the event
    //so each element of the vector is a vector containing 5 pairs
    //the first element in the pair is relative to the pi, the second to the k
    pair<double,double> nmassPair;
    pair<double,double> pPair;
    pair<double,double> thetaPair;
    pair<double,double> phiPair;
    //to iterate i put all the thing i need in just 1 vector
    vector<vector<pair<double,double>>> dataSample;

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

        /*I multiply the true momentum by a gaussian factor
          around 1, with a given dispersion(given by the 
          resolution), then I use this new smeaerd momentum
          to compute the energy, assuming no error on the mass,
          so with the complete 4 momentum of pi and k I can 
          comput the invariant mass
          */

        //3momentun of pi and k in lab frame (true value)
        TVector3 p3_pi_0 = p4_pi_0.Vect();
        TVector3 p3_k_0 = p4_k_0.Vect();

        //magnitude of pi and k 3momentum in lab frame (true value)
        double p_pi_0 = p3_pi_0.Mag(); 
        double p_k_0 = p3_pi_0.Mag();

        //3momentum of pi and k after smearing (lab frame, measured value)
        TVector3 p3_pi_meas = det3.smearing(p3_pi_0);
        TVector3 p3_k_meas = det3.smearing(p3_k_0);


        //Now I can compute the invariant mass...

        double invMassMeas; //invariant mass in the decay
        TLorentzVector p4_pi_meas = TLorentzVector(p3_pi_meas, sqrt(p3_pi_meas.Mag2() +Mpi*Mpi) );
        TLorentzVector p4_k_meas = TLorentzVector(p3_k_meas, sqrt(p3_k_meas.Mag2() +Mk*Mk) );
        invMassMeas =(p4_pi_meas+p4_k_meas).Mag();
        hMassMeas.Fill(invMassMeas); //fill the histo with data

        //Repeating the same for 3 different detectors
        //resolution 1%
        p3_pi_meas = det1.smearing(p3_pi_0);
        p3_k_meas = det1.smearing(p3_k_0);
        p4_pi_meas = TLorentzVector(p3_pi_meas, sqrt(p3_pi_meas.Mag2() +Mpi*Mpi) );
        p4_k_meas = TLorentzVector(p3_k_meas, sqrt(p3_k_meas.Mag2() +Mk*Mk) );
        invMassMeas =(p4_pi_meas+p4_k_meas).Mag();
        hMassMeas1.Fill(invMassMeas); //fill the histo with data
        //resolution 5%
        p3_pi_meas = det5.smearing(p3_pi_0);
        p3_k_meas = det5.smearing(p3_k_0);
        p4_pi_meas = TLorentzVector(p3_pi_meas, sqrt(p3_pi_meas.Mag2() +Mpi*Mpi) );
        p4_k_meas = TLorentzVector(p3_k_meas, sqrt(p3_k_meas.Mag2() +Mk*Mk) );
        invMassMeas =(p4_pi_meas+p4_k_meas).Mag();
        hMassMeas5.Fill(invMassMeas); //fill the histo with data
        //resolution 10%
        p3_pi_meas = det10.smearing(p3_pi_0);
        p3_k_meas = det10.smearing(p3_k_0);
        p4_pi_meas = TLorentzVector(p3_pi_meas, sqrt(p3_pi_meas.Mag2() +Mpi*Mpi) );
        p4_k_meas = TLorentzVector(p3_k_meas, sqrt(p3_k_meas.Mag2() +Mk*Mk) );
        invMassMeas =(p4_pi_meas+p4_k_meas).Mag();
        hMassMeas10.Fill(invMassMeas); //fill the histo with data

        //I store just the data relative to the 10% detector
        vector<pair<double,double>> sample; //just 1 sample = a vector with 5 pairs
        sample.push_back(std::make_pair(p4_pi_meas.Mag(),p4_k_meas.Mag()));
        sample.push_back(std::make_pair(p3_pi_meas.Mag(),p3_k_meas.Mag()));
        sample.push_back(std::make_pair(p3_pi_meas.Theta(),p3_k_meas.Theta()));
        sample.push_back(std::make_pair(p3_pi_meas.Phi(),p3_k_meas.Phi()));
        //I put everything into a bigget vector
        dataSample.push_back(sample);


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

    //plot of the invariant mass (measured value)
    hMassMeas.GetXaxis()->SetTitle("Invariant Mass [MeV]");
    hMassMeas.GetYaxis()->SetTitle("Occurences");
    hMassMeas.Draw(); //plot the histogram
    hMassMeas.SetLineColor(kBlue);
    canv.SaveAs("./measured-mass.pdf");
    hMassTrue.Draw("SAMES");
    hMassMeas.Draw("SAMES");
    canv.SaveAs("./invariant-mass.pdf");

    //plot of the invariant mass (measured value)
    hMassMeas1.GetXaxis()->SetTitle("Invariant Mass [MeV]");
    hMassMeas1.GetYaxis()->SetTitle("Occurences");
    hMassMeas1.Draw(); //plot the histogram
    hMassMeas1.SetLineColor(kRed);
    hMassMeas5.Draw("SAMES");
    hMassMeas5.SetLineColor(kBlue);
    hMassMeas10.Draw("SAMES");
    hMassMeas10.SetLineColor(kGreen);
    canv.SaveAs("./invariant-mass_Detectors.pdf");

    //Now comes the TTree storage part

    TString rootfname("./decay_data.root");
    TFile* orootfile = new TFile( rootfname, "RECREATE");
    if( !orootfile->IsOpen() ) {
        std::cout << "problems creating root file. exiting... " << std::endl;
        exit(-1);
    }
    std::cout << "Ttree storing iniziated... " << rootfname << std::endl;

    TTree* tree = new TTree("DecayDataTree", "tree containing data relative to the decay B to Pi K");
    TVector3 p_B = TVector3(pb_x,0.0,0.0);
    int nDau = 2;
    pair<double,double> nmass,p,theta,phi;
    tree->Branch("p_B", &p_B,  "value/D");
    tree->Branch("nDau", &nDau, "nDau/I");
    tree->Branch("nmass", &nmass, "nmassPi/D:nmassK/D");
    tree->Branch("p", &p, "pPi/D:pK/D");
    tree->Branch("theta", &theta, "thetaPi/D:thetaK/D");
    tree->Branch("phi", &phi, "phiPi/D:phiK/D");


    for(vector<vector<pair<double,double>>>::const_iterator it = dataSample.begin(); it != dataSample.end(); ++it) {
        //since p_B and nDau are alway the same I do not change them
        nmass = it->at(0);
        p = it->at(1);
        theta = it->at(2);
        phi = it->at(3);
        // Store data in tree IN MEMORY
        tree->Fill();
    }

    // Actually write tree in file on disk
    tree->Write();

    // Print some info about the tree
    tree->Print();
   
    // Critical to close the file!
    orootfile->Close();

    // ==== Done storing data in a TTree

    delete orootfile;


    return 0;

}