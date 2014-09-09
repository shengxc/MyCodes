#encoding:utf8
import MySQLdb
import json

conn = MySQLdb.connect(host='10.21.31.106',user='xli',passwd='123456',db='project973v2_20140702',charset="utf8")
cursor = conn.cursor()
kind_map = {"CountryRegion":1,"State":2,"City":3,"Region":4}

def real_insert(sql):
  print sql
  cursor.execute(sql.encode("utf8"))
  #cursor.execute("select * from locations".encode("utf8"))
  cursor.execute("select @@IDENTITY".encode("utf8"))
  id = cursor.fetchone()[0]
  conn.commit()
  return id

def insert_to_mysql(parentid,node):
  id = parentid
  if "ch_name"in node:
    name = node["ch_name"]
    if "longitude" not in node:
      longitude = -1
    else:
      longitude = node["longitude"]
    if "latitude" not in node:
      latitude = -1
    else:
      latitude = node["latitude"]
    kind = kind_map[node["type"]]
    sql = "INSERT INTO locations(name,longitude,latitude,parent_location_id,kind) VALUES('%s',%f,%f,%d,%d)" % (name,longitude,latitude,parentid,kind)
    id = real_insert(sql)
  if "children" in node:
    for n in node["children"]:
      insert_to_mysql(id,n)

with open("result.js") as f:
  locations = json.load(f)
for n in locations["children"]:
  insert_to_mysql(0,n)

cursor.close()
conn.close()
