#include "experiment.h"
#include <iostream>
#include <fstream>
using namespace std;

experiment::experiment(string name):  exp_name(name){}

experiment::~experiment(){
      //bisogna svuotare tutte le mappe
      descr.clear();
      h1map.clear();
      h2map.clear();
      graphmap.clear();
      graph_errormap.clear();
      ntuples_map.clear();
      objects.clear();
}

experiment::experiment(const experiment& e){
      exp_name = e.exp_name;
      descr= e.descr;
      objects = e.objects;
      h1map = e.h1map;
      h2map = e.h2map;
      graphmap = e.graphmap;
      graph_errormap = e.graph_errormap;
      ntuples_map= e.ntuples_map;
}

experiment& experiment::operator= (const experiment& e){
      exp_name = e.exp_name;
      descr= e.descr;
      objects = e.objects;
      h1map = e.h1map;
      h2map = e.h2map;
      graphmap = e.graphmap;
      graph_errormap = e.graph_errormap;
      ntuples_map= e.ntuples_map;
}

//metodi per creare nuovi dati
TH1F* experiment::newH1(string id, int nbins, double min, double max){
      TH1F* h = new TH1F(id.c_str(),id.c_str(),nbins,min,max);
      objects[id] = h;
      h1map[id]=h;
      return h;
}


TH2F* experiment::newH2(string id, int nxbins, double minx, double maxx,
                              int nybins, double miny, double maxy){
      TH2F* h = new TH2F(id.c_str(),id.c_str(),nxbins,minx,maxx,nybins,miny,maxy);
      objects[id]=h;
      h2map[id]=h;
      return h;
}


TGraph* experiment::newGraph(string id,int n, double* x, double* y){
      TGraph* g = new TGraph(n,x,y);
      g->SetTitle(id.c_str());
      g->SetName(id.c_str());
      objects[id]= g;
      graphmap[id]=g;
      return g;
}

TGraph* experiment::newGraph(string id, const char* file ){
      TGraph* g = new TGraph(file);
      g->SetTitle(id.c_str());
      g->SetName(id.c_str());
      objects[id]= g;
      graphmap[id]=g;
      return g;
}

TGraphErrors* experiment::newGraphErrors(string id, int n, double* x, double* y,
            double* ex,double* ey){
      TGraphErrors* g = new TGraphErrors(n,x,y,ex,ey);
      g->SetTitle(id.c_str());
      g->SetName(id.c_str());
      objects[id]= g;
      graph_errormap[id]=g;
      return g;
}

TGraphErrors* experiment::newGraphErrors(string id, const char* file ){
      TGraphErrors* g = new TGraphErrors(file);
      g->SetTitle(id.c_str());
      g->SetName(id.c_str());
      objects[id]= g;
      graph_errormap[id]=g;
      return g;
}

