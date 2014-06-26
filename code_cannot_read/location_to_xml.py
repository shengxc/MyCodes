#-*-coding:utf8-*-
from lxml import etree as ET
import MySQLdb
conn = MySQLdb.Connect(host='10.214.29.244',user='project973',passwd='008059c20c2ec4bca8e18ce5c9e2bea0',db='project973_20130529',charset='utf8')
cursor = conn.cursor()
root = ET.parse("level_dict.xml")
xpath = "//category[@name='地理位置']".decode("utf-8")
node = root.xpath(xpath)[0]
sql = "SELECT id,name,longitude,latitude,code,kind FROM locations WHERE kind=1"

def add(parent,son):
  loc = ET.SubElement(parent,"location")
  loc.attrib["name"] = son[1]
  loc.attrib["longitude"] = str(son[2])
  loc.attrib["latitude"] = str(son[3])
  loc.attrib["code"] = son[4]
  new_sql = "SELECT id,name,longitude,latitude,code,kind FROM locations WHERE parent_location_id=%d" % son[0]
  cursor.execute(new_sql)
  records = cursor.fetchall()
  for r in records:
    add(loc,r)

locroot = ET.SubElement(node,"country")
locroot.attrib["name"] = u"中国"
cursor.execute(sql)
records = cursor.fetchall()
for record in records:
  add(locroot,record)

print ET.tostring(root, pretty_print=True, xml_declaration=True, encoding='utf-8')
