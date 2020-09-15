echo создать переменную среды RSS_FEED
rem set RSS_FEED=http://rss.cnn.com/rss/edition.rss
rem set RSS_FEED=https://habr.com/ru/rss/flows/develop/all/?fl=ru
rem set RSS_FEED=http://rss.cnn.com/rss/edition.rss
rem set RSS_FEED=http://feeds.bbci.co.uk/news/business/rss.xml#
set RSS_FEED=http://feeds.skynews.com/feeds/rss/world.xml
echo запустить python скрипт
python rssgossip.py trump
rem python rssgossip.py google