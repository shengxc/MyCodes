#-*-coding:utf8-*-
from scrapy.contrib.spiders import CrawlSpider,Rule
from scrapy.spider import Spider
from scrapy.selector import Selector
from scrapy.contrib.linkextractors.sgml import SgmlLinkExtractor
from foodbk.items import FoodbkItem
import re
class foodbk_spider(Spider):
  name = "foodbk_spider"
  allowed_domains = ['foodbk.com']
  start_urls = ['http://www.foodbk.com/wiki/%E9%A6%96%E9%A1%B5']
  domain = "http://www.foodbk.com"
  template_url_pattern = re.compile(r"/wiki/Template:.+")
  visited_url = set()
  def parse(self,response):
    self.visited_url.add(response.url)
    dom = Selector(response)
    urls = dom.xpath("//a[contains(@title,'Category:')]/@href").extract()[0:9]
    urls = [self.domain + url for url in urls]
    for url in urls:
      if url not in self.visited_url:
        self.visited_url.add(url)
        yield self.make_requests_from_url(url).replace(callback=self.parse_category)
  def parse_category(self,response):
    self.visited_url.add(response.url)
    dom = Selector(response)
    subcategories = dom.xpath("//div[contains(@id,'mw-subcategories')]//a")
    for subcategory in subcategories:
      url = self.domain + subcategory.xpath("./@href").extract()[0]
      if url not in self.visited_url:
        self.visited_url.add(url)
        item = FoodbkItem()
        item["up"] = response.url.decode("utf-8")
        item["down"] = url
        yield item
        yield self.make_requests_from_url(url).replace(callback=self.parse_category)
    entities = dom.xpath("//div[contains(@id,'mw-pages')]//a")
    for e in entities:
      url = e.xpath("./@href").extract()[0]
      if self.template_url_pattern.match(url) != None:
        continue
      url = self.domain + url
      item = FoodbkItem()
      item["up"] = response.url.decode("utf-8")
      item["down"] = url
      yield item
    indexes = dom.xpath("//a[contains(text(),'200')]")
    for index in indexes:
      if index.xpath("./text()").extract()[0] == u'后200条':
        url = self.domain + index.xpath("./@href").extract()[0]
        if url not in self.visited_url:
          self.visited_url.add(url)
          yield self.make_requests_from_url(url).replace(callback=self.parse_category)
