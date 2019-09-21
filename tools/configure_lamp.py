import requests
import time
# https://github.com/awkman/pywifi
import pywifi
from pywifi import const

wifi = pywifi.PyWiFi()
iface = wifi.interfaces()[0]

iface.disconnect()
time.sleep(1)
assert iface.status() in \
       [const.IFACE_DISCONNECTED, const.IFACE_INACTIVE]
print('Disconnected from previous wifi network')

profile = pywifi.Profile()
profile.ssid = 'WiFi_Lamp'
profile.auth = const.AUTH_ALG_OPEN
profile.akm.append(const.AKM_TYPE_NONE)
profile.cipher = const.CIPHER_TYPE_CCMP

iface.remove_network_profile(profile)
tmp_profile = iface.add_network_profile(profile)

iface.connect(tmp_profile)
connectTimeout = 10
while iface.status() != const.IFACE_CONNECTED and connectTimeout > 0:
    time.sleep(1)
    connectTimeout -= 1

if iface.status() == const.IFACE_CONNECTED:
    isDeviceConnected = True
    print('Connected to wifi network \'' + tmp_profile.ssid + '\'')

    URL = "http://192.168.4.1/config"
    PARAMS = {
        'ssid':'zzuummaa-2GHz',
        'pass':'fom12345',
        'blynk':'4Hv5ZsJ7mqM-74asV89_Zjh3bjIZcHBm',
        'host':'zzuummaa.sytes.net',
        'port':'8081'
    }

    try:
        resp = requests.post(url = URL, params = PARAMS, timeout=5)
    except requests.exceptions.ConnectionError:
        print('Configure request timeout.')
        print('Maybe device configured.')

    iface.disconnect()
    time.sleep(1)
    assert iface.status() in \
           [const.IFACE_DISCONNECTED, const.IFACE_INACTIVE]
    print('Disconnected from wifi network \'' + tmp_profile.ssid + '\'')
else:
    print('Wifi network \'' + tmp_profile.ssid + '\' not available')
    isDeviceConnected = False

profile = pywifi.Profile()
profile.ssid = 'zzuummaa-5GHz'
profile.auth = const.AUTH_ALG_OPEN
profile.akm.append(const.AKM_TYPE_WPA2PSK)
profile.cipher = const.CIPHER_TYPE_CCMP
profile.key = 'fom12345'

tmp_profile = iface.add_network_profile(profile)

iface.connect(tmp_profile)
connectTimeout = 15
while iface.status() != const.IFACE_CONNECTED and connectTimeout > 0:
    time.sleep(1)
    connectTimeout -= 1
assert iface.status() == const.IFACE_CONNECTED
print('Connected to wifi network \'' + tmp_profile.ssid + '\'')