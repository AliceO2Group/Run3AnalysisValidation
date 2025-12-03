#!/bin/bash
# shellcheck disable=SC2034 # Ignore unused parameters.

DATABASE_O2="workflows_run5.yml"  # Workflow specification database

# Activation of O2 workflows
DOO2_CAND_X=0       # hf-candidate-creator-x
DOO2_CAND_CHIC=0    # hf-candidate-creator-chic
DOO2_CAND_XICC=0    # hf-candidate-creator-xicc
# Selectors
DOO2_SEL_JPSI=0     # hf-candidate-selector-jpsi
DOO2_SEL_X=0        # hf-candidate-selector-x-to-jpsi-pi-pi
DOO2_SEL_CHIC=0     # hf-candidate-selector-chic-to-jpsi-gamma
DOO2_SEL_XICC=0     # hf-candidate-selector-xicc-to-p-k-pi-pi
# Analysis tasks
DOO2_TASK_JPSI=0    # hf-task-jpsi
DOO2_TASK_X=0       # hf-task-x
DOO2_TASK_CHIC=0    # hf-task-chic
DOO2_TASK_XICC=0    # hf-task-xicc
# Tree creators
DOO2_TREE_X=0       # hf-tree-creator-x-to-jpsi-pi-pi
DOO2_TREE_CHIC=0    # hf-tree-creator-chic-to-jpsi-gamma
DOO2_TREE_XICC=0    # hf-tree-creator-xicc-to-p-k-pi-pi
# QA
DOO2_REJ_ALICE3=0   # hf-task-qa-pid-rejection

# Selection cuts
APPLYCUTS_JPSI=0    # Apply J/ψ selection cuts.
APPLYCUTS_X=0       # Apply X selection cuts.
APPLYCUTS_CHIC=0    # Apply χc(1p) selection cuts.
APPLYCUTS_XICC=0    # Apply Ξcc selection cuts.

####################################################################################################

# Modify the JSON file.
function AdjustJson {
  # Enable J/ψ selection.
  if [ $APPLYCUTS_JPSI -eq 1 ]; then
    MsgWarn "Using J/ψ selection cuts"
    ReplaceString "\"selectionFlagJpsi\": \"0\"" "\"selectionFlagJpsi\": \"1\"" "$JSON" || ErrExit "Failed to edit $JSON."
  fi

  # Enable X(3872) selection.
  if [ $APPLYCUTS_X -eq 1 ]; then
    MsgWarn "Using X(3872) selection cuts"
    ReplaceString "\"selectionFlagX\": \"0\"" "\"selectionFlagX\": \"1\"" "$JSON" || ErrExit "Failed to edit $JSON."
  fi

  # Enable χc(1p) selection.
  if [ $APPLYCUTS_CHIC -eq 1 ]; then
    MsgWarn "Using χc(1p) selection cuts"
    ReplaceString "\"selectionFlagChic\": \"0\"" "\"selectionFlagChic\": \"1\"" "$JSON" || ErrExit "Failed to edit $JSON."
  fi

  # Enable Ξcc selection.
  if [ $APPLYCUTS_XICC -eq 1 ]; then
    MsgWarn "Using Ξcc selection cuts"
    ReplaceString "\"selectionFlagXicc\": \"0\"" "\"selectionFlagXicc\": \"1\"" "$JSON" || ErrExit "Failed to edit $JSON."
  fi
}

# Generate the O2 script containing the full workflow specification.
function MakeScriptO2 {
  WORKFLOWS=""
  # Vertexing
  [ $DOO2_CAND_X -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-candidate-creator-x"
  [ $DOO2_CAND_CHIC -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-candidate-creator-chic"
  [ $DOO2_CAND_XICC -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-candidate-creator-xicc"
  # Selectors
  [ $DOO2_SEL_JPSI -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-candidate-selector-jpsi${SUFFIX_RUN}"
  [ $DOO2_SEL_X -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-candidate-selector-x-to-jpsi-pi-pi"
  [ $DOO2_SEL_CHIC -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-candidate-selector-chic-to-jpsi-gamma"
  [ $DOO2_SEL_XICC -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-candidate-selector-xicc-to-p-k-pi-pi"
  # Analysis tasks
  [ $DOO2_TASK_JPSI -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-task-jpsi"
  [ $DOO2_TASK_X -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-task-x"
  [ $DOO2_TASK_CHIC -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-task-chic"
  [ $DOO2_TASK_XICC -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-task-xicc"
  # Tree creators
  [ $DOO2_TREE_X -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-tree-creator-x-to-jpsi-pi-pi"
  [ $DOO2_TREE_CHIC -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-tree-creator-chic-to-jpsi-gamma"
  [ $DOO2_TREE_XICC -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-tree-creator-xicc-to-p-k-pi-pi"
  # QA
  [ $DOO2_REJ_ALICE3 -eq 1 ] && WORKFLOWS+=" o2-analysis-hf-task-qa-pid-rejection"
}

function MakeScriptPostprocess {
  # Compare AliPhysics and O2 histograms.
  [[ $DOALI -eq 1 && $DOO2 -eq 1 ]] && {
    OPT_COMPARE=""
    [ $DOO2_TASK_JPSI -eq 1 ] && OPT_COMPARE+=" jpsi "
  }
  # Plot particle reconstruction efficiencies.
  [[ $DOO2 -eq 1 && $INPUT_IS_MC -eq 1 ]] && {
    PARTICLES=""
    [ $DOO2_TASK_JPSI -eq 1 ] && PARTICLES+=" jpsi "
    [ $DOO2_TASK_XICC -eq 1 ] && PARTICLES+=" xicc-mc "
  }
}
