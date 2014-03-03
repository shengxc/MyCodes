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
from neo4jrestclient.client import GraphDatabase
gdb = GraphDatabase("http://localhost:7474/db/data/")
jsonfiledir = "/media/sxc/Seagate Backup Plus Drive/EncyclopediaData/hudongbaikeknowledges"


def dealforquery(string):
  return string.replace('"','\\"').replace("'","\\'")

def dealtagstartwithnumbers(string):
  numbers = ['0','1','2','3','4','5','6','7','8','9']
  try:
    if string[0] in numbers:
      string = "num" + string
  except Exception,e:
    print e
    print "string=",string
  return string

def pretreatinfobox(infobox):
  res = {}
  for k,v in infobox.items():
    k = k.strip()
    if k[-1] == u"：":
      k = k[0:-1]
    k = dealtagstartwithnumbers(dealforquery(k))
    v = dealforquery(v.strip())
    res[k] = v
  return res

def pretreatcategories(categories):
  res = []
  for c in categories:
    res.append(dealtagstartwithnumbers(dealforquery(c.strip())))
  return res

def execute(query):
    try:
      return gdb.query(query)
    except Exception,e:
      print "wrong:\t",query
      pass

def isexist(name):
    testexistquery = "match (n {name:'%s'}) return count(n)" % name
    return execute(testexistquery)[0][0] > 0

for root,dirs,filenames in os.walk(jsonfiledir):
  for filename in filenames:
    if filename.split(".")[-1] != "json":
      continue
    with open(os.path.join(root,filename)) as inputfile:
      item = json.load(inputfile)
    infobox = pretreatinfobox(item["infobox"])            #dict
    entry = dealforquery(item["entry"].strip())           #unicode
    categories = pretreatcategories(item["categories"])   #list


    if not isexist(entry):
      addnodequery = None
      if len(categories) > 0:
        addnodequery = '''create (n :%s {name:"%s"})''' % (":".join(categories),entry)
      else:
        addnodequery = '''create (n {name:"%s"})''' % (entry)
      execute(addnodequery)
    else:
      editnodequery = None
      if len(categories) > 0:
        editnodequery = '''match (n {name:"%s"}) set n:%s''' % (entry,":".join(categories))
      execute(editnodequery)

    for k,v in infobox.items():
      if not isexist(v):
        addnodequery = '''create (n {name:"%s"})''' % (v)
        execute(addnodequery)
      addrelquery = '''match (ent {name:"%s"}),(att {name:"%s"}) create ent-[:%s]->att''' % (entry,v,k)
      execute(addrelquery)
