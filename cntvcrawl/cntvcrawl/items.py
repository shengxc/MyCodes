# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

from scrapy.item import Item, Field

class CntvcrawlItem(Item):
    # define the fields for your item here like:
    # name = Field()
    topictitle = Field()
    title = Field()
    videourl = Field()
    imgurl = Field()
    time = Field()
    pass
