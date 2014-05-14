from scrapy.contrib.spiders import CrawlSpider,Rule
from scrapy.selector import HtmlXPathSelector
from EncyclopediaCrawl.items import EncyclopediacrawlItem
from scrapy.http import Request
import urllib
import json
import re

class hudongSpider(CrawlSpider):
  name = "hudongspider"
  categoryurlpattern = "(http://)?fenlei.baike.com/.+/"
  wikientryurlpattern = "(http://)?www.baike.com/wiki/.+"
  #wikipagefold = "/media/sxc/Seagate Backup Plus Drive/hudongwiki/"
  wikipagefold = "/home/sxc/hudongwiki/"
  hassavedwikientries = set()
  allowed_domains = ["baike.com"]
  start_urls = ["http://fenlei.baike.com/"]

  def parse_start_url(self,response):
    pagehxs = HtmlXPathSelector(response)
    links = pagehxs.select('//div[@id="f-a"]//a/@href').extract()
    categoryrequests = []
    pattern = re.compile(self.categoryurlpattern)
    for link in links:
      if pattern.match(link) != None:
        categoryrequests.append(Request((link+"list"),callback = self.parse_category_url))
    return categoryrequests

  def parse_category_url(self,response):
    categoryhxs = HtmlXPathSelector(response)
    links = categoryhxs.select('//div[@id="all-sort"]//a/@href').extract()
    pattern = re.compile(self.wikientryurlpattern)
    wikientryrequests = []
    for link in links:
      if pattern.match(link) != None:
        wikientryrequests.append(Request(link,callback = self.parse_wikientry_url))
    return wikientryrequests

  def parse_wikientry_url(self,response):
    entryhxs = HtmlXPathSelector(response)
    self.savepage(entryhxs)
    '''
    item = EncyclopediacrawlItem()
    if self.savepage(entryhxs) == True:
      item["entry"] = self.getentryname(entryhxs)
      item["infobox"] = self.getinfobox(entryhxs)
      item["categories"] = self.getcategories(entryhxs)
    with open("hudongentriesknowledge/" + item["entry"] + ".json","w") as f:
      f.write(json.dumps(dict(item),ensure_ascii=False).encode("utf-8"))
    return item
    '''

  def savepage(self,entryhxs):
    entryname = self.getentryname(entryhxs)
    if entryname not in self.hassavedwikientries:
      self.hassavedwikientries.add(entryname)
      with open(self.wikipagefold + self.getentryname(entryhxs) + ".html","w") as f:
        f.write(entryhxs.extract().encode("utf-8"))
      return True
    else:
      return False

  def getentryname(self,entryhxs):
    return entryhxs.select('//h1/text()').extract()[0]

'''
  def getinfobox(self,entryhxs):
    knowledge = {}
    infoboxhxs = entryhxs.select('//div[@class="module zoom"]//table')
    if(len(infoboxhxs) != 0):
      infoboxhxs = infoboxhxs[0]
      for tdhxs in infoboxhxs.select('.//td[not(@class)]'):
        key = tdhxs.select('./strong/text()').extract()[0]
        #value need special deal,for some urls
        value = tdhxs.select('./span/text()').extract()
        if "".join(value).strip() == "":
          value = tdhxs.select('./span//a/text()').extract()
        value = "".join(value)
        knowledge[key] = value
    return knowledge

  def getcategories(self,entryhxs):
    return entryhxs.select('//p[@id="openCatp"]//a/text()').extract()
    '''