//usiamo ntuple da 1 a 3 variabili
TNtuple* experiment::newNtuple(string id, int var){
      TNtuple* n;
      switch(var){
            case 1:
                  n = new TNtuple(id.c_str(),id.c_str(),"x1");
                  break;
            case 2:
                  n = new TNtuple(id.c_str(),id.c_str(),"x1:x2");
                  break;
            case 3:
                  n = new TNtuple(id.c_str(),id.c_str(),"x1:x2:x3");
                  break;
      }
      objects[id]= n;
      ntuples_map[id]=n;
      return n;
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

void  experiment::addGraphErrors(string id, TGraphErrors* g){
      objects[id]=g;
      graph_errormap[id]=g;
}

void experiment::addNtuple(string id, TNtuple* nt){
      objects[id]= nt;
      ntuples_map[id]=nt;
}

void  experiment::addDescription(string id, string desc){
      descr[id]=desc;
}

//metodi di ricerca.
TObject* experiment::get(string id){
      map<string,TObject*>::iterator it = objects.find(id);
      if(it != objects.end()){
            return it->second;
      }else{
            return NULL;
      }
}

TH1F* experiment::getH1(string id){
      map<string,TH1F*>::iterator it = h1map.find(id);
      if(it != h1map.end()){
            return it->second;
      }else{
            return NULL;
      }
}

TH2F* experiment::getH2(string id){
      map<string,TH2F*>::iterator it = h2map.find(id);
      if(it != h2map.end()){
            return it->second;
      }else{
            return NULL;
      }
}

TGraph* experiment::getGraph(string id){
      map<string,TGraph*>::iterator it = graphmap.find(id);
      if(it != graphmap.end()){
            return it->second;
      }else{
            return NULL;
      }
}

TGraphErrors* experiment::getGraphErrors(string id){
      map<string,TGraphErrors*>::iterator it = graph_errormap.find(id);
      if(it != graph_errormap.end()){
            return it->second;
      }else{
            return NULL;
      }
}

TNtuple* experiment::getNtuple(string id){
      map<string,TNtuple*>::iterator it = ntuples_map.find(id);
      if(it != ntuples_map.end()){
            return it->second;
      }else{
            return NULL;
      }
}

//metodi informativi
void experiment::listObjects(){
      cout << "TH1F:\n ";
      map<string,TH1F* >::iterator it = h1map.begin();
      while(it != h1map.end()){
            cout <<"\t"<< it->first << " : " <<descr[it->first]<<endl;
            it++;
      }
      cout << "TH2F:\n ";
      map<string,TH2F* >::iterator it2 = h2map.begin();
      while(it2 != h2map.end()){
            cout << it2->first << " : " <<descr[it2->first]<<endl;
            it2++;
      }
      cout << "TGraph:\n ";
      map<string,TGraph* >::iterator it3 = graphmap.begin();
      while(it3 != graphmap.end()){
            cout << it3->first << " : "<< descr[it3->first]<<endl;
            it3++;
      }
      cout << "TGraphErrors:\n ";
      map<string,TGraphErrors* >::iterator it4 = graph_errormap.begin();
      while(it4 != graph_errormap.end()){
            cout << it4->first << " : " <<descr[it4->first]<<endl;
            it4++;
      }
}

string experiment::getObjectDescription(string id){
      cout << id <<"  -   "<< descr[id];
      return descr[id];
}

//salvataggio dati
void experiment::saveData(){
      TFile* file = new TFile( exp_name.c_str(), "UPDATE");
      map<string, TObject*>::iterator it = objects.begin();
      while(it != objects.end()){
            it->second->Write();
            it++;
      }

      //ora si salvano i nomi su un file di informazioni
      ofstream out (exp_name+".info",ios::out);
      //per ogni tipo di file inseriamo nome e descrizione
      out<< "#TH1F"<<endl;
      map<string,TH1F*>::iterator ith1 = h1map.begin();
      while(ith1 != h1map.end()){
            out << ith1->first << "   " << descr[ith1->first]<<endl;
            ith1++;
      }
      out<< "#TH2F"<<endl;
      map<string,TH2F*>::iterator ith2 = h2map.begin();
      while(ith2 != h2map.end()){
            out << ith2->first << "   " << descr[ith2->first]<<endl;
            ith2++;
      }
      out<< "#TGraph"<<endl;
      map<string,TGraph*>::iterator itg = graphmap.begin();
      while(itg != graphmap.end()){
            out << itg->first << "   " << descr[itg->first]<<endl;
            itg++;
      }
      out<< "#TGraphErrors"<<endl;
      map<string,TGraphErrors*>::iterator itge = graph_errormap.begin();
      while(itge != graph_errormap.end()){
            out << itge->first << "   " << descr[itge->first]<<endl;
            itge++;
      }
      out<< "#TNtuple"<<endl;
      map<string,TNtuple*>::iterator itn = ntuples_map.begin();
      while(itn != ntuples_map.end()){
            out << itn->first << "   " << descr[itn->first]<<endl;
            itn++;
      }
      out.close();
}
