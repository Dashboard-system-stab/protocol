import os,sys,argparse
import json
from idl_parser import parser

from MicroJet import MicroJet

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument ('--idl', default='./')
    parser.add_argument ('--template', default='./')
    parser.add_argument ('--ppath', default='./')
    parser.add_argument ('--tex',action='store_true')
    parser.add_argument ('--lib',action='store_true')
    parser.add_argument ('--qt',action='store_true')
    parser.add_argument ('-s','--spec')
    parser.add_argument ('--ver', default='0')
    ns = parser.parse_args (sys.argv[1:])
    fspec = open(ns.spec)
    spec = json.load(fspec)
    fspec.close()
    cc = MicroJet(spec,ns.idl,ns.template)
    if ns.tex == True:
        cc.createComTable(ns.ppath,ns.ver)
    if ns.lib == True:
        cc.createComLib(ns.ppath,ns.ver)
    if ns.qt == True:
        cc.createQtLib(ns.ppath)
