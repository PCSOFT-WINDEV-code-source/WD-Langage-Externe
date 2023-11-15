/*-----------------------------------------------------------------------------------------------------------*/
/* Interface avec la dll HyperFile - PC SOFT 2002 - Ne pas modifier                                          */
/*-----------------------------------------------------------------------------------------------------------*/

#include <windows.h>
#include "WDHF.h"
#include "HFContext.h"
#include "WinDev.h"

CHFContext		gclHF;				// Gestion du contexte Hyper File

extern "C"{

BOOL bInitHF(void)
{
	IHFContext * pIHF;
	return (nWDGetHFContext((void**)&pIHF)==0) && gclHF.bInit(pIHF); 
}

BOOL bAssociate( PCXSTR pzTable, LPVOID pBuffer, size_t nSize )
{
	return gclHF.bAssociate(pzTable,pBuffer,nSize);
}
	
BOOL Hinit(pstHFFileCtx pTabCtx, short nMaxCtx)
{                              
	IHFContext * pIHF;
	if (nWDGetHFContext((void**)&pIHF)!=0) return FALSE;
	return Hinitpartage((long)pIHF, pTabCtx, nMaxCtx);
}

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hinitpartage( long pCtx, pstHFFileCtx pTabCtx, short nMaxCtx )
{
	if (!gclHF.bInit((IHFContext *)pCtx)) return FALSE;
	for (int i = 0; i < nMaxCtx; i++)
	{
		if (!gclHF.bAssociate(pTabCtx[i].pszNomFic,pTabCtx[i].pData,pTabCtx[i].nSize)) return FALSE;
	}
	return TRUE;
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hftermine(void)
{               
	WDFINHF
}


/*-----------------------------------------------------------------------------------------------------------*/
void Hfterminepartage(void)
{                    
	WDFINHF
}

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Houvreanalyse(LPCSTR pszNomWDD, LPCSTR pszMotDePasse, LPCSTR pszAdrServ, LPCSTR pszUser, LPCSTR pszPwd)
{   
	return ((pszAdrServ != NULL) || (pszUser != NULL) || (pszPwd != NULL)) ? gclHF.piGetHFContext()->bHOuvreAnalyseDistante(pszNomWDD, pszMotDePasse, pszAdrServ, pszUser, pszPwd) : gclHF.HOuvreAnalyse(pszNomWDD,pszMotDePasse);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hfermeanalyse(void)
{                                    
	gclHF.HFermeAnalyse();
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hajoute(LPCSTR pszNomFic)
{   
	gclHF.HAjoute(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hassigne(LPCSTR pszNomFic, LPCSTR pszNomRep)
{         
	gclHF.HChangeRep(pszNomFic,pszNomRep);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hcreation(LPCSTR pszNomFic)
{
	gclHF.HCreation(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hecrit (LPCSTR pszNomFic, DWORD dwNumEnr)
{
	gclHF.HEcrit(pszNomFic,dwNumEnr);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hferme(LPCSTR pszNomFic)
{                                    
	gclHF.HFerme(pszNomFic);
}                                   

/*-----------------------------------------------------------------------------------------------------------*/
void Hfermesanscommit(LPCSTR pszNomFic)
{   
	gclHF.HFerme(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hinfogene(LPCSTR pszNomFic)
{   
	gclHF.piGetHFContext()->bHInfoGene(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hinfogenevue(DWORD dwHdlVue)
{   
	gclHF.piGetHFContext()->bHInfoGene((LPCSTR)dwHdlVue);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlit(LPCSTR pszNomFic, DWORD dwNumEnreg)
{
	gclHF.HLit(pszNomFic,dwNumEnreg);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitvue(DWORD dwHdlVue, DWORD dwNumEnreg)
{
	gclHF.HLit((LPCSTR)dwHdlVue,dwNumEnreg);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitdernier(LPCSTR pszNomFic, LPCSTR pszNomCle)
{
	gclHF.HLitDernier(pszNomFic, pszNomCle);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitderniervue(DWORD dwHdlVue)
{
	gclHF.HLitDernier((LPCSTR)dwHdlVue);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hdernier(LPCSTR pszNomFic, LPCSTR pszNomCle)
{   
	gclHF.HDernier(pszNomFic, pszNomCle);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitprecedent(LPCSTR pszNomFic, LPCSTR pszNomCle)
{
	gclHF.HLitPrecedent(pszNomFic, pszNomCle);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitprecedentvue(DWORD dwHdlVue)
{
	gclHF.HLitPrecedent((LPCSTR)dwHdlVue);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hprecedent(LPCSTR pszNomFic, LPCSTR pszNomCle)
{                                             
	gclHF.HPrecedent(pszNomFic, pszNomCle);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitpremier(LPCSTR pszNomFic, LPCSTR pszNomCle)
{
	gclHF.HLitPremier(pszNomFic, pszNomCle);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitpremiervue(DWORD dwHdlVue)
{
	gclHF.HLitPremier((LPCSTR)dwHdlVue);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hpremier(LPCSTR pszNomFic, LPCSTR pszNomCle)
{   
	gclHF.HPremier(pszNomFic, pszNomCle);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherche(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech)
{   
	gclHF.HLitRecherchePremier(pszNomFic, pszNomCle, pszValRech,HDEFAULTSIZE,HGENERIC);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherchenum(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech, WORD wSize)
{   
	gclHF.HLitRecherchePremier(pszNomFic, pszNomCle, pszValRech, wSize);
}

/*-----------------------------------------------------------------------------------------------------------*/
/* Hlitrecherche pour clés textes ou numériques (façon WinDev 4.1) */
/* La taille utile de la clé est déterminée ici */
void HlitrechercheWD4( LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech )
{   
	gclHF.HLitRecherchePremier(pszNomFic, pszNomCle, pszValRech );
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherchevue(DWORD dwHdlVue, LPCSTR pszNomCle, LPCSTR pszValRech)
{   
	gclHF.HLitRecherchePremier((LPCSTR)dwHdlVue, pszNomCle, pszValRech,HDEFAULTSIZE,HGENERIC);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hrecherche(LPCSTR pszNomFic, LPCSTR pszNomCle, LPSTR pszValRech)
{   
	gclHF.HRecherchePremier(pszNomFic, pszNomCle, pszValRech,HDEFAULTSIZE,HGENERIC);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hrecherchenum(LPCSTR pszNomFic, LPCSTR pszNomCle, LPSTR pszValRech, WORD wSize)
{                                         
	gclHF.HRecherchePremier(pszNomFic, pszNomCle, pszValRech, wSize);
}

/*-----------------------------------------------------------------------------------------------------------*/
/* Hrecherche pour clés textes ou numériques (façon WinDev 4.1) */
/* La taille utile de la clé est déterminée ici */
void HrechercheWD4( LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech )
{   
	gclHF.HRecherchePremier(pszNomFic, pszNomCle, pszValRech );
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitsuivant(LPCSTR pszNomFic, LPCSTR pszNomCle)
{
	gclHF.HLitSuivant(pszNomFic, pszNomCle);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitsuivantvue(DWORD dwHdlVue)
{
	gclHF.HLitSuivant((LPCSTR)dwHdlVue);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hsuivant(LPCSTR pszNomFic, LPCSTR pszNomCle)
{                                             
	gclHF.HSuivant(pszNomFic, pszNomCle);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlibere(LPCSTR pszNomFic)
{   
	gclHF.HLibere(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hmodifie(LPCSTR pszNomFic)
{                   
	gclHF.HModifie(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hmodifievue(DWORD dwHdlVue)
{                   
	gclHF.HModifie((LPCSTR)dwHdlVue);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Houvre(LPCSTR pszNomFic)
{                   
	gclHF.HOuvre(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Houvresansbloquer(LPCSTR pszNomFic)
{                                     
	gclHF.HOuvre(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hraye(LPCSTR pszNomFic)
{   
	gclHF.HRaye(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hrayevue(DWORD dwHdlVue)
{   
	gclHF.HRaye((LPCSTR)dwHdlVue);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hreplace(LPCSTR /*pszNomFic*/, LPCSTR /*pszNomCle*/, LPSTR /*pszValCle*/, DWORD /*dwNumEnr*/, LPSTR /*pszCleGen*/)
{   
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hreplacenum(LPCSTR /*pszNomFic*/, LPCSTR /*pszNomCle*/, LPSTR /*pszValCle*/, WORD /*wTailleCle*/, DWORD /*dwNumEnr*/, LPSTR /*pszCleGen*/)
{   
}

/*-----------------------------------------------------------------------------------------------------------*/
/* Hreplace pour clés textes ou numériques (façon WinDev 4.1) */
/* La taille utile de la clé est déterminée ici */
void HreplaceWD4( LPCSTR /*pszNomFic*/, LPCSTR /*pszNomCle*/, LPSTR /*pszValCle*/, DWORD /*dwNumEnr*/, LPSTR /*pszCleGen */)
{   
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hsecurite (short nLevel)
{
	int nOldLevel;
	gclHF.piGetHFContext()->bHSecurite(&nOldLevel,"*",nLevel);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hsubstrep (LPCSTR pszRepLog, LPCSTR pszRepPhys)
{   
	gclHF.HSubstRep(pszRepLog, pszRepPhys);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hsubstnom (LPCSTR pszNomFicLog, LPCSTR pszNomFicPhys)
{   
	gclHF.HChangeNom(pszNomFicLog, pszNomFicPhys);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hsupprime(LPCSTR pszNomFic)
{                                     
	gclHF.HSupprime(pszNomFic);
}                              

/*-----------------------------------------------------------------------------------------------------------*/
void Hsupprimevue(DWORD dwHdlVue)
{                              
	gclHF.HSupprime((LPCSTR)dwHdlVue);
}                              

/*-----------------------------------------------------------------------------------------------------------*/
void Hvalcle(LPCSTR/* pszNomFic*/, LPSTR/* pszValCle*/)
{   
}

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertE(LPSTR pszDest, short far *pnEntier)
{   
	gclHF.piGetHFContext()->bHConvertE((BYTE *)pszDest, *pnEntier);
}

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertU(LPSTR pszDest, unsigned short far *pnUEntier)
{   
	gclHF.piGetHFContext()->bHConvertU((BYTE *)pszDest, *pnUEntier);
}

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertC(LPSTR pszDest, unsigned char far *pcCar)
{             
	gclHF.piGetHFContext()->bHConvertC((BYTE *)pszDest, *pcCar);
}

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertV(LPSTR pszDest, void far *pEntierCourt)
{             
	gclHF.piGetHFContext()->bHConvertV((BYTE *)pszDest, *(char *)pEntierCourt);
}

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertL(LPSTR pszDest, long far *plLong)
{             
	gclHF.piGetHFContext()->bHConvertL((BYTE *)pszDest, *plLong);
}

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertR(LPSTR pszDest,float far *pfReel)
{
	gclHF.piGetHFContext()->bHConvertR((BYTE *)pszDest,*pfReel);
}

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertD(LPSTR pszDest,double far *pfDouble)
{   
	gclHF.piGetHFContext()->bHConvertD((BYTE *)pszDest,*pfDouble);
}

/*-----------------------------------------------------------------------------------------------------------*/
void HconvertP(LPSTR pszDest,void far *pReel6)
{   
	gclHF.piGetHFContext()->bHConvertP((BYTE *)pszDest,pReel6);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitbloque(LPCSTR pszNomFic, DWORD dwNumEnreg)
{                                             
	gclHF.HLit(pszNomFic, dwNumEnreg,HLOCKREADWRITE);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitdernierbloque(LPCSTR pszNomFic, LPCSTR pszNomCle)
{                                             
	gclHF.HLitDernier(pszNomFic, pszNomCle,HLOCKREADWRITE);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitprecedentbloque(LPCSTR pszNomFic, LPCSTR pszNomCle)
{                                             
	gclHF.HLitPrecedent(pszNomFic, pszNomCle,HLOCKREADWRITE);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitprecedentbloquesitrouve(LPCSTR pszNomFic, LPCSTR pszNomCle)
{                                             
	gclHF.HLitPrecedent(pszNomFic, pszNomCle,HLOCKREADWRITE);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitpremierbloque(LPCSTR pszNomFic, LPCSTR pszNomCle)
{   
	gclHF.HLitPremier(pszNomFic, pszNomCle,HLOCKREADWRITE);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherchebloque(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech)
{
	gclHF.HLitRecherchePremier(pszNomFic, pszNomCle, pszValRech,HDEFAULTSIZE,HLOCKREADWRITE|HGENERIC);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherchebloquenum(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech, WORD wSize)
{                                                    
	gclHF.HLitRecherchePremier(pszNomFic, pszNomCle, pszValRech,wSize,HLOCKREADWRITE|HGENERIC);
}

/*-----------------------------------------------------------------------------------------------------------*/
/* Hlitrecherchebloque pour clés textes ou numériques (façon WinDev 4.1) */
/* La taille utile de la clé est déterminée ici */
void HlitrecherchebloqueWD4( LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech )
{   
	gclHF.HLitRecherchePremier(pszNomFic, pszNomCle, pszValRech,HDEFAULTSIZE,HLOCKREADWRITE|HGENERIC);
}

/*-----------------------------------------------------------------------------------------------------------*/
void HlitrecherchebloqueConv(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech,WORD wSize, BOOL /*bConvert*/)
{                                                    
	gclHF.HLitRecherchePremier(pszNomFic, pszNomCle, pszValRech,wSize,HLOCKREADWRITE|HGENERIC);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherchebloquesitrouve(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech)
{   
	gclHF.HLitRecherchePremier(pszNomFic, pszNomCle, pszValRech,HDEFAULTSIZE,HLOCKREADWRITE|HGENERIC);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitsuivantbloque(LPCSTR pszNomFic, LPCSTR pszNomCle)
{                                             
	gclHF.HLitSuivant(pszNomFic, pszNomCle,HLOCKREADWRITE);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitsuivantbloquesitrouve(LPCSTR pszNomFic, LPCSTR pszNomCle)
{                                             
	gclHF.HLitSuivant(pszNomFic, pszNomCle,HLOCKREADWRITE);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hbloquefichier(LPCSTR pszNomFic)
{                                         
	gclHF.HBloqueFichier(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hdebloquefichier(LPCSTR pszNomFic)
{   
	gclHF.HDebloqueFichier(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hbloquetotalfichier(LPCSTR pszNomFic)
{                                    
	gclHF.HBloqueFichier(pszNomFic,HLOCKREADWRITE);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hdebloquetotalfichier(LPCSTR pszNomFic)
{                                    
	gclHF.HDebloqueFichier(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hdebloquenumenr(LPCSTR pszNomFic, DWORD dwNumEnr)
{                                    
	gclHF.HDebloqueNumEnr(pszNomFic, dwNumEnr);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hinterditmodif(LPCSTR pszNomFic)
{                   
	gclHF.piGetHFContext()->bHInterditModif(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hfininterditmodif(LPCSTR pszNomFic)
{                   
	gclHF.piGetHFContext()->bHFinInterditModif(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hmodeauto(void)
{
	gclHF.HMode("*",HMODEMONO);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hmodesemiperso(void)
{
	gclHF.HMode("*",HMODEMULTI);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hmodeperso(BOOL /*bLectureBloquante*/)
{
	gclHF.HMode("*",HMODEMULTI);
}

/*-----------------------------------------------------------------------------------------------------------*/
/*fonctions de gestion du journal*/
void Hjournalrecree(LPCSTR /*pszNomFic*/)
{                               
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hjournalredemarre(LPCSTR /*pszNomFic*/)
{                               
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hjournalstop(LPCSTR /*pszNomFic*/)
{                               
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hjournalinfo(LPCSTR /*pszNomFic*/, LPSTR /*pszInfo*/)
{                               
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hposte(short nVal)
{
	gclHF.piGetHFContext()->bHPoste(nVal);
}

/*-----------------------------------------------------------------------------------------------------------*/
/*fonctions de gestion des transactions*/
void Htransactiondebut(LPCSTR pszNomLst)
{
	gclHF.piGetHFContext()->bHTransactionDebut(NULL,pszNomLst);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Htransactionfin(void)
{                          
	gclHF.piGetHFContext()->bHTransactionFin();
}

/*-----------------------------------------------------------------------------------------------------------*/
void Htransactionannule(void)
{   
	gclHF.piGetHFContext()->bHTransactionAnnule();
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hdebutverrou(void)
{                               	
	gclHF.piGetHFContext()->bHDebutVerrou();
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hfinverrou(void)
{                               
	gclHF.piGetHFContext()->bHFinVerrou();
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitsansbloquer(LPCSTR pszNomFic, DWORD dwNumEnreg)
{                                             	
	gclHF.HLit(pszNomFic, dwNumEnreg,HLOCKNO);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitderniersansbloquer(LPCSTR pszNomFic, LPCSTR pszNomCle)
{                                             
	gclHF.HLitDernier(pszNomFic, pszNomCle,HLOCKNO);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitprecedentsansbloquer(LPCSTR pszNomFic, LPCSTR pszNomCle)
{                                             
	gclHF.HLitPrecedent(pszNomFic, pszNomCle,HLOCKNO);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitpremiersansbloquer(LPCSTR pszNomFic, LPCSTR pszNomCle)
{                                             
	gclHF.HLitPremier(pszNomFic, pszNomCle,HLOCKNO);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherchesansbloquer(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech)
{   
	gclHF.HLitRecherchePremier(pszNomFic, pszNomCle,pszValRech,HDEFAULTSIZE,HLOCKNO|HGENERIC);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitrecherchesansbloquernum(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech, WORD wSize)
{   
	gclHF.HLitRecherchePremier(pszNomFic, pszNomCle,pszValRech,wSize,HLOCKNO);
}

/*-----------------------------------------------------------------------------------------------------------*/
/* Hlitrecherchesansbloquer pour clés textes ou numériques (façon WinDev 4.1) */
/* La taille utile de la clé est déterminée ici */
void HlitrecherchesansbloquerWD4( LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszValRech )
{   
	gclHF.HLitRecherchePremier(pszNomFic, pszNomCle,pszValRech,HDEFAULTSIZE,HLOCKNO);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hlitsuivantsansbloquer(LPCSTR pszNomFic, LPCSTR pszNomCle)
{                                             
	gclHF.HLitSuivant(pszNomFic, pszNomCle,HLOCKNO);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hcreationsiinexistant(LPCSTR pszNomFic)
{                                    
	gclHF.HCreationSiInexistant(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hversion(LPCSTR pszNomFic)
{   
	gclHF.HVersion(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
short Hsauveposition(LPCSTR pszNomFic)
{                 
	return (short)gclHF.HSauvePosition(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hretourposition (short nCtx)
{
	gclHF.HRetourPosition(nCtx);
}

/*-----------------------------------------------------------------------------------------------------------*/
/*fonction de gestion des filtres*/
LPSTR Hfiltre(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszBorneMin, WORD wSizeMin, LPCSTR pszBorneMax, WORD wSizeMax, LPCSTR pszWhere)
{             
	return gclHF.HFiltre(pszNomFic,pszNomCle,pszBorneMin,wSizeMin,pszBorneMax,wSizeMax,pszWhere);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hactivefiltre(LPCSTR pszNomFic)
{                                     
	gclHF.HActiveFiltre(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hdesactivefiltre(LPCSTR pszNomFic)
{                                 
    gclHF.HDesactiveFiltre(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hchangecle(LPCSTR pszNomFic, LPCSTR pszNomCle)
{ 
	gclHF.HChangeCle(pszNomFic, pszNomCle);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Havance(LPCSTR pszNomFic, LPCSTR pszNomCle, DWORD dwNbrEnreg)
{   
	gclHF.HAvance(pszNomFic, pszNomCle, dwNbrEnreg);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hrecule(LPCSTR pszNomFic, LPCSTR pszNomCle, DWORD dwNbrEnreg)
{
	gclHF.HRecule(pszNomFic, pszNomCle, dwNbrEnreg);
}

/*-----------------------------------------------------------------------------------------------------------*/
DWORD Hpositionne(LPCSTR pszNomFic, LPCSTR pszNomCle, DWORD dwPos, DWORD/* dwPosMax*/)
{                  
	return gclHF.HPositionne(pszNomFic, pszNomCle, dwPos);
}

/*-----------------------------------------------------------------------------------------------------------*/
short Halias(LPCSTR pszNomFic, LPCSTR pszNomAlias, LPCSTR pszAbrAlias)
{    
	return (short)gclHF.HAlias(pszNomFic, pszNomAlias, pszAbrAlias);
}

/*-----------------------------------------------------------------------------------------------------------*/
short Hcopieenreg(LPCSTR pszNomFic, LPCSTR pszNomAlias)
{                            
	return (short)gclHF.HCopieEnreg(pszNomFic, pszNomAlias);
}

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hrecupererubrique(LPCSTR pszNomFic, short nIndice)
{
	return gclHF.HRecupereRubrique(pszNomFic, nIndice);
}

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hrecupererubriquevue(DWORD dwHdlVue, short nIndice)
{   
	return gclHF.HRecupereRubrique((PCXSTR)dwHdlVue, nIndice);
}

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hrecupererubriquetout(LPCSTR pszNomFic)
{            
	return gclHF.HRecupereRubrique(pszNomFic,(UINT)-1);
}

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hrecupererubriquetoutvue(DWORD dwHdlVue)
{            
	return gclHF.HRecupereRubrique((PCXSTR)dwHdlVue,(UINT)-1);
}

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hlisteanalyse(LPSTR pszRepInit, LPSTR pszSep)
{                                              
	return gclHF.HListeAnalyse(pszRepInit, pszSep);
}

/*-----------------------------------------------------------------------------------------------------------*/
/*Syntaxe: Hlistefichier(NULL, NULL, <flag>)*/
/*         Hlistefichier(<nomwdd>, NULL, <flag>)*/
/*         Hlistefichier(<nomwdd>, <passwd>, <flag>)*/
/**/
LPSTR Hlistefichier(LPCSTR pszNomWDD, LPCSTR pszPasswd, BOOL bFormatLong)
{                                              
	return gclHF.HListeFichier(pszNomWDD, pszPasswd, bFormatLong ? HLSTDETAIL : HLSTNORMAL);
}

/*-----------------------------------------------------------------------------------------------------------*/
/*Syntaxe: Hlisterubrique(<nomfic>, NULL, NULL, <format>)*/
/*         Hlisterubrique(<nomfic>, <nomwdd>, NULL, <format>)*/
/*         Hlisterubrique(<nomfic>, <nomwdd>, <passwd>, <format>)*/
/**/
LPSTR Hlisterubrique(LPCSTR pszNomFic, LPCSTR pszNomWDD, LPCSTR pszPasswd, int nFormat)
{
	return gclHF.HListeRubrique(pszNomFic, pszNomWDD, pszPasswd, nFormat ? HLSTDETAIL : HLSTNORMAL);
}

/*-----------------------------------------------------------------------------------------------------------*/
/*Syntaxe: Hlistecle(<nomfic>, NULL, NULL, <flag>)*/
/*         Hlistecle(<nomfic>, <nomwdd>, NULL, <flag>)*/
/*         Hlistecle(<nomfic>, <nomwdd>, <passwd>, <flag>)*/
/**/
LPSTR Hlistecle(LPCSTR pszNomFic, LPCSTR pszNomWDD, LPCSTR pszPasswd, BOOL bFormatLong)
{   
	return gclHF.HListeCle(pszNomFic, pszNomWDD, pszPasswd, bFormatLong ? HLSTDETAIL : HLSTNORMAL);
}

/*-----------------------------------------------------------------------------------------------------------*/
/*Syntaxe: Hlistetrigger(NULL,NULL)*/
/*         Hlistetrigger(<nomfic>, NULL)*/
/*         Hlistetrigger(<nomfic>, <nomwdd>)*/
/**/
LPSTR Hlistetrigger(LPCSTR pszNomFic, LPCSTR pszNomWDD)
{   
	LPSTR pszListe = NULL;
	gclHF.piGetHFContext()->bHListeTrigger(&pszListe,pszNomFic, pszNomWDD);
	return pszListe;
}

void Hversrubrique(LPCSTR pszNomFic, short nIndice, LPSTR pszVal)
{             
	gclHF.HVersRubrique(pszNomFic, nIndice, pszVal);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hraz(LPCSTR pszNomFic)
{
	gclHF.HRAZ(pszNomFic);
}

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hlisterep(LPCSTR pszNomFicRep, LPCSTR pszNomFicLog, LPCSTR pszNomFicPhys, short nMode)
{      
	return gclHF.HListeREP(pszNomFicRep, pszNomFicLog, pszNomFicPhys, nMode);
}

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hinfofichier(LPCSTR/* pszNomFic*/,LPCSTR/* pszReserved*/)
{
	return NULL;
}

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hinforubrique(LPCSTR pszNomFic, LPCSTR pszNomRub, int /*nFormat*/)
{
	LPSTR pszInfo = NULL;
	gclHF.piGetHFContext()->bHInfoRubrique(&pszInfo,pszNomFic, pszNomRub);
	return pszInfo;
}

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hinforubriquenum(LPCSTR pszNomFic, short nIndiceRub, int /*nFormat*/)
{
	LPSTR pszInfo = NULL;
	gclHF.piGetHFContext()->bHInfoRubrique(&pszInfo,pszNomFic, nIndiceRub);
	return pszInfo;
}

/*-----------------------------------------------------------------------------------------------------------*/
/* NDX_NORMAL=0, 		:réindexation normale*/
/* NDX_SUPPRESSION=1,	:pour supprimer les enregs endommagés*/
/* NDX_COMPACTAGE=2,	:pour compacter le .FIC*/
/* NDX_MUET=4,			:pour n'afficher aucune jauge ni aucun message*/
/**/
short Hreindexe(LPCSTR pszFicL,LPCSTR pszFicP,LPCSTR pszRepP,short nMode, long /*hWnd*/,LPCSTR /*pszDesc*/)
{
	return (short)gclHF.HReindexe(pszFicL,pszFicP,pszRepP,(eHNDXMODE)(((nMode & 1) ? HNDXDELETE : 0) | ((nMode & 2) ? HNDXCOMPACT : 0) | ((nMode & 4) ? HNDXSILENT : 0)));
}

/*-----------------------------------------------------------------------------------------------------------*/
/*Syntaxe: Hlisteliaison(NULL, NULL, NULL)*/
/*         Hlisteliaison(<nomfic>, NULL, NULL)*/
/*         Hlisteliaison(<nomfic>, <nomwdd>, NULL)*/
/*         Hlisteliaison(<nomfic>, <nomwdd>, <passwd>)*/
/**/
LPSTR Hlisteliaison(LPCSTR pszNomFic, LPCSTR pszNomWDD, LPCSTR pszPasswd)
{
	return gclHF.HListeLiaison(pszNomFic, pszNomWDD, pszPasswd);
}

/*-----------------------------------------------------------------------------------------------------------*/
/* <pszFicL> est un nom de fichier logique, c'est le fichier HF destination*/
/* <pszNomTxt> est un nom de fichier texte complet, c'est le fichier source*/
/* <pszListeRub> est la liste des rubriques correspondant aux colonnes du fichier texte*/
/*        format: "rub1+RC+rub2+RC+rub3"*/
/* <pszSep> contient le séparateur de colonnes, de lignes, et le délimiteur de chaînes*/
/*        format: séparateur colonne + Caract(0x7F) + délimiteur de chaînes + Caract(0x7F) +  séparateur  de lignes*/
/* <nMode> = combinaison des valeurs suivantes*/
/*	1:IMP_CREATION		: création du .FIC (écrasement s'il existe déjà)*/
/*	2:IMP_OEM2ANSI		: conversion OEM vers ANSI des chaînes*/
/*	4:IMP_NONEXCLUSIF		: prise de tour à chaque HAjoute*/
/*	8:IMP_TESTDOUBLON		: test des doublons*/
/*	16:IMP_TESTINTEGRITE	: test de l'intégrité*/
/*	32:IMP_SANSDELIMITEUR	: pas de délimiteur de chaines*/
/**/
short Himportetexte(LPSTR pszFicL, LPSTR pszNomTxt, LPSTR pszListeRub, LPSTR pszSep, short nMode, long /*hWnd*/)
{
	return (short)gclHF.HImporteTexte(pszFicL, pszNomTxt, pszListeRub, pszSep, nMode);
}

/*-----------------------------------------------------------------------------------------------------------*/
/*Syntaxe 0: <nResult>=HAliasExterne(<nomfic>)*/
/*Syntaxe 1: <nResult>=HAliasExterne(<nomfic>,<nomwdd>)*/
/*Syntaxe 2: <nResult>=HAliasExterne(<nomfic>,<nomwdd>,<nomalias>)*/
/**/
/*Renvoie 0 si ok, un code d'erreur sinon:*/
/**/
/* 1 = fichier .WDD introuvable*/
/* 2 = fichier logique existant déjà dans l'analyse en cours*/
/* 3 = alias existant déjà dans l'analyse en cours*/
/* 4 = aucune analyse en cours*/
/* 5 = erreur lors du chargement de la description*/
/**/
short Haliasexterne(LPCSTR pszNomFic, LPCSTR pszNomWDD, LPCSTR pszMotDePasse, LPCSTR pszNomAlias)
{            
	int nRes = 0;
	gclHF.piGetHFContext()->bHAliasExterne(&nRes,pszNomFic,pszNomWDD,pszMotDePasse,pszNomAlias);
	return (short)nRes;
}

/*----------------- Fonctions de gestion des vues -----------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------*/
/*valeurs pour mle mode de création de la vue (combinaison de bits)*/
/**/
/* 1 = pour bloquer les enregs lus dans le fichier principal seulement*/
/* 2 = pour ne garder que les enregs dont les liaisons ont pu être réalisées*/
/* 4 = pour ne pas exécuter la vue dès la création*/
/* 8 = pour prendre son tour 1 seule fois avant d'exécuter la vue*/
/* 16 = pour ne pas vider la vue lors du HExecuteVue (mode ajoût)*/
/**/
DWORD Hcreevue(LPCSTR pszNomFic, LPCSTR pszDescRub, LPCSTR pszRubTri, LPCSTR pszWhere, BYTE byMode, short nTaillePage)
{
	int dwVue = 0;
	gclHF.piGetHFContext()->bHCreeVue_55(&dwVue,pszNomFic,pszDescRub,pszRubTri,pszWhere,byMode,nTaillePage);
	return dwVue;
}

/*-----------------------------------------------------------------------------------------------------------*/
/*Valeur de nOperation:*/
/*	1025 = union de 2 vues*/
/*	1026 = intersection de 2 vues*/
/*	1027 = vue A - intersection de A et B*/
/*	1028 = union exclusive de 2 vues*/
/*  1029 = jointure entre 2 vues*/
/**/
DWORD Hcreevueindirecte(DWORD dwHdlA, DWORD dwHdlB, short nOperation, LPCSTR pszRubTriA, LPCSTR /*pszRubTriB*/)
{
	int dwVue = 0;
	gclHF.piGetHFContext()->bHCreeVueDeVue_55(&dwVue,dwHdlA,dwHdlB,nOperation,pszRubTriA);
	return dwVue;
}

/*-----------------------------------------------------------------------------------------------------------*/
short Hdetruitvue(DWORD dwHdlVue)
{   
	return (short)gclHF.HDetruitVue((LPCSTR)dwHdlVue);
}

/*-----------------------------------------------------------------------------------------------------------*/
short Htrivue(DWORD dwHdlVue, short nIndRub, short nSens)
{
	return (short)gclHF.piGetHFContext()->bHTrieVue_55((LPCSTR)dwHdlVue,nIndRub,nSens);
}

/*-----------------------------------------------------------------------------------------------------------*/
short Hvueversfichier(DWORD dwHdlVue)
{   
	return (short)gclHF.HVueVersFichier((LPCSTR)dwHdlVue);
}

/*-----------------------------------------------------------------------------------------------------------*/
short Hexecutevue(DWORD dwHdlVue, LPCSTR pszWhere)
{                  
	return (short)gclHF.HExecuteVue((LPCSTR)dwHdlVue, pszWhere);
}

/*-----------------------------------------------------------------------------------------------------------*/
short Heffacevue(DWORD dwHdlVue)
{                  
	return (short)gclHF.HEffaceVue((LPCSTR)dwHdlVue);
}

/*----------------- Fonctions de compte-rendu ---------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------*/
long Hnbenr(void)
{
	return (long)gclHF.HNbEnr();
}

/*-----------------------------------------------------------------------------------------------------------*/
long Hnumenr(void)
{
	return (long)gclHF.HNumEnr();
}

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hendehors(void)
{
	return gclHF.HEnDehors();
}

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hactif(void)
{
	return TRUE;
}

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hsup(void)
{
	return TRUE;
}

/*-----------------------------------------------------------------------------------------------------------*/
short Herreur(void)
{
	return (short)gclHF.HErreur();
}                          

/*-----------------------------------------------------------------------------------------------------------*/
short Herreurint(void)
{
	return 0;
}                          

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hdoublon(void)
{
	return gclHF.HErreurDoublon();
}

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Herrintegrite(void)
{
	return gclHF.HErreurIntegrite();
}   

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hdejabloque(void)
{
	BOOL bErr = FALSE;
	gclHF.piGetHFContext()->bHDejaBloque(&bErr);
	return bErr;
}   

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hcommentaire(void)
{
	return NULL;
}   

/*-----------------------------------------------------------------------------------------------------------*/
/*Renvoie 0 si le fichier n'a aucun index, une valeur positive sinon*/
/**/
short Htyp(void)
{
	return 1;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
long Hnbsup(void)
{
	return (long)gclHF.HNbSup_55();
}                 

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hnomfichier(void)
{
	return NULL;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Htrouve(void)
{
	return gclHF.HTrouve();
}                 

/*-----------------------------------------------------------------------------------------------------------*/
short Hgen(void)
{
	return 0;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
short Hlenr(void)
{
	return 0;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hdesc(void)
{
	return NULL;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hcre(void)
{
	return NULL;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hrep(void)
{
	return NULL;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hind(void)
{
	return NULL;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
LPSTR Hext(void)
{
	return NULL;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
short Hechange(void)
{
	return 0;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
short Hmemo(void)
{
	return 0;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
short Hjnl(void)
{
	return 0;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
short Hnbessais(void)
{
	return 1;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
short Hnbessaismessage(void)
{
	return 0;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
short Hniveau(void)
{
	return 0;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Herrignore(void)
{
	return TRUE;
}                 

/*-----------------------------------------------------------------------------------------------------------*/
char Hmodeblocage(void)
{
	return 0;
}         

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hmodedebug(void)
{
	return FALSE;
}         

/*-----------------------------------------------------------------------------------------------------------*/
char Haction(void)
{
	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/
char Hafaire(void)
{
	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hsetnbessais(short/* nVal*/)
{
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hsetnbessaismessage(short/* nVal*/)
{
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hseterrignore(BOOL/* bVal*/)
{
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hseterrormode(short/* nVal*/)
{
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hsetpasse(LPCSTR/* pszNomFic*/, LPSTR/* pszPasse*/)
{
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hsetnumenr(DWORD/* dwNumEnr*/)
{
}                 

/*-----------------------------------------------------------------------------------------------------------*/
void Hsetafaire(char/* cVal*/)
{
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hsetaction(char/* cVal*/)
{
}                 

/*-----------------------------------------------------------------------------------------------------------*/
void Hgeredoublonoui(void)
{
	gclHF.HGereDoublon("*","*",TRUE);
}                 

/*-----------------------------------------------------------------------------------------------------------*/
void Hgeredoublonnon(void)
{
	gclHF.HGereDoublon("*","*",FALSE);
}                   

/*-----------------------------------------------------------------------------------------------------------*/
void Hgereintegritenon(void)
{
	gclHF.HGereIntegrite("*","*",(DWORD)-1,FALSE);
}                 

/*-----------------------------------------------------------------------------------------------------------*/
void Hgereintegriteoui(void)
{
	gclHF.HGereIntegrite("*","*",(DWORD)-1,TRUE);
}                   

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hgerereplication(BOOL/* bMode*/)
{                                                 
	return FALSE;
}                   

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hgeretrigger(BOOL bMode)
{                                                 
	BOOL	bOld = FALSE;
	return gclHF.piGetHFContext()->bHGereTrigger(&bOld,bMode);
}                   

/*-----------------------------------------------------------------------------------------------------------*/
BOOL Hgereaccesdistant(BOOL bMode)
{                                                 
	BOOL	bOld = FALSE;
	return gclHF.piGetHFContext()->bHGereAccesDistant(&bOld,bMode);
}                   

/*-----------------------------------------------------------------------------------------------------------*/
void Hgerejnloui(void)
{
	BOOL	bOld = FALSE;
	gclHF.piGetHFContext()->bHGereJournal(&bOld,TRUE);
}                   

/*-----------------------------------------------------------------------------------------------------------*/
void Hgerejnlnon(void)
{
	BOOL	bOld = FALSE;
	gclHF.piGetHFContext()->bHGereJournal(&bOld,FALSE);
}   

/*-----------------------------------------------------------------------------------------------------------*/
void Hgeretrsoui(void)
{
	gclHF.piGetHFContext()->bHGereTransaction(NULL,TRUE);
}                   

/*-----------------------------------------------------------------------------------------------------------*/
void Hgeretrsnon(void)
{
	gclHF.piGetHFContext()->bHGereTransaction(NULL,FALSE);
}                                        

/*-----------------------------------------------------------------------------------------------------------*/
void Hgerememooui(void)
{
	gclHF.HGereMemo("*","*",HMEMOYES);
}                   

/*-----------------------------------------------------------------------------------------------------------*/
void Hgerememonon(void)
{
	gclHF.HGereMemo("*","*",HMEMONO);
}   

/*-----------------------------------------------------------------------------------------------------------*/
void Hgererepoui(LPCSTR pszRepFile)
{
	gclHF.HGereREP(TRUE,NULL,pszRepFile);
}                   

/*-----------------------------------------------------------------------------------------------------------*/
void Hgererepnon(void)
{
	gclHF.HGereREP(FALSE);
}                   

/*---------------- GESTION DES MEMOS ------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------*/
BOOL HGetMemoData(LPCSTR pszNomFic, LPCSTR pszNomRub, LPVOID *ppData, DWORD *pdwSize)
{
	return gclHF.bGetMemoData(pszNomFic, pszNomRub, (LPCVOID *)ppData, pdwSize);
}

/*-----------------------------------------------------------------------------------------------------------*/
BOOL HSetMemoData(LPCSTR pszNomFic, LPCSTR pszNomRub, LPVOID pData, DWORD dwSize)
{
	return gclHF.bSetMemoData(pszNomFic, pszNomRub, pData, dwSize);
}

/*---------------- FICHIERS DYNAMIQUES ----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------*/
void Hdecritfichier(LPCSTR pszNomFic, LPCSTR pszAbrFic, LPCSTR pszRepFic)
{                                                              
	gclHF.HDecritFichier(pszNomFic, pszAbrFic, pszRepFic);
}   

/*-----------------------------------------------------------------------------------------------------------*/
/*
<pszNomFic> est une chaîne de caractères contenant le nom logique du fichier
<pszDescRub> est une chaîne de caractères qui a la forme <Nom Rubrique>,<Type Rubrique>
	<Nom Rubrique> contient le nom logique de la rubrique
	<Type Rubrique> contient le type de la rubrique et peut prendre pour valeur : 

	- E : pour les entier
	- L : pour les entier long
	- C : pour les entier court
	- S : pour les texte réel simple
	- D : pour les réel double
	- A : pour les date sur 8 (AAAAMMJJ)
	- H : pour les heure HHMM
	- T,<Taille> : pour les rubriques texte (<Taille> est la taille de la chaîne de caractères)
	- M : pour les Mémo texte
	- F : pour les monétaire

	Il ne doit pas y avoir d'espace entre <Nom Rubrique> et <Type Rubrique>.

<NIndice> est un entier optionnel qui donne la taille du tableau de rubriques, 0 sinon
*/
void Hdecritrubrique(LPCSTR pszNomFic, LPCSTR pszDescRub, short nIndice)
{
	gclHF.HDecritRubrique(pszNomFic, pszDescRub, nIndice);
}

/*-----------------------------------------------------------------------------------------------------------*/
/*
<pszNomFic> contient le nom du fichier logique
<pszNomCle> contient le nom de la clé (100 caractères maximum)
<pszLstRub> est une chaine de caractères optionnelle contenant la liste des rubriques composant la clé.
	- dans le cas d'une clé composée, dans <pszLstRub> chaque rubrique est séparée par une virgule : 
	<NomRub1>, <NomRub2>, ...
	- dans le cas d'une clé simple, <pszLstRub> contient le nom de la clé.
<Multiple> est un BOOLéen optionnel permettant de savoir si la clé est unique ou multiple : 
	- à Vrai si la clé est multiple (avec doublons)
	- à Faux si la clé est unique
    Par défaut, <Multiple> est à Vrai
*/
void Hdecritcle(LPCSTR pszNomFic, LPCSTR pszNomCle, LPCSTR pszLstRub, BOOL bMultiple)
{
	gclHF.HDecritCle(pszNomFic, pszNomCle, pszLstRub, bMultiple);
}

/*-----------------------------------------------------------------------------------------------------------*/
void Hdecritliaison(LPCSTR, LPCSTR, LPCSTR, LPCSTR, LPCSTR, LPCSTR)
{
}

/*-----------------------------------------------------------------------------------------------------------*/
/*Création d'un trigger*/
/*TRIG_AVANT = 1, TRIG_APRES = 2*/
/**/
short Hdecrittrigger(LPCSTR /*pszNomFic*/, LPCSTR /*pszNomFoncHF*/, FARPROC /*pFonc*/, short /*nType*/)
{
	return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/
/*Activation, Désactivation ou destruction d'un trigger*/
/**/
short Hannuletrigger(LPCSTR pszNomFic, LPCSTR pszNomFoncHF, short nType, BOOL * /*pbStatus*/)
{
	return (short)gclHF.piGetHFContext()->bHDesactiveTrigger(pszNomFic, pszNomFoncHF, nType);
}

}	/*Fin du extern "C"*/
