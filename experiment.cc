#include "experiment.h"
#include <iostream>
#include <fstream>
#include <sstream>
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
      canvas_map.clear();
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
      canvas_map= e.canvas_map;
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
      canvas_map= e.canvas_map;
}

//metodi per creare nuovi dati
TH1F* experiment::newH1(string id, string title,int nbins, double min, double max){
      TH1F* h = new TH1F(id.c_str(),title.c_str(),nbins,min,max);
      objects[id] = h;
      h1map[id]=h;
      return h;
}


TH2F* experiment::newH2(string id, string title,int nxbins, double minx, double maxx,
                              int nybins, double miny, double maxy){
      TH2F* h = new TH2F(id.c_str(),title.c_str(),nxbins,minx,maxx,nybins,miny,maxy);
      objects[id]=h;
      h2map[id]=h;
      return h;
}


TGraph* experiment::newGraph(string id, string title,int n, double* x, double* y){
      TGraph* g = new TGraph(n,x,y);
      g->SetTitle(title.c_str());
      g->SetName(id.c_str());
      objects[id]= g;
      graphmap[id]=g;
      return g;
}

TGraph* experiment::newGraph(string id, string title, const char* file ){
      TGraph* g = new TGraph(file);
      g->SetTitle(title.c_str());
      g->SetName(id.c_str());
      objects[id]= g;
      graphmap[id]=g;
      return g;
}

TGraphErrors* experiment::newGraphErrors(string id, string title,int n, double* x, double* y,
            double* ex,double* ey){
      TGraphErrors* g = new TGraphErrors(n,x,y,ex,ey);
      g->SetTitle(title.c_str());
      g->SetName(id.c_str());
      objects[id]= g;
      graph_errormap[id]=g;
      return g;
}

