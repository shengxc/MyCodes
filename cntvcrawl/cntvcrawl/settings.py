# Scrapy settings for cntvcrawl project
#
# For simplicity, this file contains only the most important settings by
# default. All the other settings are documented here:
#
#     http://doc.scrapy.org/en/latest/topics/settings.html
#

BOT_NAME = 'cntvcrawl'

SPIDER_MODULES = ['cntvcrawl.spiders']
NEWSPIDER_MODULE = 'cntvcrawl.spiders'
ITEM_PIPELINES = {
    'cntvcrawl.pipelines.CntvcrawlPipeline':1
    }
# Crawl responsibly by identifying yourself (and your website) on the user-agent
#USER_AGENT = 'cntvcrawl (+http://www.yourdomain.com)'
