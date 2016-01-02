#ifndef  experiment_h
#define experiment_h

#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TNtuple.h"
#include "TObject.h"
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TObject.h"
#include <map>
#include <string>

using namespace std;

/**
*     Classe che rappresenta i dati di un singolo esperimento.
*     E' un container di oggetti Root facilmente leggibili e salvabili.
*
**/
class experiment{

public:
      //costruttori e distruttori
      experiment(string name);
      ~experiment();
      experiment(const experiment& e);
      experiment& operator=(const experiment& e);

      //creazione oggetti
      TH1F* newH1(string id, string title,int nbins, double min, double max);
      TH2F* newH2(string id,string title, int nxbins, double minx, double maxx,
                                    int nybins, double miny, double maxy);
      TGraph* newGraph(string id,string title,int n, double* x, double* y);
      TGraph* newGraph(string id,string title,const char* file );
      TGraphErrors* newGraphErrors(string id,string title, int n, double* x, double* y,
                                    double* ex,double* ey);
      TGraphErrors* newGraphErrors(string id,string title,const char* file );
      TNtuple* newNtuple(string id, int nvar );
      TCanvas* newCanvas(string id,string title);

      //aggiunta oggetti
      void addH1( TH1F* h);
      void addH2( TH2F* h);
      void addGraph(string id, TGraph* g);
      void addGraphErrors(string id,TGraphErrors* g);
      void addMultiGraph(string id, TMultiGraph* m);
      void addNtuple(TNtuple* nt);
      void addCanvas( TCanvas* c);
      void addTF1(TF1* f);
      void addObjDescr(string id, string desc);

      //metodo get generico
      TObject* get(string id);
      //metodi get non generici
      TH1F* getH1(string id);
      TH2F* getH2(string id);
      TGraph* getGraph(string id);
      TGraphErrors* getGraphErrors(string id);
      TMultiGraph* getMultiGraph(string id);
      TNtuple* getNtuple(string id);
      TCanvas* getCanvas(string id);
      TF1* getTF1(string id);

      //metodi informativi
      void listObjects();
      string getObjDescr(string id);

      //salvataggio e caricamento
      void saveData();
      void close();
      static experiment*  loadExperiment(string name);

      //METODI HELPER
      //metodo helper per la lettura delle ntuple
      static void loadNtuple(TNtuple* nt,string path, int arg);
      static void loadNtuple(TNtuple* nt,string path, int arg,int salto);
      static void loadNtuple(TNtuple* nt,string path, int arg,int salto, int after);
      //metodo helper che crea array di double con il valore scelto
      static double* arrayN(double x, int n);
      //metodi per spostare le statistiche
      static TPaveStats* moveDownStats(TCanvas* c, TObject* t);
      static TPaveStats* moveLeftStats(TCanvas* c, TObject* t);
      static TPaveStats* moveStats(TCanvas* c, TObject* t,float x1,float y1);

private:
      //nome dell'esperimento
      string exp_name;
      //mappe di dati
      std::map<string,string> descr;
      //mappa di tutti gli oggetti
      std::map<string, TObject*> objects;
      std::map<string,TH1F*> h1map;
      std::map<string, TH2F*> h2map;
      std::map<string,TGraph*> graphmap;
      std::map<string,TGraphErrors*> graph_errormap;
      std::map<string,TMultiGraph*>mgraph_map;
      std::map<string,TCanvas*> canvas_map;
      std::map<string,TF1*> tf1_map;
      //usiamo ntuple da 1 a 3 variabili
      std::map<string,TNtuple*> ntuples_map;
      //TFile
      TFile * file;
      bool file_open;
};


#endif
