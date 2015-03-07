#include "experiment.h"
#include <iostream>
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

//metodi per creare nuovi dati
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

//metodi per aggiungere dati
void  experiment::addH1(string id, TH1F* h){
      objects[id]= h;
      h1map[id]=h;
}

void  experiment::addH2(string id, TH2F* h){
      objects[id]= h;
      h2map[id]=h;
}

void  experiment::addGraph(string id, TGraph* g){
      objects[id]= g;
      graphmap[id]=g;
}

void  experiment::addErrorsGraph(string id, TGraphErrors* g){
      objects[id]=g;
      grap_errormap[id]=g;
}

void  experiment::addDescription(string id, string desc){
      descr[id]=desc;
}

//metodi di ricerca.
TObject* experiment::get(string id){
      map<string,TObject*>::iterator it = objects.find(id);
      if(it != map::end()){
            return it->second;
      }else{
            return NULL;
      }
}

TH1F* experiment::getH1(string id){
      map<string,TH1F*>::iterator it = h1map.find(id);
      if(it != map::end()){
            return it->second;
      }else{
            return NULL;
      }
}

TH2F* experiment::getH2(string id){
      map<string,TH2F*>::iterator it = h2map.find(id);
      if(it != map::end()){
            return it->second;
      }else{
            return NULL;
      }
}

TGraph* experiment::getGraph(string id){
      map<string,TGraph*>::iterator it = graphmap.find(id);
      if(it != map::end()){
            return it->second;
      }else{
            return NULL;
      }
}

TGraphErrors* experiment::get(string id){
      map<string,TGraphErrors*>::iterator it = grap_errormap.find(id);
      if(it != map::end()){
            return it->second;
      }else{
            return NULL;
      }
}

//metodi informativi
void experiment::listObjects(){
      cout << "TH1F:\n ";
      map<string,TH1F* >::iterator it = h1map.begin();
      while(it != map::end()){
            cout <<"\t"<< it->first << " : " descr[it->first]<<endl;
            it++;
      }
      cout << "TH2F:\n ";
      map<string,TH2F* >::iterator it2 = h2map.begin();
      while(it2 != map::end()){
            cout << it2->first << " : " descr[it2->first]<<endl;
            it2++;
      }
      cout << "TGraph:\n ";
      map<string,TGraph* >::iterator it3 = graphmap.begin();
      while(it3 != map::end()){
            cout << it3->first << " : " descr[it3->first]<<endl;
            it3++;
      }
      cout << "TGraphErrors:\n ";
      map<string,TGraphErrors* >::iterator it4 = graph_errormap.begin();
      while(it4 != map::end()){
            cout << it4->first << " : " descr[it4->first]<<endl;
            it4++;
      }
}
