# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html

import MySQLdb
class CntvcrawlPipeline(object):
  conn = None
  cursor = None
  def open_spider(self,spider):
    #self.outf = open("sql.log","w")
    self.conn = MySQLdb.Connect(host="10.214.55.244",user="project973",passwd="008059c20c2ec4bca8e18ce5c9e2bea0",db="project863_20140223",charset="utf8")

    self.cursor = self.conn.cursor()

  def process_item(self, item, spider):
    sql = "INSERT INTO videos (title,video_url,img_url,published_at) VALUES ('%s','%s','%s','%s')" % (item["title"],item["videourl"],item["imgurl"],item["time"])
    #self.outf.write((sql + "\n").encode("utf-8"))
    self.cursor.execute(sql)
    self.conn.commit()
    return item

  def close_spider(self,spider):
    #self.outf.close()
    self.cursor.close()
    self.conn.close()
