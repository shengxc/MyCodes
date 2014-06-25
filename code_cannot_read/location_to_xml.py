#-*-coding:utf8-*-
from lxml import etree as ET
import MySQLdb
conn = MySQLdb.Connect(host='10.214.29.244',user='project973',passwd='008059c20c2ec4bca8e18ce5c9e2bea0',db='project973_20130529',charset='utf8')
cursor = conn.cursor()
xml = ET.parse("level_dict.xml")