TGraphErrors* experiment::newGraphErrors(string id, string title,const char* file ){
      TGraphErrors* g = new TGraphErrors(file);
      g->SetTitle(title.c_str());
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

TCanvas* experiment::newCanvas(string id, string title){
      TCanvas* c = new TCanvas(id.c_str(),title.c_str());
      canvas_map[id]=c;
      objects[id]=c;
      return c;
}

//metodi per aggiungere dati
void  experiment::addH1( TH1F* h){
      string id = h->GetName();
      objects[id]= h;
      h1map[id]=h;
}

void  experiment::addH2(TH2F* h){
      string id = h->GetName();
      objects[id]= h;
      h2map[id]=h;
}

void  experiment::addGraph(TGraph* g){
      string id = g->GetName();
      objects[id]= g;
      graphmap[id]=g;
}

void  experiment::addGraphErrors( TGraphErrors* g){
      string id = g->GetName();
      objects[id]=g;
      graph_errormap[id]=g;
}

void experiment::addNtuple( TNtuple* nt){
      string id = nt->GetName();
      objects[id]= nt;
      ntuples_map[id]=nt;
}

void experiment::addCanvas( TCanvas* c){
      string id = c->GetName();
      objects[id]= c;
      canvas_map[id]= c;
}

void  experiment::addObjDescr(string id, string desc){
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

TCanvas* experiment::getCanvas(string id){
      map<string,TCanvas*>::iterator it = canvas_map.find(id);
      if(it!= canvas_map.end()){
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
            cout<<"\t" << it2->first << " : " <<descr[it2->first]<<endl;
            it2++;
      }
      cout << "TGraph:\n ";
      map<string,TGraph* >::iterator it3 = graphmap.begin();
      while(it3 != graphmap.end()){
            cout <<"\t"<< it3->first << " : "<< descr[it3->first]<<endl;
            it3++;
      }
      cout << "TGraphErrors:\n ";
      map<string,TGraphErrors* >::iterator it4 = graph_errormap.begin();
      while(it4 != graph_errormap.end()){
            cout <<"\t"<< it4->first << " : " <<descr[it4->first]<<endl;
            it4++;
      }
      cout << "TNtuple:\n ";
      map<string,TNtuple* >::iterator it5 = ntuples_map.begin();
      while(it5 != ntuples_map.end()){
            cout <<"\t"<< it5->first << " : " <<descr[it5->first]<<endl;
            it5++;
      }
      cout << "TCanvas:\n ";
      map<string,TCanvas* >::iterator it6 = canvas_map.begin();
      while(it6 != canvas_map.end()){
            cout <<"\t"<< it6->first << " : " <<descr[it6->first]<<endl;
            it6++;
      }
}

string experiment::getObjDescr(string id){
      cout << id <<"  -   "<< descr[id]<<endl;
      return descr[id];
}

//salvataggio dati
void experiment::saveData(){
     TFile file ( (exp_name+".root").c_str(), "RECREATE");
      map<string, TObject*>::iterator it = objects.begin();
      while(it != objects.end()){
            it->second->Write();
            it++;
      }

      //ora si salvano i nomi su un file di informazioni
      ofstream out (exp_name+".info",ios::out);
      //per ogni tipo di file inseriamo nome e descrizione
      map<string,TH1F*>::iterator ith1 = h1map.begin();
      while(ith1 != h1map.end()){
            out << "TH1F   " << ith1->first << "   " << descr[ith1->first]<<endl;
            ith1++;
      }
      map<string,TH2F*>::iterator ith2 = h2map.begin();
      while(ith2 != h2map.end()){
            out <<"TH2F   "<< ith2->first << "   " << descr[ith2->first]<<endl;
            ith2++;
      }
      map<string,TGraph*>::iterator itg = graphmap.begin();
      while(itg != graphmap.end()){
            out << "TGraph   "<<itg->first << "   " << descr[itg->first]<<endl;
            itg++;
      }
      map<string,TGraphErrors*>::iterator itge = graph_errormap.begin();
      while(itge != graph_errormap.end()){
            out <<"TGraphErrors   "<< itge->first << "   " << descr[itge->first]<<endl;
            itge++;
      }
      map<string,TNtuple*>::iterator itn = ntuples_map.begin();
      while(itn != ntuples_map.end()){
            out <<"TNtuple   "<<itn->first << "   " << descr[itn->first]<<endl;
            itn++;
      }
      map<string,TCanvas*>::iterator itc = canvas_map.begin();
      while(itc != canvas_map.end()){
            out <<"TCanvas   "<<itc->first << "   " << descr[itc->first]<<endl;
            itc++;
      }
      out.close();
}

//caricamento esperimento
experiment* experiment::loadExperiment(string name){
      experiment* e = new experiment(name);
      //prima di tutto si legge il file di info
      ifstream in (name+".info", ios::in);
      TFile* file = new TFile((name+".root").c_str(), "READ" );
      stringstream ss;
      if(in.good()){
            string line;
            while(getline(in,line)){
                  ss<<line;
                  //si legge la prima parola
                  string f,id,desc;
                  ss>>f >> id>>desc;
                  ss.clear();
                  //aggiungo descrizione
                  e->descr[id]=desc;

                  if(f == "TH1F" ){
                        TH1F* h1 = (TH1F*) file->GetObjectChecked(id.c_str(),"TH1F");
                        e->h1map[id]=h1;
                        e->objects[id]=h1;
                  }else if(f == "TH2F"){
                        TH2F* h2 = (TH2F*) file->GetObjectChecked(id.c_str(),"TH2F");
                        e->h2map[id]=h2;
                        e->objects[id]=h2;
                  }else if (f == "TGraph"){
                        TGraph* g = (TGraph*) file->GetObjectChecked(id.c_str(),"TGraph");
                        e->graphmap[id]=g;
                        e->objects[id]=g;
                  }else if(f=="TGraphErrors"){
                        TGraphErrors* ge = (TGraphErrors*) file->GetObjectChecked(id.c_str(),"TGraphErrors");
                        e->graph_errormap[id]=ge;
                        e->objects[id]=ge;
                  }else if(f=="TNtuple"){
                        TNtuple* n = (TNtuple*)file->GetObjectChecked(id.c_str(),"TNtuple");
                        e->ntuples_map[id]=n;
                        e->objects[id]= n;
                  }else if(f=="TCanvas"){
                        TCanvas* c = (TCanvas*)file->GetObjectChecked(id.c_str(),"TCanvas");
                        e->canvas_map[id]=c;
                        e->objects[id]= c;
                  }
            }
            return e;
      }
      return NULL; //errore lettura
}
