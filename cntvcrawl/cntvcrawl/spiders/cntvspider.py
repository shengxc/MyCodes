# -*- coding: utf-8 -*-
from scrapy.contrib.spiders import CrawlSpider,Rule
from scrapy.spider import BaseSpider
from scrapy.selector import Selector
from cntvcrawl.items import CntvcrawlItem
from scrapy.http import Request
import urllib
import json
import re

def addurlhead(url):
  return "http://search.cctv.com/" + url

def adddomainandclearvideourl(domain,url):
  phpurl = url.split("?")[0]
  for args in url.split("?")[1].split("&"):
    k = args.split("=")[0]
    if k == "detailsid":
      detailsid = args.split("=")[1]
  return addurlhead(phpurl + "?detailsid=" + detailsid)

class cntvSpider(BaseSpider):
  name = "cntvspider"
  allowed_domains = ["cctv.com"]
  start_urls = []
  keyword = ""
  topictitle = ""
  def __init__(self,keyword = None,topictitle = None):
    print keyword
    print topictitle
    assert keyword != None
    assert topictitle != None
    self.keyword = unicode(keyword,"utf-8")
    self.topictitle = unicode(topictitle,"utf-8")
    super(cntvSpider,self).__init__()
    self.start_urls.append("http://search.cctv.com/search.php?qtext=%s&type=video" % (keyword,))

  def parse(self,response):
    nextpagerequest = []
    pagehxs = Selector(response)
    videos = pagehxs.xpath('//div[@class="seah_main bor_t"]//li')[2:]
    for video in videos:
      item = CntvcrawlItem()
      title = video.xpath('./a[@class="p_txt"]/text()').extract()
      item["title"] = self.keyword.join(title)
      videourl = video.xpath('./a[@class="p_txt"]/@href').extract()[0]
      if response.url[0:7] == 'http://':
        domain = response.url[7:]
      item["topictitle"] = self.topictitle
      item["videourl"] = adddomainandclearvideourl(domain.split("/")[0],videourl)
      item["imgurl"] = video.xpath('.//img/@src').extract()[0]
      item["time"] = video.xpath('./p[@class="p_date"]/text()').extract()[0]
      yield(item)
    #print "********************yield getitem ",len(itemlist)

    #print "********************parse nextpage"
    nextpage = pagehxs.xpath('//a[@class="btn_page"]')
    if len(nextpage) != 0 and nextpage.xpath('./span/text()').extract()[-1] == u"下一页>>":
      nextpageurl = addurlhead(nextpage.xpath("./@href").extract()[-1])
      #print "***********************yield next page"
      yield Request(nextpageurl,callback = self.parse)
