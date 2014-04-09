#-*-encoding:utf-8-*-
import json
import sys
from neo4jrestclient.client import GraphDatabase

class JsonProducer:

  def __init__(self,url):
    self.gdb = GraphDatabase(url)
    self.graph = {}
    self.graph["nodes"] = []
    self.graph["links"] = []
    self.ENTITY = 1
    self.CATEGORY = 2

  def execute(self,q):
    return self.gdb.query(q)

  def getlabel(self,node):
    label = None
    for l in node.labels:
      if l._label == 'ENTITY':
        label = self.ENTITY
      else:
        label = self.CATEGORY
    return label

  def push_node(self,node):
    visualnode = {}
    visualnode["name"] = node.get("name")
    visualnode["type"] = self.getlabel(node)
    self.graph["nodes"].append(visualnode)
    return len(self.graph["nodes"]) - 1

  def push_link(self,start,end,name):
    link = {}
    link["source"] = start
    link["target"] = end
    link["name"] = name
    self.graph["links"].append(link)

  def getnodeurls(self,word):
    nodeurls = []
    q = '''match (n:ENTITY) where n.name='%s' return n''' % word
    res = self.execute(q)
    if len(res) != 0:
      nodeurls.append(res[0][0]['self'])
    """
    q = '''match (n:CATEGORY) where n.name='%s' return n''' % word
    res = self.execute(q)
    if len(res) != 0:
      nodeurls.append(res[0][0]['self'])
    """
    return nodeurls

  def parse(self,word,reltype = None):
    for nodeurl in self.getnodeurls(word):
      node = self.gdb.nodes.get(nodeurl)
      print node
      index1 = self.push_node(node)

      if reltype != "incoming":
        for rel in node.relationships.outgoing():
          print rel
          index2 = self.push_node(rel.end)
          if rel.type == 'CATEGORY':
            self.push_link(index1,index2,u"类别")
          else:
            self.push_link(index1,index2,rel.get("name"))

      if reltype != "outgoing":
        for rel in node.relationships.incoming():
          print rel
          index2 = self.push_node(rel.start)
          if rel.type == 'CATEGORY':
            self.push_link(index2,index1,u"类别")
          else:
            self.push_link(index2,index1,rel.get("name"))
    return self.graph

jp = JsonProducer("http://localhost:7474/db/data/")
graph = jp.parse(sys.argv[1],sys.argv[2])
s = json.dumps(graph,ensure_ascii=False)
with open("temp.json","w") as f:
  f.write(s.encode("utf-8"))
