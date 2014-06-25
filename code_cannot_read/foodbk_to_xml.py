#-*- coding:utf-8 -*-
#这份代码依赖于foodbk爬虫存入数据库的东西
#目的是构建层次词典的xml文件，并把那个数据库的东西导进来
from lxml import etree as ET
import MySQLdb
def add_one_node(parent,node):
  n = ET.SubElement(parent,"category")
  n.attrib["name"] = node
  return n
def add_sons(parent,sons):
  return [add_one_node(parent,son) for son in sons]
def gettype(url):
  if "Category" in url:
    return "category"
  else:
    return "entity"
root = ET.Element('dict')
tmp = [u'通用实体',u'食品安全实体']
son_of_root = add_sons(root,tmp)
#tmp = ['anatomy','automobile','facility','health_condition','holiday','job_title','movie','music_group','natural_disaster','operating_system','print_media','sport','technology','television_show','television_station','location']
tmp = [u'器官',u'交通工具',u'设施',u'健康',u'假期',u'工作',u'电影',u'乐队',u'自然灾害',u'操作系统',u'报纸',u'运动',u'技术',u'电视节目',u'电视台',u'地理位置']
son_of_common = add_sons(son_of_root[0],tmp)

conn = MySQLdb.Connect(host='localhost',user='root',passwd='root',db='foodbk',charset='utf8')
cursor = conn.cursor()
food_categories = [u'专家',u'食品',u'添加剂',u'化学试剂',u'仪器设备',u'企业',u'政府机构',u'科研院所',u'专业词汇']
'''
proprietary = son_of_root[1]
for cate in food_categories:
  p = ET.SubElement(proprietary,"category")
  p.attrib['name'] = cate
  sql = "SELECT * FROM relation WHERE upname='%s'" % cate
  cursor.execute(sql)
  for record in cursor.fetchall():
    p.attrib['url'] = record[2]
    s = ET.SubElement(p,gettype(record[4]))
    s.attrib['name'] = record[3]
    s.attrib['url'] = record[4]
    if gettype(record[4]) == "category":
      add(s,s.attrib['name'])
'''

def add(parent,nodename,nodeurl):
  node = ET.SubElement(parent,gettype(nodeurl))
  node.attrib['name'] = nodename
  node.attrib['url'] = nodeurl
  if gettype(nodeurl) == 'category':
    sql = "SELECT * FROM relation WHERE upname='%s'" % nodename
    cursor.execute(sql)
    for record in cursor.fetchall():
      add(node,record[3],record[4])

proprietary = son_of_root[1]
for cate in food_categories:
  sql = "SELECT upurl FROM relation WHERE upname='%s'" % cate
  cursor.execute(sql)
  url = cursor.fetchone()[0]
  add(proprietary,cate,url)

print ET.tostring(root, pretty_print=True, xml_declaration=True, encoding='utf-8')
