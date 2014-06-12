# Scrapy settings for foodbk project
#
# For simplicity, this file contains only the most important settings by
# default. All the other settings are documented here:
#
#     http://doc.scrapy.org/en/latest/topics/settings.html
#

BOT_NAME = 'foodbk'

SPIDER_MODULES = ['foodbk.spiders']
NEWSPIDER_MODULE = 'foodbk.spiders'

# Crawl responsibly by identifying yourself (and your website) on the user-agent
#USER_AGENT = 'foodbk (+http://www.yourdomain.com)'
ITEM_PIPELINES = {
    'foodbk.pipelines.FoodbkPipeline' : 300
    }
