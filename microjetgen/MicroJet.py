import os
import socket
import ipaddress
import socket
import binascii
from crc import Calculator, Configuration
from jinja2 import Environment, FileSystemLoader, select_autoescape
import math
import json
from idl_parser import parser
import shutil
import datetime
import shutil

class TopologicalSort:
    UNVISITED = 0
    VISITING = 1
    VISITED = 2

    def __init__(self, dependency_graph):
        self.dependency_graph = dependency_graph
        self.topological_order = []
        self.node_states = {}
        self.has_cycle = False

    def dfs(self, node):
        if self.node_states[node] == self.VISITING:
            self.has_cycle = True
            return
        if self.node_states[node] == self.UNVISITED:
            self.node_states[node] = self.VISITING
            for successor in self.dependency_graph.get(node, []):
                self.dfs(successor)
            self.node_states[node] = self.VISITED
            self.topological_order.append(node)

    def sort(self):
        for node in self.dependency_graph.keys():
            self.node_states[node] = self.UNVISITED

        for node in self.dependency_graph.keys():
            if self.node_states[node] == self.UNVISITED:
                self.dfs(node)

        self.topological_order.reverse()

        if self.has_cycle:
            return None  # A cycle was detected, indicating no valid topological order
        else:
            return self.topological_order

class MicroJet():
    def __init__(self, spec, idlPath, tmppath):
        self.idl_ver = '0'
        idl_ver_file = open(idlPath + '/version.txt','r',encoding='utf-8')
        if (idl_ver_file):
            self.idl_ver = idl_ver_file.readline()
            idl_ver_file.close()
        self.devs = spec['devices']
        self.msg = spec['msg']
        self.interfaces = spec['interfaces']
        self.spec = spec
        config16 = Configuration(
            width=16,
            polynomial=0x8BB7,
            init_value=0x00,
            final_xor_value=0xFFFF,
            reverse_input=False,
            reverse_output=False,
        )
        config8 = Configuration(
            width=8,
            polynomial=0x1D,
            init_value=0x00,
            final_xor_value=0xFF,
            reverse_input=False,
            reverse_output=False,
        )

        config32 = Configuration(
            width=32,
            polynomial=0x8BB7,
            init_value=0x00,
            final_xor_value=0xFFFF,
            reverse_input=False,
            reverse_output=False,
        )
        
        self.msgHashCalc = Calculator(config16)
        self.devIDCalc = Calculator(config16)
        self.prmIDCalc = Calculator(config32)
        
        self.required_if_parameters = {}
        for mj_if in self.interfaces:
            self.required_if_parameters[f"com_if_{mj_if}"] = ({"type":"string","unit":"-","if_name":mj_if})
        
        self.required_base_parameters = {f"dev_id":{"type":"int","unit":"-"}}
        
        
        self.spec['parameters'] = spec['parameters'] | self.required_if_parameters | self.required_base_parameters
        
        for dev in spec['devices']:
            out_if = self.outInterfaces(dev)
            in_if = self.inputInterfaces(dev)
            if (not self.spec['devices'][dev].get('parameters')):
                self.spec['devices'][dev]["parameters"] = {"dev_id":self.devHash(dev,True)}
            else:
                self.spec['devices'][dev]["parameters"] = self.spec['devices'][dev]["parameters"] | {"dev_id":self.devHash(dev,True)}
            for rp_if in self.required_if_parameters:
                if self.required_if_parameters[rp_if]["if_name"] in out_if or self.required_if_parameters[rp_if]["if_name"] in in_if:
                    self.spec['devices'][dev]["parameters"][rp_if] = spec['interfaces'][self.required_if_parameters[rp_if]["if_name"]]["IP"]+":"+str(spec['interfaces'][self.required_if_parameters[rp_if]["if_name"]]["port"])
        typesInc = ""
        for devName in self.devs:
            # try:
            #     os.mkdir(devName)
            # except OSError as error:
            #     None
            dev = self.devs[devName]
            for m in self.msg:
                typesInc = typesInc+'#include \"'+self.msg[m]['type']+'.idl\"\n'
            parser_ = parser.IDLParser()
            self.idl = parser_.load(typesInc,[idlPath])
        self.ver = '11'
        self.mver = '5'
        self.spec_name = spec["name"]
        self.spec_name_low = spec["name"].lower()
        self.spec_name_up = spec["name"].upper()
        self.spec_name_cap = spec["name"].capitalize()
        TemplateLoader = FileSystemLoader(os.path.abspath(tmppath))
        self.env = Environment(loader=TemplateLoader,autoescape=select_autoescape(
        enabled_extensions=('c', 'h','tex'),
        default_for_string=True,
        ))
        self.env.globals['binascii'] = binascii
        self.env.globals['hex'] = hex
        self.env.globals['len'] = len
        self.env.globals['gendate'] = str(datetime.datetime.now(datetime.datetime.now().astimezone().tzinfo).strftime("%d-%m-%y"))
        self.env.globals['sorted']=sorted
        self.env.trim_blocks = True
        self.env.globals['mj'] = self

    def get_active_structs(self,ex_flags):
        for m in self.get_active_msg(ex_flags):
            st = self.subTypes(self.msg[m]['type'])
        return list(set(st))
    
    def get_active_enums(self,ex_flags):
        for m in self.get_active_msg(ex_flags):
            en = self.enums(self.msg[m]['type'])
        return list(set(en))

    def get_active_dev(self,ex_flags):
        devs = {}
        for dev in self.spec['devices']:
            dev_flag = self.spec['devices'][dev].get('flag')
            if (not dev_flag) or (not any(x in ex_flags for x in dev_flag)):
                devs[dev] = self.spec['devices'][dev]
        return devs
    
    def get_active_msg(self,ex_flags):
        act_devs = self.get_active_dev(ex_flags)
        msgs = {}
        for dev in act_devs:
            dev_out_msg = self._get_dev_output_spec(dev)
            for msg in dev_out_msg:
                msg_flag = self.spec['msg'][msg].get('flag')
                if (not msg_flag) or (not any(x in ex_flags for x in msg_flag)):
                    msgs[msg] = self.spec['msg'][msg]
        return msgs
        
    def toCapitalize(self,s):
        return s.capitalize()
    
    def sortedEnums(self):
        return sorted(self.idl.enums, key=lambda x: x.basename, reverse=False)
    
    def sortedStruct(self):
        return sorted(self.idl.structs, key=lambda x: x.basename, reverse=False)
    
    def topSortedStruct(self):
        # dependency_graph = {}
        # for struct in self.sortedStruct():
        #     dependency_graph[struct.basename] = []
        #     for field in struct.members:
        #         if field.type.is_struct:
        #             if field.type in dependency_graph:  # Assuming all structs are known
        #                 dependency_graph[struct.basename].append(field.type)
        # for key, value in dependency_graph.items():
        #     dependency_graph[key] = list(set(value))  # Remove duplicates

        # topological_sort = TopologicalSort(dependency_graph)
        # sorted_structs = topological_sort.sort()

        return self.idl.structs
        
    
    def toUpper(self,s):
        return s.upper()

    def toLower(self,s):
        return s.lower()
    
    def topLvlTypes(self, dev):
        #o_msg = self.spec['devices'][dev]['out']
        #i_msg = self.spec['devices'][dev]['in']
        o_msg = self._get_dev_output_spec(dev)
        i_msg = self._get_dev_input_spec(dev)

        per = []
        for m in o_msg:
            if not self.msg[m]['type'] in per:
                per.append(self.msg[m]['type'])
        for m in i_msg:
            if not self.msg[m]['type'] in per:
                per.append(self.msg[m]['type'])
        return per

    def texEscape(self,str):
        return str.replace('_','\_').replace('^','\^{}').replace('+-','$\pm$')
    
    def luaEscape(self,str):
        return str.replace('.','_')
    
    def texLabel(self,str):
        return str.replace('_',':')

    def msgAlignPad(self,offset,type):
        s = self.idl.struct_by_name(type)
        return s.aligment - offset%s.aligment

    def msgSerialize(self,name,path):
        serList = self.structSerialize(name,path,0)
        return serList
    
    def round(self,val):
        return round(val)

    def getMsgPrioriry(self,msg_name:str):
        try:
            return self.msg[msg_name]['priority']
        except:
            return None

    def txPeriods(self,dev):
        #o_msg = self.spec['devices'][dev]['out']
        o_msg = self._get_dev_output_spec(dev)
        per = []
        for m in o_msg:
            tic_per = (self.msg[m]['period'])
            if not tic_per in per:
                per.append(tic_per)
        return sorted(per)

    def msgHash(self,name,path, dec = False):
        serList = self.structSerialize(name,path,0)
        hashStr = ''
        for e in serList:
            hashStr = hashStr+e['type']+str(e['size'])+e['path'].replace('.','')  
        hashVal = self.msgHashCalc.checksum(hashStr.encode())
        if dec:
            return hashVal
        else:
            return f'0x{hashVal:X}'

    def devHash(self,name, dec = False):
        hashVal = self.devIDCalc.checksum(name.encode())
        if dec:
            return hashVal
        else:
            return f'0x{hashVal:X}'
    
    def devPrms(self,dev):
        dev_prms = {}
        parent_dev = self.spec['devices'][dev].get('parent')
        if (parent_dev):
            dev_spec = dev_spec = self.spec['devices'][parent_dev]['parameters']
            child_param = self.spec['devices'][dev]['parameters']
            if child_param:
                dev_spec = dev_spec | child_param
        else:
            dev_spec = self.spec['devices'][dev]['parameters']
        for p in dev_spec:
            dev_prms[p] = self.spec['parameters'][p]['type']
        return dev_prms
    
    def prmHash(self,name):
        hashVal = self.prmIDCalc.checksum(name.encode())
        return f'0x{hashVal:X}'
    
    def prmStructHash(self,dev):
        dev_spec = self.spec['devices'][dev]['parameters']
        str = ''
        for p in dev_spec:
            str = str + p+dev_spec[p]["type"]+dev_spec[p]["unit"]+dev_spec[p]["type"]
        hashVal = self.prmIDCalc.checksum(str.encode())
        return f'0x{hashVal:X}'

    def align(self,offset, size):
        if offset > 0:
            if offset > size:
                offset =  math.ceil(offset / size)*size
            else:
                offset =  offset + (size - offset)
        return offset

    def subTypes(self,type,st=[]):
        s = self.idl.struct_by_name(type)
        for m in s.members:
            if m.type.is_struct:
                st.append(m.type.name)
                st = self.subTypes(m.type.name,st)
        return st

    def utf8_to_cp866_c_array(self,input_str):
        # Step 1: Encode the input string to CP866
        encoded_str = input_str.encode('cp866')
        str = ""
        str_len  = len(encoded_str)
        i = 0
        for byte in encoded_str:
            # Format each byte as hex and print. The format `02x` ensures two characters, padding with zero if necessary.
            str += '0x' + format(byte, '02x')
            i = i + 1
            if i != str_len:
                str+=','
            
        return str

    def enums(self,type,st=[]):
        s = self.idl.struct_by_name(type)
        for m in s.members:
            if m.type.is_struct:
                st = self.enums(m.type.name,st)
            elif m.type.is_enum:
                st.append(m.type.name)
            elif m.type.is_primitive:
                if (m._alias and self.idl.enum_by_name(m._alias)):
                    st.append(m._alias)
                
        return st

    def getStructByName(self,name):
        return self.idl.struct_by_name(name)

    def structSerialize(self,name,path,offset,des='',deep = 100000):
        serList = []
        s = self.idl.struct_by_name(name)
        delim = '.'
        if (len(path) > 0 and path[-1] == '>'):
            delim = ''
        for m in s.members:
            if m.type.is_struct:
                offset = self.align(offset,m.type.aligment)
                deep = deep - 1
                if (deep > 0):
                    serList = serList + self.structSerialize(m.type.name,path + delim +m.name,offset,m.des + ' ',deep)
                    offset = serList[-1]['offset'] + serList[-1]['size']
                else:
                    slist = self.structSerialize(m.type.name,path + delim +m.name,0,m.des + ' ',100000)
                    sz = slist[-1]['offset'] + slist[-1]['size']
                    serList.append({'type':m.type.name,'size':sz,'path':path+delim+m.name,'offset':offset,'des':des+m.des,'stype':'struct','alias':'','alias_type':''})
                    offset = offset + sz
            elif m.type.is_primitive:
                alias = m._alias
                if alias == '':
                    alias_type = ''
                else:
                    alias_type = 'enum'
                sz = m.type.basesize
                offset = self.align(offset,sz)
                serList.append({'type':m.type.name,'size':sz,'path':path+delim+m.name,'offset':offset,'des':des+m.des,'stype':'base','alias':alias,'alias_type':alias_type})
                offset = offset + sz
            elif m.type.is_enum:
                sz = m.type.basesize
                offset = self.align(offset,sz)
                serList.append({'type':m.type.name,'size':sz,'path':path+delim+m.name,'offset':offset,'des':des+m.des,'stype':'enum','alias':'','alias_type':''})
                offset = offset + sz
            elif m.type.is_array:
                if (m.type.type.is_primitive):
                    sz = m.type.type.basesize
                    offset = self.align(offset,sz)
                    serList.append({'type':m.type.name,'size':sz*m.type.size,'path':path+delim+m.name,'offset':offset,'des':des+m.des,'stype':'array','alias':'','alias_type':''})
                    offset = offset + sz*m.type.size
                else:
                    ar_st_el = self.idl.struct_by_name(m.type.type.basename)
                    offset = self.align(offset,ar_st_el.aligment)
                    deep = deep - 1
                    if (deep > 0):
                        serList = serList + self.structSerialize(m.type.type.basename,path + delim + m.name + '[0]',offset,m.des + ' ',deep)
                        offset = serList[-1]['offset'] + serList[-1]['size']
                    else:
                        slist = self.structSerialize(ar_st_el.name,path + delim +m.name,0,m.des + ' ',100000)
                        sz = slist[-1]['offset'] + slist[-1]['size']
                        serList.append({'type':m.type.type.basename,'size':sz,'path':path+delim+m.name,'offset':offset,'des':des+m.des,'stype':'struct','alias':'','alias_type':''})
                        offset = offset + sz
        return serList
    
    def struct2Dic(self,name,path, level = 0):
        serDic = {}
        s = self.idl.struct_by_name(name)
        if level == 0:
            spc = '->'
        else:
            spc = '.'
        for m in s.members:
            if m.type.is_struct:
                level = level + 1
                serDic[m.name] = self.struct2Dic(m.type.name,path + spc +m.name, level)
                serDic[m.name]['__path__'] = ''
                serDic[m.name]['__setpath__'] = ''
                serDic[m.name]['__cast__'] = ''
                serDic[m.name]['__convfcn__'] = ''
                serDic[m.name]['__values__'] = []
                serDic[m.name]['__data__'] = []
            elif m.type.is_primitive:
                if m._alias == '':
                    serDic[m.name] = {'__path__': path+spc+m.name}
                    serDic[m.name]['__cast__'] = m.type.basetype
                    serDic[m.name]['__setpath__'] = path+spc+m.name+'='+f'data.value<{m.type.basetype}>()'
                    serDic[m.name]['__convfcn__'] = ''
                    serDic[m.name]['__values__'] = []
                    serDic[m.name]['__data__'] = []
                else:
                    if 'PRM_ID_FROM_SPEC' in m._alias:
                        alias = self.spec_name_low + '_prm_id'
                        serDic[m.name] = {'__path__': '(int32_t)('+path+spc+m.name+')'}
                        serDic[m.name]['__cast__'] = 'int32_t'
                        serDic[m.name]['__convfcn__'] = 'mj_get_prm_name('+path+spc+m.name+')'
                        serDic[m.name]['__setpath__'] = path+spc+m.name+'=('+m.type.basetype+')(data.value<int32_t>())'
                        prms_val = self.parameters()
                        serDic[m.name]['__values__'] = []
                        serDic[m.name]['__data__'] = []
                        for p in prms_val:
                            serDic[m.name]['__values__'].append(p)
                            serDic[m.name]['__data__'].append(prms_val[p]['id'])
                    elif 'MSG_ID_FROM_SPEC' in m._alias:
                        alias = self.spec_name_low+'_msg_id'
                        serDic[m.name] = {'__path__': '(int32_t)('+path+spc+m.name+')'}
                        serDic[m.name]['__values__'] = []
                        serDic[m.name]['__data__'] = []
                        serDic[m.name]['__cast__'] = 'int32_t'
                        serDic[m.name]['__convfcn__'] = 'mj_get_msg_name('+path+spc+m.name+')'
                    else:
                        alias = m._alias
                        enum = self.idl.enum_by_name(alias)
                        serDic[m.name] = {'__path__': '(int32_t)('+path+spc+m.name+')'}
                        serDic[m.name]['__cast__'] = 'int32_t'
                        serDic[m.name]['__convfcn__'] = alias + '_str('+path+spc+m.name+')'
                        serDic[m.name]['__setpath__'] = path+spc+m.name+'=('+m.type.basetype+')(data.value<int32_t>())'
                        serDic[m.name]['__values__'] = []
                        serDic[m.name]['__data__'] = []
                        for i in range(0,len(enum.values)):
                            serDic[m.name]['__values__'].append(enum.values[i].name)
                            serDic[m.name]['__data__'].append(enum.values[i].value)
            elif m.type.is_enum:
                serDic[m.name] = {'__path__': '(int32_t)('+path+spc+m.name+')'}
                serDic[m.name]['__cast__'] = 'int32_t'
                serDic[m.name]['__convfcn__'] = m.type.basename+'_str('+path+spc+m.name+')'
                serDic[m.name]['__values__'] = []
                serDic[m.name]['__data__'] = []
                serDic[m.name]['__setpath__'] = path+spc+m.name+'=('+m.type.basename+')(data.value<int32_t>())'
                for i in range(0,len(m.type.values)):
                    serDic[m.name]['__values__'].append(m.type.values[i].name)
                    serDic[m.name]['__data__'].append(m.type.values[i].value)
            elif m.type.is_array:
                if 'char' in m.type.basename:
                    if m._alias == 'FROM_PRM_SPEC':
                        serDic[m.name] = {'__path__': 'prm2QVariant('+path+spc+'id,(uint8_t*)'+path+spc+m.name+',sizeof('+path+spc+m.name+'))'}
                        serDic[m.name]['__cast__'] = []
                        serDic[m.name]['__setpath__'] = 'QVariant2prm('+path+spc+'id,(uint8_t*)'+path+spc+m.name+',sizeof('+path+spc+m.name+'),data)'
                        serDic[m.name]['__convfcn__'] = ''
                        serDic[m.name]['__values__'] = []
                        serDic[m.name]['__data__'] = []
                    else:
                        serDic[m.name] = {'__path__': 'cp866ToQString('+path+spc+m.name+',sizeof('+path+spc+m.name+'))'}
                        serDic[m.name]['__setpath__'] = 'memcpy('+path+spc+m.name+',data.value<QString>().toStdString().c_str(),'+f'{m.type.size})';
                        serDic[m.name]['__cast__'] = 'QString'
                        serDic[m.name]['__convfcn__'] = ''
                        serDic[m.name]['__values__'] = []
                        serDic[m.name]['__data__'] = []
                else:
                    serDic[m.name] = {'__path__': '','__cast__':'','__convfcn__':'','__values__':[]}
                    if m.type.type.is_primitive:
                        for ind in range(m.type.size):
                            cast_type = m.type.basename.split(' ')[0]
                            serDic[m.name][f'[{ind}]'] = {'__path__': path+spc+m.name+f'[{ind}]','__cast__':cast_type,'__convfcn__':''}
                            serDic[m.name][f'[{ind}]']['__setpath__'] = path+spc+m.name+f'[{ind}]'+'='+f'data.value<{cast_type}>()'
                            serDic[m.name][f'[{ind}]']['__path__']+'='
                            serDic[m.name][f'[{ind}]']['__values__'] = []
                            serDic[m.name]['__data__'] = []
                    else:
                        level = level + 1
                        for ind in range(m.type.size):
                            cast_type = m.type.basename.split(' ')[0]
                            serDic[m.name][f'[{ind}]'] = self.struct2Dic(m.type.basename.split(' ')[0] ,path + spc + m.name +f'[{ind}]', level)
                            serDic[m.name][f'[{ind}]']['__path__'] = ''
                            serDic[m.name][f'[{ind}]']['__setpath__'] = ''
                            serDic[m.name][f'[{ind}]']['__cast__'] = ''
                            serDic[m.name][f'[{ind}]']['__convfcn__'] = ''
                            serDic[m.name][f'[{ind}]']['__values__'] = []
                            serDic[m.name][f'[{ind}]']['__data__'] = []
        return serDic

    def ip4Convert(self,strAdr):
        return hex(socket.htonl(int(ipaddress.IPv4Address(strAdr))))

    def portConvert(self,port):
        return hex(socket.htons(port))

    def createComTable(self,targetFolder,gv):
        ctmp = self.env.get_template("profile.tex.j2")
        code = ctmp.render()
        try:
            os.mkdir(targetFolder)
        except OSError as error:
            None
        clib = open(targetFolder+'/comtable.tex','w',encoding="utf-8")
        clib.write(code)
        clib.close()
        msgtmp = self.env.get_template("msgspec.tex.j2")
        msg = msgtmp.render()
        tmpf = open(targetFolder+'/msgspec.tex','w',encoding="utf-8")
        tmpf.write(msg)
        tmpf.close()

        typetmp = self.env.get_template("types.tex.j2")
        typestr = typetmp.render()
        tmpf = open(targetFolder+'/types.tex','w',encoding="utf-8")
        tmpf.write(typestr)
        tmpf.close()

        entmp = self.env.get_template("enums.tex.j2")
        typestr = entmp.render()
        tmpf = open(targetFolder+'/enums.tex','w',encoding="utf-8")
        tmpf.write(typestr)
        tmpf.close()

        titletmp = self.env.get_template("title.tex.j2")
        titlestr = titletmp.render(global_ver = gv)
        tmpf = open(targetFolder+'/title.tex','w',encoding="utf-8")
        tmpf.write(titlestr)
        tmpf.close()
        
        titletmp = self.env.get_template("parameters.tex.j2")
        titlestr = titletmp.render(global_ver = gv)
        tmpf = open(targetFolder+'/parameters.tex','w',encoding="utf-8")
        tmpf.write(titlestr)
        tmpf.close()

    def structDes(self,type):
        s = self.idl.struct_by_name(type)
        return s.des

    def enumDes(self,type):
        s = self.idl.enum_by_name(type)
        return s.des

    def enumElements(self,type):
        enum = self.idl.enum_by_name(type)
        return enum.values
    
    def interfaces(self):
        return self.spec['interfaces']
    
    def inputInterfaces(self,dev):
        dev_spec = self._get_dev_input_spec(dev)
        intList = set()
        for m in dev_spec:
            interface = self.msg[m]['transport']
            intList.add(interface)
        return intList
    
    def outInterfaces(self,dev):
        #dev_spec = self.spec['devices'][dev]['out']
        dev_spec = self._get_dev_output_spec(dev)
        intList = set()
        for m in dev_spec:
            interface = self.msg[m]['transport']
            intList.add(interface)
        return intList
    
    def allInterfaces(self,dev):
        return sorted(self.inputInterfaces(dev) | self.outInterfaces(dev))
    
    def allActiveInterfaces(self,ex_flags):
        act_msg = self.get_active_msg(ex_flags)
        act_if = set()
        for msg in act_msg:
            act_if.add(act_msg[msg]['transport'])
        return act_if
        
    def allGroupAddr(self,ex_flags):
        act_int = self.allActiveInterfaces(ex_flags)
        addr_list = set()
        for g_if in act_int:
            addr_list.add(self.spec['interfaces'][g_if]['IP'])
        return addr_list
    
    def parameters(self):
        prmList = dict()
        if ('parameters' in self.spec):
            prm_spec = self.spec['parameters']
            for p in prm_spec:
                prmList[p]= {'id':self.prmHash(p+self.spec['parameters'][p]["type"]+self.spec['parameters'][p]["unit"]),'type':self.spec['parameters'][p]["type"]}
        return prmList
    
    def toTexUnit(self,str):
        if str == "-":
            return ""
        elif str == "V":
            return "$ \\text{В} $"
        elif str == "V^2":
            return "$ \\text{В}^2 $"
        elif str == "A":
            return "$ \\text{А} $"
        elif str == "A^2":
            return "$ \\text{А}^2 $"
        elif str == "s":
            return "$ \\text{с} $"
        elif str == "ms":
            return "$ \\text{мс} $"
        elif str == "rad":
            return "$ \\text{рад} $"
        elif str == "rad^2":
            return "$ \\text{рад}^2 $"
        elif str == "1/s":
            return "$ \\text{c}^{-1} $"
        elif str == "rad/s^2":
            return "$ {\\text{рад}}/{\\text{c}^2} $"
        elif str == "(rad/s)/V":
            return "$ \\frac{\\text{рад}}{\\text{В}\\cdot\\text{с}} $"
        elif str == "rad/s":
            return "$ \\text{рад}/\\text{с} $"
        elif str == "(rad/s)^2":
            return "$ \\text{рад}^2/\\text{с}^2 $"
        elif str == "kg/m^2":
            return "$ \\text{кг}/\\text{м}^2 $"
        elif str == "N*m/(rad/s)":
            return "$ \\frac{\\text{Н}\\cdot\\text{м}}{\\text{рад}/\\text{с}} $"
        elif str == "N*m":
            return "$ \\text{Н}\\cdot\\text{м} $"
        elif str == "(N*m)^2":
            return "$ \\text{Н}^2\\cdot\\text{м}^2 $"
        elif str == "N*m/A":
            return "$ \\frac{\\text{Н}\\cdot\\text{м}}{\\text{А}} $"
        elif str == "Om":
            return "$ \\text{Ом} $"
        elif str == "mH":
            return "$ \\text{мГн} $"
        elif str == "(rad/s)/V":
            return "$ \\frac{\\text{рад}/\\text{с}}{\\text{В}} $"
        elif str == "V/(rad/s)":
            return "$ \\frac{\\text{В}}{\\text{рад}/\\text{с}} $"
        elif str == "V/(rad*s)":
            return "$ \\frac{\\text{В}}{\\text{рад}\\cdot\\text{с}} $"
        elif str == "pixels":
            return "$ px $"
        elif str == "px":
            return "$ px $"
        elif str == "m":
            return "$ \\text{м} $"
        elif str == "m/s":
            return "$ \\text{м}/\\text{с} $"
        elif str == "m/s^2":
            return "$ \\text{м}/\\text{с}^2 $"
        else:
            return self.texEscape(str)
    
    def compactVal(self,val,type):
        if type != 'string':
            return "%.6g" % val
        return val
    
    def getParamTypeSize(self,type=str):
        if type == "bool":
            return 1
        elif type == "int":
            return 4
        elif type == "float":
            return 4
        elif type == "string":
            return 32
        else:
            return -1
        
    def dev_parameters(self, dev):
        dev_prm = dict()
        parent = self.spec['devices'][dev].get('parent')

        if (parent):
            parent_prms = self.spec['devices'][parent]['parameters'].copy()
            child_prms = self.spec['devices'][dev]['parameters']
            if (child_prms):
               child_prms = child_prms | parent_prms 
            for p in child_prms:
                prm_val = None
                try:
                    prm_val = self.spec['devices'][dev]['parameters'][p]
                except:
                    prm_val = self.spec['devices'][parent]['parameters'][p]
                dev_prm[p] = {'id':self.prmHash(p+self.spec['parameters'][p]["type"]+self.spec['parameters'][p]["unit"]),'type':self.spec['parameters'][p]["type"],'val':prm_val}
        elif ('parameters' in self.spec['devices'][dev]):
            dev_spec = self.spec['devices'][dev]['parameters']
            for p in dev_spec:
                prm_val = self.spec['devices'][dev]['parameters'][p]
                dev_prm[p] = {'id':self.prmHash(p+self.spec['parameters'][p]["type"]+self.spec['parameters'][p]["unit"]),'type':self.spec['parameters'][p]["type"],'val':prm_val}
                    
        return dev_prm

    def msgTypes(self,dev = None):
        types = set()
        if (dev):
            dev_spec = self._get_dev_input_spec(dev)
            for m in dev_spec:
                types.add(self.spec['msg'][m]['type'])
            dev_spec = self._get_dev_output_spec(dev)
            for m in dev_spec:
                types.add(self.spec['msg'][m]['type'])
        else:
            for m in self.spec['msg']:
                types.add(self.spec['msg'][m]['type'])
        return sorted(types)
    
    def msgSources(self,m,_dev):
        src = set()
        alias = m
        try: 
            alias = self.spec['devices'][_dev]['in'][m]['proto']
        except:
            None
        for dev in self.spec['devices']:
            if _dev != dev:
                #to revert rm str below
                devout = self._get_dev_output_spec(dev)
                #if alias in self.spec['devices'][dev]['out']:
                if alias in devout:
                    src.add(dev)
        return sorted(src)
    
    def inputDev(self,_dev):
        dev_spec = self._get_dev_input_spec(_dev)
        in_dev = set()
        for m in dev_spec:
            alias = m
            try:
                alias = self.spec['devices'][_dev]['in'][m]['proto']
            except:
                None
            for dev in self.spec['devices']:
                if dev != _dev:
                    #to revert rm str below
                    devout = self._get_dev_output_spec(dev)
                    #if alias in self.spec['devices'][dev]['out']:
                    if alias in devout:
                        in_dev.add(dev)
        return in_dev
    
    def _get_dev_input_spec(self,dev):
        parent = self.spec['devices'][dev].get('parent')
        if parent:
            dev_spec = self.spec['devices'][parent]['in'].copy()
            child_in = self.spec['devices'][dev].get('in')
            if (child_in):
                for ch_in_msg in child_in:
                    proto_msg = self.spec['devices'][dev]['in'][ch_in_msg].get("proto")
                    if (proto_msg):
                        del dev_spec[proto_msg]
                dev_spec = dev_spec | child_in
        else:
            dev_spec = self.spec['devices'][dev]['in']
        return dev_spec
    
    def _get_dev_output_spec(self,dev):
        parent = self.spec['devices'][dev].get('parent')
        if parent:
            dev_spec = self.spec['devices'][parent]['out'].copy()
            child_out = self.spec['devices'][dev].get('out')
            if (child_out):
                for ch_out_msg in child_out:
                    proto_msg = self.spec['devices'][dev]['out'][ch_out_msg].get("proto")
                    if (proto_msg):
                        del dev_spec[proto_msg]
                dev_spec = dev_spec | child_out
        else:
            dev_spec = self.spec['devices'][dev]['out']
        return dev_spec
    
    def inputMsg(self,dev,dev_src):
        
        dev_spec = self._get_dev_input_spec(dev)
        dev_src_spec = self._get_dev_output_spec(dev_src)
        in_msg = set()
        for m in dev_spec:
            alias = m
            try: 
                alias = self.spec['devices'][dev]['in'][m]['proto']
            except:
                None
            if alias in dev_src_spec:
                in_msg.add(m)
        return in_msg
    
    def creatFolderWoExept(self,folder):
        try:
            os.mkdir(folder)
        except OSError as error:
            None
    
    def rmFolderWoExept(self,folder):
        shutil.rmtree(folder, ignore_errors=False, onerror=None)

    def createComLib(self,_targetFolder, gv):
        spec_h_tmp = self.env.get_template("system_spec.h.j2")
        dev_spec_h_tmp = self.env.get_template("mj_dev_spec.h.j2")
        dev_spec_c_tmp = self.env.get_template("mj_dev_spec.c.j2")
        sys_spec_lua_tmp = self.env.get_template("desector.lua.j2")
        # self.rmFolderWoExept(_targetFolder + '/src')
        # self.rmFolderWoExept(_targetFolder + '/inc')

        # self.creatFolderWoExept(_targetFolder + '/src')
        # self.creatFolderWoExept(_targetFolder + '/inc')
        # self.creatFolderWoExept(_targetFolder + '/src/target')
        # self.creatFolderWoExept(_targetFolder + '/src/monitor')
        spec_h_code = spec_h_tmp.render(gver = gv)
        targetFolder = _targetFolder
        self.creatFolderWoExept(targetFolder)
        self.creatFolderWoExept(targetFolder + '/inc/')
        self.creatFolderWoExept(targetFolder + '/src/')
        spec_h = open(targetFolder + '/inc/' + 'mjsysspec.h','w',encoding="utf-8")
        spec_h.write(spec_h_code)
        spec_h.close()

        for dev in sorted(self.spec['devices']):
            try:
                if 'no_lib' in self.spec['devices'][dev]['flag']:
                    continue
            except:
                None
            dev_targetFolder = targetFolder +'/' + dev
            self.creatFolderWoExept(dev_targetFolder)
            # self.creatFolderWoExept(dev_targetFolder + '/src')
            # self.creatFolderWoExept(dev_targetFolder + '/inc')

            dev_spec_h_code = dev_spec_h_tmp.render(dev_name = dev, spec = self.spec['devices'][dev])
            dev_spec_h = open(f"{dev_targetFolder}/mj_{dev}_spec.h",'w')
            dev_spec_h.write(dev_spec_h_code)
            dev_spec_h.close()

            dev_spec_c_code = dev_spec_c_tmp.render(dev_name = dev, spec = self.spec['devices'][dev], in_int = sorted(self.inputInterfaces(dev)), msgs = sorted(self.msgTypes(dev)))
            dev_spec_c = open(f"{dev_targetFolder}/mj_{dev}_spec.c",'w')
            dev_spec_c.write(dev_spec_c_code)
            dev_spec_c.close()

        # self.creatFolderWoExept(targetFolder + '/wireshark/')
        # spec_lua_code = sys_spec_lua_tmp.render(gver = gv)
        # spec_lua = open(targetFolder + '/wireshark/' + self.spec_name_low + '.lua','w',encoding="utf-8")
        # spec_lua.write(spec_lua_code)
        # spec_lua.close()
        # for dev in sorted(self.spec['devices']):
            # code = ctmp.render(spec = self.spec['devices'][dev],in_int = sorted(self.inputInterfaces(dev)), msgs = sorted(self.msgTypes(dev)),dev_name = dev)
            # htmp = self.env.get_template("microjet.h.j2")
            # head = htmp.render(spec = self.spec['devices'][dev],msgs = sorted(self.msgTypes(dev)),dev_name = dev)
            
            # targetFolder = _targetFolder + '/src/target' + f'/{dev}'
            # self.creatFolderWoExept(targetFolder)

            # clib = open(targetFolder +'/microjet.c','w')
            # clib.write(code)
            # clib.close()

            # self.creatFolderWoExept(targetFolder)

            # hlib = open(targetFolder+'/microjet.h','w')
            # hlib.write(head)
            # hlib.close()

        self.createTypes(targetFolder)


        #self.createQtLib(_targetFolder)

    def createQtLib(self,_targetFolder):
        ctmp = self.env.get_template("signaltree.cpp.j2")
        htmp = self.env.get_template("signaltree.h.j2")
        for dev in self.spec['devices']:
            code = ctmp.render(spec = self.spec['devices'][dev],in_int = sorted(self.inputInterfaces(dev)),msgs = sorted(self.msgTypes(dev)),dev_name = dev,com_header_file = "microjet.h")
            targetFolder = _targetFolder +'/qt/' + dev
            self.creatFolderWoExept(_targetFolder +'/qt/')
            self.creatFolderWoExept(targetFolder)
            clib = open(targetFolder + '/' + 'signaltree.cpp','w',encoding="utf-8")
            clib.write(code)
            clib.close()

            hcode = htmp.render(spec = self.spec['devices'][dev],in_int = sorted(self.inputInterfaces(dev)),msgs = sorted(self.msgTypes(dev)),dev_name = dev)
            hlib = open(targetFolder + '/' + 'signaltree.h','w',encoding="utf-8")
            hlib.write(hcode)
            hlib.close()


    def createTypes(self,targetFolder):
        try:
            os.mkdir(targetFolder)
        except OSError as error:
            None
        htmp = self.env.get_template("microjettypes.h.j2")
        ctmp = self.env.get_template("microjettypes.c.j2")
        types = htmp.render()
        ftypes = open(targetFolder+'/inc/' + 'mjtypes.h','w',encoding="utf-8")
        ftypes.write(types)
        ftypes.close()

        typesc = ctmp.render()
        ftypesc = open(targetFolder+'/src/' + 'mjtypes.c','w',encoding="utf-8")
        ftypesc.write(typesc)
        ftypesc.close()

        htmp = self.env.get_template("microjetutils.h.j2")
        hutils = htmp.render()
        ftypes = open(targetFolder + '/inc/' + 'mjutils.h','w',encoding="utf-8")
        ftypes.write(hutils)
        ftypes.close()

        ctmp = self.env.get_template("microjetutils.c.j2")
        cutils = ctmp.render()
        ftypes = open(targetFolder + '/src/' +  'mjutils.c','w',encoding="utf-8")
        ftypes.write(cutils)
        ftypes.close()
        
        shutil.copyfile(os.path.realpath(os.path.dirname(__file__)) + '/inc/microjet.h',targetFolder + '/inc/' + 'microjet.h')
        shutil.copyfile(os.path.realpath(os.path.dirname(__file__)) + '/inc/microjet_def.h',targetFolder + '/inc/' + 'microjet_def.h')
        shutil.copyfile(os.path.realpath(os.path.dirname(__file__)) + '/inc/mjdriver_interface.h',targetFolder + '/inc/' + 'mjdriver_interface.h')