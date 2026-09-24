import os, sys, traceback, math

from . import node
sep = '::'

class IDLEnumValue(node.IDLNode):
    def __init__(self, value, parent):
        super(IDLEnumValue, self).__init__('IDLEnumValue', '', parent)
        self._verbose = True
        self._value = value
        self.basetype = ''

    def parse_blocks(self, blocks, filepath=None):
        self._filepath = filepath
        if len(blocks) == 1:
            self._name = blocks[0]
        else:
            for bi in range(len(blocks)):
                if (blocks[bi]=='@value'):
                    self._name = blocks[bi+4]
                    if '0x' in blocks[bi+2]:
                        self._value = int(blocks[bi+2],16)
                    else:
                        self._value = int(blocks[bi+2])
                    bi = bi + 3
                elif (blocks[bi]=='@doc'):
                    for i, b in enumerate(blocks[(bi+2):],start=bi+2):
                        if not b == ')':
                            self._des = self._des + ' ' + b.replace('\"','').replace("'",'')
                        else:
                            bi = i+1
                            self._des = self._des.replace(' ,',',')
                            self._des = self._des.strip()
                            break
                elif (len(blocks) - bi) == 1:
                    self._name = blocks[bi]
            #else:
            #    sys.stdout.write('Unkown Enum format %s\n' % blocks)
        #name, type = self._name_and_type(blocks)
        #self._name = name
        #self._type = type

    @property
    def full_path(self):
        return self.full_path + '.' + self.name

    def to_simple_dic(self):
        dic = {self.name : self.value }
        return dic

    def to_dic(self):
        dic = { 'name' : self.name,
                'filepath' : self.filepath,
                'classname' : self.classname,
                'value' : self.value }
        return dic
    @property
    def value(self):
        return self._value




class IDLEnum(node.IDLNode):

    def __init__(self, name, parent):
        super(IDLEnum, self).__init__('IDLEnum', name, parent)
        self._verbose = True
        self._values = []
        self.basetype = ''
        self.basesize = 0

    def to_simple_dic(self, quiet=False, full_path=False, recursive=False, member_only=False):
        name = self.full_path if full_path else self.name
        if quiet:
            return 'enum %s' % name
        dic = { 'enum %s' % name : [v.to_simple_dic() for v in self.values] }
        return dic


    def to_dic(self):
        dic = { 'name' : self.name,
                'classname' : self.classname,
                'values' : [v.to_dic() for v in self.values] }
        return dic

    @property
    def full_path(self):
        return self.parent.full_path + sep + self.name

    def _baseType(self):
        v_min = self.values[0].value
        v_max = v_min
        for v in self.values[1:]:
            if v.value < v_min:
                v_min = v.value
            elif v.value > v_max:
                v_max = v.value
        val_max = max(abs(v_min),abs(v_max))+1
        bit_count = math.log2(val_max)
        if v_min < 0:
            bit_count = bit_count+1
        byte_count = math.ceil(bit_count/8)
        if byte_count <= 1:
            self.basetype = 'int32_t'
        elif byte_count <= 2:
            self.basetype = 'int32_t'
        elif byte_count <= 4:
            self.basetype = 'int32_t'
        else:
            self.basetype = 'int32_t'
        self.basesize = self.cTypeSize[self.basetype]
        #self.basetype = self.cTypeDict[self.basetype]

    def parse_tokens(self, token_buf, filepath=None):
        self._filepath = filepath
        self._counter = 0
        ln, fn, kakko = token_buf.pop()
        if not kakko == '{':
            if self._verbose: sys.stdout.write('# Error. No kakko "{".\n')
            raise InvalidIDLSyntaxError()

        block_tokens = []
        while True:
            ln, fn, token = token_buf.pop()
            if token == None:
                if self._verbose: sys.stdout.write('# Error. No kokka "}".\n')
                raise InvalidIDLSyntaxError()

            elif token == '}':
                ln, fn, token = token_buf.pop()
                if not token == ';':
                    if self._verbose: sys.stdout.write('# Error. No semi-colon after "}".\n')
                    raise InvalidIDLSyntaxError()

                if len(block_tokens) > 0:
                    self._parse_block(block_tokens)
                    self._baseType()
                break
            elif token == '@doc':
                block_tokens.append(token)
                while not token == ')':
                    ln, fn, token = token_buf.pop()
                    block_tokens.append(token)
            elif token == ',':
                self._parse_block(block_tokens)
                block_tokens = []
                continue
            block_tokens.append(token)

    def _parse_block(self, blocks):
        v = IDLEnumValue(self._counter, self)
        v.parse_blocks(blocks, self.filepath)
        self._counter = v.value + 1
        self._values.append(v)

    @property
    def values(self):
        return self._values


    def value_by_name(self, name):
        for m in self.values:
            if m.name == name:
                return m
        return None
