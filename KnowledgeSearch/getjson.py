#-*-encoding:utf-8-*-
import jieba
import json
from neo4jrestclient.client import GraphDatabase
#gdb = GraphDatabase("http://10.21.31.91:7474/db/data/")
class RelationParser:
  def __init__(self):
    self.ENTITYNODE = 1
    self.CATEGORYNODE = 2
    self.PROPERTYLINK = 1
    self.CATEGORYLINK = 2
    self.gdb = GraphDatabase("http://localhost:7474/db/data/")
    self.graph = {}
    self.graph["nodes"] = []
    self.graph["links"] = []

def execute(self,q):
  return self.gdb.query(q)

def getwords(self,text):
  return jieba.cur_for_search(text)

def getnodeids(self,nodename):
  nodeids = []
  q = '''match (n:ENTITY {name:'%s'}) return n''' % nodename
  res = self.execute(q)
  if len(res) != 0:
    nodeids.append((res[0][0]['self'].split("/")[-1],self.ENTITYNODE))
  q = '''match (n:CATEGORY {name:'%s'}) return n''' % nodename
  res = self.execute(q)
  if len(res) != 0:
    nodeids.append((res[0][0]['self'].split("/")[-1],self.CATEGORYNODE))
  return nodeids

def getnodeurls(self,nodename):
  nodeurls = []
  q = '''match (n:ENTITY {name:'%s'}) return n''' % nodename
  res = self.execute(q)
  if len(res) != 0:
    nodeurls.append(res[0][0]['self']
  q = '''match (n:CATEGORY {name:'%s'}) return n''' % nodename
  res = self.execute(q)
  if len(res) != 0:
    nodeurls.append(res[0][0]['self']

def parsetext(self,text):
  words = getwords(text)
  for word in words:
    nodeurls = self.getnodeurls(word)
    for nodeurl in nodeurls:
      startnode = self.gdb.nodes.get(nodeurl)
      
"""
def parserel(self,word1,word2):
  startnodeids = self.getnodeids(word1)
  endnodeids = self.getnodeids(word2)
  for nodeid in nodeids:
    q = '''start n=node(%s) match (n)-[r]-(m {name:'%s'}) return n.name,r.name''' % (nodeid,word2)
    res = execute(q)


def parsenode(self,word):
  nodeids = self.getnodeids(word)
  for nodeidtuple in nodeids:
    q = '''start n=node(%s) match (n)-[r]-(m) return n.name,r.name,m.name''' % nodeidtuple[0]
    res = execute(q)
    if len(res) != 0:
      node = {}
      node["name"] = word
      node["type"] = nodeidtuple[1]
      self.graph["nodes"].append(node)
      index1 = len(self.graph["nodes"]) - 1
      for row in res:
        link = {}
"""


