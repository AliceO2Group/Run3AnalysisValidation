import sys
from ROOT import TFile

for f in sys.argv[1:]:
    file = TFile.Open(f)
    print(f)
    list_parents = []
    map = file.Get("parentFiles")
    # map.Print()
    # Loop over data frames
    for key in map:
        # Get the parent file path
        # print(map.GetValue(key))
        list_parents.append(str(map.GetValue(key)))
    # Remove duplicities and sort
    print(len(list_parents))
    list_parents = list(dict.fromkeys(list_parents))
    list_parents.sort()
    # Print out list of parents
    for p in list_parents:
        print(p)
