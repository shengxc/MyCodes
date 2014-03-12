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
replacemap = {u'0':u'零',u'1':u'一',u'2':u'二',u'3':u'三',u'4':u'四',u'5':u'五',u'6':u'六',u'7':u'七',u'8':u'八',u'9':u'九',u'"':u'',u'（':u'',u'）':u'',u'“':u'',u'”':u''}
def makedictrepl(inputdict):
  rx = re.compile('|'.join(inputdict))
  def eachrepl(match):
    return inputdict[match.group(0)]
  def repl(text):
    return rx.sub(eachrepl,text)
  return repl
typereplacefunc = makedictrepl(replacemap)

def dealnodename(nodename):
  nodename = nodename.strip()
  return nodename.replace("\\",",").replace('"','\\"')


def dealtype(elemtype):
  elemtype = elemtype.strip()
  elemtype.replace(".","")    #delete . character in type
  return typereplacefunc(elemtype)

def execute(query):
  try:
    return gdb.query(query)
  except Exception,e:
    print "wrong:\t",query
    pass

def addnode(name,categories = []):
  def isexist(name):
    testexistquery = '''match (n {name:"%s"}) return count(n)''' % name
    res = execute(testexistquery)
    return res[0][0] > 0
  if not isexist(name):
    if len(categories) > 0:
      addnodequery = '''create (n :%s {name:"%s"})''' % (":".join(categories),name)
    else:
      addnodequery = '''create (n {name:"%s"})''' % (name)
    execute(addnodequery)
  else:
    if len(categories) > 0:
      editnodequery = '''match (n {name:"%s"}) set n:%s''' % (name,":".join(categories))
      execute(editnodequery)

def addrel(nodename1,nodename2,relname):
  addnode(nodename1)
  addnode(nodename2)
  addrelquery = '''match (ent {name:"%s"}),(att {name:"%s"}) create ent-[:%s]->att''' % (nodename1,nodename2,relname)
  execute(addrelquery)

hudongfilename = "/media/sxc/Seagate Backup Plus Drive/EncyclopediaData/hudongbaikeknowledgesmerge.json"
with open(hudongfilename) as inputfile:
  items = json.load(inputfile)
for item in items:
  infobox = item["infobox"]           #dict
  entry = item["entry"].strip()       #unicode
  categories = item["categories"]     #list
  addnode(dealnodename(entry),map(dealtype,categories))
  for k,v in infobox.items():
    k = k.strip()
    v = v.strip()
    if k[-1] == u"：":
      k = k[0:-1]
    addrel(dealnodename(entry),dealnodename(v),dealtype(k))
