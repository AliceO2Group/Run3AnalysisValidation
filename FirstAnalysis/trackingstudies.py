#!/usr/bin/env python
from ROOT import TCanvas, TFile, TLegend, gStyle


def saveCanvas(canvas, title):
    format_list = ["png", ".pdf", ".root"]
    for fileFormat in format_list:
        canvas.SaveAs(title + fileFormat)


# superimposed reco and gen distributions per specie
def specie_distribution(had, var):
    fileo2 = TFile("../codeHF/AnalysisResults_O2.root")
    gStyle.SetOptStat(0)
    cpt = TCanvas("cpt", "pT distribution")
    cpt.SetCanvasSize(1500, 700)
    cpt.Divide(2, 1)
    hnum = fileo2.Get("qa-tracking-efficiency-%s/%s/num" % (had, var))
    hden = fileo2.Get("qa-tracking-efficiency-%s/%s/den" % (had, var))
    hden.Rebin(4)
    hnum.Rebin(4)
    hnum.SetLineColor(6)
    hden.GetYaxis().SetRangeUser(
        0.7 * hnum.GetBinContent(hden.GetMinimumBin()),
        1.3 * hden.GetBinContent(hden.GetMaximumBin()),
    )
    hden.Draw()
    hnum.Draw("same")
    hden.SetTitle("%s tracks %s distribution" % (had, var))
    leg = TLegend(0.7, 0.7, 0.9, 0.9, "")
    leg.SetFillColor(0)
    leg.AddEntry(hnum, "Rec. Level")
    leg.AddEntry(hden, "Gen. Level")
    leg.Draw()
    saveCanvas(cpt, "%sdistribution_hfcand%s" % (var, had))


def multiplicity():
    fileo2 = TFile("../codeHF/AnalysisResults_O2.root")
    cmult = TCanvas("cmult", "mult distribution")
    cmult.SetCanvasSize(1500, 700)
    cmult.SetLogy()
    cmult.Divide(2, 1)
    hmult = fileo2.Get("qa-global-observables/multiplicity/numberOfTracks")
    hmult.Rebin(4)
    hmult.Draw()
    hmult.SetTitle("Multiplicity Distribution")
    saveCanvas(cmult, "multiplicity")


def var_tracking(var):
    fileo2 = TFile("../codeHF/AnalysisResults_O2.root")
    cvar = TCanvas("cvar", "var distribution")
    cvar.SetCanvasSize(1800, 800)
    cvar.Divide(2, 1)
    hvar = fileo2.Get("qa-tracking-kine/tracking/%s" % var)
    hvar.Rebin(4)
    hvar.Draw()
    saveCanvas(cvar, "tracking_%s" % var)


def tracking_resolution(var1, mode, var2, var3):
    fileo2 = TFile("../codeHF/AnalysisResults_O2.root")
    cres = TCanvas("cres", "resolution distribution")
    cres.SetCanvasSize(1500, 700)
    if var1 == "eta":
        heta = fileo2.Get("qa-tracking-resolution/eta/etaDiffMCRecoVsEta%s" % mode)
        heta.Draw("coltz")
        heta.SetTitle("%s resolution" % var1)
        saveCanvas(cres, "Resolution_%s_%s" % (var1, var2))

    if var1 == "impactParameter":
        himp_par = fileo2.Get(
            "qa-tracking-resolution/%s/%s%sVs%s" % (var1, var1, var2, var3)
        )
        himp_par.Draw("coltz")
        himp_par.SetTitle("Impact Parameter resolution: %s Vs %s" % (var2, var3))
        saveCanvas(cres, "impact_parameter_resolution%sVs%s" % (var2, var3))
    if var1 == "impactParameterError":
        himp_par_err = fileo2.Get(
            "qa-tracking-resolution/impactParameter/%s%sVs%s" % (var1, var2, var3)
        )
        himp_par_err.Draw("coltz")
        himp_par_err.SetTitle(
            "Impact Parameter Error resolution: %s Vs %s" % (var2, var3)
        )
        saveCanvas(cres, "impactParameterError_resolution%sVs%s" % (var2, var3))
    if var1 == "phi":
        hphi = fileo2.Get("qa-tracking-resolution/phi/phiDiffMCRec")
        hphi.Draw()
        saveCanvas(cres, "phi_resolution")

    if var1 == "pt":
        h_pt = fileo2.Get("qa-tracking-resolution/pt/ptResolutionVs%s" % var2)
        h_pt.Draw("coltz")
        saveCanvas(cres, "ptResolutionVs%s" % var2)


def vertex_distributions(var):
    fileo2 = TFile("../codeHF/AnalysisResults_O2.root")
    cvertex = TCanvas("cvertex", "vertex ")
    cvertex.SetCanvasSize(1800, 700)
    cvertex.Divide(2, 1)
    hvertex = fileo2.Get("qa-global-observables/collision/%s" % var)
    cvertex.cd(1)
    hvertex.Draw()
    hvertex_res = fileo2.Get("qa-global-observables/collision/%svsNContrib" % var)
    cvertex.cd(2)
    hvertex_res.Draw("coltz")
    saveCanvas(cvertex, "vertex_%s" % var)


multiplicity()
specie_list = ["pion", "proton", "kaon", "electron", "muon"]
var_list = ["pt", "eta", "phi"]
for specie in specie_list:
    for var in var_list:
        specie_distribution(specie, var)

vertex_coord_list = ["X", "Y", "Z"]
for coord in vertex_coord_list:
    vertex_distributions(coord)

for var in var_list:
    var_tracking(var)

var1_list = ["RPhi", "Z"]
var2_list = ["Pt", "Phi", "Eta"]
tracking_resolution("eta", "MC", "", "")
tracking_resolution("pt", "", "Eta", "")
for var1 in var1_list:
    for var2 in var2_list:
        tracking_resolution("impactParameter", "MC", var1, var2)
        tracking_resolution("impactParameterError", "MC", var1, var2)
