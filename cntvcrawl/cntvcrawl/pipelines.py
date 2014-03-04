# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html

import MySQLdb
import string
from scrapy.exceptions import DropItem
def gettopiccategoryid(time):
  date = time.split(" ")[0]
  year = string.atoi(date.split("-")[0])
  month = string.atoi(date.split("-")[1])
  return str((year - 2013) * 12 + month)

class CntvcrawlPipeline(object):
  conn = None
  cursor = None
  def open_spider(self,spider):
    #self.outf = open("sql.log","w")
    self.conn = MySQLdb.Connect(host="10.214.55.244",user="project973",passwd="008059c20c2ec4bca8e18ce5c9e2bea0",db="project863_20140223",charset="utf8")
    self.cursor = self.conn.cursor()


  def process_item(self, item, spider):
    sql = "SELECT id FROM topics WHERE title='%s' AND category_id=%s" % (item["topictitle"],gettopiccategoryid(item["time"]))
    if self.cursor.execute(sql) == 0:
      raise DropItem("There is no corresponding topics in database")
    topic_id = self.cursor.fetchone()[0]
    sql = "INSERT INTO new_videos (title,video_url,img_url,published_at,topic_id) VALUES ('%s','%s','%s','%s',%s)" % (item["title"],item["videourl"],item["imgurl"],item["time"],str(topic_id))
    #self.outf.write((sql + "\n").encode("utf-8"))
    self.cursor.execute(sql)
    self.conn.commit()
    return item

  def close_spider(self,spider):
    #self.outf.close()
    self.cursor.close()
    self.conn.close()
