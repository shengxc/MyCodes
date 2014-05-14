from django.conf.urls import patterns, include, url

from django.contrib import admin
from dajaxice.core import dajaxice_autodiscover, dajaxice_config
from knowledgesearchapp.views import demo
admin.autodiscover()
dajaxice_autodiscover()

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'knowledgesearchdemo.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),

    #url(r'^admin/', include(admin.site.urls)),
    url(dajaxice_config.dajaxice_url, include('dajaxice.urls')),
    url(r'^demo/$', demo),
)
