"""
Script to extract data frames from AO2D.root files with information about parent files
"""

import sys
from ROOT import TFile, TObject  # pylint: disable=import-error

# print(f"Name of the script      : {sys.argv[0]=}")
# print(f"Arguments of the script : {sys.argv[1:]=}")

# DF range
df_first = 0
df_last = 0

for f in sys.argv[1:]:
    df_i = 0  # DF counter
    file_in = TFile.Open(f)
    file_out = TFile.Open(f.replace(".root", "_edit.root"), "recreate")
    for key in file_in.GetListOfKeys():
        key_name = key.GetName()
        obj = file_in.Get(key_name)
        if not obj:
            continue
        if key_name == "parentFiles":
            print(f"Writing object {key_name}")
            file_out.cd()
            res = obj.Write(key_name, TObject.kSingleKey)
            if not res:
                print(f"Failed to write {key_name}")
        # DF directory
        elif obj.ClassName() == "TDirectoryFile":
            if df_first <= df_i <= df_last:
                print(f"Writing object {key_name}")
                # Create the DF directory
                dir_obj = file_out.mkdir(key_name)
                if not dir_obj:
                    print(f"Failed to create dir {key_name}")
                dir_obj.cd()
                # Write trees in the DF directory
                for key_sub in obj.GetListOfKeys():
                    key_sub_name = key_sub.GetName()
                    obj_sub = obj.Get(key_sub_name)
                    if not obj_sub:
                        continue
                    print(f"Writing object {key_name}/{key_sub_name}")
                    if obj_sub.ClassName() == "TTree":
                        res = obj_sub.CloneTree().Write()
                    else:
                        res = obj_sub.Write()
                    if not res:
                        print(f"Failed to write {key_name}/{key_sub_name}")
            df_i += 1
