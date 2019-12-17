from urllib.request import urlopen, urlretrieve
import requests

url = 'https://yandex.ru/metro/moscow?from=100&to=101&route=0'

r = requests.get(url)
print(r.content)


