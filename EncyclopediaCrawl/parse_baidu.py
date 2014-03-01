'''
@auther: sxc
@date: 2014/02/27
@function:
parse craweled baidu encyclopedia pages and get their categories,
infoboxes to json files,the wiki pages fold and output json files fold
are written in the conf file with the same name and this file
'''
from scrapy.selector import HtmlXPathSelector
import json
import os
import re

def getentryname(hxs):
	entryname = hxs.select('//h1[@class="title"]/text()').extract()
	if len(entryname) == 0:
		return None
	else:
		return entryname[0]

def clearhtmltags(str):
	s = re.sub("<.*?>","",str)
	return s.strip()

def getinfobox(hxs):
	knowledge = dict()
	keys = hxs.select('//td[@class="cardFirstTd"]')
	values = hxs.select('//td[@class="cardSecondTd"]')
	for i in range(len(keys)):
		key = keys.select('./text()').extract()[i]
		value = clearhtmltags(values.extract()[i])
		knowledge[key] = value
	keys = hxs.select('//div[@class="technology-def"]//dt')
	values = hxs.select('//div[@class="technology-def"]//dd')
	for i in range(len(keys)):
		key = keys.select('./text()').extract()[i]
		value = clearhtmltags(values.extract()[i])
		knowledge[key] = value
	return knowledge

def getcategories(hxs):
	return hxs.select('//dl[@id="viewExtCati"]//a/text()').extract()


with open("parse_baidu.conf") as conffile:
  for line in conffile.read().split("\n"):
    line = line.strip()
    if line == "":
      continue
    if line[0] != "#" and line.split(":")[0].strip() == "inputfiledir":
      inputfiledir = line.split(":")[1].strip()
    if line[0] != "#" and line.split(":")[0].strip() == "outputfiledir":
      outputfiledir = line.split(":")[1].strip()

errfile = open("err.log","w")
if not os.path.exists(outputfiledir):
  os.mkdir(outputfiledir)
for root,dirs,files in os.walk(inputfiledir):
  if root != inputfiledir:
    suboutputdirname = os.path.join(outputfiledir,root.split("/")[-1])
    os.mkdir(suboutputdirname)
    for f in files:
			item = dict()
			inputfilename = os.path.join(root,f)
			with open(inputfilename,"r") as inputfile:
				try:
					cont = inputfile.read().decode("gbk")
				except Exception,e:
					errfile.write(os.path.join(root,f) + ": read error\n")
					errfile.flush()
					continue
				hxs = HtmlXPathSelector(text=cont)
				if len(hxs.select('//div[@class="b-ent-toc-title slv-bdr"]')) != 0:
					errfile.write(os.path.join(root,f) + ": it is a polysemy\n")
					errfile.flush()
					continue
				entryname = getentryname(hxs)
				if entryname != None:
					item["entry"] = getentryname(hxs)
					item["infobox"] = getinfobox(hxs)
					item["categories"] = getcategories(hxs)
          item["source"] = "baidubaike"
					with open(os.path.join(suboutputdirname,f.split(".")[0] + ".json"),"w") as outputfile:
						outputfile.write(json.dumps(item,ensure_ascii=False).encode("utf-8"))
errfile.close()
