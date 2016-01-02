#include "experiment.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

experiment::experiment(string name):  exp_name(name),file_open(false){}

experiment::~experiment(){
      //chiusura del TFile
      file->Close();
      //bisogna svuotare tutte le mappe
      descr.clear();
      h1map.clear();
      h2map.clear();
      graphmap.clear();
      graph_errormap.clear();
      ntuples_map.clear();
      canvas_map.clear();
      objects.clear();
      tf1_map.clear();
      mgraph_map.clear();
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
      tf1_map = e.tf1_map;
      mgraph_map= e.mgraph_map;
      file = e.file;
      file_open= e.file_open;
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
      tf1_map = e.tf1_map;
      mgraph_map= e.mgraph_map;
      file = e.file;
      file_open = e.file_open;
      return *this;
}

void experiment::close(){
      file_open= false;
      file->Close();
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
            default:
                  n = new TNtuple(id.c_str(),id.c_str(),"x1");
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

void  experiment::addGraph(string id, TGraph* g){
      objects[id]= g;
      graphmap[id]=g;
}

void  experiment::addGraphErrors(string id, TGraphErrors* g){
      objects[id]=g;
      graph_errormap[id]=g;
}

void experiment::addMultiGraph(string id, TMultiGraph* m){
      objects[id]=m;
      mgraph_map[id]= m;
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

void experiment::addTF1(TF1* f){
      string id = f->GetName();
      objects[id]=f;
      tf1_map[id]=f;
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

TMultiGraph* experiment::getMultiGraph(string id){
       map<string,TMultiGraph*>::iterator it = mgraph_map.find(id);
      if(it != mgraph_map.end()){
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

TF1* experiment::getTF1(string id){
       map<string,TF1*>::iterator it = tf1_map.find(id);
      if(it!= tf1_map.end()){
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
        cout << "TMultiGraph:\n ";
      map<string,TMultiGraph* >::iterator it8 = mgraph_map.begin();
      while(it8 != mgraph_map.end()){
            cout <<"\t"<< it8->first << " : " <<descr[it8->first]<<endl;
            it8++;
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
      cout << "TF1:\n";
      map<string,TF1* >::iterator it7 = tf1_map.begin();
      while(it7 != tf1_map.end()){
            cout <<"\t"<< it7->first << " : " <<descr[it7->first]<<endl;
            it7++;
      }
}

string experiment::getObjDescr(string id){
      cout << id <<"  -   "<< descr[id]<<endl;
      return descr[id];
}

//salvataggio dati
void experiment::saveData(){
      if(!file_open){
           this->file = new TFile( (exp_name+".root").c_str(), "RECREATE");
           file_open= true;
     }
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
       map<string,TMultiGraph*>::iterator itm = mgraph_map.begin();
      while(itm != mgraph_map.end()){
            out <<"TMultiGraph   "<< itm->first << "   " << descr[itm->first]<<endl;
            itm++;
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
      map<string,TF1*>::iterator itf = tf1_map.begin();
      while(itf != tf1_map.end()){
            out <<"TF1   "<<itf->first << "   " << descr[itf->first]<<endl;
            itf++;
      }
      out.close();
}

//caricamento esperimento
experiment* experiment::loadExperiment(string name){
      experiment* e = new experiment(name);
      //prima di tutto si legge il file di info
      ifstream in (name+".info", ios::in);
      TFile* file = new TFile((name+".root").c_str(), "UPDATE" );
      e->file_open = true;
      e->file = file;
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
                        TGraphErrors* ge = (TGraphErrors*) file->GetObjectChecked(
                         id.c_str(),"TGraphErrors");
                        e->graph_errormap[id]=ge;
                        e->objects[id]=ge;
                   }else if(f=="TGraphErrors"){
                        TMultiGraph* m = (TMultiGraph*) file->GetObjectChecked(
                         id.c_str(),"TMultiGraph");
                        e->mgraph_map[id]=m;
                        e->objects[id]=m;
                  }else if(f=="TNtuple"){
                        TNtuple* n = (TNtuple*)file->GetObjectChecked(id.c_str(),"TNtuple");
                        e->ntuples_map[id]=n;
                        e->objects[id]= n;
                  }else if(f=="TCanvas"){
                        TCanvas* c = (TCanvas*)file->GetObjectChecked(id.c_str(),"TCanvas");
                        e->canvas_map[id]=c;
                        e->objects[id]= c;
                  }else if(f=="TF1"){
                        TF1* c = (TF1*)file->GetObjectChecked(id.c_str(),"TF1");
                        e->tf1_map[id]=c;
                        e->objects[id]= c;
                  }
            }
            return e;
      }
      return NULL; //errore lettura
}

void experiment::loadNtuple(TNtuple* nt,string path, int arg){
      ifstream f ;
      f.open(path);
      stringstream ss;
      string line;
      //si salta la prima riga che contiene le info sulle colonne
      getline(f,line);
      while(getline(f,line)){
            ss<< line;
            if(line[0]=='#'){
                  //si saltano le righe commentate
                  ss.clear();
                  continue;
            }
            float d[arg];
            for(int i = 0; i< arg;i++){
                  float a;
                  ss>>a;
                  d[i]=a;
            }
            ss.clear();
            //si inserisce la riga nell'ntupla
            nt->Fill(&d[0]);
      }
      f.close();
}

void experiment::loadNtuple(TNtuple* nt,string path, int arg,int salto){
      ifstream f ;
      f.open(path);
      stringstream ss;
      string line;
      //si salta la prima riga che contiene le info sulle colonne
      getline(f,line);
      int i = 0;
      while(getline(f,line)){
            if((i % salto) != 0){
                  i++;
                  continue;
            }
            i++;
            ss<< line;
            if(line[0]=='#'){
                  //si saltano le righe commentate
                  ss.clear();
                  continue;
            }
            float d[arg];
            for(int i = 0; i< arg;i++){
                  float a;
                  ss>>a;
                  d[i]=a;
            }
            ss.clear();
            //si inserisce la riga nell'ntupla
            nt->Fill(&d[0]);
      }
      f.close();
}

void experiment::loadNtuple(TNtuple* nt,string path, int arg,int salto,int after){
      ifstream f ;
      f.open(path);
      stringstream ss;
      string line;
      //si salta la prima riga che contiene le info sulle colonne
      getline(f,line);
      int i = 0;
      int s = 0;
      while(getline(f,line)){
            if(s>after){
                  if((i % salto) != 0){
                        i++;
                        continue;
                  }
                  i++;
            }
            s++;
            ss<< line;
            if(line[0]=='#'){
                  //si saltano le righe commentate
                  ss.clear();
                  continue;
            }
            float d[arg];
            for(int i = 0; i< arg;i++){
                  float a;
                  ss>>a;
                  d[i]=a;
            }
            ss.clear();
            //si inserisce la riga nell'ntupla
            nt->Fill(&d[0]);
      }
      f.close();
}

double* experiment::arrayN(double x, int n){
      double* d = new double[n];
      for (int i = 0; i < n; ++i)
      {
            d[i]=x;
      }
      return d;
}

TPaveStats* experiment::moveDownStats(TCanvas* c, TObject* t){
      c->Update();
      TPaveStats* stat1 = (TPaveStats*) t->FindObject("stats");
      float height=  stat1->GetY2NDC() - stat1->GetY1NDC();
      stat1->SetY1NDC(0.2);
      stat1->SetY2NDC(0.2+ height);
      stat1->Draw();
      return stat1;
}

TPaveStats* experiment::moveLeftStats(TCanvas* c, TObject* t){
      c->Update();
      TPaveStats* stat1 = (TPaveStats*) t->FindObject("stats");
      float width=  stat1->GetX2NDC() - stat1->GetX1NDC();
      stat1->SetX1NDC(0.15);
      stat1->SetX2NDC(0.15+ width);
      stat1->Draw();
      return stat1;
}

TPaveStats* experiment::moveStats(TCanvas* c , TObject* t,float x1,float y1){
      c->Update();
      TPaveStats* stat1 = (TPaveStats*) t->FindObject("stats");
      float width=  stat1->GetX2NDC() - stat1->GetX1NDC();
      stat1->SetX1NDC(x1);
      stat1->SetX2NDC(x1+ width);
      float height=  stat1->GetY2NDC() - stat1->GetY1NDC();
      stat1->SetY1NDC(y1);
      stat1->SetY2NDC(y1+ height);
      stat1->Draw();
      return stat1;
}