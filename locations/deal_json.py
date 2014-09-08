#-*- encoding:utf8 -*-
from xml.etree import ElementTree as ET
import json
import urllib2
import string
def load_loc_dict(filename):
	res = {}
	for line in open(filename):
		if line.strip() == "":
			continue
		tuple = line.split("\t")
		name = tuple[0].decode("utf8")
		last_loc_name = name
		longitude = string.atof(tuple[1].decode("utf8"))
		latitude = string.atof(tuple[2].decode("utf8"))
		res[name] = {}
		res[name]["longitude"] = longitude
		res[name]["latitude"] = latitude
	return res
	

def get_loc(name):
	res = {}
	if name in loc_dict:
		res = loc_dict[name]
	else:
		return res
		query = "http://maps.googleapis.com/maps/api/geocode/json?address=%s&sensor=true" % name
		response = json.load(urllib2.urlopen(query.encode("utf8")))
		if response["status"] == "OK":
			loc = response["results"][0]["geometry"]["location"]
			res["longitude"] = loc["lng"]
			res["latitude"] = loc["lat"]
			loc_dict[name] = res
			loc_fp.write((name + "\t" + str(res["longitude"]) + "\t" + str(res["latitude"]) + "\n").encode("utf8"))
			loc_fp.flush()
		else:
			if response["status"] == "OVER_QUERY_LIMIT":
				print "你妹的！api不让用了！！！还让不让人干活了啊！！！换台电脑试试？"
				exit()
			else:
				print json.dumps(response)
	return res

def add_lng_lat(data):
	if "full_name" in data:
		loc = get_loc(data["full_name"])
		if loc:
			data["longitude"] = loc["longitude"]
			data["latitude"] = loc["latitude"]
	if "children" in data:
		for child in data["children"]:
			add_lng_lat(child)
			
			

			
			
def write_json(filename,obj):
	s = json.dumps(obj,sort_keys=True,indent=4,ensure_ascii=False)
	with open(filename,"w") as f:
		f.write(s.encode("utf8"))
		#json.dump(obj,f,sort_keys=True,indent=4,ensure_ascii=False)

def load_lan_dict(filename):
	res = {}
	for line in open(filename):
		if line.strip() == "":
			continue
		line = line.decode("utf8")
		ch_name = line.split("\t")[0]
		en_name = line.split("\t")[1]
		res[ch_name] = en_name
	return res

def get_en(ch):
	if ch in lan_dict:
		en = lan_dict[ch]
	else:
		query = "http://openapi.baidu.com/public/2.0/bmt/translate?client_id=ZrVwcYTZpGqlmNpmtnvNbm0S&q=%s&from=zh&to=en" % ch
		res = json.load(urllib2.urlopen(query.encode("utf8")))
		en = res["trans_result"][0]["dst"]
		lan_dict[ch] = en
		lan_fp.write((ch + "\t" + en + "\n").encode("utf8"))
		lan_fp.flush()
	return en

def add_en_name(data):
	if "ch_name" in data:
		print data["ch_name"].encode("utf8")
		data["en_name"] = get_en(data["ch_name"]).strip()
	if "children" in data:
		for child in data["children"]:
			add_en_name(child)

	  
	  
	  
loc_dict_file = "loc_dict.txt"
loc_dict = load_loc_dict(loc_dict_file)
loc_fp = open(loc_dict_file,"a")

lan_dict_file = "lan_dict.txt"
lan_dict = load_lan_dict(lan_dict_file)
lan_fp = open(lan_dict_file,"a")


with open("locations.js") as f:
  data = json.load(f)
add_en_name(data)
#add_lng_lat(data)
write_json("result.js",data)
loc_fp.close()
lan_fp.close()
