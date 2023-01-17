//Emilio Taggi 1910388 2023/01/16
//app.cpp
//compile with: g++ -o app app.cpp Particle.cc Ensemble.cc `$ROOTSYS/bin/root-config --libs --cflags` -Wall
#include "Particle.h"
#include "Ensemble.h"

#include "TVector3.h" //for the Ensemble's position and velocity

#include "TH1F.h"     //plotting
#include "TCanvas.h"

#include "TFile.h"
#include "TTree.h"
#include "TString.h"


#include "TFile.h"

#include <iostream>
using namespace std;

#include <vector>
using std::vector;

int main(){

    //fast check on correct behavior of class particle
    Particle par1 = Particle(10,TVector3(1.0,1.0,1.0),TVector3(2.0,2.0,2.0));
    par1.print("Particle 1");

    //fast check on correct behavior of class Ensemble
    Ensemble ens1 = Ensemble(10);
    ens1.print("Ensemble 1");
    Ensemble ens2 = Ensemble::EnsembleGaussian(100,20,2,5,1,5,2); //gaussian generated ensemble
    ens2.print("Ensemble 2");

    //Part 1 point 4
    int myN = 1000;
    double my_m_mean = 20;
    double my_m_sig = 2;
    double my_x_mean = 5;
    double my_x_sig = 1;
    double my_v_mean = 5;
    double my_v_sig = 2;
    //generate an enseble gaussianly
    Ensemble myEns = Ensemble::EnsembleGaussian(myN, my_m_mean,my_m_sig, my_x_mean,my_x_sig, my_v_mean,my_v_sig); 
    vector<Particle> particleList = myEns.particles(); //list of the particle I'll loop over

    //variables for the histogram
    int nbins = 100;
    TH1F hm("hm", "Distribution of the mass", nbins, my_m_mean-6*my_m_sig,my_m_mean+6*my_m_sig);
    TH1F hx1("hx1", "Distribution of the x coordinate", nbins, my_x_mean-6*my_x_sig,my_x_mean+6*my_x_sig);
    TH1F hx2("hx2", "Distribution of the y coordinate", nbins, my_x_mean-6*my_x_sig,my_x_mean+6*my_x_sig);
    TH1F hx3("hx3", "Distribution of the z coordinate", nbins, my_x_mean-6*my_x_sig,my_x_mean+6*my_x_sig);
    TH1F hv1("hv1", "Distribution of the vx coordinate", nbins, my_v_mean-6*my_v_sig,my_v_mean+6*my_v_sig);
    TH1F hv2("hv2", "Distribution of the vy coordinate", nbins, my_v_mean-6*my_v_sig,my_v_mean+6*my_v_sig);
    TH1F hv3("hv3", "Distribution of the vz coordinate", nbins, my_v_mean-6*my_v_sig,my_v_mean+6*my_v_sig);

    for(std::vector<Particle>::iterator p = particleList.begin(); p != particleList.end(); p++) {
        //std::cout << "\nm=" << p->m() << std::endl; //debugging purpose
        hm.Fill(p->m());
        hx1.Fill(p->x().x());
        hx2.Fill(p->x().y());
        hx3.Fill(p->x().z());
        hv1.Fill(p->v().x());
        hv2.Fill(p->v().y());
        hv3.Fill(p->v().z());
    }

    //canvas adjustements
    TCanvas canv("canv", "canvas for plotting", 1280, 1024); //canvas for the plots
    canv.SetRightMargin(0.09); //to avoid text cropping
    canv.SetLeftMargin(0.15);
    canv.SetBottomMargin(0.15);

    //plot of the invariant mass (True Value)
    hm.GetXaxis()->SetTitle("mass distribution [Kg]");
    hm.GetYaxis()->SetTitle("Occurences");
    hm.SetLineColor(kBlue);
    hm.Draw(); //plot the histogram
    hm.Fit("gaus"); //overlay the fit
    canv.SaveAs("./mass.pdf");//plot of the invariant mass (True Value)

    hx1.GetXaxis()->SetTitle("x distribution [m]");
    hx1.GetYaxis()->SetTitle("Occurences");
    hx1.SetLineColor(kBlue);
    hx1.Draw(); //plot the histogram
    hx1.Fit("gaus"); //overlay the fit
    canv.SaveAs("./x.pdf");

    hx2.GetXaxis()->SetTitle("y distribution [m]");
    hx2.GetYaxis()->SetTitle("Occurences");
    hx2.SetLineColor(kBlue);
    hx2.Draw(); //plot the histogram
    hx2.Fit("gaus"); //overlay the fit
    canv.SaveAs("./y.pdf");

    hx3.GetXaxis()->SetTitle("z distribution [m]");
    hx3.GetYaxis()->SetTitle("Occurences");
    hx3.SetLineColor(kBlue);
    hx3.Draw(); //plot the histogram
    hx3.Fit("gaus"); //overlay the fit
    canv.SaveAs("./z.pdf");

    hv1.GetXaxis()->SetTitle("vx distribution [m/s]");
    hv1.GetYaxis()->SetTitle("Occurences");
    hv1.SetLineColor(kBlue);
    hv1.Draw(); //plot the histogram
    hv1.Fit("gaus"); //overlay the fit
    canv.SaveAs("./vx.pdf");

    hv2.GetXaxis()->SetTitle("vy distribution [m/s]");
    hv2.GetYaxis()->SetTitle("Occurences");
    hv2.SetLineColor(kBlue);
    hv2.Draw(); //plot the histogram
    hv2.Fit("gaus"); //overlay the fit
    canv.SaveAs("./vy.pdf");
    
    hv3.GetXaxis()->SetTitle("vz distribution [m/s]");
    hv3.GetYaxis()->SetTitle("Occurences");
    hv3.SetLineColor(kBlue);
    hv3.Draw(); //plot the histogram
    hv3.Fit("gaus"); //overlay the fit
    canv.SaveAs("./vz.pdf");



    //Now comes the TTree storage part

    TString rootfname("./ensemble_data.root");
    TFile* orootfile = new TFile( rootfname, "RECREATE");
    if( !orootfile->IsOpen() ) {
        std::cout << "problems creating root file. exiting... " << std::endl;
        exit(-1);
    }
    std::cout << "Ttree storing iniziated... " << rootfname << std::endl;

    TTree* tree = new TTree("EnsembleDataTree", "tree containing data relative to the decay B to Pi K");
    //TVector3 CoM = myEns.CoM();
    int N = myEns.N();
    double T = myEns.T();
    double m,x,y,z,vx,vy,vz;
    tree->Branch("N", &N,  "N/I");
    tree->Branch("T", &T, "T/D");
    tree->Branch("m", &m, "m/D");
    tree->Branch("x", &x, "x/D");
    tree->Branch("y", &y, "y/D");
    tree->Branch("z", &z, "z/D");
    tree->Branch("vx", &vx, "vx/D");
    tree->Branch("vy", &vy, "vy/D");
    tree->Branch("vz", &vz, "vz/D");


    for(vector<Particle>::const_iterator it = particleList.begin(); it != particleList.end(); ++it) {
        //since N and T are always the same I do not change them
        m = it->m();
        x = it->x().x();
        y = it->x().y();
        z = it->x().z();
        vx = it->v().x();
        vy = it->v().y();
        vz = it->v().z();
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