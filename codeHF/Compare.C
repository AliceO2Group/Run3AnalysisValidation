// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

// Comparison of AliPhysics and O2 histograms

#include "../exec/utilitiesValidation.h"

Int_t Compare(TString pathFileO2 = "AnalysisResults_O2.root", TString pathFileAli = "AnalysisResults_ALI.root", TString options = "", bool doRatio = false)
{
  TString pathListAli = "HFVertices/clistHFVertices";
  TString labelParticle = "";

  // Histogram specification: axis label, AliPhysics name, O2Physics path/name, rebin, log scale histogram, log scale ratio, projection axis

  VecSpecHis vecHisEvents;
  AddHistogram(vecHisEvents, "primary vtx x (cm)", "hPrimVertX", "hf-track-index-skim-creator-tag-sel-collisions/hPosXAfterEvSel", 1, 1, 0);
  AddHistogram(vecHisEvents, "primary vtx y (cm)", "hPrimVertY", "hf-track-index-skim-creator-tag-sel-collisions/hPosYAfterEvSel", 1, 1, 0);
  AddHistogram(vecHisEvents, "primary vtx z (cm)", "hPrimVertZ", "hf-track-index-skim-creator-tag-sel-collisions/hPosZAfterEvSel", 1, 1, 0);
  AddHistogram(vecHisEvents, "primary vtx N contributors", "fHistPrimVertContr", "hf-track-index-skim-creator-tag-sel-collisions/hNumPvContributorsAfterSel", 1, 1, 0);

  VecSpecHis vecHisTracks;
  AddHistogram(vecHisTracks, "#it{p}_{T} before selections (GeV/#it{c})", "hPtAllTracks", "hf-track-index-skim-creator-tag-sel-tracks/hPtNoCuts", 2, 1, 0);
  AddHistogram(vecHisTracks, "#it{p}_{T} (2-prong sel.)", "hPtSelTracks2prong", "hf-track-index-skim-creator-tag-sel-tracks/hPtCuts2Prong", 2, 1, 0);
  AddHistogram(vecHisTracks, "#it{p}_{T} (3-prong sel.)", "hPtSelTracks3prong", "hf-track-index-skim-creator-tag-sel-tracks/hPtCuts3Prong", 2, 1, 0);
  AddHistogram(vecHisTracks, "#it{p}_{T} (bachelor sel.)", "hPtSelTracksbachelor", "hf-track-index-skim-creator-tag-sel-tracks/hPtCutsV0bachelor", 2, 1, 0);
  AddHistogram(vecHisTracks, "DCA XY to prim. vtx. (2-prong sel.) (cm)", "hImpParSelTracks2prong", "hf-track-index-skim-creator-tag-sel-tracks/hDCAToPrimXYVsPtCuts2Prong", 2, 1, 0, "y");
  AddHistogram(vecHisTracks, "DCA XY to prim. vtx. (3-prong sel.) (cm)", "hImpParSelTracks3prong", "hf-track-index-skim-creator-tag-sel-tracks/hDCAToPrimXYVsPtCuts3Prong", 2, 1, 0, "y");
  AddHistogram(vecHisTracks, "DCA XY to prim. vtx. (bachelor sel.) (cm)", "hImpParSelTracksbachelor", "hf-track-index-skim-creator-tag-sel-tracks/hDCAToPrimXYVsPtCutsV0bachelor", 2, 1, 0, "y");
  AddHistogram(vecHisTracks, "#it{#eta} (2-prong sel.)", "hEtaSelTracks2prong", "hf-track-index-skim-creator-tag-sel-tracks/hEtaCuts2Prong", 2, 0, 0);
  AddHistogram(vecHisTracks, "#it{#eta} (3-prong sel.)", "hEtaSelTracks3prong", "hf-track-index-skim-creator-tag-sel-tracks/hEtaCuts3Prong", 2, 0, 0);
  AddHistogram(vecHisTracks, "#it{#eta} (bachelor sel.)", "hEtaSelTracksbachelor", "hf-track-index-skim-creator-tag-sel-tracks/hEtaCutsV0bachelor", 2, 0, 0);

  VecSpecHis vecHisSkim;
  AddHistogram(vecHisSkim, "secondary vtx x - 2prong (cm)", "h2ProngVertX", "hf-track-index-skim-creator/hVtx2ProngX", 5, 1, 0);
  AddHistogram(vecHisSkim, "secondary vtx y - 2prong (cm)", "h2ProngVertY", "hf-track-index-skim-creator/hVtx2ProngY", 5, 1, 0);
  AddHistogram(vecHisSkim, "secondary vtx z - 2prong (cm)", "h2ProngVertZ", "hf-track-index-skim-creator/hVtx2ProngZ", 5, 1, 0);
  AddHistogram(vecHisSkim, "secondary vtx x - 3prong (cm)", "h3ProngVertX", "hf-track-index-skim-creator/hVtx3ProngX", 5, 1, 0);
  AddHistogram(vecHisSkim, "secondary vtx y - 3prong (cm)", "h3ProngVertY", "hf-track-index-skim-creator/hVtx3ProngY", 5, 1, 0);
  AddHistogram(vecHisSkim, "secondary vtx z - 3prong (cm)", "h3ProngVertZ", "hf-track-index-skim-creator/hVtx3ProngZ", 5, 1, 0);

  VecSpecHis vecHisCand2;
  AddHistogram(vecHisCand2, "XX element of PV cov. matrix (cm^{2})", "hCovMatPrimVXX2Prong", "hf-candidate-creator-2prong/hCovPVXX", 1, 1, 0);
  AddHistogram(vecHisCand2, "XX element of SV cov. matrix (cm^{2})", "hCovMatSecVXX2Prong", "hf-candidate-creator-2prong/hCovSVXX", 1, 1, 0);

  VecSpecHis vecHisCand3;
  AddHistogram(vecHisCand3, "XX element of PV cov. matrix (cm^{2})", "hCovMatPrimVXX3Prong", "hf-candidate-creator-3prong/hCovPVXX", 1, 1, 0);
  AddHistogram(vecHisCand3, "XX element of SV cov. matrix (cm^{2})", "hCovMatSecVXX3Prong", "hf-candidate-creator-3prong/hCovSVXX", 1, 1, 0);
  AddHistogram(vecHisCand3, "YY element of PV cov. matrix (cm^{2})", "hCovMatPrimVYY3Prong", "hf-candidate-creator-3prong/hCovPVYY", 1, 1, 0);
  AddHistogram(vecHisCand3, "YY element of SV cov. matrix (cm^{2})", "hCovMatSecVYY3Prong", "hf-candidate-creator-3prong/hCovSVYY", 1, 1, 0);
  AddHistogram(vecHisCand3, "ZZ element of PV cov. matrix (cm^{2})", "hCovMatPrimVZZ3Prong", "hf-candidate-creator-3prong/hCovPVZZ", 1, 1, 0);
  AddHistogram(vecHisCand3, "ZZ element of SV cov. matrix (cm^{2})", "hCovMatSecVZZ3Prong", "hf-candidate-creator-3prong/hCovSVZZ", 1, 1, 0);

  VecSpecHis vecHisD0;
  AddHistogram(vecHisD0, "#it{p}_{T} prong 0 (GeV/#it{c})", "hPtD0Dau0", "hf-task-d0/hPtProng0", 2, 1, 0);
  AddHistogram(vecHisD0, "#it{p}_{T} prong 1 (GeV/#it{c})", "hPtD0Dau1", "hf-task-d0/hPtProng1", 2, 1, 0);
  AddHistogram(vecHisD0, "#it{p}_{T} D^{0} (GeV/#it{c})", "hPtD0", "hf-task-d0/hPtCand", 2, 1, 0);
  AddHistogram(vecHisD0, "2-prong mass (#pi K) (GeV/#it{c}^{2})", "hInvMassD0", "hf-task-d0/hMass", 2, 0, 0);
  AddHistogram(vecHisD0, "d0d0 (cm^{2})", "hd0Timesd0", "hf-task-d0/hd0d0", 2, 1, 0);
  AddHistogram(vecHisD0, "d0 prong 0 (cm)", "hImpParD0Dau0", "hf-task-d0/hd0Prong0", 2, 1, 0);
  AddHistogram(vecHisD0, "d0 prong 1 (cm)", "hImpParD0Dau1", "hf-task-d0/hd0Prong1", 2, 1, 0);
  AddHistogram(vecHisD0, "impact parameter error prong 0 (cm)", "hImpParErrD0Dau0", "hf-task-d0/hd0ErrProng0", 1, 1, 0);
  AddHistogram(vecHisD0, "impact parameter error prong 1 (cm)", "hImpParErrD0Dau1", "hf-task-d0/hd0ErrProng1", 1, 1, 0);
  AddHistogram(vecHisD0, "decay length (cm)", "hDecLenD0", "hf-task-d0/hDecLength", 2, 1, 0);
  AddHistogram(vecHisD0, "decay length XY (cm)", "hDecLenXYD0", "hf-task-d0/hDecLengthxy", 2, 1, 0);
  AddHistogram(vecHisD0, "decay length error (cm)", "hDecLenErrD0", "hf-task-d0/hDecLenErr", 1, 1, 0);
  AddHistogram(vecHisD0, "decay length XY error (cm)", "hDecLenXYErrD0", "hf-task-d0/hDecLenXYErr", 1, 1, 0);
  AddHistogram(vecHisD0, "cos pointing angle", "hCosPointD0", "hf-task-d0/hCPA", 2, 1, 0);

  labelParticle = "D^{0} #rightarrow #pi K";
  VecSpecHis vecHisD0MC;
  AddHistogram(vecHisD0MC, labelParticle + ", matched prompt: #it{p}_{T}^{rec} (GeV/#it{c})", "hPtRecoPromptD0Kpi", "hf-task-d0/hPtRecSigPrompt", 2, 1, 0);
  AddHistogram(vecHisD0MC, labelParticle + ", gen. prompt: #it{p}_{T}^{gen} (GeV/#it{c})", "hPtGenLimAccPromptD0Kpi", "hf-task-d0/hPtGenPrompt", 2, 1, 0);
  AddHistogram(vecHisD0MC, labelParticle + ", matched non-prompt: #it{p}_{T}^{rec} (GeV/#it{c})", "hPtRecoFeeddwD0Kpi", "hf-task-d0/hPtRecSigNonPrompt", 2, 1, 0);
  AddHistogram(vecHisD0MC, labelParticle + ", gen. non-prompt: #it{p}_{T}^{gen} (GeV/#it{c})", "hPtGenLimAccFeeddwD0Kpi", "hf-task-d0/hPtGenNonPrompt", 2, 1, 0);

  VecSpecHis vecHisDs;
  AddHistogram(vecHisDs, "#it{p}_{T} prong 0 (GeV/#it{c})", "hPtDsDau0", "hf-task-ds/hPtProng0", 2, 1, 0);
  AddHistogram(vecHisDs, "#it{p}_{T} prong 1 (GeV/#it{c})", "hPtDsDau1", "hf-task-ds/hPtProng1", 2, 1, 0);
  AddHistogram(vecHisDs, "#it{p}_{T} prong 2 (GeV/#it{c})", "hPtDsDau2", "hf-task-ds/hPtProng2", 2, 1, 0);
  AddHistogram(vecHisDs, "#it{p}_{T} D_{s}^{+} (GeV/#it{c})", "hPtDs", "hf-task-ds/hPt", 2, 1, 0);
  AddHistogram(vecHisDs, "3-prong mass (K K #pi) (GeV/#it{c}^{2})", "hInvMassDs", "hf-task-ds/hMass", 5, 0, 0);
  AddHistogram(vecHisDs, "impact par. XY (cm)", "hImpParXYDs", "hf-task-ds/hImpactParameterXY", 4, 1, 0);
  AddHistogram(vecHisDs, "decay length (cm)", "hDecLenDs", "hf-task-ds/hDecayLength", 4, 1, 0);
  AddHistogram(vecHisDs, "decay length XY (cm)", "hDecLenXYDs", "hf-task-ds/hDecayLengthXY", 4, 1, 0);
  AddHistogram(vecHisDs, "norm. decay length XY", "hNormDecLenXYDs", "hf-task-ds/hNormalisedDecayLengthXY", 2, 1, 0);
  AddHistogram(vecHisDs, "cos pointing angle", "hCosPointDs", "hf-task-ds/hCPA", 2, 1, 0);
  AddHistogram(vecHisDs, "cos pointing angle XY", "hCosPointXYDs", "hf-task-ds/hCPAxy", 2, 1, 0);
  AddHistogram(vecHisDs, "norm. IP", "hNormIPDs", "hf-task-ds/hMaxNormalisedDeltaIP", 4, 1, 0);
  AddHistogram(vecHisDs, "|M(KK) - M(#phi)| (GeV/#it{c}^{2})", "hDeltaMassPhiDs", "hf-task-ds/hDeltaMassPhi", 1, 1, 0);
  AddHistogram(vecHisDs, "cos^{3} #theta'(K)", "hCos3PiKDs", "hf-task-ds/hCos3PiK", 2, 1, 0);
  AddHistogram(vecHisDs, "|cos^{3} #theta'(K)|", "hAbsCos3PiKDs", "hf-task-ds/hAbsCos3PiK", 2, 2, 0);

  VecSpecHis vecHisDPlus;
  AddHistogram(vecHisDPlus, "#it{p}_{T} prong 0 (GeV/#it{c})", "hPtDplusDau0", "hf-task-dplus/hPtProng0", 2, 1, 0);
  AddHistogram(vecHisDPlus, "#it{p}_{T} prong 1 (GeV/#it{c})", "hPtDplusDau1", "hf-task-dplus/hPtProng1", 2, 1, 0);
  AddHistogram(vecHisDPlus, "#it{p}_{T} prong 2 (GeV/#it{c})", "hPtDplusDau2", "hf-task-dplus/hPtProng2", 2, 1, 0);
  AddHistogram(vecHisDPlus, "#it{p}_{T} D^{+} (GeV/#it{c})", "hPtDplus", "hf-task-dplus/hPt", 2, 1, 0);
  AddHistogram(vecHisDPlus, "3-prong mass (#pi K #pi) (GeV/#it{c}^{2})", "hInvMassDplus", "hf-task-dplus/hMass", 5, 0, 0);
  AddHistogram(vecHisDPlus, "impact par. XY (cm)", "hImpParXYDplus", "hf-task-dplus/hImpactParameterXY", 4, 1, 0);
  AddHistogram(vecHisDPlus, "decay length (cm)", "hDecLenDplus", "hf-task-dplus/hDecayLength", 4, 1, 0);
  AddHistogram(vecHisDPlus, "decay length XY (cm)", "hDecLenXYDplus", "hf-task-dplus/hDecayLengthXY", 4, 1, 0);
  AddHistogram(vecHisDPlus, "norm. decay length XY", "hNormDecLenXYDplus", "hf-task-dplus/hNormalisedDecayLengthXY", 2, 1, 0);
  AddHistogram(vecHisDPlus, "cos pointing angle", "hCosPointDplus", "hf-task-dplus/hCPA", 2, 1, 0);
  AddHistogram(vecHisDPlus, "cos pointing angle XY", "hCosPointXYDplus", "hf-task-dplus/hCPAxy", 2, 1, 0);
  AddHistogram(vecHisDPlus, "norm. IP", "hNormIPDplus", "hf-task-dplus/hMaxNormalisedDeltaIP", 4, 1, 0);
  AddHistogram(vecHisDPlus, "decay length error (cm)", "hDecLenErrDplus", "hf-task-dplus/hDecayLengthError", 2, 1, 0);
  AddHistogram(vecHisDPlus, "decay length XY error (cm)", "hDecLenXYErrDplus", "hf-task-dplus/hDecayLengthXYError", 2, 1, 0);
  AddHistogram(vecHisDPlus, "prong 0 impact parameter (cm)", "hImpParDplusDau0", "hf-task-dplus/hd0Prong0", 2, 1, 0);
  AddHistogram(vecHisDPlus, "prong 1 impact parameter (cm)", "hImpParDplusDau1", "hf-task-dplus/hd0Prong1", 2, 1, 0);
  AddHistogram(vecHisDPlus, "prong 2 impact parameter (cm)", "hImpParDplusDau2", "hf-task-dplus/hd0Prong2", 2, 1, 0);
  AddHistogram(vecHisDPlus, "prong impact parameter error (cm)", "hImpParErrDplusDau", "hf-task-dplus/hImpactParameterError", 2, 1, 0);
  AddHistogram(vecHisDPlus, "sq. sum of prong imp. par. (cm^{2})", "hSumSqImpParDplusDau", "hf-task-dplus/hImpactParameterProngSqSum", 2, 1, 0);

  VecSpecHis vecHisLc;
  AddHistogram(vecHisLc, "#it{p}_{T} prong 0 (GeV/#it{c})", "hPtLcDau0", "hf-task-lc/Data/hPtProng0", 2, 1, 0);
  AddHistogram(vecHisLc, "#it{p}_{T} prong 1 (GeV/#it{c})", "hPtLcDau1", "hf-task-lc/Data/hPtProng1", 2, 1, 0);
  AddHistogram(vecHisLc, "#it{p}_{T} prong 2 (GeV/#it{c})", "hPtLcDau2", "hf-task-lc/Data/hPtProng2", 2, 1, 0);
  AddHistogram(vecHisLc, "#it{p}_{T} #Lambda_{c}^{#plus} (GeV/#it{c})", "hPtLc", "hf-task-lc/Data/hPt", 2, 1, 0);
  AddHistogram(vecHisLc, "3-prong mass (p K #pi) (GeV/#it{c}^{2})", "hInvMassLc", "hf-task-lc/Data/hMass", 2, 0, 0, "x");
  AddHistogram(vecHisLc, "prong 0 DCAxy to prim. vertex (cm)", "hImpParLcDau0", "hf-task-lc/Data/hd0Prong0", 2, 1, 0);
  AddHistogram(vecHisLc, "prong 1 DCAxy to prim. vertex (cm)", "hImpParLcDau1", "hf-task-lc/Data/hd0Prong1", 2, 1, 0);
  AddHistogram(vecHisLc, "prong 2 DCAxy to prim. vertex (cm)", "hImpParLcDau2", "hf-task-lc/Data/hd0Prong2", 2, 1, 0);
  AddHistogram(vecHisLc, "decay length (cm)", "hDecLenLc", "hf-task-lc/Data/hDecLength", 2, 1, 0);
  AddHistogram(vecHisLc, "decay length xy (cm)", "hDecLenLcXY", "hf-task-lc/Data/hDecLengthxy", 2, 1, 0);
  AddHistogram(vecHisLc, "proper lifetime (#Lambda_{c}) * #it{c} (cm)", "hCt", "hf-task-lc/Data/hCt", 2, 1, 0);
  AddHistogram(vecHisLc, "cos pointing angle", "hCosPointLc", "hf-task-lc/Data/hCPA", 2, 1, 0);
  AddHistogram(vecHisLc, "cos pointing angle xy", "hCosPointXYLc", "hf-task-lc/Data/hCPAxy", 2, 1, 0);
  AddHistogram(vecHisLc, "#it{#eta}", "hEtaLc", "hf-task-lc/Data/hEta", 2, 1, 0);
  AddHistogram(vecHisLc, "#it{#varphi}", "hPhiLc", "hf-task-lc/Data/hPhi", 2, 1, 0);

  labelParticle = "#Lambda_{c}^{#plus} #rightarrow p K #pi";
  VecSpecHis vecHisLcMCPt;
  AddHistogram(vecHisLcMCPt, labelParticle + ", matched prompt: #it{p}_{T}^{rec} (GeV/#it{c})", "hPtRecoPromptLcpKpi", "hf-task-lc/MC/reconstructed/prompt/hPtRecSigPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPt, labelParticle + ", gen. prompt: #it{p}_{T}^{gen} (GeV/#it{c})", "hPtGenLimAccPromptLcpKpi", "hf-task-lc/MC/generated/prompt/hPtGenPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPt, labelParticle + ", matched non-prompt: #it{p}_{T}^{rec} (GeV/#it{c})", "hPtRecoFeeddwLcpKpi", "hf-task-lc/MC/reconstructed/nonprompt/hPtRecSigNonPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPt, labelParticle + ", gen. non-prompt: #it{p}_{T}^{gen} (GeV/#it{c})", "hPtGenLimAccFeeddwLcpKpi", "hf-task-lc/MC/generated/nonprompt/hPtGenNonPrompt", 2, 1, 0);

  VecSpecHis vecHisLcMCEta;
  AddHistogram(vecHisLcMCEta, labelParticle + ", matched prompt: #it{#eta}", "hEtaLcPrompt", "hf-task-lc/MC/reconstructed/prompt/hEtaRecSigPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCEta, labelParticle + ", gen. prompt: #it{#eta}", "hEtaGenLimAccPromptLcpKpi", "hf-task-lc/MC/generated/prompt/hEtaGenPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCEta, labelParticle + ", matched non-prompt: #it{#eta}", "hEtaLcNonPrompt", "hf-task-lc/MC/reconstructed/nonprompt/hEtaRecSigNonPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCEta, labelParticle + ", gen. non-prompt: #it{#eta}", "hEtaGenLimAccFeeddwLcpKpi", "hf-task-lc/MC/generated/nonprompt/hEtaGenNonPrompt", 2, 1, 0);

  VecSpecHis vecHisLcMCPhi;
  AddHistogram(vecHisLcMCPhi, labelParticle + ", matched prompt: #it{#varphi}", "hPhiLcPrompt", "hf-task-lc/MC/reconstructed/prompt/hPhiRecSigPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPhi, labelParticle + ", gen. prompt: #it{#varphi}", "hPhiGenLimAccPromptLcpKpi", "hf-task-lc/MC/generated/prompt/hPhiGenPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPhi, labelParticle + ", matched non-prompt: #it{#varphi}", "hPhiLcNonPrompt", "hf-task-lc/MC/reconstructed/nonprompt/hPhiRecSigNonPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPhi, labelParticle + ", gen. non-prompt: #it{#varphi}", "hPhiGenLimAccFeeddwLcpKpi", "hf-task-lc/MC/generated/nonprompt/hPhiGenNonPrompt", 2, 1, 0);

  VecSpecHis vecHisLcMCPrompt;
  AddHistogram(vecHisLcMCPrompt, "#it{p}_{T} prong 0 (GeV/#it{c})", "hPtLcDau0Prompt", "hf-task-lc/MC/reconstructed/prompt/hPtRecProng0SigPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPrompt, "#it{p}_{T} prong 1 (GeV/#it{c})", "hPtLcDau1Prompt", "hf-task-lc/MC/reconstructed/prompt/hPtRecProng1SigPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPrompt, "#it{p}_{T} prong 2 (GeV/#it{c})", "hPtLcDau2Prompt", "hf-task-lc/MC/reconstructed/prompt/hPtRecProng2SigPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPrompt, "3-prong mass (p K #pi) (GeV/#it{c}^{2})", "hInvMassLcPrompt", "hf-task-lc/MC/reconstructed/prompt/hMassRecSigPrompt", 2, 0, 0, "x");
  AddHistogram(vecHisLcMCPrompt, "prong 0 DCAxy to prim. vertex (cm)", "hImpParLcDau0Prompt", "hf-task-lc/MC/reconstructed/prompt/hd0RecProng0SigPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPrompt, "prong 1 DCAxy to prim. vertex (cm)", "hImpParLcDau1Prompt", "hf-task-lc/MC/reconstructed/prompt/hd0RecProng1SigPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPrompt, "prong 2 DCAxy to prim. vertex (cm)", "hImpParLcDau2Prompt", "hf-task-lc/MC/reconstructed/prompt/hd0RecProng2SigPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPrompt, "decay length (cm)", "hDecLenLcPrompt", "hf-task-lc/MC/reconstructed/prompt/hDecLengthRecSigPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPrompt, "decay length xy (cm)", "hDecLenLcXYPrompt", "hf-task-lc/MC/reconstructed/prompt/hDecLengthxyRecSigPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPrompt, "proper lifetime (#Lambda_{c}) * #it{c} (cm)", "hCtPrompt", "hf-task-lc/MC/reconstructed/prompt/hCtRecSigPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPrompt, "cos pointing angle", "hCosPointLcPrompt", "hf-task-lc/MC/reconstructed/prompt/hCPARecSigPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCPrompt, "cos pointing angle xy", "hCosPointXYLcPrompt", "hf-task-lc/MC/reconstructed/prompt/hCPAxyRecSigPrompt", 2, 1, 0);

  VecSpecHis vecHisLcMCNonPrompt;
  AddHistogram(vecHisLcMCNonPrompt, "#it{p}_{T} prong 0 (GeV/#it{c})", "hPtLcDau0NonPrompt", "hf-task-lc/MC/reconstructed/nonprompt/hPtRecProng0SigNonPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCNonPrompt, "#it{p}_{T} prong 1 (GeV/#it{c})", "hPtLcDau1NonPrompt", "hf-task-lc/MC/reconstructed/nonprompt/hPtRecProng1SigNonPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCNonPrompt, "#it{p}_{T} prong 2 (GeV/#it{c})", "hPtLcDau2NonPrompt", "hf-task-lc/MC/reconstructed/nonprompt/hPtRecProng2SigNonPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCNonPrompt, "3-prong mass (p K #pi) (GeV/#it{c}^{2})", "hInvMassLcNonPrompt", "hf-task-lc/MC/reconstructed/nonprompt/hMassRecSigNonPrompt", 2, 0, 0, "x");
  AddHistogram(vecHisLcMCNonPrompt, "prong 0 DCAxy to prim. vertex (cm)", "hImpParLcDau0NonPrompt", "hf-task-lc/MC/reconstructed/nonprompt/hd0RecProng0SigNonPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCNonPrompt, "prong 1 DCAxy to prim. vertex (cm)", "hImpParLcDau1NonPrompt", "hf-task-lc/MC/reconstructed/nonprompt/hd0RecProng1SigNonPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCNonPrompt, "prong 2 DCAxy to prim. vertex (cm)", "hImpParLcDau2NonPrompt", "hf-task-lc/MC/reconstructed/nonprompt/hd0RecProng2SigNonPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCNonPrompt, "decay length (cm)", "hDecLenLcNonPrompt", "hf-task-lc/MC/reconstructed/nonprompt/hDecLengthRecSigNonPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCNonPrompt, "decay length xy (cm)", "hDecLenLcXYNonPrompt", "hf-task-lc/MC/reconstructed/nonprompt/hDecLengthxyRecSigNonPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCNonPrompt, "proper lifetime (#Lambda_{c}) * #it{c} (cm)", "hCtNonPrompt", "hf-task-lc/MC/reconstructed/nonprompt/hCtRecSigNonPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCNonPrompt, "cos pointing angle", "hCosPointLcNonPrompt", "hf-task-lc/MC/reconstructed/nonprompt/hCPARecSigNonPrompt", 2, 1, 0);
  AddHistogram(vecHisLcMCNonPrompt, "cos pointing angle xy", "hCosPointXYLcNonPrompt", "hf-task-lc/MC/reconstructed/nonprompt/hCPAxyRecSigNonPrompt", 2, 1, 0);

  VecSpecHis vecHisJpsi;
  AddHistogram(vecHisJpsi, "#it{p}_{T} prong 0 (GeV/#it{c})", "hPtJpsiDau0", "hf-task-jpsi/hPtProng0", 2, 1, 0);
  AddHistogram(vecHisJpsi, "#it{p}_{T} prong 1 (GeV/#it{c})", "hPtJpsiDau1", "hf-task-jpsi/hPtProng1", 2, 1, 0);
  AddHistogram(vecHisJpsi, "#it{p}_{T} J/#psi (GeV/#it{c})", "hPtJpsi", "hf-task-jpsi/hPtCand", 2, 1, 0);
  AddHistogram(vecHisJpsi, "2-prong mass (e^{#plus} e^{#minus}) (GeV/#it{c}^{2})", "hInvMassJpsi", "hf-task-jpsi/hMass", 2, 0, 0);
  AddHistogram(vecHisJpsi, "d0d0 (cm^{2})", "hd0Timesd0Jpsi", "hf-task-jpsi/hd0d0", 2, 1, 0);
  AddHistogram(vecHisJpsi, "d0 prong 0 (cm)", "hImpParJpsiDau0", "hf-task-jpsi/hd0Prong0", 2, 1, 0);
  AddHistogram(vecHisJpsi, "d0 prong 1 (cm)", "hImpParJpsiDau1", "hf-task-jpsi/hd0Prong1", 2, 1, 0);
  AddHistogram(vecHisJpsi, "decay length (cm)", "hDecLenJpsi", "hf-task-jpsi/hDecLength", 2, 1, 0);
  AddHistogram(vecHisJpsi, "decay length XY (cm)", "hDecLenXYJpsi", "hf-task-jpsi/hDecLengthxy", 2, 1, 0);
  AddHistogram(vecHisJpsi, "cos pointing angle", "hCosPointJpsi", "hf-task-jpsi/hCPA", 2, 1, 0);
  AddHistogram(vecHisJpsi, "decay length error (cm)", "hDecLenErrJpsi", "hf-task-jpsi/hDecLenErr", 1, 1, 0);
  AddHistogram(vecHisJpsi, "decay length XY error (cm)", "hDecLenXYErrJpsi", "hf-task-jpsi/hDecLenXYErr", 1, 1, 0);

  VecSpecHis vecHisJets;
  AddHistogram(vecHisJets, "#it{p}_{T}^{jet} (GeV/#it{c})", "fHistJetPt", "jet-finder-hf-data/h_jet_pt", 1, 1, 0);
  AddHistogram(vecHisJets, "#phi", "fHistJetPhi", "jet-finder-hf-data/h_jet_phi", 1, 1, 0);
  AddHistogram(vecHisJets, "#eta", "fHistJetEta", "jet-finder-hf-data/h_jet_eta", 1, 1, 0);
  AddHistogram(vecHisJets, "#it{N}_{tracks}", "fHistJetNConstituents", "jet-finder-hf-data/h_jet_ntracks", 1, 1, 0);
  AddHistogram(vecHisJets, "#it{p}_{T}^{cand} (GeV/#it{c})", "fHistJetCandPt", "jet-finder-hf-data/h_D0_pt", 1, 1, 0);

  VecSpecHis vecHisJetSubstructure;
  AddHistogram(vecHisJetSubstructure, "#it{z}_{g}", "fHistJetZg", "jet-substructure-d0-data/h_jet_zg", 1, 0, 0);
  AddHistogram(vecHisJetSubstructure, "#it{R}_{g}", "fHistJetRg", "jet-substructure-d0-data/h_jet_rg", 1, 0, 0);
  AddHistogram(vecHisJetSubstructure, "#it{n}_{SD}", "fHistJetNsd", "jet-substructure-d0-data/h_jet_nsd", 1, 0, 0);

  VecSpecHis vecHisJetsMC;
  AddHistogram(vecHisJetsMC, "#it{p}_{T,det}^{jet} (GeV/#it{c})", "fHistJetPt", "jet-finder-hf-mcd/h_jet_pt", 1, 1, 0);
  AddHistogram(vecHisJetsMC, "#it{p}_{T,gen}^{jet} (GeV/#it{c})", "fHistJetPt_Part", "jet-finder-hf-mcp/h_jet_pt", 1, 1, 0);
  AddHistogram(vecHisJetsMC, "#phi_{det}", "fHistJetPhi", "jet-finder-hf-mcd/h_jet_phi", 1, 1, 0);
  AddHistogram(vecHisJetsMC, "#phi_{gen}", "fHistJetPhi_Part", "jet-finder-hf-mcp/h_jet_phi", 1, 1, 0);
  AddHistogram(vecHisJetsMC, "#eta_{det}", "fHistJetEta", "jet-finder-hf-mcd/h_jet_eta", 1, 1, 0);
  AddHistogram(vecHisJetsMC, "#eta_{gen}", "fHistJetEta_Part", "jet-finder-hf-mcp/h_jet_eta", 1, 1, 0);
  AddHistogram(vecHisJetsMC, "#it{N}_{tracks,det}", "fHistJetNConstituents", "jet-finder-hf-mcd/h_jet_ntracks", 1, 1, 0);
  AddHistogram(vecHisJetsMC, "#it{N}_{tracks,gen}", "fHistJetNConstituents_Part", "jet-finder-hf-mcp/h_jet_ntracks", 1, 1, 0);
  AddHistogram(vecHisJetsMC, "#it{p}_{T,det}^{cand} (GeV/#it{c})", "fHistJetCandPt", "jet-finder-hf-mcd/h_D0_pt", 1, 1, 0);
  AddHistogram(vecHisJetsMC, "#it{p}_{T,gen}^{cand} (GeV/#it{c})", "fHistJetCandPt_Part", "jet-finder-hf-mcp/h_D0_pt", 1, 1, 0);

  VecSpecHis vecHisJetSubstructureMC;
  AddHistogram(vecHisJetSubstructureMC, "#it{z}_{g,det}", "fHistJetZg", "jet-substructure-d0-mcd/h_jet_zg", 1, 0, 0);
  AddHistogram(vecHisJetSubstructureMC, "#it{z}_{g,gen}", "fHistJetZg_Part", "jet-substructure-d0-mcp/h_jet_zg", 1, 0, 0);
  AddHistogram(vecHisJetSubstructureMC, "#it{R}_{g,det}", "fHistJetRg", "jet-substructure-d0-mcd/h_jet_rg", 1, 0, 0);
  AddHistogram(vecHisJetSubstructureMC, "#it{R}_{g,gen}", "fHistJetRg_Part", "jet-substructure-d0-mcp/h_jet_rg", 1, 0, 0);
  AddHistogram(vecHisJetSubstructureMC, "#it{n}_{SD,det}", "fHistJetNsd", "jet-substructure-d0-mcd/h_jet_nsd", 1, 0, 0);
  AddHistogram(vecHisJetSubstructureMC, "#it{n}_{SD,gen}", "fHistJetNsd_Part", "jet-substructure-d0-mcp/h_jet_nsd", 1, 0, 0);

  // vector of specifications of vectors: name, VecSpecHis, pads X, pads Y
  VecSpecVecSpec vecSpecVecSpec;

  // Add vector specifications in the vector.
  if (options.Contains(" events "))
    vecSpecVecSpec.push_back(std::make_tuple("events", vecHisEvents, 4, 2));
  if (options.Contains(" tracks "))
    vecSpecVecSpec.push_back(std::make_tuple("tracks", vecHisTracks, 5, 3));
  if (options.Contains(" skim "))
    vecSpecVecSpec.push_back(std::make_tuple("skim", vecHisSkim, 5, 3));
  if (options.Contains(" cand2 "))
    vecSpecVecSpec.push_back(std::make_tuple("cand2", vecHisCand2, 5, 3));
  if (options.Contains(" cand3 "))
    vecSpecVecSpec.push_back(std::make_tuple("cand3", vecHisCand3, 5, 3));
  if (options.Contains(" d0 "))
    vecSpecVecSpec.push_back(std::make_tuple("d0", vecHisD0, 5, 3));
  if (options.Contains(" d0-mc "))
    vecSpecVecSpec.push_back(std::make_tuple("d0-mc", vecHisD0MC, 2, 2));
  if (options.Contains(" ds "))
    vecSpecVecSpec.push_back(std::make_tuple("ds", vecHisDs, 5, 3));
  if (options.Contains(" dplus "))
    vecSpecVecSpec.push_back(std::make_tuple("dplus", vecHisDPlus, 5, 4));
  if (options.Contains(" lc "))
    vecSpecVecSpec.push_back(std::make_tuple("lc", vecHisLc, 5, 3));
  if (options.Contains(" lc-mc-pt "))
    vecSpecVecSpec.push_back(std::make_tuple("lc-mc-pt", vecHisLcMCPt, 2, 2));
  if (options.Contains(" lc-mc-eta "))
    vecSpecVecSpec.push_back(std::make_tuple("lc-mc-eta", vecHisLcMCEta, 2, 2));
  if (options.Contains(" lc-mc-phi "))
    vecSpecVecSpec.push_back(std::make_tuple("lc-mc-phi", vecHisLcMCPhi, 2, 2));
  if (options.Contains(" lc-mc-prompt "))
    vecSpecVecSpec.push_back(std::make_tuple("lc-mc-prompt", vecHisLcMCPrompt, 5, 3));
  if (options.Contains(" lc-mc-nonprompt "))
    vecSpecVecSpec.push_back(std::make_tuple("lc-mc-nonprompt", vecHisLcMCNonPrompt, 5, 3));
  if (options.Contains(" jpsi "))
    vecSpecVecSpec.push_back(std::make_tuple("jpsi", vecHisJpsi, 5, 3));
  if (options.Contains(" jets-data "))
    vecSpecVecSpec.push_back(std::make_tuple("jets-data", vecHisJets, 5, 3));
  if (options.Contains(" jets-mc "))
    vecSpecVecSpec.push_back(std::make_tuple("jets-mc", vecHisJetsMC, 5, 3));
  if (options.Contains(" jets-substructure-data "))
    vecSpecVecSpec.push_back(std::make_tuple("jets-substructure-data", vecHisJetSubstructure, 5, 3));
  if (options.Contains(" jets-substructure-mc "))
    vecSpecVecSpec.push_back(std::make_tuple("jets-substructure-mc", vecHisJetSubstructureMC, 5, 3));

  return MakePlots(vecSpecVecSpec, pathFileO2, pathFileAli, pathListAli, doRatio);
}
