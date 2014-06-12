#-*-coding:utf8-*-
# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html
import urllib
import MySQLdb

def getname(url):
  item = url.split("/")[-1].split(":")[-1]
  return urllib.unquote(item.encode("utf-8")).decode("utf-8")

class FoodbkPipeline(object):
  def open_spider(self,spider):
    self.conn=MySQLdb.connect(host="localhost",user="root",passwd="root",db="foodbk",charset="utf8")
    self.cursor = self.conn.cursor()
  def process_item(self, item, spider):
    sql = u"INSERT INTO `foodbk`.`relation`(`id`,`upname`,`upurl`,`downname`,`downurl`)VALUES(NULL,'%s','%s','%s','%s');"%(getname(item["up"]),item["up"],getname(item["down"]),item["down"])
    self.cursor.execute(sql)
    self.conn.commit()
    return item
  def close_spider(self,spider):
    self.cursor.close()
    self.conn.close()
