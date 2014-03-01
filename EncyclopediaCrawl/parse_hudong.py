'''
@auther: sxc
@date: 2014/02/27
@function:
parse craweled hudong encyclopedia pages and get their categories,
infoboxes to json files,the wiki pages fold and output json files fold
are written in the conf file with the same name and this file
'''
from scrapy.selector import HtmlXPathSelector
from EncyclopediaCrawl.items import EncyclopediacrawlItem
import json
import re
import os

def getentryname(entryhxs):
  return entryhxs.select('//h1/text()').extract()[0]

def clearhtmltags(str):
  s = re.sub("<.*?>","",str)
  return s.strip()

def getinfobox(entryhxs):
  knowledge = {}
  infoboxhxs = entryhxs.select('//div[@class="module zoom"]//table')
  if(len(infoboxhxs) != 0):
    infoboxhxs = infoboxhxs[0]
    for tdhxs in infoboxhxs.select('.//td[not(@class)]'):
      key = tdhxs.select('./strong/text()').extract()[0]
      #value need special deal,for some urls
      value = tdhxs.select('./span').extract()[0]
      value = clearhtmltags(value)
      knowledge[key] = value
  return knowledge

def getcategories(entryhxs):
  return entryhxs.select('//p[@id="openCatp"]//a/text()').extract()


with open("parse_hudong.conf") as conffile:
  for line in conffile.read().split("\n"):
    line = line.strip()
    if line == "":
      continue
    if line[0] != "#" and line.split(":")[0].strip() == "inputfiledir":
      inputfiledir = line.split(":")[1].strip()
    if line[0] != "#" and line.split(":")[0].strip() == "outputfiledir":
      outputfiledir = line.split(":")[1].strip()

print "inputfiledir:\t",inputfiledir
print "outputfiledir:\t",outputfiledir
if not os.path.exists(outputfiledir):
  os.mkdir(outputfiledir)
for root,dirs,files in os.walk(inputfiledir):
  for f in files:
    item = dict()
    inputfilename = os.path.join(root,f)
    with open(inputfilename,"r") as inputfile:
      cont = inputfile.read()
      hxs = HtmlXPathSelector(text = cont)
      item["entry"] = getentryname(hxs)
      item["infobox"] = getinfobox(hxs)
      item["categories"] = getcategories(hxs)
      item["source"] = "hudongbaike"
    with open(os.path.join(outputfiledir,f.split(".")[0] + ".json"),"w") as outputfile:
      outputfile.write(json.dumps(item,ensure_ascii=False).encode("utf-8"))
