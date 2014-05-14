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
import sys
from neo4jrestclient.client import GraphDatabase
gdb = GraphDatabase("http://10.21.31.91:7474/db/data/")
fout = open("run.log","w")
dealf = open("deal.log","w")

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
  def isexistnode(nodetype,nodename):
    testexistquery = '''match (n:%s {name:"%s"}) return count(n)''' % (nodetype,nodename)
    res = execute(testexistquery)
    return res[0][0] > 0
  assert(nodetype == 'ENTITY' or nodetype == 'CATEGORY')
  if not isexistnode(nodetype,nodename):
    addnodequery = '''create (n:%s {name:"%s"})''' % (nodetype,nodename)
    execute(addnodequery)

def addrel(nodename1,nodename2,reltype,relname=None):
  def isexistrel(nodename1,nodename2,reltype,relname=None):
    if reltype == 'PROPERTY':
      testrelquery = '''match (ent:ENTITY {name:"%s"})-[rel:%s {name:"%s"}]->(att:ENTITY {name:"%s"}) return count(rel) ''' % (nodename1,reltype,relname,nodename2)
    else:
      testrelquery = '''match (ent:ENTITY {name:"%s"})-[rel:%s]->(att:ENTITY {name:"%s"}) return count(rel) ''' % (nodename1,reltype,nodename2)
    res = execute(testrelquery)
    return res[0][0] > 0
  assert(reltype == 'PROPERTY' or reltype == 'CATEGORY')
  if not isexistrel(nodename1,nodename2,reltype,relname):
    if reltype == 'PROPERTY':
      addrelquery = '''match (ent:ENTITY {name:"%s"}),(att:ENTITY {name:"%s"}) create ent-[:%s {name:"%s"}]->att''' % (nodename1,nodename2,reltype,relname)
    else:
      addrelquery = '''match (ent:ENTITY {name:"%s"}),(cate:CATEGORY {name:"%s"}) create ent-[:%s]->cate''' % (nodename1,nodename2,reltype)
    execute(addrelquery)

#hudongfilename = "/media/sxc/Seagate Backup Plus Drive/EncyclopediaData/hudongbaikeknowledgesmerge.json"
hudongfilename = sys.argv[1]
with open(hudongfilename) as inputfile:
  items = json.load(inputfile)
index = 0
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
  dealf.write((str(index) + "\n").encode("utf-8"))
  dealf.flush()
  index = index + 1
fout.close()
dealf.close()
