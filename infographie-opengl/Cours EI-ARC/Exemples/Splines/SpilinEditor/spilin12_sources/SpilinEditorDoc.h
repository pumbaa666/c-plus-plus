// SpilinEditorDoc.h : interface of the CSpilinEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPILINEDITORDOC_H__6976DBCC_A493_11D1_80B1_977233DC2865__INCLUDED_)
#define AFX_SPILINEDITORDOC_H__6976DBCC_A493_11D1_80B1_977233DC2865__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSpilinEditorView;
class CGLView;
class CSettingSheet;

struct nodo{
		CPoint pun;
		BOOL selected;
		nodo *succ;
		nodo *prec;
};

class CSpilinEditorDoc : public CDocument, public CUndo
{
private:
	void Clamping(CPoint &punto);
	float pviewHeight;
	BOOL Dist(CPoint p1,CPoint p2,CPoint p3,float soglia);
	void canclista();
	int numnodi;
	BOOL chiusa;
	nodo *listaultimo;
	nodo *corr;
	nodo *listaprimo;

protected: // create from serialization only
	CSpilinEditorDoc();
	DECLARE_DYNCREATE(CSpilinEditorDoc)

// Attributes
public:
	CSpilinEditorView* pEditView;
	CGLView* pGLView;
	enum primitiva {LATHE,PRISM,SOR};
	void GeometryUpdate(BOOL &culling);
	void SpostaTuttiNodi(char dir,int gridsize);
	void CheckPovPrimitive(BOOL &sorwarn, BOOL &selfintersect,float &max,int &ymax);
	BOOL inscorrel(CPoint punto);
	BOOL pviewnormflip;
	int sezsolido;
	char genRevolution();
	char genExtrusion();
	CPoint NextPunto();
	int numsteps;
	int Rdisplist;
	int Edisplist;

// inline functions
public:
	BOOL echiusa() {return chiusa;};
	int nnodi() {return numnodi;};
	nodo* nprimo() {return listaprimo;};
	nodo* nultimo() {return listaultimo;};
	nodo* ncorr() {return corr;};

// Operations
public:
	void aggnodo(CPoint p);		// aggiunge un nodo in fondo alla lista
	void inserisci(CPoint p);		// inserisce un nodo alla posiz di corrente
	void chiudi();				// rende chiusa la spline
	void sostnodo(CPoint punto);
	BOOLEAN pickcorrel(CPoint punto);
	void POVoutput(CString nomefile);
	void VRMLoutput(CString nomefile,CString nomogg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpilinEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual void OnCloseDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SaveSettings();
	void RetrieveSettings();
	BOOL IsCurrentSelected() {return corr!=NULL?corr->selected:FALSE;};
	void UpdateGLView();
	void UpdateEditView();
	CPoint CenterOfSelectedPoints();
	void CancSelNodes();
	void FixSelDocVect();
	int Esidedisplist;
	BOOL exportConic;
	BOOL exportOpen;
	BOOL exportSturm;
	CString exportObjName;
	BOOL proportional;
	int cmapfactor;
	primitiva exportObjType;
	float exportHeight;
	void SelectAllPoint();
	void SelectNoPoint();
	void SelectNextPoint();
	void SpostaSelectNodi(char dir,int gridsize);
	void SelectCurrent(BOOL add=FALSE);
	void SelectSingle(nodo* punt);
	int SelectInRect(CRect rett);
	void PovToClipboard(primitiva prim);
	int numstepspreview;
	virtual ~CSpilinEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int CallSettingSheet(CSettingSheet &propSheet);

// Generated message map functions
protected:
	//{{AFX_MSG(CSpilinEditorDoc)
	afx_msg void OnUpdateSteps(CCmdUI *pCmdUI);  //steps indicator on statusbar
	afx_msg void OnUpdateNodi(CCmdUI *pCmdUI);  //nodes indicator on statusbar
	afx_msg void OnUpdatePolygons(CCmdUI *pCmdUI);  //Polygons indicator on statusbar
	afx_msg void OnFileEsportainpov();
	afx_msg void OnFileEsportainvrml20();
	afx_msg void OnFlipN();
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnSnap();
	afx_msg void OnRevolution();
	afx_msg void OnEstrusion();
	afx_msg void OnSmoothShade();
	afx_msg void OnUpdateEstrusion(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRevolution(CCmdUI* pCmdUI);
	afx_msg void OnStatoCrea();
	afx_msg void OnStatoInser();
	afx_msg void OnStatoModifica();
	afx_msg void OnStatoSelect();
	afx_msg void OnSettings();
	afx_msg void OnViewGridplane();
	afx_msg void OnUpdateViewGridplane(CCmdUI* pCmdUI);
	afx_msg void OnStatoRuota();
	afx_msg void OnUpdateStatoRuota(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStatoCrea(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStatoInser(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStatoModifica(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStatoSelect(CCmdUI* pCmdUI);
	afx_msg void OnStatoScala();
	afx_msg void OnUpdateStatoScala(CCmdUI* pCmdUI);
	afx_msg void OnModificaChiudispline();
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditSelectNone();
	afx_msg void OnUpdateStatoMirrorX(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStatoMirrorY(CCmdUI* pCmdUI);
	afx_msg void OnUpdateModificaChiudispline(CCmdUI* pCmdUI);
	afx_msg void OnStatoMirrorX();
	afx_msg void OnStatoMirrorY();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPILINEDITORDOC_H__6976DBCC_A493_11D1_80B1_977233DC2865__INCLUDED_)
