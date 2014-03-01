# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

from scrapy.item import Item, Field

class EncyclopediacrawlItem(Item):
    # define the fields for your item here like:
    # name = Field()
    entry = Field()       #string
    infobox = Field()     #dict
    categories = Field()  #list
    pass
