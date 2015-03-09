#ifndef  experiment_h
#define experiment_h

#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TNtuple.h"
#include "TObject.h"
#include "TFile.h"
#include "TCanvas.h"
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
      TH1F* newH1(string id, int nbins, double min, double max);
      TH2F* newH2(string id, int nxbins, double minx, double maxx,
                                    int nybins, double miny, double maxy);
      TGraph* newGraph(string id,int n, double* x, double* y);
      TGraph* newGraph(string id,const char* file );
      TGraphErrors* newGraphErrors(string id, int n, double* x, double* y,double* ex,double* ey);
      TGraphErrors* newGraphErrors(string id,const char* file );
      TNtuple* newNtuple(string id, int nvar );
      TCanvas* newCanvas(string id,string title);

      //aggiunta oggetti
      void addH1(string id, TH1F* h);
      void addH2(string id, TH2F* h);
      void addGraph(string id, TGraph* g);
      void addGraphErrors(string id, TGraphErrors* g);
      void addNtuple(string id, TNtuple* nt);
      void addCanvas(string id, TCanvas* c);
      void addDescription(string id, string desc);

      //metodo get generico
      TObject* get(string id);
      //metodi get non generici
      TH1F* getH1(string id);
      TH2F* getH2(string id);
      TGraph* getGraph(string id);
      TGraphErrors* getGraphErrors(string id);
      TNtuple* getNtuple(string id);
      TCanvas* getCanvas(string id);

      //metodi informativi
      void listObjects();
      string getObjectDescription(string id);

      //salvataggio e caricamento
      void saveData();
      static experiment*  loadExperiment(string name);

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
      std::map<string,TCanvas*> canvas_map;
      //usiamo ntuple da 1 a 3 variabili
      std::map<string,TNtuple*> ntuples_map;
};


#endif
