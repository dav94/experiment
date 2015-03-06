#include "experiment.h"

using namespace std;

experiment::experiment(string name):  exp_name(name){}

experiment::~experiment(){
      //bisogna svuotare tutte le mappe
      descr.clear();
      h1map.clear();
      h2map.clear();
      graphmap.clear();
      grap_errormap.clear();
      ntuples.clear();
      objects.clear();
}

experiment::experiment(const experiment& e){
      exp_name = e.exp_name;
      descr= e.descr;
      object = e.objects;
      h1map = e.h1map;
      h2map = e.h2map;
      graphmap = e.graphmap;
      grap_errormap = e.grap_errormap;
      ntuples= e.ntuples;
}

experiment& experiment::operator= (const experiment&){
      exp_name = e.exp_name;
      descr= e.descr;
      object = e.objects;
      h1map = e.h1map;
      h2map = e.h2map;
      graphmap = e.graphmap;
      grap_errormap = e.grap_errormap;
      ntuples= e.ntuples;
}

TH1F* experiment::newH1(string id, int nbins, double min, double max){
      TH1F* h = new TH1F(id,id,nbins,min,max);
      objecs[id] = h;
      h1map[id]=h;
      return h;
}


TH2F* experiment::newH2(string id, int nxbins, double minx, double maxx,
                              int nybins, double miny, double maxy){
      TH2F* h = new TH2F(id,nxbins,minx,maxx,nybins,miny,maxy);
      objects[id]=h;
      h2map[id]=h;
      return h;
}


TGraph* experiment::newGraph(string id,int n, double* x, double* y){
      TGraph* g = new TGraph(n,x,y);
      g->SetTitle(id);
      objects[id]= g;
      graphmap[id]=g;
      return g;
}

TGraph* experiment::newGraph(string id, const char* file ){
      TGraph* g = new TGraph(file);
      g->SetTitle(id);
      objects[id]= g;
      graphmap[id]=g;
      return g;
}

TGraphErrors* experiment::newGraphErrors(string id, int n, double* x, double* y,
            double* ex,double* ey){
      TGraphErrors* g = new TGraphErrors(n,x,y,ex,ey);
      g->SetTitle(id);
      objects[id]= g;
      graph_errormap[id]=g;
      return g;
}

TGraphErrors* experiment::newGraphErrors(string id, const char* file ){
      TGraphErrors* g = new TGraphErrors(file);
      g->SetTitle(id);
      objects[id]= g;
      graph_errormap[id]=g;
      return g;
}

TObject* experiment::get(string id){
      return objects.find(id)->second;
}
