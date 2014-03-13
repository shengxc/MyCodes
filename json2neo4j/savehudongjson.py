# -*- coding:utf-8 -*-
'''
@auther: sxc
@date:   20140228
@function:
  read hudongbaike infobox json files and save them to
  neo4j database
'''
import json
import os
import re
from neo4jrestclient.client import GraphDatabase
gdb = GraphDatabase("http://localhost:7474/db/data/")
fout = open("run.log","a")
'''
replacemap = {u'0':u'零',u'1':u'一',u'2':u'二',u'3':u'三',u'4':u'四',u'5':u'五',u'6':u'六',u'7':u'七',u'8':u'八',u'9':u'九',u'"':u'',u'（':u'',u'）':u'',u'“':u'',u'”':u'',u'-':u''}
def makedictrepl(inputdict):
  rx = re.compile('|'.join(inputdict))
  def eachrepl(match):
    return inputdict[match.group(0)]
  def repl(text):
    return rx.sub(eachrepl,text)
  return repl
typereplacefunc = makedictrepl(replacemap)
def dealtype(elemtype):
  elemtype = elemtype.strip()
  res = elemtype.replace(u".",u"")    #delete . character in type
  res = typereplacefunc(elemtype)
  if elemtype != res:
    fout.write(("typechange:" + elemtyp + "-->" + res + "\n").encode("utf-8"))
    fout.flush()
  return res
'''
def dealname(nodename):
  nodename = nodename.strip()
  res = nodename.replace("\\",",").replace('"','\\"')
  if nodename != res:
    fout.write(("nodenamechanged:" + nodename + "-->" + res + "\n").encode("utf-8"))
    fout.flush()
  return res

def execute(query):
  try:
    return gdb.query(query)
  except Exception,e:
    print "wrong:\t",query
    pass

def addnode(nodetype,nodename):
  assert(nodetype == 'ENTITY' or nodetype == 'CATEGORY')
  def isexist(nodetype,nodename):
    testexistquery = '''match (n:%s {name:"%s"}) return count(n)''' % (nodetype,nodename)
    res = execute(testexistquery)
    return res[0][0] > 0
  if not isexist(nodetype,nodename):
    addnodequery = '''create (n:%s {name:"%s"})''' % (nodetype,nodename)
    execute(addnodequery)

def addrel(nodename1,nodename2,reltype,relname=None):
  assert(reltype == 'PROPERTY' or reltype == 'CATEGORY')
  if reltype == 'PROPERTY':
    addrelquery = '''match (ent:ENTITY {name:"%s"}),(att:ENTITY {name:"%s"}) create ent-[:%s {name:"%s"}]->att''' % (nodename1,nodename2,reltype,relname)
  else:
    addrelquery = '''match (ent:ENTITY {name:"%s"}),(cate:CATEGORY {name:"%s"}) create ent-[:%s]->cate''' % (nodename1,nodename2,reltype)
  execute(addrelquery)

hudongfilename = "/media/sxc/Seagate Backup Plus Drive/EncyclopediaData/hudongbaikeknowledgesmerge.json"
with open(hudongfilename) as inputfile:
  items = json.load(inputfile)
for item in items:
  entry = dealname(item["entry"])       #unicode
  categories = item["categories"]     #list
  infobox = item["infobox"]           #dict
  for cate in categories:
    cate = dealname(cate)
    if cate == "":
      continue
    addnode("ENTITY",entry)
    addnode("CATEGORY",cate)
    addrel(entry,cate,"CATEGORY")
  for prop,value in infobox.items():
    value = dealname(value)
    prop = dealname(prop)
    if value == "" or prop == "":
      continue
    addnode("ENTITY",value)
    addrel(entry,value,"PROPERTY",prop)
fout.close()
