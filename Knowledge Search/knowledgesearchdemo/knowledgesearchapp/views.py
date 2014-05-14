#-*-encoding:utf-8-*-
import json
from django.shortcuts import render_to_response
from django.http import HttpResponse, Http404
from dajaxice.decorators import dajaxice_register
from dajax.core import Dajax
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
      if l._label == 'ENTITY' or l._label == 'wikiEntity':
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
    else:
      q = '''match (n:wikiEntity) where n.name='%s' return n''' % word
      res = self.execute(q)
      if len(res) != 0:
        nodeurls.append(res[0][0]['self'])

    q = '''match (n:CATEGORY) where n.name='%s' return n''' % word
    res = self.execute(q)
    if len(res) != 0:
      nodeurls.append(res[0][0]['self'])

    return nodeurls

  def parse(self,word,reltype = None,limit = True):
    limitoutgoingcount = 20
    limitincomingcount = 20
    for nodeurl in self.getnodeurls(word):
      node = self.gdb.nodes.get(nodeurl)
      index1 = self.push_node(node)
      if reltype != u"搜索输入":
        incomingcount = 0
        for rel in node.relationships.outgoing():
          index2 = self.push_node(rel.end)
          if rel.type == 'CATEGORY':
            self.push_link(index1,index2,u"类别")
          else:
            self.push_link(index1,index2,rel.get("name"))

          incomingcount += 1
          if limit and incomingcount >= limitincomingcount:
            break


      if reltype != u"搜索输出":
        outgoingcount = 0
        for rel in node.relationships.incoming():
          index2 = self.push_node(rel.start)
          if rel.type == 'CATEGORY':
            self.push_link(index2,index1,u"类别")
          else:
            self.push_link(index2,index1,rel.get("name"))

          outgoingcount += 1
          if limit and outgoingcount >= limitoutgoingcount:
            break
    return self.graph

def demo(request):
    return render_to_response('html/demo.html', locals())

@dajaxice_register(method='POST')
def deal(request, content,type):
    dajax = Dajax()
    jp = JsonProducer("http://10.21.31.91:7474/db/data/")
    graph = jp.parse(content,type)
    s = json.dumps(graph,ensure_ascii=False)
    dajax.add_data(s,'graphready')
    return dajax.json()
