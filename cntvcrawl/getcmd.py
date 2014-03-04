# -*- coding:utf-8 -*-
for line in open("topicandkeywords.txt").read().split("\n"):
  topictitle = line.split(":")[0]
  for keyword in line.split(":")[1].split("|"):
    print "scrapy crawl cntvspider -a keyword=%s -a topictitle=%s" % (keyword,topictitle)
